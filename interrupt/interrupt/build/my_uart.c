#include "my_uart.h"
#include "init.h"   // d? dùng HAL_Delay

void UART_Init(uint32_t baudrate)
{
    // Reset UART
    UART_CTRL = 0;

    // TODO: tính toán baudrate theo clock MCU
    // UART_BAUD = Fclk / (16 * baudrate)

    // Enable TX/RX, 8N1 m?c d?nh
    UART_CTRL = (1 << 0) | (1 << 1); // bit0 = RX enable, bit1 = TX enable
}

int UART_Receive(uint8_t *ch, uint32_t timeout_ms)
{
    uint32_t t = 0;
    while(!(UART_STATUS & UART_STATUS_RX_READY))
    {
        HAL_Delay(1);
        t++;
        if(t >= timeout_ms) return 1; // timeout
    }

    *ch = UART_DATA & 0xFF;
    return 0; // OK
}

void UART_Send(uint8_t ch)
{
    while(!(UART_STATUS & UART_STATUS_TX_READY));
    UART_DATA = ch;
}
