#include <boarddefs.h>

#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include <String.h>

#include "music_system.h"
//#include "tv_control.h"

//Definitions

#define rxPin 10
#define txPin 11
#define PIN_PLUG_STRIP 5
#define PIN_HARDDISK 6
#define PIN_BLUETOOTH 7

#define MAX_IR_LENGTH 67


//Global Variables
int anlage    = 0;
int leiste    = 0;
int bt        = 0;
int fp        = 0;
int fernseher = 0;
int ps        = 0;
int binaer    = 0b00000000;

SoftwareSerial btSerial(rxPin, txPin);
String btData;

//Music control
music_system music = music_system();
int k = 2;   

void readVoiceInput() {
  binaer = 0;
  if(digitalRead(53)==HIGH)binaer=binaer|0b00000001;
  if(digitalRead(51)==HIGH)binaer=binaer|0b00000010;
  if(digitalRead(49)==HIGH)binaer=binaer|0b00000100;
  if(digitalRead(47)==HIGH)binaer=binaer|0b00001000;
  if(digitalRead(45)==HIGH)binaer=binaer|0b00010000;
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
  //Input voice control
  //readVoiceInput();

  if (btSerial.available() || binaer != 0) {
    btData = btSerial.readString();

    //Anlage
    if (btData == "anlage an" || binaer == 19) {
      btSerial.println("Die Anlage wird angemacht");
      music.turnMusicsystemOn();
    }
    if (btData == "anlage aus" || binaer == 20) {
      music.turnMusicsystemOff();
      btSerial.println("Die Anlage wird ausgemacht");
    }
    if (btData == "source h" || binaer == 32) {
      music.sourceOneUp();
      btSerial.println("Source eins nach oben");
    }
    if (btData == "source r" || binaer == 31) {
      music.sourceOneDown();
      btSerial.println("Source eins nach unten");
    }
    if (btData == "dvd") {
      if (anlage == 0) {
        music.turnMusicsystemOn();
        delay(2000);
      }
      music.setSourceDVD();
    }
    if (btData == "tape") {
      if (anlage == 0) {
        music.turnMusicsystemOn();
        delay(2000);
      }
      music.setSourceTape();
    }
    if (btData == "aux" || binaer == 23) {
      if (anlage == 0) {
        music.turnMusicsystemOn();
        delay(2000);
      }
      music.setSourceAux();
      music.setVolume(30);
    }
    if (btData == "alauter") {
      music.volumeOneUp();
    }
    if (btData == "aleiser") {
      music.volumeOneDown();
    }

    if( btData == "amute"){
      music.setVolumeMute();
    }

    if(btData == "amax"){
      music.setVolume(1);
    }
    if (btData == "a5" || binaer == 9) {
      music.setVolume(5);
    }
    if (btData == "a10" || binaer == 10) {
      music.setVolume(10);
    }
    if (btData == "a15" || binaer == 11) {
      music.setVolume(15);
    }
    if (btData == "a20" || binaer == 12) {
      music.setVolume(20);
    }
    if (btData == "a25" || binaer == 13) {
      music.setVolume(25);
    }
    if (btData == "a30" || binaer == 14) {
      music.setVolume(30);
    }
    if (btData == "a35" || binaer == 15) {
      music.setVolume(35);
    }
    if (btData == "a40" || binaer == 16) {
      music.setVolume(40);
    }
    if (btData == "a45" || binaer == 17) {
      music.setVolume(45);
    }
    if (btData == "a50" || binaer == 18) {
      music.setVolume(50);
    }

//
//     if (btData == "ext" || binaer == 24) {
//
//      fext();
//      btSerial.println("Externe Lautsprächer");
//      fextt = 1;
//    }
//
//    if (btData == "int" || binaer == 25) {
//      fint();
//      fextt = 0;
//
//    }
//    if (btData == "fernseher an" || binaer == 3) {
//      fon();
//      btSerial.println("Der Fernseher wird angemacht");
//    }
//
//    if (btData == "fernseher aus" || binaer == 6) {
//      foff();
//      btSerial.println("Der Fernseher ist nun aus");
//    }
//
//    if (btData == "p0") {
//      fnull();
//      btSerial.println("0");
//    }
//
//    if (btData == "p1") {
//      feins();
//      btSerial.println("1");
//    }
//
//    if (btData == "p2") {
//      fzwei();
//      btSerial.println("2");
//    }
//
//    if (btData == "p3") {
//      fdrei();
//      btSerial.println("3");
//    }
//
//    if (btData == "p4") {
//      fvier();
//      btSerial.println("4");
//    }
//
//    if (btData == "p5") {
//      ffuenf();
//      btSerial.println("5");
//    }
//
//    if (btData == "p6") {
//      fsechs();
//      btSerial.println("6");
//    }
//
//    if (btData == "p7") {
//      fsieben();
//      btSerial.println("7");
//    }
//
//    if (btData == "p8") {
//      facht();
//      btSerial.println("8");
//    }
//
//    if (btData == "p9") {
//      fneun();
//      btSerial.println("9");
//    }
//
//    if (btData == "info") {
//      finfo();
//      btSerial.println("Info");
//    }
//
//    if (btData == "guide") {
//      fguide();
//      btSerial.println("Guide");
//    }
//
//    if (btData == "tools") {
//      ftools();
//      btSerial.println("Tools");
//    }
//
//    if (btData == "mute") {
//      fmute();
//      btSerial.println("Mute");
//    }
//
//    if (btData == "enter") {
//      fenter();
//      btSerial.println("Enter");
//    }
//
//    if (btData == "zurück" || btData == "return") {
//      freturn();
//      btSerial.println("zurück");
//    }
//
//    if (btData == "links") {
//      flinks();
//    }
//
//    if (btData == "rechts") {
//      frechts();
//    }
//
//    if (btData == "hoch") {
//      fhoch();
//    }
//
//    if (btData == "runter") {
//      frunter();
//    }
//
//    if (btData == "source") {
//      fsource();
//    }
//
//    if (btData == "pause") {
//      if (fernseher == 0)fon();
//      fpon();
//      delay(15000);
//      freturn();
//      delay(1000);
//      fpause();
//      record = 1;
//
//      btSerial.println("Pause");
//    }
//
//    if (btData == "play" && fernseher == 1 || binaer == 27) {
//      fplay();
//      btSerial.println("Play");
//    }
//
//    if (btData == "stop" && fernseher == 1) {
//      fstop();
//      record = 0;
//      btSerial.println("Stop");
//    }
//
//    if (btData == "-10" || btData == "-9" || btData == "-8" || btData == "-7" || btData == "-6" || btData == "-5" || btData == "-4" || btData == "-3" || btData == "-2" || btData == "-1" || btData == "1" || btData == "2" || btData == "3" || btData == "4" || btData == "5" || btData == "6" || btData == "7" || btData == "8" || btData == "9" || btData == "10") {
//      volume = atoi(btData.c_str());
//      switch (volume) {
//        case -10:
//          vcounter = 10;
//          break;
//        case -9:
//          vcounter = 9;
//          break;
//        case -8:
//          vcounter = 8;
//          break;
//        case -7:
//          vcounter = 7;
//          break;
//        case -6:
//          vcounter = 6;
//          break;
//        case -5:
//          vcounter = 5;
//          break;
//        case -4:
//          vcounter = 4;
//          break;
//        case -3:
//          vcounter = 3;
//          break;
//        case -2:
//          vcounter = 2;
//          break;
//        case -1:
//          vcounter = 1;
//          break;
//        case 1:
//          vcounter = 1;
//          break;
//        case 2:
//          vcounter = 2;
//          break;
//        case 3:
//          vcounter = 3;
//          break;
//        case 4:
//          vcounter = 4;
//          break;
//        case 5:
//          vcounter = 5;
//          break;
//        case 6:
//          vcounter = 6;
//          break;
//        case 7:
//          vcounter = 7;
//          break;
//        case 8:
//          vcounter = 8;
//          break;
//        case 9:
//          vcounter = 9;
//          break;
//        case 10:
//          vcounter = 10;
//          break;
//      }
//      if (volume > 0)flauter();
//      if (volume < 0)fleiser();
//    }
//
//    if (btData == "rec" && fernseher == 1) {
//      if (fp == 0) {
//        fpon();
//        delay(15000);
//        freturn();
//      }
//      fp = 1;
//      frec();
//    }
//
//    if (btData == "ppause" || binaer == 26) {
//      fpause();
//    }

    if (btData == "hilfe" || btData == "help" || btData == "-h") {
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
  delay(100);
}
