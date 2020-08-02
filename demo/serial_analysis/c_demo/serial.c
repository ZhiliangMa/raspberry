#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

// 最大帧长度
#define MaxFrameLength	10						// 对最大帧长度加以限定，防止接收到过长的帧数据
// 完整的帧头，2个字节
#define Frame_Header1   0x3A                    // 串口接收消息包的帧头的第1个字节
#define Frame_Header2   0x3B                    // 串口接收消息包的帧头的第2个字节
// 完整的帧尾，2个字节
#define Frame_Tail1     0x7E                    // 串口接收消息包的帧尾的第1个字节
#define Frame_Tail2     0x7F                    // 串口接收消息包的帧尾的第2个字节

int main(void)
{
    int hs1;
    int snum = 0;                               // 系统串口接收缓存区的可用字节数
    int tnum = 0;                               // 用户串口接收区的数目
    unsigned char chrtmp[100];                  // 用户串口接收区，将缓存的数据放入这里处理
    int f_h1_flag = 0;                          // 接收到帧头的第一个字节标志位
    int f_h_flag = 0;                           // 接收到帧头标志位
    int f_t1_flag = 0;                          // 接收到帧尾的第一个字节标志位


    wiringPiSetup();                            // 使用wiring编码去初始化GPIO序号
    //hs1 = serialOpen("/dev/ttyS0", 115200);     // 打开 /dev/ttyS0 串口设备，波特率115200
    hs1 = serialOpen("/dev/ttyUSB0", 115200);     // 打开 /dev/ttyUSB0 串口设备，波特率115200


    /*printf("ttyS0 uart test2:\n");              // 终端打印
    serialPrintf(hs1, "Hello World!\r\n");      // 串口打印
    serialPrintf(hs1, "Enter a paragraph and end with Enter:\r\n");*/

    while (1)
    {
        snum = serialDataAvail(hs1);                	// 获取串口接收缓存区的可用字节数
        if(snum > 0)
        {
            chrtmp[tnum] = serialGetchar(hs1);  		// 从接收缓存区读取一个字节

            if (f_h_flag == 1)  // 有帧头，判断帧尾，接收消息
            {
                if (f_t1_flag == 1) //有帧头，有帧尾1
                {
                    if (chrtmp[tnum] == Frame_Tail2)
                    {
                        /* 用户处理代码 */
                        /* 将接收到符合帧定义的帧，原路发送回去 */
                        int i = 0;
                        for (i = 0; i < (tnum + 1); i++)
                        {
                            serialPutchar(hs1, chrtmp[i]);	// 通过串口发送字节
                        }

                        /*  处理完用户代码，重新接收计数 */
                        tnum = 0;
                    }
                    else
                    {
                        f_t1_flag = 0;
                        tnum ++;
                    }
                }
                else									// 有帧头，无帧尾1
                {
                    if (chrtmp[tnum] == Frame_Tail1)
                    {
                        f_t1_flag = 1;
                        tnum ++;
                    }
                    else								// 接收消息包中间内容
                    {
                        tnum ++;
                    }
                }
            }
            else										// 没有接收到帧头
            {
                if (f_h1_flag == 1)						//没有帧头，有帧头1。下一步判断是否为第2个字节
                {
                    if (chrtmp[tnum] == Frame_Header2)  // 如果为帧头的第2个字节，接收到帧头标志位标志位置1，tnum自增
                    {
                        f_h_flag = 1;
                        tnum ++;
                    }
                    else
                    {
                        f_h1_flag = 0;
                        tnum = 0;
                    }
                }
                else									//没有帧头，没有有帧头1。下一步判断，是否为帧头的第1个字节
                {
                    if (chrtmp[tnum] == Frame_Header1)  // 如果为帧头的第1个字节，标志位置1，tnum自增
                    {
                        f_h1_flag = 1;
                        tnum ++;
                    }
                    else                                // 否则，标志位清0，tnum清0
                    {
                        tnum = 0;
                    }
                }
            }

            // 大于MaxFrameLength个字节的帧不接收
            if (tnum > (MaxFrameLength - 1) )
            {
                tnum = 0;
                f_h1_flag = 0;
                f_h_flag = 0;
                f_t1_flag = 0;
                continue;
            }

        }
    }

    return 0;
}