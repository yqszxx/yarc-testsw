#define LED 19

#define _REG32(p, i) (*(volatile unsigned int *) ((p) + (i)))

#define GPIO_CTRL_ADDR 0x10012000UL
#define GPIO_INPUT_EN   (0x04)
#define GPIO_OUTPUT_EN  (0x08)
#define GPIO_OUTPUT_VAL (0x0C)
#define GPIO_IOF_EN     (0x38)
#define GPIO_IOF_SEL    (0x3C)
#define GPIO_REG(offset) _REG32(GPIO_CTRL_ADDR, offset)


#define UART0_CTRL_ADDR 0x10013000UL
#define UART_REG_TXFIFO 0x00
#define UART_REG_RXFIFO 0x04
#define UART_REG_TXCTRL 0x08
#define UART_REG_RXCTRL 0x0c
#define UART_REG_DIV    0x18
#define IOF0_UART0_MASK 0x00030000UL
#define UART_TXEN 0x1
#define UART_RXEN 0x1
#define UART0_REG(offset) _REG32(UART0_CTRL_ADDR, offset)

#define DELAY_FACTOR 7550
void delay(int ms) {
    volatile int i;
    while (ms--) {
        i = DELAY_FACTOR;
        while (i--);
    }
}

void setLED(int state) {
    state &= 0x01;
    GPIO_REG(GPIO_OUTPUT_VAL)  =  (state << LED) ;
}

void init() {
    GPIO_REG(GPIO_INPUT_EN)    &= ~(0x1 << LED) ;
    GPIO_REG(GPIO_OUTPUT_EN)   |=  (0x1 << LED) ;
    setLED(0);

    GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
    UART0_REG(UART_REG_DIV) = 1000; // 57600bps
    UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
    UART0_REG(UART_REG_RXCTRL) |= UART_RXEN;
}

char getchar() {
    unsigned int rxFifo;
    while (1) {
        rxFifo = UART0_REG(UART_REG_RXFIFO);
        if ((rxFifo & 0x80000000) == 0) return rxFifo & 0xFF;
    }
}

void putchar(char c) {
    while (UART0_REG(UART_REG_TXFIFO) & 0x80000000);
    UART0_REG(UART_REG_TXFIFO) = c;
}


void puts(char *s) {
    while (*s != '\0') {
        putchar(*s++);
    }
}

int gets(char *s) {
    int cnt = 0;
    while (1) {
        *s = getchar();
        if (*s == '\n') break;
        s++;
        cnt++;
    }
    s++;
    *s = '\0';
    return cnt;
}

void main() {
    init();
    int i = 0;
    puts("To everyone's suprise, I'm actually running!!!\n");
    while (1) {
        setLED(i);
        delay(1000);
        i = ~i;
        puts(i ? "Ping!\n" : "Pong~\n");
    }
}
