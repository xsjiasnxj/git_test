#include "stm32f4xx.h"
#include "pid.h"

void pid_init(pidtype* pid, float kp, float ki, float kd)
{
    pid->set_speed = 0.0;
    pid->actual_speed = 0.0;
    pid->error = 0.0;
    pid->error_next = 0.0;
    pid->error_last = 0.0;
    //可调节PID 参数。使跟踪曲线慢慢接近阶跃函数//
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

float pid_realize(float set, float actual, pidtype* pid)//实现pid
{
    pid->set_speed = set;//设置目标速度
    pid->actual_speed = actual;
    pid->error = pid->set_speed - pid->actual_speed;
    if(((pid->error) >= 0.0f && (pid->error) <= 0.02f) || ((pid->error) <= 0.0f && (pid->error) >= -0.02f))
    {
    	pid->error = 0.0f;
    	pid->error_next = 0.0f;
    }
    float increment_speed =
    		pid->kp*(pid->error-pid->error_next)
    		+pid->ki*pid->error
			+ pid->kd*(pid->error-2.0f*pid->error_next+pid->error_last);//增量计算公式
    pid->error_last = pid->error_next;//下一次迭代
    pid->error_next = pid->error;
    return increment_speed;
}

float pid_limited(pidtype* pid, float set, float actual, float output, float min, float max)
{
    pid->set_speed = set;//设置目标速度
    pid->actual_speed = actual;
    pid->error = pid->set_speed - pid->actual_speed;
    if(((pid->error) >= 0.0f && (pid->error) <= 0.02f) || ((pid->error) <= 0.0f && (pid->error) >= -0.02f))
    {
    	pid->error = 0.0f;
    	pid->error_next = 0.0f;
    }

    float increment_speed =
    		pid->kp*(pid->error-pid->error_next)
    		+pid->ki*pid->error
			+ pid->kd*(pid->error-2.0f*pid->error_next+pid->error_last);//增量计算公式
    if(output + increment_speed >= max || output + increment_speed <= min)
    {
    	increment_speed = pid->kp*(pid->error-pid->error_next);
    }
    pid->error_last = pid->error_next;//下一次迭代
    pid->error_next = pid->error;
    return increment_speed;
}