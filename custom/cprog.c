extern volatile int GPIO;
extern volatile int UART[];

void setGPIO(int s) {
    GPIO = s;
}

void main() {
    int recv;
    while (1) {
        while (!(UART[0] & 0x01)); // wait for data
        UART[0] = 0;
        UART[0] = 0;
        recv = UART[1];
        setGPIO(recv);
        UART[2] = '0' + recv;
        UART[0] = 0x02;
        while (UART[0] & 0x02); // wait for tx done
    }
}
