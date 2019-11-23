extern volatile int GPIO;
extern volatile int UART[];

void setGPIO(int s) {
    GPIO = s;
}

void main() {
    int i = 0, state = 0;
    while (1) {
        if (i == 457143) {
            i = 0;
            state = ~state;
            setGPIO(state);
            UART[2] = '6';
            UART[0] = 0x02;
        } else {
            i++;
        }
    }
}
