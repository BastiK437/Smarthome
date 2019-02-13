const unsigned int tonoff []PROGMEM = {8800, 4400, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 1650, 500, 1700, 500, 1650, 550, 1650, 500, 1700, 500, 1650, 550};
const unsigned int tstumm []PROGMEM = {8750, 4400, 550, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 550, 550, 500, 1650, 550, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 550, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 550, 550, 1700, 500, 1650, 500, 1650, 550, 1650, 550, 1650, 500, 1650, 550, 1650, 550};
const unsigned int tsourceh[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500, 550, 500, 600, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 600, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tsourcer[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 550, 1650, 500, 600, 500, 1650, 550, 1650, 500, 1650, 550, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 550, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tlauter[]PROGMEM = {8800, 4400, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500};
const unsigned int tleiser[]PROGMEM = {8800, 4400, 500, 600, 500, 600, 500, 550, 500, 650, 450, 600, 500, 1650, 550, 1650, 500, 600, 500, 1650, 550, 550, 550, 1650, 500, 1650, 550, 1650, 500, 600, 500, 600, 500, 1650, 550, 550, 500, 1700, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 600, 450, 600, 500, 1700, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550};

//Global variables


void turnMusicsystemOn() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
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

void turnMusicsystemOff() {

  setSourceDVD();
  delay(500);
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tonoff + counter);
  }

  counter = 5;
  while (counter > 0) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }

  anlage = 0;
}

void sourceOneUp() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tsourceh + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void sourceOneDown() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tsourcer + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void setSourceDVD() {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    tape = 0;
  }

  if (aux == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    aux = 0;
  }

  dvd = 1;
}

void setSourceTape() {
  if (dvd == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    dvd = 0;
  }

  if (aux == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    aux = 0;
  }

  tape = 1;
}

void setSourceAux() {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    tape = 0;
  }

  if (dvd == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    dvd = 0;
  }

  aux = 1;
}

void volumeOneUp() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tlauter + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void volumeOneDown() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tleiser + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void setVolumeMute() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tstumm + counter);
  }
  irsend.sendRaw(senden, sizeof(senden) / sizeof(int), 40);
}

void setVolume(int value){
  counter2 = al - value;
  al = value;
  if(counter2 > 0){
    while(counter2 > 0){
      volumeOneUp();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0){
    while(counter2 < 0){
      volumeOneDown();
      delay(td);
      counter2++;
    }
  }
}
