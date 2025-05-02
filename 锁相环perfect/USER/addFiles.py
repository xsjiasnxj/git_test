import os
import glob
import xml.etree.ElementTree as ET
import argparse
import shutil

def indent(elem, level=0):
    """ Helper function to indent the XML for pretty printing. """
    i = "\n" + level * "    "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "    "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level + 1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i
        if not elem.tail:
            elem.tail = "\n"

def find_c_h_files(folder_path):
    """查找文件夹中的所有.c和.h文件，返回文件信息列表"""
    file_info = []
    
    if not os.path.exists(folder_path):
        print(f"错误: 文件夹 '{folder_path}' 不存在!")
        return file_info
    
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith('.c') or file.endswith('.h'):
                abs_path = os.path.join(root, file)
                file_info.append({
                    'name': file,
                    'dir': root,
                    'abs_path': abs_path,
                    'type': '1' if file.endswith('.c') else '5'
                })
    
    return file_info

def add_include_paths(root, folders, project_dir):
    """将文件夹添加到项目的包含路径中"""
    # 找到IncludePath节点
    include_path_nodes = root.findall('.//IncludePath')
    if not include_path_nodes:
        print("警告: 在项目文件中找不到IncludePath节点")
        return False
    
    paths_added = 0
    
    for include_path_node in include_path_nodes:
        current_paths = include_path_node.text.split(';') if include_path_node.text else []
        
        # 对于每个包含文件的文件夹
        for folder in folders:
            # 计算相对于项目目录的路径
            rel_path = os.path.relpath(folder, start=project_dir)
            rel_path = rel_path.replace('\\', '/')
            
            # 检查路径是否已存在
            if rel_path not in current_paths and rel_path != '.':
                current_paths.append(rel_path)
                paths_added += 1
                print(f"添加包含路径: {rel_path}")
        
        # 更新IncludePath节点的值
        include_path_node.text = ';'.join(current_paths)
    
    print(f"共添加了 {paths_added} 个包含路径")
    return paths_added > 0

