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
#define INSTRU TAMBORIM
#define NBPIX 12

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
uint8_t varAnimation = 0; // variable pour les variations dans les animations

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
        }
        break;
      }
    }
  }
}

void playScript(uint16_t s)
{
  switch(s)
  {
  default:
    break;
  case KEY_0:
    colorFull(off);
    break;
  case KEY_1:
    Mangueira();
    break;
  case KEY_2:
    Girls();
    break;
  case KEY_3:
    Brasil();
    break;
  case KEY_4:
    Geo(1);
    break;
  case KEY_5:
    Geo(3);
    break;
  case KEY_6:
    Geo(9);
    break;
  case KEY_7:
    Drums();
    break;
  case KEY_8:
    Sambagogo();
    break;
  case KEY_9:
    Wave();
    break;
  case KEY_ASTERISK:
    break;
  case KEY_HASH:
    break;
  }
}

// Animations
void colorFull(uint32_t c)
{
  for(uint16_t i = 0; i < instrument.nbLED; i++)
  {
    strip.setPixelColor(i,c);
  }
}

void colorWipe(uint32_t c) 
{
  if(indexLED < instrument.nbLED) {
    strip.setPixelColor(indexLED, c); 
  }
  else 
  {
    strip.setPixelColor(instrument.nbLED + indexLED, c); 
  }
}

void colorPathForward(uint32_t cp, uint32_t cr, uint8_t l)
{
  // LED PATH
  if(indexLED < instrument.nbLED)
  {
    strip.setPixelColor(indexLED, cp);
  }
  else
  {
    strip.setPixelColor(instrument.nbLED + indexLED, cp);
  }

  // LED REMAIN
  if(indexLED >= l)
  {
    strip.setPixelColor(indexLED - l, cr);
  }
  else
  {
    strip.setPixelColor(instrument.nbLED + indexLED - l, cr);
  }
}

void colorPathBackward(uint32_t cp, uint32_t cr, uint8_t l)
{
  // LED PATH
  if(indexLED <= instrument.nbLED)
  {
    strip.setPixelColor(instrument.nbLED - indexLED - 1, cp);	
  }
  else
  {
    strip.setPixelColor(2 * instrument.nbLED - indexLED, cp);
  }

  // LED REMAIN
  if(indexLED >= l + 1)
  {
    strip.setPixelColor(instrument.nbLED - indexLED + l, cr);
  }
  else
  {
    strip.setPixelColor(l - indexLED, cr);
  }
}

void colorPathBackForth(uint32_t cp, uint32_t cr, uint8_t l)
{
  if(animDirection == 0)
  {
    colorPathForward(cp,cr,l);
    if(indexLED == instrument.nbLED - 1)
      animDirection = 1;
  }
  else
  {
    colorPathBackward(cp,cr,l);
    if(indexLED == instrument.nbLED - 1)
      animDirection = 0;		
  }

}

void colorGauge(uint32_t c)
{
  colorGauge(c,c);
}
void colorGauge(uint32_t cp, uint32_t cr)
{	
  if(animDirection == 0)
  {
    colorPathForward(cp,cp,instrument.nbLED);
    if(indexLED == instrument.nbLED - 1)
      animDirection = 1;
  }
  else
  {
    colorPathBackward(cr,cr,instrument.nbLED);
    if(indexLED == instrument.nbLED - 1)
      animDirection = 0;		
  }

}


// Changement de couleurs
uint32_t oneColorEach(uint8_t nb)
{
  if(indexLED%nb == 0)
    indexColor++;

  if(indexColor >= NBCOLOR)
    indexColor = 0;

  return sambaColors[indexColor];

}

uint32_t oneColorEachLoop()
{
  return oneColorEach(instrument.nbLED);
}

