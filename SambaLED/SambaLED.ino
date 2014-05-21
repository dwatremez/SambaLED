#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h>
#include <RCSwitch.h>

#define DEBUG 0

// Branchement physique sur la carte
#define LEDPIN 6
#define RFPIN 2

// Liste des instruments
enum {
  AGOGO, SURDO1, SURDO2, SURDO3, CAIXA, REPIQUE,
  CHOCALHO, CUICA, TAMBORIM,
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
#define INSTRU CAIXA
#define NBPIX 28

// Forme de l'instrument
#define BAR 0
#define CIRCULAR 1
#define BIG_CIRCULAR 2


// Luminosité
#define BRIGHTNESS_SURDO 255
#define BRIGHTNESS_CAIXA 255
#define BRIGHTNESS_REPIQUE 255
#define BRIGHTNESS_CUICA 255
#define BRIGHTNESS_AGOGO 120
#define BRIGHTNESS_CHOCA 200
#define BRIGHTNESS_TAMBORIM 120

// Emplacement général du percussioniste (devant, milieu, derrière)
#define FIRST 0
#define BETWEEN 1
#define LAST 2

// Messages de la télécommande
#define KEY_1 6918
#define KEY_2 6833
#define KEY_3 6748
#define KEY_4 6663
#define KEY_5 6578
#define KEY_6 6493
#define KEY_7 6308
#define KEY_8 6223
#define KEY_9 6138
#define KEY_0 6053
#define KEY_ASTERISK 5970
#define KEY_HASH 5380

// Paramètres de l'instrument
struct defineInstrument{
  char name;
  int type;
  int nbLED;
  int brightness;
  int place;
  int lenght;
  int delayCoef;
};

// Variables globales
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NBPIX, LEDPIN, NEO_GRB + NEO_KHZ800);
RCSwitch mySwitch = RCSwitch();
struct defineInstrument instrument;
uint16_t indexLED = 0;
uint8_t animStep = 1;
uint16_t script[2]; // les nouveaux et anciens scripts (ordre défini par indexScript)
uint8_t indexScript = 1;
uint32_t animDelay = 1000;
uint8_t animDirection = 0;
uint8_t animVariation = 0; // variable pour les variations dans les animations

// Définition des couleurs utilisées

#define NBCOLOR 10

uint32_t sambaWhite = strip.Color(255, 255, 255);
uint32_t sambaRed = strip.Color(255, 44, 15);
uint32_t sambaBlue = strip.Color(44,28,255);
uint32_t sambaAzur = strip.Color(30, 120, 200);
uint32_t sambaGreen = strip.Color(0, 255, 0);
uint32_t sambaEmeraud = strip.Color(1,215,88);
uint32_t sambaFuchsia = strip.Color(255, 62, 150);
uint32_t sambaCuisseDeNimpheEmue = strip.Color(255,105,180);
uint32_t sambaYellow = strip.Color(255,255,0); 
uint32_t sambaCarrot = strip.Color(244,102,27);
uint32_t sambaColors[NBCOLOR] = {
  sambaFuchsia,
  sambaYellow,
  sambaBlue,
  sambaCarrot,  
  sambaEmeraud,
  sambaCuisseDeNimpheEmue,
  sambaAzur,
  sambaWhite,
  sambaRed,
  sambaGreen
};
uint32_t off = strip.Color(0,0,0);
uint8_t indexColor = 0;

uint32_t geoColor[3];


