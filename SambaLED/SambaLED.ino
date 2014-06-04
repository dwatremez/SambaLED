#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h>
#include <RCSwitch.h>

#define LEDPIN 6
#define RFPIN 2

// Liste des instruments
enum {
  AGOGO, SURDO1, SURDO2, SURDO3, CAIXA, REPIQUE, CHOCALHO, CUICA, TAMBORIM,
};

enum {
  BARRE, CERCLE,
};

enum {
  ANIM_MANGUEIRA, ANIM_BRASIL, ANIM_GIRLS, ANIM_GEO, ANIM_DRUMS, ANIM_SAMBAGOGO, ANIM_CHARLIE, ANIM_ONE_COLOR,
};

// Nombre de LED par defaut (pour info)
// AGOGO 5
// CHOCA 7
// CAIXA 28
// CUICA 15 // à définir
// REPIQUE 28
// SURDO 42 ou 40 (petit)
// TAMBORIM 13 ou 12 (petit)

// Choix de l'instrument
#define NBPIX 28
#define LINE 1

#define BRIGHTNESS_SURDO 255
#define BRIGHTNESS_CAIXA 255
#define BRIGHTNESS_REPIQUE 255
#define BRIGHTNESS_CUICA 255
#define BRIGHTNESS_AGOGO 120
#define BRIGHTNESS_CHOCA 200
#define BRIGHTNESS_TAMBORIM 120

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

struct defineInstrument {
  // manual setup
  uint8_t name;
  uint8_t nbLED;
  uint8_t ligne;
  uint8_t gauche;
  uint8_t charlie;
  uint8_t leader;
  // automatic setup
  uint8_t type;
};

// Variables globales
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NBPIX, LEDPIN, NEO_GRB + NEO_KHZ800);
RCSwitch mySwitch = RCSwitch();
struct defineInstrument instrument;

uint16_t indexLED = 0;
uint16_t indexShift = 0;
uint8_t modeInformation;
uint8_t mode;
uint8_t previousAnimation;
uint16_t currentModulo;

uint32_t colorWhite = strip.Color(255, 255, 255);
uint32_t colorRed = strip.Color(255, 44, 15);
uint32_t colorBlue = strip.Color(44,28,255);
uint32_t colorAzur = strip.Color(30, 120, 200);
uint32_t colorGreen = strip.Color(0, 255, 0);
uint32_t colorEmeraud = strip.Color(1, 215, 88);
uint32_t colorFuchsia = strip.Color(255, 62, 150);
uint32_t colorCuisseDeNimpheEmue = strip.Color(255, 105, 180);
uint32_t colorYellow = strip.Color(255, 255, 0); 
uint32_t colorCarrot = strip.Color(244, 102, 27);
uint32_t colorArgent = strip.Color(214, 205, 196);
uint32_t colorOff = strip.Color(0, 0, 0);
uint8_t indexColor = 0;
uint32_t geoColor[3];
uint32_t charlieColors[2] = {
  colorRed,
  colorWhite
};

void setup() {
  // manual setup
  instrument.name = CAIXA;
  instrument.nbLED = NBPIX;
  instrument.ligne = 1;
  instrument.gauche = 1;
  instrument.charlie = 0;
  instrument.leader = 1;
  // automatic setup
  indexLED = 0;
  modeInformation = 0;
  mode = 0;
  previousAnimation = 0;
  currentModulo = 1;
  switch (instrument.name) {
  case AGOGO:
    instrument.type = BARRE;
    break;
  case SURDO1:
    instrument.type = CERCLE;
    break;
  case SURDO2:
    instrument.type = CERCLE;
    break;
  case SURDO3:
    instrument.type = CERCLE;
    break;
  case CAIXA:
    instrument.type = CERCLE;
    break;
  case REPIQUE:
    instrument.type = CERCLE;
    break;
  case CHOCALHO:
    instrument.type = BARRE;
    break;
  case CUICA:
    instrument.type = CERCLE;
    break;
  case TAMBORIM:
    instrument.type = CERCLE;
    break;
  default:
    instrument.type = BARRE;
    instrument.nbLED = 1;
    break;
  }
  strip.begin();
  mySwitch.enableReceive(0);
}

int toggle;

void loop() {
  listenRF();
}

