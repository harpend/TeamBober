#include "MicroBit.h"

MicroBit uBit;

static Pin *pin = NULL;
static uint8_t pitchVolume = 0xff;


void playNotifySound() {
    NRF_P0->PIN_CNF[MICROBIT_PIN_SPEAKER] = 1;
    int freq = 200;
    for (int i = 0; i < 2; i++) {
        freq = 200;
        int v = 1 << (pitchVolume >> 5);
        pin->setAnalogValue(v);
        pin->setAnalogPeriodUs(1000000/freq);
        uBit.sleep(400);
        freq = 500;
        v = 1 << (pitchVolume >> 5);
        pin->setAnalogValue(v);
        pin->setAnalogPeriodUs(1000000/freq);
        uBit.sleep(400);
    }
    
    pin->setAnalogValue(0);
}

void playSwooshSound() {
    NRF_P0->PIN_CNF[MICROBIT_PIN_SPEAKER] = 1;
    int freq = 200;
    for (int i = 0; i < 20; i++) {
        freq = freq + (20 * i);
        int v = 1 << (pitchVolume >> 5);
        pin->setAnalogValue(v);
        pin->setAnalogPeriodUs(1000000/freq);
        uBit.sleep(50);
    }
    
    pin->setAnalogValue(0);
}

void onButtonA(MicroBitEvent e){
    playSwooshSound();
    uBit.serial.printf("Completed\n");
}

void onButtonB(MicroBitEvent e){
    uBit.audio.setVolume(255);
    uBit.audio.soundExpressions.play("sad");
    uBit.serial.printf("Rejected\n");
}

int main() {
    uBit.init();  
    pin = &uBit.audio.virtualOutputPin;
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    while (true) {
        ManagedString incomingData = uBit.serial.readUntil('\n');  
        if (incomingData.length() >0) {
            playNotifySound();
        }
        uBit.display.scroll(incomingData); 
        uBit.sleep(50);
    }

    release_fiber();
}
