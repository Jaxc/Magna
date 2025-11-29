/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_STACK_SIZE           (512u)
#define AUDIO_THREAD_STACK_SIZE     (8096u)
#define IO_THREAD_STACK_SIZE        (8096u)
#define MONITOR_THREAD_STACK_SIZE   (512u)

#define MONITOR_QUEUE_LENGTH        (1u)
#define MONITOR_QUEUE_SIZE          (4u * MONITOR_QUEUE_LENGTH)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */




UCHAR __attribute__((section(".stack")))stack_audio[AUDIO_THREAD_STACK_SIZE];
UCHAR __attribute__((section(".stack")))stack_io[IO_THREAD_STACK_SIZE];
UCHAR __attribute__((section(".stack")))stack_monitor[MONITOR_THREAD_STACK_SIZE];
UCHAR __attribute__((section(".stack")))stack_blinky[THREAD_STACK_SIZE];



UCHAR __attribute__((section(".stack")))monitor_data_queue[MONITOR_QUEUE_SIZE];

TX_SEMAPHORE __attribute__((section(".stack")))semaphore_audio_dma;
TX_QUEUE __attribute__((section(".stack")))monitor_data_ptr_queue;



TX_THREAD __attribute__((section(".stack")))thread_ptr_blinky;
TX_THREAD __attribute__((section(".stack")))thread_ptr_audio;
TX_THREAD __attribute__((section(".stack")))thread_ptr_io;
TX_THREAD __attribute__((section(".stack")))thread_ptr_monitor;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID blinky (ULONG initial_input);
VOID audio_handler (ULONG initial_input);
VOID io_handler (ULONG initial_input);
VOID system_monitor (ULONG initial_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */

  tx_semaphore_create(&semaphore_audio_dma,"Audio buffers ready",0);
  tx_queue_create(&monitor_data_ptr_queue, "monitor ADC queue", 1, &monitor_data_queue, MONITOR_QUEUE_SIZE);

  tx_thread_create(
    &thread_ptr_blinky,  "blinky",         blinky,         0,  stack_blinky,   THREAD_STACK_SIZE,         15,  15,  1,  TX_AUTO_START);
  tx_thread_create(
    &thread_ptr_audio,   "Audio",          audio_handler,  0,  stack_audio,    AUDIO_THREAD_STACK_SIZE,   10,  10,  1,  TX_AUTO_START);
  tx_thread_create(
    &thread_ptr_io,      "IO",             io_handler,     0,  stack_io,       IO_THREAD_STACK_SIZE,      12,  12,  1,  TX_AUTO_START);
  tx_thread_create(
    &thread_ptr_monitor, "System Monitor", system_monitor, 0,  stack_monitor,  MONITOR_THREAD_STACK_SIZE,  8,   8,  1,  TX_AUTO_START);

  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
