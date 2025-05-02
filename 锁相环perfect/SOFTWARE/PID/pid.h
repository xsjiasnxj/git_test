#ifndef	__PID_H__
#define	__PID_H__

typedef struct
{
    float set_speed;//设定速度
    float actual_speed;//实际速度
    float error;//偏差
    float error_next;//上一个偏差
    float error_last;//上上一个偏差
    float kp,ki,kd;//定义比例，积分，微分参数
}pidtype;
void pid_init(pidtype* pid, float kp, float ki, float kd);
float pid_realize(float set, float actual, pidtype* pid);//实现pid
float pid_limited(pidtype* pid, float set, float actual, float output, float min, float max);
#endif