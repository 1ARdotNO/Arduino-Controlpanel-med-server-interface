#include <SPI.h>
//#include <Dhcp.h>
//#include <Dns.h>
#include <Ethernet.h>
//#include <Streaming.h>		// See http://arduiniana.org/libraries/streaming/ to download Thanks Mikal!
#include <Bounce2.h>
#include "FastLED.h"
#include <aREST.h>



//Tell it how many leds are in the strip.
#define NUM_LEDS 10
// This is an array of leds. One item for each led in your strip.
CRGB leds[NUM_LEDS];


#define DATA_PIN 3 //GREEN wire
// Clock pin SPI
#define CLOCK_PIN 2 //BLUE wire
#define MAX_BRIGHTNESS 255

//define start colour for leds (0xFF4500 orangered)
int ledfarge0R = 255;
int ledfarge0G = 69;
int ledfarge0B = 0;
int ledfarge1R = 255;
int ledfarge1G = 69;
int ledfarge1B = 0;
int ledfarge2R = 255;
int ledfarge2G = 69;
int ledfarge2B = 0;
int ledfarge3R = 255;
int ledfarge3G = 69;
int ledfarge3B = 0;
int ledfarge4R = 255;
int ledfarge4G = 69;
int ledfarge4B = 0;
int ledfarge5R = 255;
int ledfarge5G = 69;
int ledfarge5B = 0;
int ledfarge6R = 255;
int ledfarge6G = 69;
int ledfarge6B = 0;
int ledfarge7R = 255;
int ledfarge7G = 69;
int ledfarge7B = 0;
int ledfarge8R = 255;
int ledfarge8G = 69;
int ledfarge8B = 0;
int ledfarge9R = 255;
int ledfarge9G = 69;
int ledfarge9B = 0;

int LightsOff = 0;


int switchlight = 6; //pwm for lys i brytere


#define BUTTON_PIN0 A1
Bounce debouncer0 = Bounce(); 
int forrigebuttonvalue0 = HIGH;

#define BUTTON_PIN1 A2
Bounce debouncer1 = Bounce(); 
int forrigebuttonvalue1 = HIGH;

#define BUTTON_PIN2 A3
Bounce debouncer2 = Bounce(); 
int forrigebuttonvalue2 = HIGH;

#define BUTTON_PIN3 A4
Bounce debouncer3 = Bounce(); 
int forrigebuttonvalue3 = HIGH;

#define BUTTON_PIN4 A5
Bounce debouncer4 = Bounce(); 
int forrigebuttonvalue4 = HIGH;



byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
}; //Sets mac address
byte ip[] = { 10, 33, 0, 33 };

//http  remote server 
IPAddress server(10,33,0,208); int port = 8888;

EthernetClient client;

//aREST
EthernetServer RESTserver(80);
aREST rest = aREST();


//This function is used to setup things like pins, Serial ports etc.
void setup()
{

        Serial.begin(115200);

        //BUTTON LIGHTS
        analogWrite(switchlight, 255);
        
        //BUTTON CONFIG START
        pinMode(BUTTON_PIN0,INPUT_PULLUP);         // Setup the button
        debouncer0.attach(BUTTON_PIN0);     // After setting up the button, setup the Bounce instance :
        debouncer0.interval(5);             // interval in ms
        
        pinMode(BUTTON_PIN1,INPUT_PULLUP);         // Setup the button
        debouncer1.attach(BUTTON_PIN1);     // After setting up the button, setup the Bounce instance :
        debouncer1.interval(5);             // interval in ms
        
        pinMode(BUTTON_PIN2,INPUT_PULLUP);         // Setup the button
        debouncer2.attach(BUTTON_PIN2);     // After setting up the button, setup the Bounce instance :
        debouncer2.interval(5);             // interval in ms        
                
        pinMode(BUTTON_PIN3,INPUT_PULLUP);         // Setup the button
        debouncer3.attach(BUTTON_PIN3);     // After setting up the button, setup the Bounce instance :
        debouncer3.interval(5);             // interval in ms        
                
        pinMode(BUTTON_PIN4,INPUT_PULLUP);         // Setup the button
        debouncer4.attach(BUTTON_PIN4);     // After setting up the button, setup the Bounce instance :
        debouncer4.interval(5);             // interval in ms        
        //BUTTON CONFIG END
        
        //LED CONFIG START
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS); //DEFINES SETTINGS FOR LEDS    
        //LED CONFIG END
        
        //SD-CARD CONFIG BEGIN
        pinMode (4, OUTPUT); //deselects sd-card
        digitalWrite(4, HIGH); //deselects sd-card
        //SD-CARD CONFIG END
        
        //ETHERNET CONFIG BEGIN
        Ethernet.begin(mac,ip);
