#ifndef	__KEY_H__
#define	__KEY_H__


typedef enum {
    NUMBER_EVENT,   //数字输入事件
    SET_EVENT,      //SET事件
    SWITCH_EVENT,   //开关事件
    BACK_EVENT,     //回退事件
}Key_Event;

typedef struct _Key_HandleTypeDef   //按键句柄
{
    char key_num;   //键码
    char key_event; //对应事件

}Key_HandleTypeDef;



/**********************************************************/
/* user */


void key_command_callback(Key_HandleTypeDef* key);         //按键回调函数，返回键值

/**********************************************************/

/**********************************************************/
/* driver */

void R_I_DOWN(void);                //矩阵键盘所有行下拉输入
void R_O_UP(void);                  //矩阵键盘所有行上拉输出
void C_I_DOWN(void);                //矩阵键盘所有列下拉输入
void C_O_UP(void);                  //矩阵键盘所有列上拉输出
uint8_t is_key_down(void);          //是否有按键被按下，有1无0

/**********************************************************/

//#define C3_Pin 							GPIO_Pin_2
//#define C3_GPIO_Port 					GPIOE
//#define C2_Pin 							GPIO_Pin_3
//#define C2_GPIO_Port 					GPIOE
//#define C1_Pin 							GPIO_Pin_4
//#define C1_GPIO_Port 					GPIOE
//#define C0_Pin 							GPIO_Pin_5
//#define C0_GPIO_Port 					GPIOE
//#define R3_Pin 							GPIO_Pin_6
//#define R3_GPIO_Port 					GPIOE
//#define R2_Pin 							GPIO_Pin_13
//#define R2_GPIO_Port 					GPIOC
//#define R1_Pin 							GPIO_Pin_0
//#define R1_GPIO_Port 					GPIOE
//#define R0_Pin 							GPIO_Pin_1
//#define R0_GPIO_Port 					GPIOE

#endif