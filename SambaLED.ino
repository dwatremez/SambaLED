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
	SURDO2_SMALL, TAMBORIM_SMALL
};

// Choix de l'instrument
#define INSTRU AGOGO

// Forme de l'instrument
#define BAR 0
#define CIRCULAR 1
#define BIG_CIRCULAR 2

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

// Paramètres de l'instrument
struct defineInstrument{
	char name;
	int type;
	int nbLED;
	int brightness;
};

// Variables globales
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LEDPIN, NEO_GRB + NEO_KHZ800);
RCSwitch mySwitch = RCSwitch();
struct defineInstrument instrument;
uint16_t indexLED = 0;
uint8_t animStep = 1;
uint16_t script[2]; // les nouveaux et anciens scripts (ordre défini par indexScript)
uint8_t indexScript = 1;
uint32_t animDelay = 1000;
uint8_t animDirection = 0;

// Définition des couleurs utilisées
uint32_t sambaColor[4] = {
	strip.Color(120, 130, 18),	//Yellow
	strip.Color(255, 44, 15),	//Red
	strip.Color(30, 120, 200),	//Blue
	strip.Color(100,207,19)		//Green
};
uint32_t off = strip.Color(0,0,0);
uint8_t indexColor = 0;


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
	switch (INSTRU) {
	case AGOGO:
		instrument.type = BAR;
		instrument.nbLED = NB_LED_AGOGO;
		instrument.brightness = BRIGHTNESS_AGOGO;
		break;
	case SURDO1:
		instrument.type = BIG_CIRCULAR;
		instrument.nbLED = NB_LED_SURDO;
		instrument.brightness = BRIGHTNESS_SURDO;
		break;
	case SURDO2:
		instrument.type = BIG_CIRCULAR;
		instrument.nbLED = NB_LED_SURDO;
		instrument.brightness = BRIGHTNESS_SURDO;
		break;
	case SURDO3:
		instrument.type = BIG_CIRCULAR;
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
		instrument.type = BIG_CIRCULAR;
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

	// Initialiser NeoPixel
	strip.begin();
	strip.setBrightness(instrument.brightness);

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
	script[0] = KEY_0;
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
				case 5910:
					break;
				case 5920:
					break;
				case 5390:
				case 5391:
				case 5392:
				case 5393:
				case 5394:
				case 5395:
				case 5396:
				case 5397:
				case 5398:
				case 5399:
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
			// Définir le script ici !
			break;
		case KEY_0:
			// Définir le script ici !
			break;
		case KEY_1:
			// Définir le script ici !
			break;
		case KEY_2:
			// Définir le script ici !
			break;
		case KEY_3:
			// Définir le script ici !
			break;
		case KEY_4:
			// Définir le script ici !
			break;
		case KEY_5:
			// Définir le script ici !
			break;
		case KEY_6:
			// Définir le script ici !
			break;
		case KEY_7:
			// Définir le script ici !
			break;
		case KEY_8:
			// Définir le script ici !
			break;
		case KEY_9:
			// Définir le script ici !
			break;
		case KEY_ASTERISK:
			// Définir le script ici !
			break;
		case KEY_HASH:
			// Définir le script ici !
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

// Changement de couleurs
uint32_t oneColorEachLoop()
{
	if(indexLED == instrument.nbLED - 1)
		indexColor = (indexColor + 1)%(sizeof(sambaColor));

	return sambaColor[indexColor];
}

uint32_t oneColorEach(uint8_t nb)
{
	if(indexLED%nb == 0)
		indexColor = (indexColor + 1)%(sizeof(sambaColor));

	return sambaColor[indexColor];
	
}


void loop()
{
	// Écouter messages radio
	listenRF(); 

	// Jouer les 2 scripts enregistrés
	playScript(script[0]);
	playScript(script[1]);	

	// Mise à jour du bandeau
	strip.show();

	// Attente entre deux intérations de l'animation
	delay( (0.5 + 0.25 * instrument.type * (1 + instrument.type)) * (int)(animDelay/instrument.nbLED));
	
	
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
			Serial.print(script[2]);
		}

		indexLED = 0; // retour au début du bandeau
		
		if(script[0] != 0 && script[1] != 0)
			script[indexScript] = 0;	// arrêter le précédent script en fin de boucle		
	}

}