//
//        int ethstatus = Ethernet.begin(mac);
//        if (ethstatus == 1){
//          cylon(CRGB::Green,25, 5);
//        }
//        else if (ethstatus == 0){
//          cylon(CRGB::Red,25, 5);
//        }
//        delay(5000); //wait for network init
        //ETHERNET CONFIG END
        
        //aREST CONFIG BEGIN
          
          // Function to be exposed
          rest.function("SetLeds",SetLeds);
          rest.function("looptest",looptest);
          rest.function("LightsToggle",LightsToggle);
          // Give name and ID to device
          rest.set_id("033");
          rest.set_name("Arduino");
          
          RESTserver.begin();
          Serial.print("server is at ");
          Serial.println(Ethernet.localIP());
        //aREST CONFIG END
        
 

}

void loop()
{
       //Set LED colour from variables START
       if (LightsOff==0){
       FastLED.clear();
       FastLED.setBrightness(MAX_BRIGHTNESS);
        leds[0].setRGB(ledfarge0R,ledfarge0G,ledfarge0B);
        leds[1].setRGB(ledfarge1R,ledfarge1G,ledfarge1B);
        leds[2].setRGB(ledfarge2R,ledfarge2G,ledfarge2B);
        leds[3].setRGB(ledfarge3R,ledfarge3G,ledfarge3B);
        leds[4].setRGB(ledfarge4R,ledfarge4G,ledfarge4B);
        leds[5].setRGB(ledfarge5R,ledfarge5G,ledfarge5B);
        leds[6].setRGB(ledfarge6R,ledfarge6G,ledfarge6B);
        leds[7].setRGB(ledfarge7R,ledfarge7G,ledfarge7B);
        leds[8].setRGB(ledfarge8R,ledfarge8G,ledfarge8B);
        leds[9].setRGB(ledfarge9R,ledfarge9G,ledfarge9B);
        FastLED.show();
       //Set LED colour from variables END
       }
        
        //BUTTON A0 START
        debouncer0.update();
        int buttonvalue0 = debouncer0.read();
        if ((buttonvalue0 == LOW) && (forrigebuttonvalue0 == HIGH)) {
          PSsend(".\\button0.ps1");
          Serial.println("button0 LOW");
        }
        forrigebuttonvalue0 = buttonvalue0;
        //BUTTON A0 END
        
        //BUTTON A1 START
        debouncer1.update();
        int buttonvalue1 = debouncer1.read();
        if ((buttonvalue1 == LOW) && (forrigebuttonvalue1 == HIGH)) {
          PSsend(".\\button1.ps1");
          Serial.println("button1 LOW");
          LightsToggle("1337");
        }
        forrigebuttonvalue1 = buttonvalue1;
        //BUTTON A1 END
        
        //BUTTON A2 START
        debouncer2.update();
        int buttonvalue2 = debouncer2.read();
        if ((buttonvalue2 == LOW) && (forrigebuttonvalue2 == HIGH)) {
          PSsend(".\\button2.ps1");
          Serial.println("button2 LOW");
        }
        forrigebuttonvalue2 = buttonvalue2;
        //BUTTON A2 END
                
        //BUTTON A3 START
        debouncer3.update();
        int buttonvalue3 = debouncer3.read();
        if ((buttonvalue3 == LOW) && (forrigebuttonvalue3 == HIGH)) {
          PSsend(".\\button3.ps1");
          Serial.println("button3 LOW");
        }
        forrigebuttonvalue3 = buttonvalue3;
        //BUTTON A3 END
        
        //BUTTON A4 START
        debouncer4.update();
        int buttonvalue4 = debouncer4.read();
        if ((buttonvalue4 == LOW) && (forrigebuttonvalue4 == HIGH)) {
          PSsend(".\\button4.ps1");
          Serial.println("button4 LOW");
        }
        forrigebuttonvalue4 = buttonvalue4;
        //BUTTON A4 END
        
        
        //aREST BEGIN
        // listen for incoming clients
        EthernetClient clientrest = RESTserver.available();
        rest.handle(clientrest);
        //aREST END

}




