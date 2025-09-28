#include "init.h"

/* USER CODE BEGIN #0 */

/* USER CODE END #0 */
GPIO_Init_T GPIO3_PIN3_INIT;
GPIO_Init_T GPIO3_PIN4_INIT;

uint32_t sn34f7_GPIO_Init(void)
{
    GPIO3_PIN3_INIT.pin   = GPIO_PIN_3;
    GPIO3_PIN3_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO3_PIN3_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO3, &GPIO3_PIN3_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO3, GPIO_PIN_3, GPIO_PIN_LOW) != HAL_OK)
        return HAL_ERROR;

    GPIO3_PIN4_INIT.pin  = GPIO_PIN_4;
    GPIO3_PIN4_INIT.mode = GPIO_MODE_IT_RISING;
    GPIO3_PIN4_INIT.pull = GPIO_PULL_INACTIVE;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO3, &GPIO3_PIN4_INIT))
        return HAL_ERROR;

    return HAL_OK;
}

uint32_t init(void)
{
    /* USER CODE BEGIN Init #0 */

    /* USER CODE END Init #0 */

    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_GPIO_Init(), HAL_OK), HAL_ERROR);

    /* USER CODE BEGIN Init #1 */

    /* USER CODE END Init #1 */

    return HAL_OK;
}

uint32_t uninit(void)
{
    /* USER CODE BEGIN Uninit #0 */

    /* USER CODE END Uninit #0 */

    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_GPIO_DeInit(SN_GPIO3, GPIO_PIN_3), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_GPIO_DeInit(SN_GPIO3, GPIO_PIN_4), HAL_OK), HAL_ERROR);

    HAL_DeInit();

    /* USER CODE BEGIN Uninit #1 */

    /* USER CODE END Uninit #1 */

    return HAL_OK;
}
