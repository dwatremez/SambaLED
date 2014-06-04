#include <Adafruit_NeoPixel.h>
#include <RCSwitch.h>
#include <Keypad.h>

// Messages de la télécommande
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 7
#define KEY_8 8
#define KEY_9 9
#define KEY_0 10
#define KEY_ASTERISK 11
#define KEY_HASH 12

// Émetteur RF
RCSwitch mySwitch;
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  { '#','0','*'  } ,
  { '9','8','7'  },
  { '6','5','4'  },
  { '3','2','1'  }
};
byte rowPins[rows] = {5,4,3,2}; //connect to the row pinouts of the keypad
byte colPins[cols] = {8,7,6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

uint16_t indexLED;
uint8_t mode;
uint8_t modeInformation;
uint8_t keyValue;

void setup() {
  mySwitch = RCSwitch();
  mySwitch.enableTransmit(12); // active l'émission de messages sur le pin 12
  mySwitch.setRepeatTransmit(1);
  indexLED = 0;
  mode = 0;
  modeInformation = 0;
  keyValue = 0;
}

void loop() {
  uint8_t tmpKeyValue;
  char keyController = keypad.getKey();
  if (keyController) { // Check for a valid key.
    tmpKeyValue = 0;
    switch (keyController) {
    case '0':
      tmpKeyValue = KEY_0;
      break;
    case '1':
      tmpKeyValue = KEY_1;
      break;
    case '2':
      tmpKeyValue = KEY_2;
      break;
    case '3':
      tmpKeyValue = KEY_3;
      break;
    case '4':
      tmpKeyValue = KEY_4;
      break;
    case '5':
      tmpKeyValue = KEY_5;
      break;
    case '6':
      tmpKeyValue = KEY_6;
      break;
    case '7':
      tmpKeyValue = KEY_7;
      break;
    case '8':
      tmpKeyValue = KEY_8;
      break;
    case '9':
      tmpKeyValue = KEY_9;
      break;
    case '*':
      tmpKeyValue = KEY_ASTERISK;
      break;
    case '#':
      modeInformation = (modeInformation+1)%2;
      break;
    default:
      break;
    }
    if (tmpKeyValue!=0) {
      if ((keyValue==KEY_8) && (mode==1) && (tmpKeyValue==KEY_8)) {
        // Note : le break intro Vila Isabel (mode 1 + touche 8) nécessite un changement de la sémantique de "indexLED"
        indexLED = indexLED+1;
      }
      else {
        keyValue = tmpKeyValue;
        indexLED = 0;
        mode = modeInformation;
      }
    }
  }
  else {
    if ((keyValue!=KEY_8) || (mode!=1)) {
      // Note : le break intro Vila Isabel (mode 1 + touche 8) nécessite un changement de la sémantique de "indexLED"
      indexLED = indexLED+1;
    }
  }
  sendPeriodicInfo();
//  delay(300);
//  attendre();
}

void sendPeriodicInfo() {
  // Note: is the API able to send more than 15 bytes correctly? it seems that the radioValue is considered to be 16 signed bits (and everything gets messy if the 16-th bit is 1)
  uint32_t radioValue = (modeInformation<<14) + (mode<<13) + ((keyValue%16)<<9) + (indexLED%512); // 15 bits: 1 modeInformation + 1 mode + 4 keyValue + 10 indexLED
  mySwitch.send(radioValue, 24);
}

void attendre() {
  // TODO
}

