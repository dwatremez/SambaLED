void scriptPathForward(uint32_t colorOn, uint32_t colorOff, int start, int length) {
  strip.setPixelColor((indexLED+indexShift+start)%instrument.nbLED, colorOn);
  strip.setPixelColor((indexLED+indexShift+start+instrument.nbLED-length)%instrument.nbLED, colorOff);
  currentModulo = instrument.nbLED;
}

void scriptPathBackward(uint32_t colorOn, uint32_t colorOff, int start, int length) {
  strip.setPixelColor((2*instrument.nbLED-(indexLED%instrument.nbLED)+start-indexShift)%instrument.nbLED, colorOn);
  strip.setPixelColor((2*instrument.nbLED-(indexLED%instrument.nbLED)+start+length-indexShift)%instrument.nbLED, colorOff);
  currentModulo = instrument.nbLED;
}

void scriptShadeAll(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB, int increment) {
  unsigned int amplitude = (maximum(absolue(redA-redB), maximum(absolue(blueA-blueB), absolue(greenA-greenB)))+increment-1)/increment;
  if (indexLED%(2*amplitude)<amplitude) {
    scriptShadeAllAB(redA, greenA, blueA, redB, greenB, blueB, increment, amplitude);
  }
  else {
    scriptShadeAllAB(redB, greenB, blueB, redA, greenA, blueA, increment, amplitude);
  }
  currentModulo = 2*amplitude;
}

void scriptShadeAllAB(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB, int increment, int amplitude) {
  uint8_t red = scriptShadeColorCompAB(redA, redB, increment, amplitude);
  uint8_t green = scriptShadeColorCompAB(greenA, greenB, increment, amplitude);
  uint8_t blue = scriptShadeColorCompAB(blueA, blueB, increment, amplitude);
  uint32_t color = strip.Color(red, green, blue);
  scriptSetAll(color);
}

void scriptShadePath(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB, int increment) {
  unsigned int amplitude = (maximum(absolue(redA-redB), maximum(absolue(blueA-blueB), absolue(greenA-greenB)))+increment-1)/increment;
  if (indexLED%(2*amplitude)<amplitude) {
    scriptShadePathAB(redA, greenA, blueA, redB, greenB, blueB, increment, amplitude);
  }
  else {
    scriptShadePathAB(redB, greenB, blueB, redA, greenA, blueA, increment, amplitude);
  }
  currentModulo = 2*amplitude;
}

void scriptShadePathAB(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB, int increment, int amplitude) {
  uint8_t red = scriptShadeColorCompAB(redA, redB, increment, amplitude);
  uint8_t green = scriptShadeColorCompAB(greenA, greenB, increment, amplitude);
  uint8_t blue = scriptShadeColorCompAB(blueA, blueB, increment, amplitude);
  uint32_t color = strip.Color(red, green, blue);
  strip.setPixelColor(indexLED%instrument.nbLED, color);
}

uint8_t scriptShadeColorCompAB(uint8_t colorCompA, uint8_t colorCompB, int increment, int amplitude) {
  int16_t colorComp;
  if (colorCompA==colorCompB) {
    return colorCompA;
  }
  if (colorCompA<colorCompB) {
    colorComp = colorCompA+increment*((indexLED+indexShift)%amplitude);
    if (colorComp>colorCompB) {
      colorComp = colorCompB;
    }
  }
  else {
    colorComp = colorCompA-increment*((indexLED+indexShift)%amplitude);
    if (colorComp<colorCompB) {
      colorComp = colorCompB;
    }
  }
  return (uint8_t)colorComp;
}

void scriptSetAll(uint32_t c) {
  for(uint16_t i = 0; i < instrument.nbLED; i++) {
    strip.setPixelColor(i,c);
  }
}

void scriptGauge(uint32_t colorOnForward, uint32_t colorOffForward, uint32_t colorOnBackward, uint32_t colorOffBackward) {
  if ((indexLED+indexShift)%(2*instrument.nbLED)==0) {
    strip.setPixelColor(0, colorOffForward);
  }
  else if ((indexLED+indexShift)%(2*instrument.nbLED)<instrument.nbLED) {
    scriptPathForward(colorOnForward, colorOffForward, 0, 1);
  }
  else if ((indexLED+indexShift)%(2*instrument.nbLED)==instrument.nbLED) {
    strip.setPixelColor(0, colorOffBackward);
  }
  else {
    scriptPathBackward(colorOnBackward, colorOffBackward, instrument.nbLED, 1);
  }
  currentModulo = 2*instrument.nbLED;
}

uint8_t minimum(uint8_t a, uint8_t b) {
  if (a<b) {
    return a;
  }
  else {
    return b;
  }
}

uint8_t maximum(uint8_t a, uint8_t b) {
  if (a>b) {
    return a;
  }
  else {
    return b;
  }
}

uint16_t absolue(int a) {
  if (a>=0) {
    return a;
  }
  else {
    return -a;
  }
}

void scriptShadingOff() {
  for(uint16_t i = 0; i < instrument.nbLED; i++) {
    uint32_t currentColor = strip.getPixelColor(i);
    uint8_t partRed = (currentColor>>16)%256;
    uint8_t partGreen = (currentColor>>8)%256;
    uint8_t partBlue = currentColor%256;
    if (partRed>=indexLED) {
      partRed = partRed-indexLED;
    }
    else {
      partRed = 0;
    }
    if (partGreen>=indexLED) {
      partGreen = partGreen-indexLED;
    }
    else {
      partGreen = 0;
    }
    if (partBlue>=indexLED) {
      partBlue = partBlue-indexLED;
    }
    else {
      partBlue = 0;
    }
    uint32_t newColor = ((uint32_t)partRed<<16)+((uint32_t)partGreen<<8)+partBlue;
    strip.setPixelColor(i, newColor);
  }
}

