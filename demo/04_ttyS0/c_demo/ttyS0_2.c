#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void)
{
    int hs1;
    int snum = 0;
    int tnum = 0;
    unsigned char chrtmp[100];
    wiringPiSetup();                            // 使用wiring编码去初始化GPIO序号
    hs1 = serialOpen("/dev/ttyS0", 115200);     // 打开 /dev/ttyS0 串口设备，波特率115200

    printf("ttyS0 uart test2:\n");              // 终端打印
    serialPrintf(hs1, "Hello World!\r\n");      // 串口打印
    serialPrintf(hs1, "Enter a paragraph and end with Enter:\r\n");

    /* 串口缓存区记录到数组，遇到\n结束，并完整输出接收到的数据 */
    while (1)
    {
        snum = serialDataAvail(hs1);            // 获取串口接收缓存区的可用字节数
        if(snum > 0)
        {
            chrtmp[tnum] = serialGetchar(hs1);  // 从接收缓存区读取一个字节
            tnum ++;
            if(chrtmp[tnum - 1] == '\n') break;
        }
        //delay(2000);
        //printf("%d  ,  %d\n",snum,tnum);
    }

    int i = 0;
    while (tnum--)
    {
        serialPutchar(hs1,chrtmp[i++]);         // 通过串口发送字节
    }
    serialPrintf(hs1, "\r\nserial close\r\n\r\n");  // 串口打印

    serialClose(hs1);                           // 关闭串口
    return 0;
}