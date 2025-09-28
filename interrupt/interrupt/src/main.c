#include "init.h"
#include <string.h>

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    if (init() != HAL_OK)
        goto error;

    // -----------------------------
    // C?u hình chân P3.10 làm LED ra
    GPIO_Init_T gp;
    gp.pin   = GPIO_PIN_10;    
    gp.mode  = GPIO_MODE_OUTPUT;
    gp.pull  = 0;              // Không kéo lên/xu?ng
    gp.drive = 0;              
    HAL_GPIO_Init(SN_GPIO3, &gp);

    // C?u hình chân P1.14 làm nút nh?n vào (active-low)
    GPIO_Init_T buttonGp;
    buttonGp.pin   = GPIO_PIN_14;
    buttonGp.mode  = GPIO_MODE_INPUT;
    buttonGp.pull  = GPIO_PULL_UP;   
    buttonGp.drive = 0;              
    HAL_GPIO_Init(SN_GPIO1, &buttonGp);

    // C?u hình chân P3.7 làm nút reset ph?n m?m
    GPIO_Init_T resetGp;
    resetGp.pin   = GPIO_PIN_7;
    resetGp.mode  = GPIO_MODE_INPUT;
    resetGp.pull  = GPIO_PULL_UP;   // Nh?n = LOW
    resetGp.drive = 0;
    HAL_GPIO_Init(SN_GPIO3, &resetGp);

    while (1)
    {
        // -----------------------------
        // Ki?m tra nút reset P3.7
        if (HAL_GPIO_ReadPin(SN_GPIO3, GPIO_PIN_7) == GPIO_PIN_LOW)
        {
            // Reset ph?n m?m
            NVIC_SystemReset();   // CMSIS: kh?i d?ng l?i MCU
        }

        // -----------------------------
        // Ki?m tra nút P1.14 d? b?t/t?t LED P3.10
        if (HAL_GPIO_ReadPin(SN_GPIO1, GPIO_PIN_14) == GPIO_PIN_LOW)  // Nh?n
        {
            HAL_GPIO_WritePin(SN_GPIO3, GPIO_PIN_10, GPIO_PIN_LOW);  // LED ON (active-low)
        }
        else
        {
            HAL_GPIO_WritePin(SN_GPIO3, GPIO_PIN_10, GPIO_PIN_HIGH); // LED OFF
        }

        HAL_Delay(100); // Tránh ki?m tra quá nhanh
    }

error:
    uninit();
    Error_Handler();
}
