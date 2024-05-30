/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "userGui.h"
#include "u8g2.h"
#include "shell_port.h"
#include "shell.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId guiTaskHandle;
osThreadId shellTaskHandle;
osSemaphoreId spiTranBinarySemHandle;
osSemaphoreId pageBinarySemHandle;
osSemaphoreId uartSendBinarySemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern SPI_HandleTypeDef hspi1;
/* USER CODE END FunctionPrototypes */

void osGuiTask(void const * argument);
void osShellTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of spiTranBinarySem */
  osSemaphoreDef(spiTranBinarySem);
  spiTranBinarySemHandle = osSemaphoreCreate(osSemaphore(spiTranBinarySem), 1);

  /* definition and creation of pageBinarySem */
  osSemaphoreDef(pageBinarySem);
  pageBinarySemHandle = osSemaphoreCreate(osSemaphore(pageBinarySem), 1);

  /* definition and creation of uartSendBinarySem */
  osSemaphoreDef(uartSendBinarySem);
  uartSendBinarySemHandle = osSemaphoreCreate(osSemaphore(uartSendBinarySem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of guiTask */
  osThreadDef(guiTask, osGuiTask, osPriorityNormal, 0, 128);
  guiTaskHandle = osThreadCreate(osThread(guiTask), NULL);

  /* definition and creation of shellTask */
  osThreadDef(shellTask, osShellTask, osPriorityIdle, 0, 256);
  shellTaskHandle = osThreadCreate(osThread(shellTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_osGuiTask */
/**
  * @brief  Function implementing the guiTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_osGuiTask */
void osGuiTask(void const * argument)
{
  /* USER CODE BEGIN osGuiTask */
  userGuiInit();
  /* Infinite loop */
  for(;;)
  {
		userGuiTask();
  }
  /* USER CODE END osGuiTask */
}

/* USER CODE BEGIN Header_osShellTask */
/**
* @brief Function implementing the shellTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_osShellTask */
void osShellTask(void const * argument)
{
  /* USER CODE BEGIN osShellTask */
  /* Infinite loop */
	userShellInit();
  for(;;)
  {
		shellTask(&shell);
  }
  /* USER CODE END osShellTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

