#include "my_uart.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    UART_Init(115200); // kh?i t?o UART 115200 baud

    while(1)
    {
        uint8_t c;
        if(UART_Receive(&c, 100) == 0)
        {
            UART_Send(c); // echo l?i byte nh?n du?c
        }
    }
}
