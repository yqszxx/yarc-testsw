extern volatile int GPIO;

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
        } else {
            i++;
        }
    }
}