uint8_t changeAfterSomeSurdoRevolutions(uint8_t nb, uint8_t rev)
{
  if(indexLED == instrument.nbLED - 1)
    varAnimation += 2 * instrument.type;
    
  if(varAnimation >= nb * rev * 2 * BIG_CIRCULAR)
    varAnimation = 0;
    
  return floor(varAnimation / (2 * rev * BIG_CIRCULAR));
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


// Animations Complètes

void Brasil()
{
  if(instrument.type == BAR)
  {
    if(varAnimation == 0)
    {
      colorWipe(sambaYellow);
      if(indexLED == instrument.nbLED - 1)
        varAnimation = 1;
    }
    else
    {
      colorWipe(sambaGreen);
      if(indexLED == instrument.nbLED - 1)
        varAnimation = 0;
    }     
  }

  if(instrument.type == CIRCULAR || instrument.name == SURDO3)
  {
    colorPathForward(sambaYellow, off, instrument.lenght);
    colorPathBackward(sambaGreen, off, instrument.lenght);           

  }

  if(instrument.name == SURDO1)
    colorPathForward(sambaYellow, off, instrument.lenght);

  if(instrument.name == SURDO2)
    colorPathBackward(sambaGreen, off, instrument.lenght);
}

void Mangueira()
{
  if(instrument.type == BAR)
    colorPathBackForth(sambaFuchsia, sambaGreen, 1);

  if(instrument.type == CIRCULAR || instrument.name == SURDO3)
    colorPathForward(sambaGreen, sambaFuchsia, 0.5 * instrument.nbLED);

  if(instrument.name == SURDO1)
    colorPathForward(sambaFuchsia, off, 0.5 * instrument.nbLED);

  if(instrument.name == SURDO2)
    colorPathForward(sambaGreen, off, 0.5 * instrument.nbLED);

}

void Girls()
{

  if(instrument.type == BAR)
    colorGauge(sambaEmeraud, sambaCuisseDeNimpheEmue);
  if(instrument.type == CIRCULAR)
    colorGauge(sambaEmeraud, sambaCuisseDeNimpheEmue);

  if(instrument.name == SURDO1)
    colorPathBackward(sambaEmeraud, off, instrument.lenght);
  if(instrument.name == SURDO2)
    colorPathForward(sambaCuisseDeNimpheEmue, off, instrument.lenght);  

  if(instrument.name == SURDO3)
  {
    if(varAnimation == 0)
    {
      colorPathForward(sambaEmeraud, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        varAnimation = 1;
    }
    else
    {
      colorPathBackward(sambaCuisseDeNimpheEmue, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        varAnimation = 0;
    }     
  }

}


void Geo(uint8_t index)
{
  // Définition GeoColor
  geoColor[0] = sambaColors[index];
  if(index + 1 < NBCOLOR)
  {
    geoColor[1] = sambaColors[index + 1];
  }
  else
  {
    geoColor[1] = sambaColors[index + 1 - NBCOLOR];
  }
  if(index + 7 < NBCOLOR)
  {
    geoColor[2] = sambaColors[index + 7];
  }
  else
  {
    geoColor[2] = sambaColors[index + 7 - NBCOLOR];
  }

  // geoIndexColor est l'index de la couleur de l'animation
  uint8_t geoIndexColor = changeAfterSomeSurdoRevolutions(3,5);

  // Définition par placement
  if(instrument.place == FIRST)
    colorPathBackForth(geoColor[geoIndexColor], off, instrument.lenght);


  if(instrument.place == BETWEEN)
  {
    if(geoIndexColor + 1 < 3)
    {
      colorPathForward(geoColor[geoIndexColor + 1], off, instrument.lenght);
    }
    else
    {
      colorPathForward(geoColor[geoIndexColor + 1 - 3], off, instrument.lenght);
    }
  }

  if(instrument.place == LAST)  
  {
    if(geoIndexColor + 2 < 3)
    {
      colorPathForward(geoColor[geoIndexColor + 2], off, instrument.lenght);
    }
    else
    {
      colorPathForward(geoColor[geoIndexColor + 2 - 3], off, instrument.lenght);
    }
  }

}

void Sambagogo()
{
  if(instrument.name == AGOGO)
    colorWipe(sambaRed);

  if(instrument.name == TAMBORIM)
    colorWipe(sambaYellow);

  if(instrument.name == CHOCALHO)
    colorWipe(sambaCarrot);

  if(instrument.name == CAIXA)
    colorWipe(sambaCarrot);

  if(instrument.name == REPIQUE)
    colorWipe(sambaYellow);

  if(instrument.type == BIG_CIRCULAR)
    colorWipe(sambaRed);
}

void Drums()
{
  if(instrument.name != CAIXA && instrument.name != REPIQUE)
  {
    colorWipe(off);
  }
  else
  {          
    colorPathForward(sambaCarrot, off, instrument.lenght);
    colorPathBackward(sambaRed, off, instrument.lenght);          
  }


}

void Wave()
{
  if(instrument.type != BIG_CIRCULAR)
  {
    colorWipe(off);
  }
  else
  {
    colorPathForward(sambaEmeraud, off, instrument.lenght);
    colorPathBackward(sambaBlue, off, instrument.lenght);

  }
}




