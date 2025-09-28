#ifndef __SN34F78X_HAL_GPIO_H
#define __SN34F78X_HAL_GPIO_H

#include <stdint.h>
#include <string.h>

/* ---------- Basic types / status ---------- */
typedef enum {
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_Status_T;

/* ---------- GPIO pin defines (0..31) ---------- */
#define GPIO_PIN_0   (1UL << 0)
#define GPIO_PIN_1   (1UL << 1)
#define GPIO_PIN_2   (1UL << 2)
#define GPIO_PIN_3   (1UL << 3)
#define GPIO_PIN_4   (1UL << 4)
#define GPIO_PIN_5   (1UL << 5)
#define GPIO_PIN_6   (1UL << 6)
#define GPIO_PIN_7   (1UL << 7)
#define GPIO_PIN_8   (1UL << 8)
#define GPIO_PIN_9   (1UL << 9)
#define GPIO_PIN_10  (1UL << 10)
#define GPIO_PIN_11  (1UL << 11)
#define GPIO_PIN_12  (1UL << 12)
#define GPIO_PIN_13  (1UL << 13)
#define GPIO_PIN_14  (1UL << 14)
#define GPIO_PIN_15  (1UL << 15)
#define GPIO_PIN_16  (1UL << 16)
#define GPIO_PIN_17  (1UL << 17)
#define GPIO_PIN_18  (1UL << 18)
#define GPIO_PIN_19  (1UL << 19)
#define GPIO_PIN_20  (1UL << 20)
#define GPIO_PIN_21  (1UL << 21)
#define GPIO_PIN_22  (1UL << 22)
#define GPIO_PIN_23  (1UL << 23)
#define GPIO_PIN_24  (1UL << 24)
#define GPIO_PIN_25  (1UL << 25)
#define GPIO_PIN_26  (1UL << 26)
#define GPIO_PIN_27  (1UL << 27)
#define GPIO_PIN_28  (1UL << 28)
#define GPIO_PIN_29  (1UL << 29)
#define GPIO_PIN_30  (1UL << 30)
#define GPIO_PIN_31  (1UL << 31)

#define GPIO_PIN_LOW  0U
#define GPIO_PIN_HIGH 1U

/* ---------- GPIO modes (simple mapping) ---------- */
#define GPIO_MODE_INPUT      0x00U
#define GPIO_MODE_OUTPUT     0x01U  /* LSB=1 => output in driver code */
#define GPIO_MODE_IT_RISING  0x02U
#define GPIO_MODE_IT_FALLING 0x04U
#define GPIO_MODE_IT_BOTH    (GPIO_MODE_IT_RISING | GPIO_MODE_IT_FALLING)
#define GPIO_MODE_EVT_HIGH   0x08U
#define GPIO_MODE_EVT_LOW    0x09U

/* ---------- Pull / drive ---------- */
#define GPIO_PULL_NONE 0x00U
#define GPIO_PULL_UP   0x01U
#define GPIO_PULL_DOWN 0x02U

#define GPIO_DRIVE_LEVEL0 0x00U
#define GPIO_DRIVE_LEVEL1 0x01U

/* ---------- Helper checks (minimal) ---------- */
#define ASSERT_PARAM(expr) ((void)0)
#define IS_GPIO_ALL_INSTANCE(gpio) (1)
#define IS_GPIO_PIN(gpio, pin) ((pin) != 0)
#define IS_GPIO_MODE(mode) (1)
#define IS_GPIO_PULL(p) (1)
#define IS_GPIO_CLOCK_MODE(x) (1)
#define IS_GPIO_PIN_STATE_LOW(datain, pin) (((datain) & (pin)) == 0)
#define IS_GPIO_PULL_INACTIVE(p) ((p) == GPIO_PULL_NONE)
#define IS_GPIO_PULL_ENABLE(p) ((p) != GPIO_PULL_NONE)
#define IS_GPIO_IRQ_TRIGGER(x) ( (x) == 0 ? 0 : 1 )

/* ---------- Simple register access macros (stub) ---------- */
#define HAL_REG_READ(reg) (reg)
#define HAL_REG_WRITE(reg, val) ((reg) = (val))
#define HAL_REG_SBIT(reg, val) ((reg) |= (val))
#define HAL_REG_CBIT(reg, val) ((reg) &= ~(val))

#define HAL_ENABLE  1U
#define HAL_DISABLE 0U
#define RET_FLAG_LACK(a,b,r) ( ( (a) & (b) ) ? 0 : 0 )

/* ---------- Minimal GPIO register struct (stub) ---------- */
typedef struct {
    volatile uint32_t DATAIN;
    volatile uint32_t DATAOUT;
    volatile uint32_t DIR;
    volatile uint32_t BSET;
    volatile uint32_t BCLR;
    volatile uint32_t PULLEN;
    volatile uint32_t PUTYPE;
    volatile uint32_t CLKMODE;
    volatile uint32_t RIS_RF;
    volatile uint32_t IC;
    volatile uint32_t IE;
    volatile uint32_t IMASKEN;
    volatile uint32_t ITRIG;
    volatile uint32_t IBETRIG;
    volatile uint32_t IRFTRIG;
    volatile uint32_t BNEN;
    volatile uint32_t BNCLKPRE;
} SN_GPIO_Regs;

/* SN_GPIO_Type in SDK is used like a pointer to GPIO register block */
typedef SN_GPIO_Regs *SN_GPIO_Type;

/* Provide dummy base addresses so code can use SN_GPIO1 etc. Adjust if you have real addresses */
#define SN_GPIO0 ((SN_GPIO_Type)0x40010000U)
#define SN_GPIO1 ((SN_GPIO_Type)0x40011000U)
#define SN_GPIO2 ((SN_GPIO_Type)0x40012000U)
#define SN_GPIO3 ((SN_GPIO_Type)0x40013000U)

/* ---------- small structs referenced in .c (minimal) ---------- */
typedef struct {
    uint32_t instance;
    uint8_t offset;
    uint32_t desc;
} AFIO_Info_T;

typedef struct {
    uint32_t pin;
    uint32_t mode;
    uint32_t pull;
    uint32_t drive;
} GPIO_Init_T;

typedef struct {
    uint32_t index;
    uint32_t mask;
} GPIO_PnSTR_T;

/* Minimal SN_SCU stub used by HAL_GPIO_ReleaseOutput */
typedef struct {
    struct {
        uint32_t GPIO_HOLD;
    } BTUP_STS_b;
} SN_SCU_Type;
extern SN_SCU_Type *SN_SCU;

/* ---------- Function prototypes (implemented in sn34f78x_hal_gpio.c) ---------- */
HAL_Status_T HAL_GPIO_Init(SN_GPIO_Type gpio, GPIO_Init_T *gpio_init);
HAL_Status_T HAL_GPIO_DeInit(SN_GPIO_Type gpio, uint32_t gpio_pin);
uint32_t     HAL_GPIO_ReadPin(SN_GPIO_Type gpio, uint32_t gpio_pin);
HAL_Status_T HAL_GPIO_WritePin(SN_GPIO_Type gpio, uint32_t gpio_pin, uint32_t pin_state);
HAL_Status_T HAL_GPIO_TogglePin(SN_GPIO_Type gpio, uint32_t gpio_pin);
HAL_Status_T HAL_GPIO_ChangeClockMode(SN_GPIO_Type gpio, uint32_t clock_mode);
HAL_Status_T HAL_GPIO_ConfigDebounce(SN_GPIO_Type gpio, uint32_t gpio_pin, uint32_t deb_en, uint32_t deb_pre);
HAL_Status_T HAL_GPIO_ReleaseOutput(void);
HAL_Status_T HAL_GPIO_SetAFIO(SN_GPIO_Type gpio, uint32_t gpio_pin, uint16_t option);
HAL_Status_T HAL_GPIO_GetAFIO(SN_GPIO_Type gpio, uint32_t gpio_pin, uint16_t *option);
void         HAL_GPIO_IRQHandler(SN_GPIO_Type gpio);
void         HAL_GPIO_Callback(SN_GPIO_Type gpio, uint32_t gpio_pin);

#endif /* __SN34F78X_HAL_GPIO_H */