void setup()
{
  // Pour debug
  if(DEBUG)
  {
    Serial.begin(9600);
    Serial.println("Script Led");
  }

  // Définition de l'instrument
  instrument.name = INSTRU;
  instrument.nbLED = NBPIX;
  switch (INSTRU) 
  {
  case AGOGO:
    instrument.type = BAR;
    instrument.brightness = BRIGHTNESS_AGOGO;
    instrument.place = FIRST;
    break;
  case SURDO1:
    instrument.type = BIG_CIRCULAR;
    instrument.brightness = BRIGHTNESS_SURDO;
    instrument.place = LAST;
    break;
  case SURDO2:
    instrument.type = BIG_CIRCULAR;
    instrument.brightness = BRIGHTNESS_SURDO;
    instrument.place = LAST;
    break;
  case SURDO3:
    instrument.type = BIG_CIRCULAR;
    instrument.brightness = BRIGHTNESS_SURDO;
    instrument.place = LAST;
    break;
  case CAIXA:
    instrument.type = CIRCULAR;
    instrument.brightness = BRIGHTNESS_CAIXA;
    instrument.place = BETWEEN;
    break;
  case REPIQUE:
    instrument.type = CIRCULAR;
    instrument.brightness = BRIGHTNESS_REPIQUE;
    instrument.place = BETWEEN;
    break;
  case CHOCALHO:
    instrument.type = BAR;
    instrument.brightness = BRIGHTNESS_CHOCA;
    instrument.place = FIRST;
    break;
  case CUICA:
    instrument.type = CIRCULAR;
    instrument.brightness = BRIGHTNESS_CUICA;
    instrument.place = BETWEEN;
    break;
  case TAMBORIM:
    instrument.type = CIRCULAR;
    instrument.brightness = BRIGHTNESS_TAMBORIM;
    instrument.place = FIRST;
    break;
  default:
    instrument.type = BAR;
    instrument.nbLED = 1;
    instrument.brightness = 100;
    break;
  }

  instrument.lenght = ceil(instrument.nbLED/5);   
  instrument.delayCoef = 0.5 + 0.25 * instrument.type * (1 + instrument.type);

  // Initialiser NeoPixel
  strip.begin();

  // Initialiser Communication RF
  mySwitch.enableReceive(0);

  // Démarrage avec 5 flashs
  stripStart(5);


}

void stripStart(uint8_t nb)
{
  for(uint8_t start = 0; start < nb; start ++)
  {
    strip.setPixelColor(0, 255,0,0);
    strip.setPixelColor(floor(instrument.nbLED / 4), 255,0,0);
    strip.setPixelColor(floor(instrument.nbLED / 2), 255,0,0);
    strip.setPixelColor(floor(instrument.nbLED / 4 * 3), 255,0,0);
    strip.show();
    delay(200);
    strip.show();
    strip.setPixelColor(0, off);
    strip.setPixelColor(floor(instrument.nbLED / 4), off);
    strip.setPixelColor(floor(instrument.nbLED / 2), off);
    strip.setPixelColor(floor(instrument.nbLED / 4 * 3), off);
    strip.show();
    delay(200);
    strip.show();
  }

  // Définir le premier script à effectuer
  script[0] = KEY_3;
  script[1] = 0;

}

void listenRF()
{
  if(mySwitch.available())
  {
    int value = mySwitch.getReceivedValue();
    if(value == 0)
    {
      if(DEBUG)
        Serial.print("Unknown encoding");
    }
    else
    {
      if(DEBUG)
      {
        Serial.print("Received ");
        Serial.print(mySwitch.getReceivedValue());
        Serial.print(" / ");
        Serial.print(mySwitch.getReceivedBitlength());
        Serial.print("bit ");
        Serial.print("Protocol: ");
        Serial.println(mySwitch.getReceivedProtocol());
      }
      switch(value)
      {
      default :
        if(DEBUG)
          Serial.println("Unknown message");
        break;
      case KEY_ASTERISK:
        break;	// Les pulses plus tard
      case KEY_HASH:
        break;	// Les pulses plus tard
      case KEY_0:
      case KEY_1:
      case KEY_2:
      case KEY_3:
      case KEY_4:
      case KEY_5:
      case KEY_6:
      case KEY_7:
      case KEY_8:
      case KEY_9:
        if(value != script[0] && value != script[1])
        {
          // Définir le nouveau script à partir du message
          script[indexScript] = value;
          indexScript = (indexScript +1)%2;
          
          // Initialiser les variables d'animation et de direction au changement de script
          animVariation = 0;
          animDirection = 0;
        }
        break;
      }
    }
  }
}


void loop()
{
  // Écouter messages radio
  listenRF(); 

  // Jouer les 2 scripts enregistrés
  playScript(script[0]);
  playScript(script[1]);	

  // Mise à jour du bandeau
  strip.setBrightness(instrument.brightness);
  strip.show();

  // Attente entre deux intérations de l'animation
  delay(instrument.delayCoef * (int)(animDelay/instrument.nbLED));


  // Se placer sur la LED suivante
  indexLED = indexLED + animStep;

  // Fin de bandeau
  if(indexLED >= instrument.nbLED)
  {
    if(DEBUG) // Affichage scripts en cours
    {
      Serial.print("S1 = ");
      Serial.print(script[0]);
      Serial.print(" ------------- S2 = ");
      Serial.println(script[2]);
    }

    indexLED = 0; // retour au début du bandeau

    if(script[0] != 0 && script[1] != 0)
      script[indexScript] = 0;	// arrêter le précédent script en fin de boucle		
  }

}





