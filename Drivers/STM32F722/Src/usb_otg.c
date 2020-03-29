/**
  ******************************************************************************
  * File Name          : USB_OTG.c
  * Description        : This file provides code for the configuration
  *                      of the USB_OTG instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_otg.h"

/* USER CODE BEGIN 0 */
#include "usbd_internal.h"
/* USER CODE END 0 */

PCD_HandleTypeDef hpcd_USB_OTG_FS;

void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */

  /* USER CODE END USB_OTG_FS_MspInit 0 */
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USB_OTG_FS GPIO Configuration    
    PA8     ------> USB_OTG_FS_SOF
    PA9     ------> USB_OTG_FS_VBUS
    PA10     ------> USB_OTG_FS_ID
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP 
    */
    GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USB_VBUS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

    /* USB_OTG_FS clock enable */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* USB_OTG_FS interrupt Init */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspInit 1 */

  /* USER CODE END USB_OTG_FS_MspInit 1 */
  }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle)
{

  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 0 */

  /* USER CODE END USB_OTG_FS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
  
    /**USB_OTG_FS GPIO Configuration    
    PA8     ------> USB_OTG_FS_SOF
    PA9     ------> USB_OTG_FS_VBUS
    PA10     ------> USB_OTG_FS_ID
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP 
    */
    HAL_GPIO_DeInit(GPIOA, USB_SOF_Pin|USB_VBUS_Pin|USB_ID_Pin|USB_DM_Pin 
                          |USB_DP_Pin);

    /* USB_OTG_FS interrupt Deinit */
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 1 */

  /* USER CODE END USB_OTG_FS_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
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

void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
    usbd_start_of_frame((usbd_context_t *)hpcd->pData);
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

int usbd_ep_open(usbd_context_t *ctx, uint8_t ep_addr,
                 uint8_t ep_type, uint16_t ep_mps)
{
    (void)ctx;

    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Open(&hpcd_USB_OTG_FS, ep_addr, ep_mps, ep_type);

    return hal_status;
}

int usbd_ep_close(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Close(&hpcd_USB_OTG_FS, ep_addr);

    return hal_status;
}

int usbd_ep_flush(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Flush(&hpcd_USB_OTG_FS, ep_addr);

    return hal_status;
}

int usbd_ep_stall(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_SetStall(&hpcd_USB_OTG_FS, ep_addr);

    return hal_status;
}

int usbd_ep_stall_clear(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_ClrStall(&hpcd_USB_OTG_FS, ep_addr);

    return hal_status;
}

int usbd_ep_is_stalled(usbd_context_t *ctx, uint8_t ep_addr)
{
    (void)ctx;
    if((ep_addr & 0x80) == 0x80)
    {
        return (int)hpcd_USB_OTG_FS.IN_ep[ep_addr & 0x7F].is_stall;
    }
    else
    {
        return (int)hpcd_USB_OTG_FS.OUT_ep[ep_addr & 0x7F].is_stall;
    }
}

int usbd_set_address(usbd_context_t *ctx, uint8_t dev_addr)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_SetAddress(&hpcd_USB_OTG_FS, dev_addr);

    return hal_status;
}

int usbd_ep_transmit(usbd_context_t *ctx, uint8_t ep_addr,
                     uint8_t *tx_buff, uint16_t size)
{
    (void)ctx;

    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Transmit(&hpcd_USB_OTG_FS, ep_addr, tx_buff, size);

    return hal_status;
}

int usbd_ep_receive(usbd_context_t *ctx, uint8_t ep_addr,
                    uint8_t *rx_buff, uint16_t size)
{
    (void)ctx;
    HAL_StatusTypeDef hal_status = HAL_PCD_EP_Receive(&hpcd_USB_OTG_FS, ep_addr, rx_buff, size);

    return hal_status;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
