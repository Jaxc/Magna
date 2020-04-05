
/* Includes ------------------------------------------------------------------*/
#include "usbd_magna_desc.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "usbd_internal.h"
#include "error_codes.h"
#include "usb_magna.h"
#include "tim.h"

#define VBUS_FS_Pin                     GPIO_PIN_9
#define VBUS_FS_GPIO_Port               GPIOA
#define OTG_FS_ID_Pin                   GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port             GPIOA
#define OTG_FS_DM_Pin                   GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port             GPIOA
#define OTG_FS_DP_Pin                   GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port             GPIOA

PCD_HandleTypeDef hpcd_magna;

void _Error_Handler(char * file, int line);
void SystemClock_Config(void);

static int stm32_to_magna_error(HAL_StatusTypeDef status)
{
    switch (status)
    {
    case HAL_OK: return MAGNA_OK;
    case HAL_ERROR: return MAGNA_FAILED;
    case HAL_BUSY: return MAGNA_BUSY;
    case HAL_TIMEOUT: return MAGNA_TIMEOUT;
    }

    return MAGNA_INVALID_ARGUMENT;
}

/*------------------------------------------------------------------------------*/
/*  STM32 HAL_PCD callbacks                                                     */
/*------------------------------------------------------------------------------*/

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
   usbd_setup_stage((usbd_context_t *)hpcd->pData, (usb_setup_packet_t *)hpcd->Setup);
}

/* Rx complete callback */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    uint8_t *xfer_buff = hpcd->OUT_ep[0xF & epnum].xfer_buff;
    uint16_t xfer_count = hpcd->OUT_ep[0xF & epnum].xfer_count;

    usbd_data_rx_stage((usbd_context_t *)hpcd->pData, epnum, xfer_buff, xfer_count);
}

/* Tx complete callback */
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    uint8_t *xfer_buff = hpcd->IN_ep[0xF & epnum].xfer_buff;

    usbd_data_tx_stage((usbd_context_t *)hpcd->pData, epnum, xfer_buff);
}

volatile uint16_t sof_times[256];
uint8_t sof_times_cnt;

void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
//    htim11.Instance->CNT = 0;

    usbd_start_of_frame((usbd_context_t *)hpcd->pData);
//    __disable_irq();
//    __HAL_TIM_ENABLE(&htim11);
//    sof_times_cnt++;
//    __HAL_TIM_DISABLE(&htim11);
//    __enable_irq();
//    sof_times[sof_times_cnt] = htim11.Instance->CNT;


}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_reset((usbd_context_t *)hpcd->pData);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_suspend((usbd_context_t *)hpcd->pData);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_resume((usbd_context_t *)hpcd->pData);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_connect((usbd_context_t *)hpcd->pData);
}


void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_disconnect((usbd_context_t *)hpcd->pData);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {

    if (0 != epnum) {
        HAL_Delay(1);
    }
}
/*------------------------------------------------------------------------------*/
/*  STM32 HAL_PCD driver interface                                              */
/*------------------------------------------------------------------------------*/

int usbd_hw_init(usbd_context_t *ctx)
{
    /* Init USB_IP */
    hpcd_magna.pData = ctx;
    ctx->dev_data = &hpcd_magna;

    hpcd_magna.Instance = USB_OTG_FS;
    hpcd_magna.Init.dev_endpoints = 7;
    hpcd_magna.Init.speed = PCD_SPEED_FULL;
    hpcd_magna.Init.dma_enable = ENABLE;
    hpcd_magna.Init.ep0_mps = DEP0CTL_MPS_64;
    hpcd_magna.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd_magna.Init.Sof_enable = DISABLE;
    hpcd_magna.Init.low_power_enable = DISABLE;
    hpcd_magna.Init.lpm_enable = DISABLE;
    hpcd_magna.Init.vbus_sensing_enable = DISABLE;
    hpcd_magna.Init.use_dedicated_ep1 = DISABLE;
    if (HAL_PCD_Init(&hpcd_magna) != HAL_OK)
    {
        return MAGNA_FAILED;
    }

    /* Set RX FIFO */
    HAL_PCDEx_SetRxFiFo(&hpcd_magna, 0x80);

    /* Set EP0(control) Fifo*/
    HAL_PCDEx_SetTxFiFo(&hpcd_magna, 0, 0x80);
    /* Set audio out fifos*/
    //HAL_PCDEx_SetTxFiFo(&hpcd_magna, 1, 0x200);
    //HAL_PCDEx_SetTxFiFo(&hpcd_magna, 2, 0x200);

    return MAGNA_OK;
}

int usbd_hw_deinit(usbd_context_t *ctx)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_DeInit(&hpcd_magna);

    return stm32_to_magna_error(hal_status);
}

int usbd_start(usbd_context_t *ctx)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_Start(&hpcd_magna);

    return stm32_to_magna_error(hal_status);
}

int usbd_stop(usbd_context_t *ctx)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_Stop(&hpcd_magna);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_open(usbd_context_t *ctx, uint8_t ep_addr,
                 uint8_t ep_type, uint16_t ep_mps)
{
    (void)ctx;

    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Open(&hpcd_magna, ep_addr, ep_mps, ep_type);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_close(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Close(&hpcd_magna, ep_addr);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_flush(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Flush(&hpcd_magna, ep_addr);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_stall(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_SetStall(&hpcd_magna, ep_addr);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_stall_clear(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_ClrStall(&hpcd_magna, ep_addr);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_is_stalled(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    if((ep_addr & 0x80) == 0x80)
    {
        return (int)hpcd_magna.IN_ep[ep_addr & 0x7F].is_stall;
    }
    else
    {
        return (int)hpcd_magna.OUT_ep[ep_addr & 0x7F].is_stall;
    }
}

int usbd_set_address(usbd_context_t *ctx, uint8_t dev_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_SetAddress(&hpcd_magna, dev_addr);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_transmit(usbd_context_t *ctx, uint8_t ep_addr,
                     uint8_t *tx_buff, uint16_t size)
{
    (void)ctx;

    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Transmit(&hpcd_magna, ep_addr, tx_buff, size);

    return stm32_to_magna_error(hal_status);
}

int usbd_ep_receive(usbd_context_t *ctx, uint8_t ep_addr,
                    uint8_t *rx_buff, uint16_t size)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Receive(&hpcd_magna, ep_addr, rx_buff, size);

    return stm32_to_magna_error(hal_status);
}

uint16_t usbd_get_rx_data_len(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    return HAL_PCD_EP_GetRxCount(&hpcd_magna, ep_addr);
}

void usbd_delay_ms(uint32_t delay_ms)
{
    HAL_Delay(delay_ms);
}