int looptest(String Derp)
{
	//This is kind of Arduino's equivalent to Main() in a standard C program
	//This, as the name implies, loops endlessly.
	//https://code.google.com/p/fastspi/wiki/CRGBreference
	//CSK 3/20/2014 I added a rainbow function just for grins
	rainbow(20);
	cylon(CRGB::Red,25, 5);
	color_chase(CRGB::Green, 15);
	color_chase(CRGB::BlueViolet, 15);
	color_chase(CRGB::Red, 15);
	color_chase(CRGB::Yellow, 15);
	color_chase(CRGB::Green, 15);
	color_chase(CRGB::Cyan, 15);
	color_chase(CRGB::Blue, 15);
	missing_dot_chase(CRGB::White, 20);
	missing_dot_chase(CRGB::Red, 20);
	missing_dot_chase(CRGB::Yellow, 20);
	missing_dot_chase(CRGB::Green, 20);
	missing_dot_chase(CRGB::Cyan, 20);
	missing_dot_chase(CRGB::Blue, 20);
	missing_dot_chase(0x3000cc, 20) ;
 return 0;
}

//These are the functions we have defined to do chase patterns.  They are actually called inside the  loop() above
//They are meant to demonstrate things such as setting LED colors, controlling brightness
void color_chase(uint32_t color, uint8_t wait)
{
	//clear() turns all LEDs off
	FastLED.clear();
	//The brightness ranges from 0-255
	//Sets brightness for all LEDS at once
	FastLED.setBrightness(MAX_BRIGHTNESS);
	// Move a single led
	for(int led_number = 0; led_number < NUM_LEDS; led_number++)
	{
		// Turn our current led ON, then show the leds
		leds[led_number] = color;

		// Show the leds (only one of which is has a color set, from above
		// Show turns actually turns on the LEDs
		FastLED.show();

		// Wait a little bit
		delay(wait);

		// Turn our current led back to black for the next loop around
		leds[led_number] = CRGB::Black;
	}
	return;
}

//Move an "empty" dot down the strip
void missing_dot_chase(uint32_t color, uint8_t wait)
{
	//Step thru some brightness levels from max to 10.  led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
	for (int led_brightness = MAX_BRIGHTNESS; led_brightness > 10; led_brightness/=2)
	{
		FastLED.setBrightness(led_brightness);

		// Start by turning all pixels on:
		//for(int led_number = 0; led_number < NUM_LEDS; led_number++) leds[led_number] = color;
		//https://github.com/FastLED/FastLED/wiki/Controlling-leds
		fill_solid(leds, NUM_LEDS, color);

		// Then display one pixel at a time:
		for(int led_number = 0; led_number < NUM_LEDS; led_number++)
		{
			leds[led_number] =  CRGB::Black; // Set new pixel 'off'
			if( led_number > 0 && led_number < NUM_LEDS)
			{
				leds[led_number-1] = color; // Set previous pixel 'on'
			}
			FastLED.show();
			delay(wait);
		}
	}
	return;
}

