#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <SoftwareSerial.h>
#include <IRremote.h>
#include <avr/pgmspace.h>

/*Dokumentation:

   - Parallele Schnittstelle an den Pins 45, 47, 49, 51, 53
   - Bt Adapter an den Pins 10 und 11 anschließen. RXD (Blau) an Pin 11, TXT (Gruen) an Pin 10
   - Relais waren angeschlossen an:
   - Infrarot LEDs sind an der Masse über einen 1k Ohm Widerstand an Pin 3 (Arduino Uno) oder Pin 9 (Arduino MEGA) angeschlossen.

*/

//Samsung Fernseher

//const unsigned int onoff[] PROGMEM = {4500, 4450, 550, 1700, 500, 1700, 550, 1700, 500, 600, 550, 550, 550, 600, 500, 600, 500, 600, 550, 1700, 500, 1700, 500, 1700, 550, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 1700, 550, 550, 550, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 1700, 550, 600, 500, 1650, 550, 1700, 550, 1700, 500, 1700, 550, 1650, 550, 1700, 550}; //AnalysIR Batch Export - RAW
//const unsigned int eins[]  PROGMEM = {4500, 4450, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 550, 1650, 550, 1700, 500, 1650, 550, 1650, 550};
//const unsigned int zwei[]  PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int drei[]  PROGMEM = {4500, 4400, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int vier[]  PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 1650, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int fuenf[] PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 550, 550, 550, 550, 1650, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550, 1650, 550};
//const unsigned int sechs[] PROGMEM = {4500, 4450, 550, 1650, 550, 1650, 550, 1650, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 1650, 550, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 550, 1650, 550, 1700, 500, 1700, 500};
//const unsigned int sieben[]PROGMEM = {4500, 4400, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int acht [] PROGMEM = {4500, 4450, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 600, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 550, 550, 500, 1700, 550, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int neun [] PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 550};
//const unsigned int zero [] PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550};
//const unsigned int source[]PROGMEM = {4500, 4400, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550};
//const unsigned int txt []  PROGMEM = {4500, 4400, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 600, 550, 550, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 1650, 550, 600, 500, 1700, 500, 1700, 500};
//const unsigned int mute [] PROGMEM = {4500, 4400, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550};
//const unsigned int lauter []PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 1700, 500, 1700, 500, 1750, 450};
//const unsigned int leiser []PROGMEM = {4450, 4400, 550, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 1700, 500, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int phoch [] PROGMEM = {4450, 4400, 550, 1700, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 550, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 550, 550, 550, 550, 1650, 550, 600, 500, 600, 500, 550, 550, 1650, 550, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 550, 1650, 550, 1700, 500};
//const unsigned int prunter[]PROGMEM = {4450, 4400, 550, 1650, 550, 1650, 550, 1700, 500, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 600, 500, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1650, 550, 550, 550, 600, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550, 1650, 550, 600, 500, 1700, 500, 1650, 550, 1650, 550};
//const unsigned int menu []  PROGMEM = {4450, 4450, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 600, 500, 550, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 550, 550, 1700, 500, 1650, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 1650, 550, 600, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550};
//const unsigned int smarthub[]PROGMEM = {4450, 4450, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 550, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 600, 500, 550, 550, 1700, 500, 1650, 550, 1700, 500, 1700, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500};
//const unsigned int guide [] PROGMEM = {4450, 4400, 550, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1650, 550, 1700, 500, 1650, 550, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 1700, 500, 1700, 500, 550, 550, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 550, 550, 500, 600, 550, 1650, 550, 1650, 550, 550, 550, 1700, 500};
//const unsigned int tools [] PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 600, 550, 550, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500};
//const unsigned int info []  PROGMEM = {4450, 4450, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 1650, 550};
//const unsigned int sreturn[]PROGMEM = {4400, 4450, 500, 1700, 550, 1700, 500, 1650, 550, 550, 550, 600, 500, 550, 550, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 550, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 550, 550, 550, 1700, 500};
//const unsigned int sexit [] PROGMEM = {4450, 4400, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 600, 500, 550, 550, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 600, 550, 550, 550, 550, 550, 1700, 500, 550, 550, 550, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500};
//const unsigned int links [] PROGMEM = {4400, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 650, 450, 600, 550, 550, 550, 600, 500, 1700, 500, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 550, 550, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 550};
//const unsigned int hoch []  PROGMEM = {4450, 4450, 500, 1650, 550, 1700, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1700, 500, 1650, 550, 1650, 550, 600, 500, 550, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 1650, 550};
//const unsigned int rechts []PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 550, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 550};
//const unsigned int runter []PROGMEM = {4450, 4400, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 500};
//const unsigned int enter [] PROGMEM = {4500, 4400, 550, 1700, 500, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 1700, 550, 550, 550, 1650, 550, 1650, 550, 550, 550, 1650, 550, 1650, 550, 1700, 500, 550, 550, 1700, 500, 600, 500, 600, 550, 1650, 550};
//const unsigned int a []     PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 550, 550, 1650, 550, 1650, 550, 600, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 1700, 550};
//const unsigned int b []     PROGMEM = {4500, 4400, 550, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 650, 450, 650, 500, 550, 550, 1700, 500, 1650, 550, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500};
//const unsigned int c []     PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 550, 550, 550, 550, 550, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 550, 550, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 650, 450, 1700, 500, 1700, 550, 1650, 550};
//const unsigned int d []     PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 1700, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550};
//const unsigned int rec []   PROGMEM = {4450, 4400, 550, 1700, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 1700, 500, 550, 550, 600, 500, 1700, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 550, 550, 1650, 550, 1650, 550, 600, 500, 1700, 500};
//const unsigned int dreid [] PROGMEM = {4450, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 550, 1650, 550, 1650, 550, 600, 500};
//const unsigned int subt []  PROGMEM = {4450, 4400, 550, 1700, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 500, 1700, 550, 550, 550, 1650, 550, 550, 550, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 550, 1650, 550, 1650, 550, 550, 550, 1700, 500, 1700, 500};
//const unsigned int stopp [] PROGMEM = {4500, 4450, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 550, 1650, 550, 550, 550, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500};
//const unsigned int zspulen[]PROGMEM = {4400, 4450, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 550, 550, 550, 550, 600, 500, 1700, 550, 550, 550, 550, 550, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 1700, 550};
//const unsigned int play []  PROGMEM = {4450, 4400, 550, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 550, 1650, 550, 600, 500, 1700, 500};
//const unsigned int pause [] PROGMEM = {4500, 4400, 550, 1650, 550, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 550, 1650, 550, 550, 550, 1650, 550};
//const unsigned int vspulen[]PROGMEM = {4450, 4400, 550, 1700, 500, 1700, 500, 1650, 550, 550, 550, 550, 550, 600, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 600, 500, 600, 550, 1650, 550, 550, 550, 550, 550, 1650, 550, 550, 550, 1650, 550, 1650, 550, 1700, 550, 550, 550, 1650, 550, 1650, 550, 550, 550, 1650, 550};

