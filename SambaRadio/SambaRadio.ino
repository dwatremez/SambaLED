#include <Keypad.h>
#include <RCSwitch.h>

#define DEBUG 0

// Émetteur RF
RCSwitch mySwitch = RCSwitch();

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

// KeyPad
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
	{'#','0','*'},
	{'9','8','7'},
	{'6','5','4'},
	{'3','2','1'}
};
byte rowPins[rows] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[cols] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup()
{
	if(DEBUG)
	{
		pinMode(13,OUTPUT);	// Définie la LED de l'arduino en sortie
		digitalWrite(13,HIGH);	// Elle traduira l'activité de la carte
		Serial.begin(9600);
	}
	
	// Activer émission de messages sur le pin 12
	mySwitch.enableTransmit(12);
	mySwitch.setRepeatTransmit(5);
}

void loop()
{
	char key = keypad.getKey();
	if(key)  // Check for a valid key.
	{
        digitalWrite(13, HIGH);
		if(DEBUG)
			Serial.println(key);
	}

	if(key == '0')
		mySwitch.send(KEY_0, 24);
	if(key == '1')
		mySwitch.send(KEY_1, 24);
	if(key == '2')
		mySwitch.send(KEY_2, 24);
	if(key == '3')
		mySwitch.send(KEY_3, 24);
	if(key == '4')
		mySwitch.send(KEY_4, 24);
	if(key == '5')
		mySwitch.send(KEY_5, 24);
	if(key == '6')
		mySwitch.send(KEY_6, 24);
	if(key == '7')
		mySwitch.send(KEY_7, 24);
	if(key == '8')
		mySwitch.send(KEY_8, 24);
	if(key == '9')
		mySwitch.send(KEY_9, 24);
	if(key == '*')
		mySwitch.send(KEY_ASTERISK, 24);
	if(key == '#')
		mySwitch.send(KEY_HASH, 24);
	


	digitalWrite(13, LOW);


}