//Cylon - LED sweeps back and forth, with the color, delay and number of cycles of your choice 
void cylon(CRGB color, uint16_t wait, uint8_t number_of_cycles)
{
	FastLED.setBrightness(255);
	for (uint8_t times = 0; times<=number_of_cycles; times++)
	{
		// Make it look like one LED is moving in one direction
		for(int led_number = 0; led_number < NUM_LEDS; led_number++)
		{
			//Apply the color that was passed into the function
			leds[led_number] = color;
			//Actually turn on the LED we just set
			FastLED.show();
			// Turn it back off
			leds[led_number] = CRGB::Black;
			// Pause before "going" to next LED
			delay(wait);
		}

		// Now "move" the LED the other direction
		for(int led_number = NUM_LEDS-1; led_number >= 0; led_number--)
		{
			//Apply the color that was passed into the function
			leds[led_number] = color;
			//Actually turn on the LED we just set
			FastLED.show();
			// Turn it back off
			leds[led_number] = CRGB::Black;
			// Pause before "going" to next LED
			delay(wait);
		}
	}
	return;
}

void rainbow(uint8_t wait) 
{

	uint16_t hue;
	FastLED.clear();

	for(hue=10; hue<255*3; hue++) 
	{

		fill_rainbow( &(leds[0]), NUM_LEDS /*led count*/, hue /*starting hue*/);		
		FastLED.show();
		delay(wait);
	}
	return;
}

void PSsend(String command){
// if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /?command=" + command + "&format=text HTTP/1.1");
    client.println("Host: servername");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
}

int LightsToggle(String input){

  int intinput = input.toInt();

  if (LightsOff == 0 || intinput == 1){
    Serial.println("LightsOFF0");
  LightsOff = 1;
  analogWrite(switchlight, 0);
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(switchlight, fadeValue);
    FastLED.setBrightness(fadeValue);
    FastLED.show();
    delay(10);
  }
  leds[0].setRGB(0,0,0);
  leds[1].setRGB(0,0,0);
  leds[2].setRGB(0,0,0);
  leds[3].setRGB(0,0,0);
  leds[4].setRGB(0,0,0);
  leds[5].setRGB(0,0,0);
  leds[6].setRGB(0,0,0);
  leds[7].setRGB(0,0,0);
  leds[8].setRGB(0,0,0);
  leds[9].setRGB(0,0,0);
  }
  else{
    LightsOff = 0;
    Serial.println("LightsOFF1");
    leds[0].setRGB(ledfarge0R,ledfarge0G,ledfarge0B);
    leds[1].setRGB(ledfarge1R,ledfarge1G,ledfarge1B);
    leds[2].setRGB(ledfarge2R,ledfarge2G,ledfarge2B);
    leds[3].setRGB(ledfarge3R,ledfarge3G,ledfarge3B);
    leds[4].setRGB(ledfarge4R,ledfarge4G,ledfarge4B);
    leds[5].setRGB(ledfarge5R,ledfarge5G,ledfarge5B);
    leds[6].setRGB(ledfarge6R,ledfarge6G,ledfarge6B);
    leds[7].setRGB(ledfarge7R,ledfarge7G,ledfarge7B);
    leds[8].setRGB(ledfarge8R,ledfarge8G,ledfarge8B);
    leds[9].setRGB(ledfarge9R,ledfarge9G,ledfarge9B);
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(switchlight, fadeValue);
    FastLED.setBrightness(fadeValue);
    FastLED.show();
    delay(10);
  }
  }

