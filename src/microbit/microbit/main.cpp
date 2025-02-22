#include "MicroBit.h"

MicroBit uBit;

void onButtonA(MicroBitEvent e){
    uBit.serial.printf("Completed\n");
}

int main() {
    uBit.init();  
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    while (true) {
        ManagedString incomingData = uBit.serial.readUntil('\n');  
        uBit.display.scroll(incomingData); 
        uBit.sleep(50);
    }

    release_fiber();
}
