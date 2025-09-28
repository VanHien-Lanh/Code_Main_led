/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */
// this function is called if an TX interrupt is generated
void HAL_GPIO_Callback(SN_GPIO_Type gpio, uint32_t gpio_pin)
{
    /* Check whether the irq port and pin match */
    if (gpio == SN_GPIO3 && (gpio_pin & GPIO_PIN_4) != 0)
    {
        key_trigger = 1;
    }
}
/* USER CODE END #0 */

/**
 * The HAL_MspInit will be called in HAL_Init.
 */
void HAL_MspInit(void)
{
    /* USER CODE BEGIN MspInit #0 */

    /* USER CODE END MspInit #0 */
}

/**
 * The HAL_MspDeInit will be called in HAL_DeInit.
 */
void HAL_MspDeInit(void)
{
    /* USER CODE BEGIN MspDeInit #0 */

    /* USER CODE END MspDeInit #0 */
}
