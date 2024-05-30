#include "main.h"
#include "shell_port.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
static ring_buffer RB;
Shell shell;
static uint8_t DataBuff[256];  //shell 用缓冲区
static uint8_t RingBuff[32];  //shell 用缓冲区
char tempData;
extern osSemaphoreId uartSendBinarySemHandle;
void userShellInit(void)
{
    shell.write = shellWrite;

    shell.read = shellRead;

    shellInit(&shell,(char *)DataBuff,256); //shell初始化
		Ring_Buffer_Init(&RB,RingBuff,32);

    HAL_UART_Receive_IT(&huart2,(uint8_t*)(&tempData),1);
}
static short shellWrite(char* data,unsigned short len)
{
    if(osSemaphoreWait(uartSendBinarySemHandle,osWaitForever)==osOK)
    {
        HAL_UART_Transmit_DMA(&huart2, (uint8_t *)data, len);
        return len;
    }
    else
    {
        return 0;
    }
}

static short shellRead(char* data,unsigned short len)
{
    unsigned short curDataLength=Ring_Buffer_Get_Lenght(&RB);
    if(curDataLength>0 && Ring_Buffer_Get_Lenght(&RB)>=len)
    {
        Ring_Buffer_Read_String(&RB,(uint8_t*)data,len);
        return len;
    }
    else if(curDataLength>0 && Ring_Buffer_Get_Lenght(&RB)<len)
    {
        Ring_Buffer_Read_String(&RB,(uint8_t*)data,curDataLength);
        return curDataLength;
    }
    else
    {
        return 0;
    }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart2)
    {
        osSemaphoreRelease(uartSendBinarySemHandle);
    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        Ring_Buffer_Write_Byte(&RB, tempData);
        HAL_UART_Receive_IT(&huart2, (uint8_t *)(&tempData), 1);
    }
}
