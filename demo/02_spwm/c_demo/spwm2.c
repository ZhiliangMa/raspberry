#include <wiringPi.h>
#include <softPwm.h>

int spwmLed = 1;                        // 定义使用wiringPi编码的1引脚
int main(void)
{
    int xnum = 0;
    wiringPiSetup();                    // 使用wiring编码去初始化GPIO序号
    softPwmCreate (spwmLed, 0, 100);    // 设置wiringPi编码的1引脚为软件PWM输出
    while(1)
    {
        for(xnum = 0; xnum <= 100; xnum++)
        {
            softPwmWrite(spwmLed, xnum);
            delay(15);                  // 延时15ms
        }
        for(xnum = 99; xnum > 0; xnum--)
        {
            softPwmWrite(spwmLed, xnum);
            delay(15);                  // 延时15ms
        }
    }
    return 0;
}