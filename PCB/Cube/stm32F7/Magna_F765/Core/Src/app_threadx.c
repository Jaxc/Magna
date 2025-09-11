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
#include "sai.h"
#include "i2s.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct {
  uint32_t *input_audio_channel1;
  uint32_t *input_audio_channel2;
  uint32_t *input_audio_channel3;
  uint32_t *input_audio_channel4;
  uint32_t *output_audio_main;
  uint32_t *output_audio_headphones;
} audio_buffers_t;

typedef struct {
  uint16_t dummy_parameter;
} parameter_data_t;

typedef enum {
  AUDIO_INPUT_CHANNEL_1 = 0,
  AUDIO_INPUT_CHANNEL_2,
  AUDIO_INPUT_CHANNEL_3,
  AUDIO_INPUT_CHANNEL_4,
  SAI_AUDIO_BUFFER_N
} sai_audio_chanels_t;

typedef enum {
  AUDIO_OUTPUT_MAIN = 0,
  AUDIO_OUTPUT_HEADPHONES,
  I2S_AUDIO_BUFFER_N
} i2s_audio_chanels_t;

typedef enum {
  DMA_HALFCOMPLETE = 0,
  DMA_FULLCOMPLETE,
} dma_complete_state_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* Thread definitions */
#define AUDIO_THREAD_STACK_SIZE     (1024)
#define IO_THREAD_STACK_SIZE        (1024)
#define IDLE_THREAD_STACK_SIZE      (32)

/* Queue definitions */
#define AUDIO_QUEUE_ELEMENTS        (6)
#define AUDIO_QUEUE_SLOTS           (32)
#define AUDIO_QUEUE_SIZE            (AUDIO_QUEUE_ELEMENTS * AUDIO_QUEUE_SLOTS)

/* Parameter queue only contains one pointer to a parameter struct. */
#define PARAMETER_QUEUE_ELEMENTS    (1)
#define PARAMETER_QUEUE_SIZE        (PARAMETER_QUEUE_ELEMENTS)
#define PARAMETER_QUEUE_SIZE_BYTES  (sizeof(parameter_data_t))

/* Audio buffer definitions */
#define AUDIO_BUFFER_SAMPLES        (128)
#define AUDIO_BUFFER_CIRCULAR_SIZE  (AUDIO_BUFFER_SAMPLES * 2)
#define SAI_DMA_SIZE                (AUDIO_BUFFER_CIRCULAR_SIZE * 4)
#define I2S_DMA_SIZE                (AUDIO_BUFFER_CIRCULAR_SIZE * 2)


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t audio_thread_stack[AUDIO_THREAD_STACK_SIZE];
uint8_t io_thread_stack[IO_THREAD_STACK_SIZE];
uint8_t idle_thread_stack[IO_THREAD_STACK_SIZE];

TX_THREAD p_audio_stack;
TX_THREAD p_io_stack;
TX_THREAD p_idle_stack;


uint8_t audio_queue_buffer[AUDIO_QUEUE_SIZE];
TX_QUEUE p_audio_queue;

uint8_t parameter_queue_buffer[PARAMETER_QUEUE_SIZE];
TX_QUEUE p_parameter_queue;


uint32_t sai_audio_buffers[SAI_AUDIO_BUFFER_N][AUDIO_BUFFER_CIRCULAR_SIZE];
uint32_t i2s_audio_buffers[I2S_AUDIO_BUFFER_N][AUDIO_BUFFER_CIRCULAR_SIZE];


SAI_HandleTypeDef *sai_audio_channel_mapping[SAI_AUDIO_BUFFER_N] = {
  &hsai_BlockA1, /* AUDIO_INPUT_CHANNEL_1*/
  &hsai_BlockA2, /* AUDIO_INPUT_CHANNEL_2*/
  &hsai_BlockB1, /* AUDIO_INPUT_CHANNEL_3*/
  &hsai_BlockB2, /* AUDIO_INPUT_CHANNEL_4*/
};

