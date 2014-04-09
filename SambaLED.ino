#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h>
#include <RCSwitch.h>


RCSwitch mySwitch = RCSwitch();

// Branchement physique sur la carte
#define LEDPIN 6
#define RFPIN 2

// Liste des instruments
enum {
  AGOGO, SURDO1, SURDO2, SURDO3, CAIXA, REPIQUE,
  CHOCALHO, CUICA, TAMBORIM,
  SURDO2_SMALL, TAMBORIM_SMALL
};

// Choix de l'instrument
#define INSTRU AGOGO

// Forme de l'instrument
#define CIRCULAR 0
#define BAR 1

// Nombre de LED par defaut
#define NB_LED_AGOGO 5
#define NB_LED_CHOCA 7
#define NB_LED_CAIXA 28
#define NB_LED_CUICA 15 // à définir
#define NB_LED_REPIQUE 28
#define NB_LED_SURDO 42
#define NB_LED_TAMBORIM 13

// Nombre de LED exceptionnel
#define NB_LED_SURDO_SMALL 40
#define NB_LED_TAMBORIM_SMALL 12

// Luminosité
#define BRIGHTNESS_SURDO 255
#define BRIGHTNESS_CAIXA 255
#define BRIGHTNESS_REPIQUE 255
#define BRIGHTNESS_CUICA 255
#define BRIGHTNESS_AGOGO 150 // à définir
#define BRIGHTNESS_CHOCA 200 // à définir
#define BRIGHTNESS_TAMBORIM 150 // à définir

// Messages de la télécommande
#define KEY_1 5391
#define KEY_2 5392
#define KEY_3 5393
#define KEY_4 5394
#define KEY_5 5395
#define KEY_6 5396
#define KEY_7 5397
#define KEY_8 5398
#define KEY_9 5399
#define KEY_0 5390
#define KEY_ASTERISK 5910
#define KEY_HASH 5920

// Definition de l'instrument
struct defineInstrument{
  char name;
  int type;
  int nbLED;
  int brightness;
};


void setup()
{
  struct defineInstrument instrument;

  instrument.name = INSTRU;
  switch (INSTRU) {
  case AGOGO:
    instrument.type = BAR;
    instrument.nbLED = NB_LED_AGOGO;
    instrument.brightness = BRIGHTNESS_AGOGO;
    break;
  case SURDO1:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_SURDO;
    instrument.brightness = BRIGHTNESS_SURDO;
    break;
  case SURDO2:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_SURDO;
    instrument.brightness = BRIGHTNESS_SURDO;
    break;
  case SURDO3:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_SURDO;
    instrument.brightness = BRIGHTNESS_SURDO;
    break;
  case CAIXA:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_CAIXA;
    instrument.brightness = BRIGHTNESS_CAIXA;
    break;
  case REPIQUE:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_REPIQUE;
    instrument.brightness = BRIGHTNESS_REPIQUE;
    break;
  case CHOCALHO:
    instrument.type = BAR;
    instrument.nbLED = NB_LED_CHOCA;
    instrument.brightness = BRIGHTNESS_CHOCA;
    break;
  case CUICA:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_CUICA;
    instrument.brightness = BRIGHTNESS_CUICA;
    break;
  case TAMBORIM:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_TAMBORIM;
    instrument.brightness = BRIGHTNESS_TAMBORIM;
    break;
  case SURDO2_SMALL:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_SURDO_SMALL;
    instrument.brightness = BRIGHTNESS_SURDO;
    break;
  case TAMBORIM_SMALL:
    instrument.type = CIRCULAR;
    instrument.nbLED = NB_LED_TAMBORIM_SMALL;
    instrument.brightness = BRIGHTNESS_TAMBORIM;
    break;
  default:
    instrument.type = BAR;
    instrument.nbLED = 1;
    instrument.brightness = 100;
    break;
  }


  // Définition du bandeau de LED
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(instrument.nbLED, LEDPIN, NEO_GRB + NEO_KHZ800);

  // Définition des couleurs utilisées
  uint32_t sambaColor[3] = {
    strip.Color(120, 130, 18),
    strip.Color(255, 44, 15),
    strip.Color(30, 120, 200)
  };

  uint32_t off = strip.Color(0,0,0);


  //Serial.begin(9600);
  //Serial.println("Script Led");

  // Initialiser NeoPixel
  strip.begin();
  strip.setBrightness(instrument.brightness);

  // Initialiser Communication RF
  mySwitch.enableReceive(0);

}

void loop()
{
}
