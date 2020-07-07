#include <wiringPi.h>

int hpwmLed = 1;                    // 定义使用wiringPi编码的1引脚
int main(void)
{
    int xnum = 0;
    wiringPiSetup();                // 使用wiring编码去初始化GPIO序号
    pinMode(hpwmLed, PWM_OUTPUT);   // 设置GPIO电气属性为pwm输出
    pwmSetRange(1024);              // pwm脉宽范围 0~1024
    pwmSetClock(75);                // 250Hz，19.2MHz / 75 / 1024 = 250Hz
    while(1)
    {
        for(xnum = 0; xnum <= 1024; xnum++)
        {
            pwmWrite(hpwmLed,xnum);
            delay(2);               // 延时2ms
        }
    }
    return 0;
}