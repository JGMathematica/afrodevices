#pragma once

#define UART_BUFFER_SIZE    64

#define UART1_RX_BUFFER_SIZE    256
#define UART1_TX_BUFFER_SIZE    256
#define UART2_RX_BUFFER_SIZE    128
#define UART2_TX_BUFFER_SIZE    64
#define MAX_SERIAL_PORTS        2

// This is a bitmask
typedef enum portmode_t {
    MODE_RX = 1,
    MODE_TX = 2,
    MODE_RXTX = 3
} portmode_t;

typedef struct {
    uint32_t baudRate;
    uint32_t rxBufferSize;
    uint32_t txBufferSize;
    volatile uint8_t *rxBuffer;
    volatile uint8_t *txBuffer;
    uint32_t rxDMAPos;
    uint32_t rxBufferHead;
    uint32_t rxBufferTail;
    uint32_t txBufferHead;
    uint32_t txBufferTail;

    DMA_Channel_TypeDef *rxDMAChannel;
    DMA_Channel_TypeDef *txDMAChannel;
    uint32_t rxDMAIrq;
    uint32_t txDMAIrq;
    bool txDMAEmpty;
    USART_TypeDef *USARTx;

    uartReceiveCallbackPtr callback;
    portmode_t mode;
} serialPort_t;

extern serialPort_t serialPort1;
extern serialPort_t serialPort2;

serialPort_t *uartOpen(USART_TypeDef *USARTx, uartReceiveCallbackPtr callback, uint32_t baudRate, portmode_t mode);
void uartChangeBaud(serialPort_t *s, uint32_t baudRate);
bool isUartAvailable(serialPort_t *s);
bool isUartTransmitEmpty(serialPort_t *s);
uint8_t uartRead(serialPort_t *s);
void uartWrite(serialPort_t *s, uint8_t ch);
void uartPrint(serialPort_t *s, const char *str);