//Teufel Anlage
const unsigned int tonoff []PROGMEM = {8800, 4400, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 1650, 500, 1700, 500, 1650, 550, 1650, 500, 1700, 500, 1650, 550};
const unsigned int tstumm []PROGMEM = {8750, 4400, 550, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 550, 550, 500, 1650, 550, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 550, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 550, 550, 1700, 500, 1650, 500, 1650, 550, 1650, 550, 1650, 500, 1650, 550, 1650, 550};
const unsigned int tsourceh[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500, 550, 500, 600, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 600, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tsourcer[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 550, 1650, 500, 600, 500, 1650, 550, 1650, 500, 1650, 550, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 550, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tlauter[]PROGMEM = {8800, 4400, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500};
const unsigned int tleiser[]PROGMEM = {8800, 4400, 500, 600, 500, 600, 500, 550, 500, 650, 450, 600, 500, 1650, 550, 1650, 500, 600, 500, 1650, 550, 550, 550, 1650, 500, 1650, 550, 1650, 500, 600, 500, 600, 500, 1650, 550, 550, 500, 1700, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 600, 450, 600, 500, 1700, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550};

#define rxPin 10
#define txPin 11
#define l 5
#define f 6
#define b 7

int leiste    = 0;
int bt        = 0;
int fp        = 0;
int anlage    = 0;
int counter   = 0;
int counter2  = 0;
int counter3  = 0;
int counter4  = 0;
int fernseher = 0;
int i         = 0;
int ps        = 0;
int fern      = 0;
int record    = 0;
int sender    = 0;
int licht     = 0;
int licht1    = 1;
int volume    = 0;
int vcounter  = 0;
int dvd       = 1;
int tape      = 0;
int aux       = 0;
int senden[67];
int al        = 50;
int td        = 100;
int fextt      = 0;
int binaer    = 0b00000000;

//Infrarot

IRsend irsend;
int k = 2;   

//

void lon() {
  digitalWrite(l, 1);
  leiste = 1;
}

void loff() {
  digitalWrite(l, 0);
  leiste = 0;
}

void bton() {
  digitalWrite(b, 1);
  bt = 1;
}

void btoff() {
  digitalWrite(b, 0);
  bt = 0;
}

void fpon() {
  digitalWrite(f, 1);
  fp = 1;
}

void fpoff() {
  digitalWrite(f, 0);
  fp = 0;
}

//Fernseher

void frec() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(rec + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fleiser() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(leiser + counter);
  }

  while (vcounter > 0) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    vcounter--;
    delay(200);
  }
}