I2S_HandleTypeDef *i2s_audio_channel_mapping[I2S_AUDIO_BUFFER_N] = {
  &hi2s2, /* AUDIO_OUTPUT_MAIN*/
  &hi2s3, /* AUDIO_OUTPUT_HEADPHONES*/
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* Thread prototypes */
VOID audio_thread(ULONG inital_input);
VOID io_thread(ULONG inital_input);
VOID idle_thread(ULONG inital_input);

/* Queue prototypes */

/* Function prototypes */
void handle_audio_dma_callbacks(dma_complete_state_t complete_state);
void init_audio_dmas (void);

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
  tx_queue_create(&p_audio_queue, "Audio buffer queue", AUDIO_QUEUE_ELEMENTS, audio_queue_buffer, AUDIO_QUEUE_SIZE);
  tx_queue_create(&p_parameter_queue, "Parameter buffer queue", PARAMETER_QUEUE_ELEMENTS ,parameter_queue_buffer, PARAMETER_QUEUE_SIZE);
  tx_thread_create(&p_audio_stack,"Audio Processing",audio_thread, 0, audio_thread_stack,AUDIO_THREAD_STACK_SIZE,5,15,1,TX_AUTO_START);
	tx_thread_create(&p_io_stack,"IO Processing",io_thread, 0, io_thread_stack,IO_THREAD_STACK_SIZE,15,15,1,TX_AUTO_START);
  tx_thread_create(&p_idle_stack,"Idle",idle_thread, 0, idle_thread_stack,IDLE_THREAD_STACK_SIZE,32,32,1,TX_AUTO_START);
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

  static uint8_t io_process_alive_counter = 0;

  init_audio_dmas();


  while(1) {
    audio_buffers_t audio_buffers;
    UINT ret = tx_queue_receive(&p_audio_queue, &audio_buffers, TX_WAIT_FOREVER);
    if (TX_SUCCESS == ret) {
      /* Do stuff*/

      /* Get latest IO settings */
      void *new_queue_data;
      UINT queue_status = tx_queue_receive(&p_parameter_queue, &new_queue_data, TX_NO_WAIT);
      if (TX_SUCCESS != queue_status) {
        /* No update from IO process, detect threaddeadness or increase counter */
        if (100 == io_process_alive_counter) {
          Error_Handler();
        } else {
          io_process_alive_counter ++;
        }
      } else {
        io_process_alive_counter = 0;
      }

      /* Do signal processing */

      /* To test, just mirror data */
      for (uint8_t i = 0; i < AUDIO_BUFFER_SAMPLES; i++) {
        audio_buffers.output_audio_main[i] = audio_buffers.input_audio_channel1[i] +
                                             audio_buffers.input_audio_channel2[i] +
                                             audio_buffers.input_audio_channel3[i] +
                                             audio_buffers.input_audio_channel4[i];
      }

    } else {
      /* Graceful shutdown*/
    }
  }
}

VOID io_thread(ULONG inital_input) {
  /* Read values/wait for DMA with values queue*/

  /* Filter/process values values */

  /* Send values to audio process by reference, this works under the assumption
   * that this queue is read faster than it is written, which it should be. */
  UINT queue_status = tx_queue_send(&p_parameter_queue, NULL, TX_NO_WAIT);

  if (TX_SUCCESS != queue_status) {
    /* Something is very wrong: audio thread has not processed last update */
    Error_Handler();
  }

}

VOID idle_thread(ULONG inital_input) {
  while(1);
}


void init_audio_dmas (void) {
  for(uint8_t i = 0; i < SAI_AUDIO_BUFFER_N; i++) {
    HAL_StatusTypeDef status = HAL_SAI_Receive_DMA(sai_audio_channel_mapping[i], (uint8_t *)(sai_audio_buffers[i]), SAI_DMA_SIZE);
    if (HAL_OK != status) {
      Error_Handler();
    }
  }

  /* Init output */
  for(uint8_t i = 0; i < I2S_AUDIO_BUFFER_N; i++) {
    /* Make super sure the output is set to 0 to avoid noise before first real transmission */
    memset(i2s_audio_buffers[i], 0, AUDIO_BUFFER_SAMPLES * 4);
    HAL_StatusTypeDef status = HAL_I2S_Transmit_DMA(i2s_audio_channel_mapping[i], (uint16_t *)(i2s_audio_buffers[i]), I2S_DMA_SIZE);
    if (HAL_OK != status) {
      Error_Handler();
    }
  }
}

/* Interrupt callbacks */
void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
  if (SAI1_Block_A == hsai->Instance) {
    /* Since all I2S are synced this means that we can hand over the first half of the buffers to process*/
      handle_audio_dma_callbacks(DMA_HALFCOMPLETE);
  }
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {
  if (SAI1_Block_A == hsai->Instance) {
    /* Since all I2S are synced this means that we can hand over the first half of the buffers to process*/
      handle_audio_dma_callbacks(DMA_FULLCOMPLETE);
  }
}

void handle_audio_dma_callbacks(dma_complete_state_t complete_state) {
  audio_buffers_t new_buffers;
  uint32_t offset;
  if (DMA_HALFCOMPLETE == complete_state) {
    offset = AUDIO_BUFFER_SAMPLES;
  } else {
    offset = 0;
  }

  new_buffers.input_audio_channel1 = &(sai_audio_buffers[AUDIO_INPUT_CHANNEL_1][offset]);
  new_buffers.input_audio_channel2 = &(sai_audio_buffers[AUDIO_INPUT_CHANNEL_2][offset]);
  new_buffers.input_audio_channel3 = &(sai_audio_buffers[AUDIO_INPUT_CHANNEL_3][offset]);
  new_buffers.input_audio_channel4 = &(sai_audio_buffers[AUDIO_INPUT_CHANNEL_4][offset]);

  new_buffers.output_audio_main = &(i2s_audio_buffers[AUDIO_OUTPUT_MAIN][offset]);
  new_buffers.output_audio_headphones = &(i2s_audio_buffers[AUDIO_OUTPUT_HEADPHONES][offset]);

  UINT queue_status = tx_queue_send(&p_audio_queue, &new_buffers, TX_NO_WAIT);

  if (TX_SUCCESS != queue_status) {
    /* Something is very wrong!! */
    Error_Handler();
  }

}

/* USER CODE END 1 */
