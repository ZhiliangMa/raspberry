#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void)
{
    int hs1;
    int snum = 0;

    wiringPiSetup();                        // 使用wiring编码去初始化GPIO序号
    hs1 = serialOpen("/dev/ttyAMA0", 115200); // 打开 /dev/ttyAMA0 串口设备，波特率115200

    printf("ttyS0 uart test1:\n");          // 终端打印
    serialPrintf(hs1, "Hello World!\r\n");  // 串口打印
    serialPrintf(hs1, "Enter 10 letters:\r\n");

    /* 串口缓存区读取10个字节，并完整输出接收到的数据 */
    do{
        snum = serialDataAvail(hs1);        // 获取串口接收缓存区的可用字节数
    }while(snum < 10);

    while(snum--)
    {
        serialPutchar(hs1,serialGetchar(hs1));  // 通过串口发送字节
    }
    serialPrintf(hs1, "\r\nserial close\r\n\r\n");  // 串口打印

    serialClose(hs1);                       // 关闭串口
    return 0;
}