void flauter() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(lauter + counter);
  }

  while (vcounter > 0) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    vcounter--;
    delay(200);
  }
}

void fsource() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(source + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fmute() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(mute + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fguide() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(guide + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fsmarthub() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(smarthub + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}


void fhoch() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(hoch + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

}

void frunter() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(runter + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void frechts() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(rechts + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void flinks() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(links + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void ftools() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tools + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fenter() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(enter + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

}

void fstop() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(stopp + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  delay(500);
  flinks();
  delay(500);
  fenter();
}

void fplay() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(play + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void fpause() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(pause + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void freturn() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(sreturn + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void finfo() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(info + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

}

void feins() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(eins + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}
void fzwei() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(zwei + counter);
  }


  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fdrei() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(drei + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fvier() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(vier + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void ffuenf() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(fuenf + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fsechs() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(sechs + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fsieben() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(sieben + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void facht() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(acht + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fneun() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(neun + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fnull() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(zero + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 1;
}

void fon() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(onoff + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
  fernseher = 1;
}

void foff() {

  if (ps == 1) {
    psoff();
    delay(13000);
    ps = 0;
  }

  if (fextt == 1) {
    fint();
    delay(1000);
    fextt = 0;
  }

  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(onoff + counter);
  }

  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  fernseher = 0;
}

void flaut() {
  ftools();
  delay(1000);
  if (ps == 0) {
    frunter();
    delay(500);
    fenter();
    delay(500);
    frunter();
    delay(500);
    fenter();
    delay(500);
    freturn();
  }

  if (ps == 1) {
    frunter();
    delay(500);
    frunter();
    delay(500);
    frunter();
    delay(500);
    frunter();
    delay(500);
    fenter();
    delay(500);
    frunter();
    delay(500);
    fenter();
    delay(500);
    freturn();
  }
}

void fext() {
  if (anlage == 0) {
    aon();
    delay(1000);
  }
  a20();
  delay(500);
  advd();
  delay(500);
  flaut();

}

void fint() {
  flaut();
  if (anlage == 1) {
    aoff();
    delay(200);
  }
}

//playstation

void pson() {
  ftools();

  delay(2000);

  fenter();

  delay(1000);

  fenter();

  ps = 1;
}

void psoff() {
  ftools();

  delay(1000);

  frunter();

  delay(500);

  fenter();

  delay(2000);

  for (counter2 == 0; counter2 < 10; counter2++) {
    flinks();
    delay(100);
  }
  counter2 = 0;

  delay(500);

  for (counter3 == 0; counter3 < 6; counter3++) {
    fhoch();
    delay(100);
  }
  counter3 = 0;

  delay(1000);

  for (counter4 == 0; counter4 < 2; counter4++) {
    fenter();
    delay(1000);
  }
  counter4 = 0;

  ps = 0;
}

void leisteaus() {

  if (fernseher == 1) {
    foff();
    delay(10000);
  }

  if (fp == 1) {
    fpoff();
    delay(500);
  }

  if (bt == 1) {
    btoff();
    delay(500);
  }
  if (anlage == 1) {
    aoff();
    delay(1000);
  }

  loff();
  al = 50;
}

void lichtt() {
  if (licht == 0 && licht1 == 1) {
    digitalWrite(4, 1);
    digitalWrite(8, 1);
    licht = 1;
  }

  if (licht == 1 && licht1 == 0) {
    digitalWrite(4, 0);
    digitalWrite(8, 0);
    licht = 0;
  }

  if (licht == 1)licht1 = 0;
  if (licht == 0)licht1 = 1;

}

//Anlage

void aon() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tonoff + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);

  delay(1000);
  counter = 10;

  while (counter > 0) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
  anlage = 1;
}

void aoff() {

  advd();
  delay(500);
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tonoff + counter);
  }

  counter = 5;
  while (counter > 0) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }

  anlage = 0;
}

void ash() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tsourceh + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void asr() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tsourcer + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void advd() {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      ash();
      delay(500);
    }
    tape = 0;
  }

  if (aux == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      ash();
      delay(500);
    }
    aux = 0;
  }

  dvd = 1;
}

void atape() {
  if (dvd == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      asr();
      delay(500);
    }
    dvd = 0;
  }

  if (aux == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      ash();
      delay(500);
    }
    aux = 0;
  }

  tape = 1;
}

void aaux() {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      asr();
      delay(500);
    }
    tape = 0;
  }

  if (dvd == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      asr();
      delay(500);
    }
    dvd = 0;
  }

  aux = 1;
}

void alauter() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tlauter + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void aleiser() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tleiser + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void amute() {
  for (counter = 0; counter < 67; counter++) {
    senden[counter] = pgm_read_word_near(tstumm + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void a5() {
  counter2 = al - 5;
  al = 5;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a10() {
  counter2 = al - 10;
  al = 10;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a15() {
  counter2 = al - 15;
  al = 15;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a20() {
  counter3 = al - 20;
  al = 20;
  if (counter3 > 0) {
    while (counter3 > 0) {
      alauter();
      delay(td);
      counter3--;
    }
  }

  if (counter3 < 0) {
    while (counter3 < 0) {
      aleiser();
      delay(td);
      counter3++;
    }
  }
}

void a25() {
  counter2 = al - 25;
  al = 25;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a30() {
  counter2 = al - 30;
  al = 30;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a35() {
  counter2 = al - 35;
  al = 35;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a40() {
  counter2 = al - 40;
  al = 40;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a45() {
  counter2 = al - 45;
  al = 45;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}

void a50() {
  counter2 = al - 50;
  al = 50;
  if (counter2 > 0) {
    while (counter2 > 0) {
      alauter();
      delay(td);
      counter2--;
    }

  }
  if (counter2 < 0) {
    while (counter2 < 0) {
      aleiser();
      delay(td);
      counter2++;
    }
  }
}


SoftwareSerial btSerial(rxPin, txPin);
String btData;

void eingabe() {
  binaer = 0;
  /*
    if(digitalRead(53)==HIGH)binaer=binaer|0b00000001;
    if(digitalRead(51)==HIGH)binaer=binaer|0b00000010;
    if(digitalRead(49)==HIGH)binaer=binaer|0b00000100;
    if(digitalRead(47)==HIGH)binaer=binaer|0b00001000;
    if(digitalRead(45)==HIGH)binaer=binaer|0b00010000;
  */
}

void setup() {
  btSerial.begin(9600);
  Serial.begin(9600);
  btSerial.println("bluetooth available");
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);

  //Meine parallele Schnittstelle
  pinMode(53, INPUT);
  pinMode(51, INPUT);
  pinMode(49, INPUT);
  pinMode(47, INPUT);
  pinMode(45, INPUT);

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void loop() {



  //if(i==0){
  //  for(int counter = 0; counter < 67; counter++)
  //{
  //  Serial.println(senden[counter]);
  //  i=1;
  //}
  //}
  eingabe();


  if (btSerial.available() || binaer != 0) {
    btData = btSerial.readString();
    if (btData == "leiste aus" || binaer == 5) {
      leisteaus();

      delay(1000);

      btSerial.println("Steckdosenleiste ist aus");
    }
    if (btData == "leiste an" || binaer == 2) {
      lon();
      btSerial.println("Steckdosenleiste ist an");
    }
    if (btData == "festplatte aus" || btData == "Festplatte aus" || binaer == 29) {
      if (record == 1) {
        fstop();
        delay(1000);
      }
      fpoff();
      btSerial.println("Festplatte ist aus");
      fenter();
    }

    if (btData == "festplatte an" || btData == "Festplatte an" || binaer == 28) {
      lon();
      fpon();

      btSerial.println("Festplatte ist an");
    }
    if (btData == "bt aus" || binaer == 22) {
      btoff();
      aoff();
      btSerial.println("Bluetooth Empfänger aus");
    }
    if (btData == "bt an" || binaer == 21) {
      lon();
      bton();
      if (anlage == 0) {
        aon();
        delay(1500);
      }
      if (tape == 0) {
        atape();
        delay(1000);
      }
      a20();
      btSerial.println("Bluetooth Empfänger an");
    }

    if (btData == "anlage an" || binaer == 19) {
      if (leiste == 0)lon();

      delay(1000);

      aon();
      btSerial.println("Die Anlage ist jetzt an");
    }

    if (btData == "anlage aus" || binaer == 20) {
      aoff();
      btSerial.println("Die Anlage wird ausgemacht");
    }

    if (btData == "source h" || binaer == 32) {
      ash();

      btSerial.println("Source eins nach oben");
    }

    if (btData == "source r" || binaer == 31) {
      asr();

      btSerial.println("Source eins nach unten");
    }

    if (btData == "dvd") {
      if (leiste == 0) {
        lon();
        delay(100);
      }
      if (anlage == 0) {
        aon();
        delay(2000);
      }
      advd();
    }

    if (btData == "tape") {
      if (leiste == 0) {
        lon();
        delay(100);
      }
      if (anlage == 0) {
        aon();
        delay(2000);
      }
      atape();
    }

    if (btData == "aux" || binaer == 23) {
      if (leiste == 0) {
        lon();
        delay(500);
      }
      if (anlage == 0) {
        aon();
        delay(2000);
      }
      aaux();

      a30();
    }

    if (btData == "alauter") {
      alauter();
    }

    if (btData == "aleiser") {
      aleiser();
    }

    if( btData == "amute"){
      amute();
    }

    if (btData == "ext" || binaer == 24) {

      fext();
      btSerial.println("Externe Lautsprächer");
      fextt = 1;
    }

    if (btData == "int" || binaer == 25) {
      fint();
      fextt = 0;

    }

    if (btData == "a5" || binaer == 9) {
      a5();
    }

    if (btData == "a10" || binaer == 10) {
      a10();
    }

    if (btData == "a15" || binaer == 11) {
      a15();
    }

    if (btData == "a20" || binaer == 12) {
      a20();
    }

    if (btData == "a25" || binaer == 13) {
      a25();
    }

    if (btData == "a30" || binaer == 14) {
      a30();
    }

    if (btData == "a35" || binaer == 15) {
      a35();
    }

    if (btData == "a40" || binaer == 16) {
      a40();
    }

    if (btData == "a45" || binaer == 17) {
      a45();
    }

    if (btData == "a50" || binaer == 18) {
      a50();
    }

    if (btData == "fernseher an" || binaer == 3) {
      if (leiste == 0) {
        leiste = 1;
        digitalWrite(l, 1);
        delay(2000);
      }

      fon();
      btSerial.println("Der Fernseher wird angemacht");
    }

    if (btData == "fernseher aus" || binaer == 6) {

      foff();
      btSerial.println("Der Fernseher ist nun aus");
    }

    if (btData == "netflix") {
      if (fernseher == 0) {
        fon();
        delay(60000);
      }

      fsmarthub();

    }

    if (btData == "p0") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fnull();
      btSerial.println("0");
    }

    if (btData == "p1") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      feins();
      btSerial.println("1");
    }

    if (btData == "p2") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fzwei();
      btSerial.println("2");
    }

    if (btData == "p3") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fdrei();
      btSerial.println("3");
    }

    if (btData == "p4") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fvier();
      btSerial.println("4");
    }

    if (btData == "p5") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      ffuenf();
      btSerial.println("5");
    }

    if (btData == "p6") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fsechs();
      btSerial.println("6");
    }

    if (btData == "p7") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fsieben();
      btSerial.println("7");
    }

    if (btData == "p8") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      facht();
      btSerial.println("8");
    }

    if (btData == "p9") {
      if (leiste == 0) {
        lon();
        delay(2000);
      }
      fneun();
      btSerial.println("9");
    }

    if (btData == "info") {
      finfo();
      btSerial.println("Info");
    }

    if (btData == "guide") {
      fguide();
      btSerial.println("Guide");
    }

    if (btData == "tools") {
      ftools();
      btSerial.println("Tools");
    }

    if (btData == "mute") {
      fmute();
      btSerial.println("Mute");
    }

    if (btData == "enter") {
      fenter();
      btSerial.println("Enter");
    }

    if (btData == "zurück" || btData == "return") {
      freturn();
      btSerial.println("zurück");
    }

    if (btData == "links") {
      flinks();
    }

    if (btData == "rechts") {
      frechts();
    }

    if (btData == "hoch") {
      fhoch();
    }

    if (btData == "runter") {
      frunter();
    }

    if (btData == "source") {
      fsource();
    }

    if (btData == "pause") {
      if (fernseher == 0)fon();
      fpon();
      delay(15000);
      freturn();
      delay(1000);
      fpause();
      record = 1;

      btSerial.println("Pause");
    }

    if (btData == "play" && fernseher == 1 || binaer == 27) {
      fplay();
      btSerial.println("Play");
    }

    if (btData == "stop" && fernseher == 1) {
      fstop();
      record = 0;
      btSerial.println("Stop");
    }

    if (btData == "-10" || btData == "-9" || btData == "-8" || btData == "-7" || btData == "-6" || btData == "-5" || btData == "-4" || btData == "-3" || btData == "-2" || btData == "-1" || btData == "1" || btData == "2" || btData == "3" || btData == "4" || btData == "5" || btData == "6" || btData == "7" || btData == "8" || btData == "9" || btData == "10") {
      volume = atoi(btData.c_str());
      switch (volume) {
        case -10:
          vcounter = 10;
          break;
        case -9:
          vcounter = 9;
          break;
        case -8:
          vcounter = 8;
          break;
        case -7:
          vcounter = 7;
          break;
        case -6:
          vcounter = 6;
          break;
        case -5:
          vcounter = 5;
          break;
        case -4:
          vcounter = 4;
          break;
        case -3:
          vcounter = 3;
          break;
        case -2:
          vcounter = 2;
          break;
        case -1:
          vcounter = 1;
          break;
        case 1:
          vcounter = 1;
          break;
        case 2:
          vcounter = 2;
          break;
        case 3:
          vcounter = 3;
          break;
        case 4:
          vcounter = 4;
          break;
        case 5:
          vcounter = 5;
          break;
        case 6:
          vcounter = 6;
          break;
        case 7:
          vcounter = 7;
          break;
        case 8:
          vcounter = 8;
          break;
        case 9:
          vcounter = 9;
          break;
        case 10:
          vcounter = 10;
          break;

      }
      if (volume > 0)flauter();
      if (volume < 0)fleiser();
    }

    if (btData == "rec" && fernseher == 1) {
      if (fp == 0) {
        fpon();
        delay(15000);
        freturn();
      }
      fp = 1;
      frec();
    }

    if (btData == "ps3 an" || binaer == 7) {
      if (leiste == 0) {
        lon();
        delay(1000);
      }
      if (fernseher == 0) {
        fon();
        delay(25000);
      }
      pson();

      btSerial.println("Ps3 wird angeschalten");
    }

    if (btData == "ps3 aus" || binaer == 8) {
      psoff();

      btSerial.println("Ps3 wird ausgeschalten");
    }

    if (btData == "ppause" || binaer == 26) {
      fpause();
    }

    if (btData == "amazon" || binaer == 4) {
      btSerial.println("Amazon wird gestartet");

      if (leiste == 0) {
        lon();
        delay(3000);
      }
      if (fernseher == 0) {
        fon();
        delay(25000);
      }
      if (ps == 0) {
        pson();
        delay(30000);
      }
      for (counter2 = 0; counter2 < 3; counter2++) {
        flinks();
        delay(400);
      }
      delay(2500);
      frunter();
      delay(800);
      fenter();
    }

    if (btData == "licht" || btData == "Licht" || binaer == 1) {
      lichtt();
      if (licht == 1) {
        btSerial.println("Relais ist an");
      }
      if (licht == 0) {
        btSerial.println("Relais ist aus");
      }
      btData = "nix";
    }

    if (btData == "gute nacht") {
      leisteaus();
      lichtt();
    }

    if (btData == "hilfe") {
      btSerial.println("-----------------------------------");
      btSerial.println("- leiste an/aus");
      btSerial.println("- festplatte an/aus");
      btSerial.println("- bt an/aus");
      btSerial.println("- anlage an/aus");
      btSerial.println("- fernseher an/aus");
      btSerial.println("- source h/r //Quelle Hoch bzw. Runter");
      btSerial.println("- dvd");
      btSerial.println("- tape");
      btSerial.println("- aux");
      btSerial.println("- alauter/aleiser //Anlage Lauter/Leiser");
      btSerial.println("- amute um die Anlage zu muten");
      btSerial.println("- ext für Anlage statt Fernseher Boxen");
      btSerial.println("- int umgekehrt");
      btSerial.println("- a5-50 Lautstärke der Anlage (5er Schritte)");
      btSerial.println("- p0-9 //Sender Fernseher");
      btSerial.println("- info");
      btSerial.println("- guide");
      btSerial.println("- tools");
      btSerial.println("- mute");
      btSerial.println("- enter");
      btSerial.println("- zurück oder return");
      btSerial.println("- links");
      btSerial.println("- rechts");
      btSerial.println("- hoch");
      btSerial.println("- runter");
      btSerial.println("- source");
      btSerial.println("- pause //Zum Pause drücken während dem Fernseh schauen");
      btSerial.println("- play");
      btSerial.println("- stop");
      btSerial.println("- -10 bis 10 Lautstärke Fernseher");
      btSerial.println("- rec");
      btSerial.println("- ps3 an/aus");
      btSerial.println("- ppause Regulärer Pause Knopf");
      btSerial.println("- pplay");
      btSerial.println("- amazon");
      btSerial.println("- licht");
      btSerial.println("- gute nacht");
      btSerial.println("-----------------------------------");
      btSerial.println("");
    }

    if (btData == "sleep timer") {
      btSerial.println("Die Leiste geht in 10 Minuten aus");
      delay(120000);
      btSerial.println("Noch 8 Minuten");
      delay(120000);
      btSerial.println("Noch 6 Minuten");
      delay(120000);
      btSerial.println("Noch 4 Minuten");
      delay(120000);
      btSerial.println("Noch 2 Minuten");
      delay(120000);

      leisteaus();
    }


    if (btData == "ps3 ist an") {
      ps = 1;
      btSerial.println("Ps3 ist an");
    }
    if (btData == "ps3 ist aus") {
      ps = 0;
      btSerial.println("Ps3 ist aus");
    }
    if (btData == "fernseher ist an" || btData == "Fernseher ist an") {
      fernseher = 1;
      btSerial.println("Der Fernseher ist an");
    }
    if (btData == "fernseher ist aus" || btData == "Fernseher ist aus") {
      fernseher = 0;
      btSerial.println("Der Fernseher ist aus");
    }
    if (btData == "anlage ist an" || btData == "Anlage ist an") {
      anlage = 1;
      btSerial.println("Die Anlage ist an");
    }
    if (btData == "anlage ist aus" || btData == "Anlage ist aus") {
      anlage = 0;
      btSerial.println("Die Anlage ist aus");
    }

    binaer == 0;
  }

  btData = "nichts";
  counter = 0;
  counter2 = 0;
  counter3 = 0;
  counter4 = 0;
  delay(100);
}
