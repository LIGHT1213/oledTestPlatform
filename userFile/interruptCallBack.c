#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "shell.h"
uint8_t curPageNum = 0;
extern SPI_HandleTypeDef hspi1;
extern osSemaphoreId spiTranBinarySemHandle;
extern osSemaphoreId pageBinarySemHandle;
uint8_t getCurPageNum()
{
	return curPageNum;
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == &hspi1)
	{
		osSemaphoreRelease(spiTranBinarySemHandle);
	}
}
void nextPage()
{
		if(curPageNum < 1)
		{
			curPageNum++;
		}
		else
		{
			curPageNum = 0;
		}
	osSemaphoreRelease(pageBinarySemHandle);
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), nextPage, nextPage, 下一页);
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == PLUS_KEY_Pin)
	{
		if(HAL_GPIO_ReadPin(PLUS_KEY_GPIO_Port,PLUS_KEY_Pin)==GPIO_PIN_SET)
		{
			if(curPageNum < 1)
			{
				curPageNum++;
			}
			else
			{
				curPageNum = 0;
			}
			osSemaphoreRelease(pageBinarySemHandle);
		}

		
	}
}
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch (msg)
	{
	case U8X8_MSG_BYTE_SEND:
		osSemaphoreWait(spiTranBinarySemHandle, osWaitForever);
		HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)arg_ptr, arg_int);
		break;
	case U8X8_MSG_BYTE_INIT:
		osDelay(arg_int);
		break;
	case U8X8_MSG_BYTE_SET_DC:
		if(arg_int == 1)
		{
			HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
		}
		break;
	case U8X8_MSG_BYTE_START_TRANSFER:
		break;
	case U8X8_MSG_BYTE_END_TRANSFER:
		break;
	default:
		return 0;
	}
	return 1;
}
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:
			break;
		case U8X8_MSG_DELAY_MILLI:
			osDelay(arg_int);
			break;
		case U8X8_MSG_GPIO_RESET:
			HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_RESET);
			osDelay(200);
			HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_SET);
			break;
		
	}
	return 1;
}