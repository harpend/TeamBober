#include "MicroBit.h"

MicroBit uBit;

void onButtonA(MicroBitEvent e){
    uBit.serial.printf("Completed\n");
}

void onButtonB(MicroBitEvent e){
    uBit.serial.printf("Rejected\n");
}

int main() {
    uBit.init();  
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    while (true) {
        ManagedString incomingData = uBit.serial.readUntil('\n');  
        uBit.display.scroll(incomingData); 
        uBit.sleep(50);
    }

    release_fiber();
}
