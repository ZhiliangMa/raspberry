#include <wiringPi.h>

int led = 7;                    // 定义使用wiringPi编码的7引脚
int main(void)
{
    wiringPiSetup();            // 使用wiring编码去初始化GPIO序号
    pinMode(led, OUTPUT);       // 设置GPIO电气属性为推挽输出
    while(1)
    {
        digitalWrite(led, 1);   // led亮
        delay(500);             // 延时500ms
        digitalWrite(led, 0);   // led灭
        delay(500);             // 延时500ms
    }
    return 0;
}