if(intinput == 0){
    LightsOff = 0;
    Serial.println("LightsOFFELSE1");
    leds[0].setRGB(ledfarge0R,ledfarge0G,ledfarge0B);
    leds[1].setRGB(ledfarge1R,ledfarge1G,ledfarge1B);
    leds[2].setRGB(ledfarge2R,ledfarge2G,ledfarge2B);
    leds[3].setRGB(ledfarge3R,ledfarge3G,ledfarge3B);
    leds[4].setRGB(ledfarge4R,ledfarge4G,ledfarge4B);
    leds[5].setRGB(ledfarge5R,ledfarge5G,ledfarge5B);
    leds[6].setRGB(ledfarge6R,ledfarge6G,ledfarge6B);
    leds[7].setRGB(ledfarge7R,ledfarge7G,ledfarge7B);
    leds[8].setRGB(ledfarge8R,ledfarge8G,ledfarge8B);
    leds[9].setRGB(ledfarge9R,ledfarge9G,ledfarge9B);
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(switchlight, fadeValue);
    FastLED.setBrightness(fadeValue);
    FastLED.show();
    delay(10);
  }
  }
  FastLED.show();
  return LightsOff;
}


int SetLeds(String LedInput){


    Serial.println(LedInput);
    
    String LedNumber = getStringPartByNr(LedInput, ',', 0);
    String LedColourR = getStringPartByNr(LedInput, ',', 1);
    String LedColourG = getStringPartByNr(LedInput, ',', 2);
    String LedColourB = getStringPartByNr(LedInput, ',', 3);
    
    
    //convert lednumber to int
    int intLedNumber = LedNumber.toInt();
    Serial.println(intLedNumber);
    //convert LedColour to int
    int intLedColourR = LedColourR.toInt();
    int intLedColourG = LedColourG.toInt();
    int intLedColourB = LedColourB.toInt();
    Serial.println(intLedColourR);
    Serial.println(intLedColourG);
    Serial.println(intLedColourB);
    //Set ledfarge variables based on input
    switch (intLedNumber){
      case 0:
        ledfarge0R = intLedColourR;
        ledfarge0G = intLedColourG;
        ledfarge0B = intLedColourB;
      break;
      case 1:
        ledfarge1R = intLedColourR;
        ledfarge1G = intLedColourG;
        ledfarge1B = intLedColourB;
      break;
      case 2:
        ledfarge2R = intLedColourR;
        ledfarge2G = intLedColourG;
        ledfarge2B = intLedColourB;
      break;
      case 3:
        ledfarge3R = intLedColourR;
        ledfarge3G = intLedColourG;
        ledfarge3B = intLedColourB;
      break;
      case 4:
        ledfarge4R = intLedColourR;
        ledfarge4G = intLedColourG;
        ledfarge4B = intLedColourB;
      break;
      case 5:
        ledfarge5R = intLedColourR;
        ledfarge5G = intLedColourG;
        ledfarge5B = intLedColourB;
      break;
      case 6:
        ledfarge6R = intLedColourR;
        ledfarge6G = intLedColourG;
        ledfarge6B = intLedColourB;
      break;
      case 7:
        ledfarge7R = intLedColourR;
        ledfarge7G = intLedColourG;
        ledfarge7B = intLedColourB;
      break;
      case 8:
        ledfarge8R = intLedColourR;
        ledfarge8G = intLedColourG;
        ledfarge8B = intLedColourB;
      break;
      case 9:
        ledfarge9R = intLedColourR;
        ledfarge9G = intLedColourG;
        ledfarge9B = intLedColourB;
      break;
      default:
        return 1;
      break;
    }
    
    return 0;

}

String getStringPartByNr(String data, char separator, int index) {
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text

    for(int i = 0; i<data.length()-1; i++) {    //Walk through the text one letter at a time

        if(data[i]==separator) {
            //Count the number of times separator character appears in the text
            stringData++;

        }else if(stringData==index) {
            //get the text when separator is the rignt one
            dataPart.concat(data[i]);

        }else if(stringData>index) {
            //return text and stop if the next separator appears - to save CPU-time
            return dataPart;
            break;

        }

    }
    //return text if this is the last part
    return dataPart;
}