def update_keil_project(uvprojx_file_path, folder_path, group_name_target, update_include=True):
    """更新Keil项目文件，添加文件到组并更新包含路径"""
    # 创建备份
    backup_path = uvprojx_file_path + '.bak'
    try:
        shutil.copy2(uvprojx_file_path, backup_path)
        print(f"已创建备份: {backup_path}")
    except Exception as e:
        print(f"警告: 创建备份失败: {e}")
    
    # 使用临时XML文件
    xml_path = uvprojx_file_path + '.temp.xml'
    try:
        # 复制而不是重命名以保留原始文件
        shutil.copy2(uvprojx_file_path, xml_path)
        
        # 解析XML文件
        tree = ET.parse(xml_path)
        root = tree.getroot()
        
        # 获取文件列表
        print(f"扫描文件夹: {folder_path}")
        file_list = find_c_h_files(folder_path)
        
        if not file_list:
            print(f"警告: 未在 '{folder_path}' 及其子文件夹中找到任何.c或.h文件")
            return
        
        print(f"找到 {len(file_list)} 个.c和.h文件")
        
        # 找到Targets节点
        targets_node = root.find('.//Targets')
        if targets_node is None:
            print("错误: 在项目文件中找不到Targets节点")
            return
            
        # 找到Target节点
        target_node = targets_node.find('./Target')
        if target_node is None:
            print("错误: 在项目文件中找不到Target节点")
            return
            
        # 找到或创建Groups节点
        groups_node = target_node.find('./Groups')
        if groups_node is None:
            print("未找到Groups节点，正在创建")
            groups_node = ET.SubElement(target_node, 'Groups')
        
        # 创建或找到主组
        main_group = None
        for group in groups_node.findall('./Group'):
            group_name = group.find('GroupName')
            if group_name is not None and group_name.text == group_name_target:
                main_group = group
                break
        
        if main_group is None:
            print(f"创建新的主组 '{group_name_target}'")
            main_group = ET.SubElement(groups_node, 'Group')
            group_name = ET.SubElement(main_group, 'GroupName')
            group_name.text = group_name_target
        
        # 获取主组的Files节点
        main_files_node = main_group.find('Files')
        if main_files_node is None:
            main_files_node = ET.SubElement(main_group, 'Files')
        
        # 项目目录的绝对路径
        project_dir = os.path.dirname(os.path.abspath(uvprojx_file_path))
        
        # 收集所有包含头文件的目录
        include_dirs = set()
        
        # 添加文件到主组
        files_added = 0
        for file_info in file_list:
            file_name = file_info['name']
            file_type = file_info['type']
            abs_path = file_info['abs_path']
            file_dir = file_info['dir']
            
            # 如果是头文件，添加其目录到包含路径
            if file_name.endswith('.h'):
                include_dirs.add(file_dir)
            
            # 计算相对路径
            rel_path = os.path.relpath(abs_path, start=project_dir)
            rel_path = rel_path.replace('\\', '/')
            
            # 检查文件是否已经存在
            file_exists = False
            for existing_file in main_files_node.findall('./File'):
                filename_node = existing_file.find('FileName')
                filepath_node = existing_file.find('FilePath')
                if (filename_node is not None and filename_node.text == file_name and
                    filepath_node is not None and filepath_node.text == rel_path):
                    file_exists = True
                    break
            
            if file_exists:
                print(f"文件已存在: {rel_path}")
                continue
            
            # 创建File节点
            file_node = ET.SubElement(main_files_node, 'File')
            
            file_name_node = ET.SubElement(file_node, 'FileName')
            file_name_node.text = file_name
            
            file_type_node = ET.SubElement(file_node, 'FileType')
            file_type_node.text = file_type
            
            file_path_node = ET.SubElement(file_node, 'FilePath')
            file_path_node.text = rel_path
            
            files_added += 1
            print(f"添加文件: {rel_path}")
        
        # 更新包含路径
        include_paths_updated = False
        if update_include and include_dirs:
            include_paths_updated = add_include_paths(root, include_dirs, project_dir)
        
        # 格式化XML
        indent(root)
        
        # 保存修改后的XML
        tree.write(xml_path, encoding='utf-8', xml_declaration=True)
        
        # 用修改后的版本覆盖原始文件
        shutil.copy2(xml_path, uvprojx_file_path)
        
        if files_added > 0 or include_paths_updated:
            print(f"成功添加 {files_added} 个文件到项目")
            if update_include:
                print("包含路径已更新")
        else:
            print("未对项目进行任何更改")
        
    except ET.ParseError as e:
        print(f"解析错误: {e}")
        print(f"您可以从备份 {backup_path} 恢复原始文件")
    except Exception as e:
        print(f"错误: {e}")
        print(f"您可以从备份 {backup_path} 恢复原始文件")
    finally:
        # 清理临时文件
        if os.path.exists(xml_path):
            try:
                os.remove(xml_path)
            except:
                print(f"警告: 无法删除临时文件 {xml_path}")

def find_uvprojx_file():
    """查找当前目录中的.uvprojx文件"""
    uvprojx_files = glob.glob("*.uvprojx")
    if not uvprojx_files:
        print("当前目录中未找到.uvprojx文件")
        return None
    elif len(uvprojx_files) > 1:
        print("当前目录中找到多个.uvprojx文件:")
        for i, file in enumerate(uvprojx_files, start=1):
            print(f"{i}. {file}")
        choice = input("输入要使用的文件编号，或输入'q'退出: ")
        if choice.lower() == 'q':
            return None
        try:
            index = int(choice) - 1
            if 0 <= index < len(uvprojx_files):
                return uvprojx_files[index]
            else:
                print("无效的选择")
                return None
        except ValueError:
            print("无效的输入")
            return None
    else:
        return uvprojx_files[0]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="更新Keil项目文件，添加文件到组并更新包含路径")
    parser.add_argument("folder_path", help="包含要添加的.c和.h文件的文件夹的相对路径")
    parser.add_argument("group_name", help="要添加文件的组的名称(如果不存在将被创建)")
    parser.add_argument("--no-include", action="store_true", help="不添加包含路径")
    args = parser.parse_args()

    # 打印当前工作目录
    print(f"当前工作目录: {os.getcwd()}")
    print(f"目标文件夹: {args.folder_path}")
    print(f"目标组名称: {args.group_name}")
    print(f"更新包含路径: {'否' if args.no_include else '是'}")

    uvprojx_file_path = find_uvprojx_file()
    if uvprojx_file_path:
        update_keil_project(uvprojx_file_path, args.folder_path, args.group_name, not args.no_include)