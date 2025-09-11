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
#include "stdio.h"
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct {
  uint32_t *input_audio;
  uint32_t *output_audio;
} audio_buffers_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define AUDIO_THREAD_STACK_SIZE   (1024)
#define IO_THREAD_STACK_SIZE      (1024)

#define AUDIO_QUEUE_ELEMENTS      (2)
#define AUDIO_QUEUE_SLOTS         (32)
#define AUDIO_QUEUE_SIZE          (AUDIO_QUEUE_ELEMENTS * AUDIO_QUEUE_SLOTS)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t audio_thread_stack[AUDIO_THREAD_STACK_SIZE];
uint8_t io_thread_stack[IO_THREAD_STACK_SIZE];

TX_THREAD p_audio_stack;
TX_THREAD p_io_stack;


uint8_t audio_queue_buffer[AUDIO_QUEUE_SIZE];
TX_QUEUE p_audio_queue;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* Thread prototypes */
VOID audio_thread(ULONG inital_input);
VOID io_thread(ULONG inital_input);

/* Queue prototypes */

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
  tx_queue_create(&p_audio_queue, "Audio buffer queue", AUDIO_QUEUE_ELEMENTS ,audio_queue_buffer,AUDIO_QUEUE_SIZE);
  tx_thread_create(&p_audio_stack,"Audio Processing",audio_thread, 0, audio_thread_stack,AUDIO_THREAD_STACK_SIZE,5,15,1,TX_AUTO_START);
	tx_thread_create(&p_io_stack,"IO Processing",io_thread, 0, io_thread_stack,IO_THREAD_STACK_SIZE,15,15,1,TX_AUTO_START);
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
VOID audio_thread(ULONG inital_input) {
  while(1) {
    audio_buffers_t audio_buffers[AUDIO_QUEUE_ELEMENTS];
    UINT ret = tx_queue_receive(&p_audio_queue, &audio_buffers, TX_WAIT_FOREVER);
    if (TX_SUCCESS == ret) {
      /* Do stuff*/

      /* Get latest IO settings */


    } else {
      /* Graceful shutdown*/
    }
  }
}

VOID io_thread(ULONG inital_input) {


}


/* Interrupt callbacks */

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
  if (hsai->Instance) {

  }
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {

}


/* USER CODE END 1 */
