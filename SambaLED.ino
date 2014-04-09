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
  SURDO2_PETIT, TAMBORIM_PETIT
};

// Choix de l'instrument
#define INSTRU AGOGO

// Forme de l'instrument
#define TYPE_INSTRUMENT_ROND 0
#define TYPE_INSTRUMENT_DROIT 1

// Nombre de LED par defaut
#define NOMBRE_LEDS_AGOGO 5
#define NOMBRE_LEDS_CHOCA 7
#define NOMBRE_LEDS_CAIXA 28
#define NOMBRE_LEDS_CUICA 15 // à définir
#define NOMBRE_LEDS_REPIQUE 28
#define NOMBRE_LEDS_SURDO 42
#define NOMBRE_LEDS_TAMBORIM 13

// Nombre de LED exceptionnel
#define NOMBRE_LEDS_SURDO_PETIT 40
#define NOMBRE_LEDS_TAMBORIM_PETIT 12

// Luminosité
#define LUM_SURDO 255
#define LUM_CAIXA 255
#define LUM_REPIQUE 255
#define LUM_CUICA 255
#define LUM_AGOGO 150 // à définir
#define LUM_CHOCA 200 // à définir
#define LUM_TAMBORIM 150 // à définir

// Messages de la télécommande
#define TOUCHE_1 5391
#define TOUCHE_2 5392
#define TOUCHE_3 5393
#define TOUCHE_4 5394
#define TOUCHE_5 5395
#define TOUCHE_6 5396
#define TOUCHE_7 5397
#define TOUCHE_8 5398
#define TOUCHE_9 5399
#define TOUCHE_0 5390
#define TOUCHE_ETOILE 5910
#define TOUCHE_DIESE 5920

// Definition de l'instrument
struct caracInstrument{
  char nom;
  int type;
  int nbLED;
  int lum;
};


void setup()
{
  struct caracInstrument instrument;

  instrument.nom = INSTRU;
  switch (INSTRU) {
  case AGOGO:
    instrument.type = TYPE_INSTRUMENT_DROIT;
    instrument.nbLED = NOMBRE_LEDS_AGOGO;
    instrument.lum = LUM_AGOGO;
    break;
  case SURDO1:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_SURDO;
    instrument.lum = LUM_SURDO;
    break;
  case SURDO2:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_SURDO;
    instrument.lum = LUM_SURDO;
    break;
  case SURDO3:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_SURDO;
    instrument.lum = LUM_SURDO;
    break;
  case CAIXA:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_CAIXA;
    instrument.lum = LUM_CAIXA;
    break;
  case REPIQUE:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_REPIQUE;
    instrument.lum = LUM_REPIQUE;
    break;
  case CHOCALHO:
    instrument.type = TYPE_INSTRUMENT_DROIT;
    instrument.nbLED = NOMBRE_LEDS_CHOCA;
    instrument.lum = LUM_CHOCA;
    break;
  case CUICA:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_CUICA;
    instrument.lum = LUM_CUICA;
    break;
  case TAMBORIM:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_TAMBORIM;
    instrument.lum = LUM_TAMBORIM;
    break;
  case SURDO2_PETIT:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_SURDO_PETIT;
    instrument.lum = LUM_SURDO;
    break;
  case TAMBORIM_PETIT:
    instrument.type = TYPE_INSTRUMENT_ROND;
    instrument.nbLED = NOMBRE_LEDS_TAMBORIM_PETIT;
    instrument.lum = LUM_TAMBORIM;
    break;
  default:
    instrument.type = TYPE_INSTRUMENT_DROIT;
    instrument.nbLED = 1;
    instrument.lum = 100;
    break;
  }


  // Définition du bandeau de LED
  Adafruit_NeoPixel bande = Adafruit_NeoPixel(instrument.nbLED, LEDPIN, NEO_GRB + NEO_KHZ800);

  // Définition des couleurs utilisées
  uint32_t sambaColor[3] = {
    bande.Color(120, 130, 18),
    bande.Color(255, 44, 15),
    bande.Color(30, 120, 200)
  };

  uint32_t off = bande.Color(0,0,0);


  //Serial.begin(9600);
  //Serial.println("Script Led");

  // Initialiser NeoPixel
  bande.begin();
  bande.setBrightness(instrument.lum);

  // Initialiser Communication RF
  mySwitch.enableReceive(0);

}

void loop()
{
}
