void listenRF() {
  scriptSetAll(colorRed);
  strip.show();
}

/*void listenRF() {
  if (mySwitch.available()) {
    uint32_t valueRadio = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    testRadioToggle();
    modeInformation = (valueRadio>>14)%2;
    uint8_t modeRadio = (valueRadio>>13)%2;
    uint8_t keyRadio = (valueRadio>>9)%16;
    uint16_t newIndexLED = valueRadio%512;
    if ((previousAnimation!=keyRadio) || (mode!=modeRadio)) {
      // animation has changed
      indexLED = 0;
      indexShift = 0;
      previousAnimation = keyRadio;
      mode = modeRadio;
      currentModulo = 1;
    }
    else {
      if (newIndexLED<indexLED) {
        // there was a loopback in indexLED
        // 1. play missing animations before loop back
        while (indexLED!=512) {
          performAnimation(keyRadio);
          indexLED = indexLED+1;
        }
        // 2. indexLED has now looped back: adjust indexShift
        indexLED = 0;
        indexShift = (512+indexShift)%currentModulo;
      }
    }
    while (indexLED<=newIndexLED) {
      performAnimation(keyRadio);
      if (instrument.leader==1) {
        showLeaderInformation();
      }
      indexLED = indexLED+1;
    }
    strip.show();
  }
}*/

void performAnimation(int keyRadio) {
  if (mode==0) {
    performAnimationBasic(keyRadio);
  }
  else {
    performAnimationAdvanced(keyRadio);
  }
}

void performAnimationBasic(int keyRadio) {
  if (keyRadio==KEY_0) {
    scriptSetAll(colorOff);
  }
  else if (keyRadio==KEY_1) {
    animationBrasil();
  }
  else if (keyRadio==KEY_2) {
    animationGirls();
  }
  else if (keyRadio==KEY_3) {
    animationMangueira();
  }
  else if (keyRadio==KEY_4) {
    animationDrums();
  }
  else if (keyRadio==KEY_5) {
    animationSambagogo();
  }
  else if (keyRadio==KEY_6) {
    animationShadingSlow();
  }
  else if (keyRadio==KEY_7) {
    animationShadingFast();
  }
  else if (keyRadio==KEY_8) {
    animationShadingPathSlow();
  }
  else if (keyRadio==KEY_9) {
    animationShadingPathFast();
  }
  else if (keyRadio==KEY_ASTERISK) {
  }
  else if (keyRadio==KEY_HASH) {
    // Note : can't be received (because of the remote control behavior)
  }
}

void performAnimationAdvanced(int keyRadio) {
  if (keyRadio==KEY_0) {
    animationShadingOff();
  }
  else if (keyRadio==KEY_1) {
    animationLignes(colorWhite, colorRed);
  }
  else if (keyRadio==KEY_2) {
    animationGaucheDroite(colorWhite, colorRed);
  }
  else if (keyRadio==KEY_3) {
    animationInstrumentsChoregraphie(colorYellow, colorAzur);
  }
  else if (keyRadio==KEY_4) {
    animationCharlie(colorRed, colorArgent);
  }
  else if (keyRadio==KEY_5) {
  }
  else if (keyRadio==KEY_6) {
  }
  else if (keyRadio==KEY_7) {
    animationLapin();
  }
  else if (keyRadio==KEY_8) {
    animationIntroVilaIsabel();
  }
  else if (keyRadio==KEY_9) {
  }
  else if (keyRadio==KEY_ASTERISK) {
  }
  else if (keyRadio==KEY_HASH) {
    // Note : can't be received (because of the remote control behavior)
  }
}

void testRadioToggle() {
    toggle = (toggle+1)%4;
    if (toggle==0) {
      strip.setPixelColor(instrument.nbLED-1, colorOff);
    }
    else {
      strip.setPixelColor(instrument.nbLED-1, colorWhite);
    }
    strip.show();
}

void testRadioValue(uint32_t value) {
  for (int i=0; i<24; i++) {
    testBooleanColor(i+1, value%2);
    value = value/2;
  }
  strip.show();
}

void testBooleanColor(int pos, int b) {
  if (b) {
    strip.setPixelColor(pos, colorWhite);
  }
  else {
    strip.setPixelColor(pos, colorOff);
  }
}

void showLeaderInformation() {
  if (modeInformation==0) {
    strip.setPixelColor(0, colorYellow);
  }
  else {
    strip.setPixelColor(0, colorAzur);
  }
}
