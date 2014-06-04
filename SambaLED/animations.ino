void animationBrasil() {
  if (instrument.type==BARRE) {
    scriptGauge(colorGreen, colorOff, colorYellow, colorOff);
  }
  else if (instrument.name==SURDO1) {
    scriptPathForward(colorYellow, colorOff, 0, 3);
  }
  else if(instrument.name == SURDO2) {
    scriptPathBackward(colorGreen, colorOff, 0, 3);
  }
  else {
    scriptPathForward(colorYellow, colorOff, 0, 3);
    scriptPathBackward(colorGreen, colorOff, 0, 3);
  }
}

void animationGirls() {
  if(instrument.name==SURDO1) {
    scriptPathBackward(colorEmeraud, colorOff, 0, 3);
  }
  else if(instrument.name==SURDO2) {
    scriptPathForward(colorCuisseDeNimpheEmue, colorOff, 0, 3);
  }
  else if(instrument.name==SURDO3) {
    scriptGauge(colorEmeraud, colorOff, colorCuisseDeNimpheEmue, colorOff);
  }
  else {
    scriptGauge(colorEmeraud, colorCuisseDeNimpheEmue, colorCuisseDeNimpheEmue, colorEmeraud);
  }
}

void animationMangueira() {
  if(instrument.type==BARRE) {
    scriptGauge(colorFuchsia, colorGreen, colorGreen, colorFuchsia);
  }
  else if(instrument.name==SURDO1) {
    scriptPathForward(colorFuchsia, colorOff, 0, 3);
  }
  else if(instrument.name==SURDO2) {
    scriptPathForward(colorGreen, colorOff, 0, 3);
  }
  else {
    scriptPathForward(colorGreen, colorFuchsia, 0, 3);
  }
}

void animationSambagogo() {
  if ((instrument.name==AGOGO) || (instrument.name==CAIXA)) {
    scriptPathForward(colorRed, colorOff, 0, 3);
  }
  else if ((instrument.name==TAMBORIM) || (instrument.name==REPIQUE)) {
    scriptPathForward(colorYellow, colorOff, 0, 3);
  }
  else {
    scriptPathForward(colorCarrot, colorOff, 0, 3);
  }
}

void animationDrums() {
  if ((instrument.name==CAIXA) || (instrument.name==REPIQUE)) {
    scriptPathForward(colorCarrot, colorOff, 0, 5);
    scriptPathBackward(colorRed, colorOff, 0, 5);
  }
  else {
    scriptPathForward(colorOff, colorOff, 0, 1);
  }
}

/*void animationGeo(uint8_t index) {
  geoColor[0] = colors[index];
  if(index + 1 < NBCOLOR) {
    geoColor[1] = colors[index + 1];
  }
  else {
    geoColor[1] = colors[index + 1 - NBCOLOR];
  }
  if(index + 7 < NBCOLOR) {
    geoColor[2] = colors[index + 7];
  }
  else {
    geoColor[2] = colors[index + 7 - NBCOLOR];
  }
  animIndexColor = changeAfterSomeSurdoRevolutions(3,5);
  // Définition par placement
//  if(instrument.place == FIRST)
//    colorPathBackForth(geoColor[animIndexColor], colorOff, instrument.length);
 // if(animIndexColor + instrument.place < 3) {
 //   colorPathForward(geoColor[animIndexColor + instrument.place], colorOff, instrument.length);
 // }
 // else {
 //   colorPathForward(geoColor[animIndexColor + instrument.place - 3], colorOff, instrument.length);
 // }
}*/

/*void animationWave() {
  if(instrument.type==CERCLE) {
//    colorPathForward(colorEmeraud, colorOff, instrument.length);
//    colorPathBackward(colorBlue, colorOff, instrument.length);
  }
  else {
    setCurrentPixel(colorOff);
  }
}*/

/*void animationLine(uint8_t nbColor, uint32_t colors[], uint8_t rev) {
  animIndexColor = changeAfterSomeSurdoRevolutions(nbColor,rev);
  if(animIndexColor + LINE < nbColor) {
    colorPathForward(colors[animIndexColor + LINE], colorOff, instrument.length);
  }
  else {
    colorPathForward(colors[animIndexColor + LINE - nbColor], colorOff, instrument.length);
  }
}*/

/*void animationCharlie() {
  animationLine(2,charlieColors,3);
}*/

void animationLignes(uint32_t colorImpair, uint32_t colorPair) {
  if (instrument.ligne%2==0) {
    scriptSetAll(colorPair);
  }
  else {
    scriptSetAll(colorImpair);
  }
}

void animationGaucheDroite(uint32_t colorGauche, uint32_t colorDroite) {
  if (instrument.gauche==1) {
    scriptSetAll(colorGauche);
  }
  else {
    scriptSetAll(colorDroite);
  }
}

void animationInstrumentsChoregraphie(uint32_t colorChore, uint32_t colorPasChore) {
  if ((instrument.type==BARRE) || (instrument.name==TAMBORIM)) {
    scriptSetAll(colorChore);
  }
  else {
    scriptSetAll(colorPasChore);
  }
}

void animationCharlie(uint32_t colorCharlie, uint32_t colorPasCharlie) {
  if (instrument.charlie==1) {
    scriptSetAll(colorCharlie);
  }
  else {
    scriptSetAll(colorPasCharlie);
  }
}

void animationShadingSlow() {
  scriptShadeAll(0, 250, 0, 0, 100, 150, 1);
}

void animationShadingFast() {
  scriptShadeAll(100, 0, 250, 100, 150, 100, 5);
}

void animationShadingPathSlow() {
  scriptShadePath(0, 0, 0, 200, 200, 200, 1);
}

void animationShadingPathFast() {
  scriptShadePath(0, 0, 0, 200, 200, 200, 5);
}

void animationLapin() {
  int delai = 5*(instrument.ligne-1)+1;
  if ((indexLED>=delai) && (indexLED<delai+10)) {
    scriptShadeAll(0, 0, 0, 200, 0, 0, 20);
  }
  else if ((indexLED>=delai+10) && (indexLED<delai+15)) {
    scriptShadeAll(200, 0, 0, 200, 100, 0, 20);
  }
  else {
    scriptSetAll(colorOff);
  }
  currentModulo = 1;
}

void animationIntroVilaIsabel() {
  if (((indexLED==1) && (instrument.name==SURDO3))
    || ((indexLED==3) && (instrument.name==REPIQUE))
    || ((indexLED==5) && (instrument.name==CAIXA))
    || ((indexLED==7) && (instrument.name==TAMBORIM))
    || ((indexLED==9) && (instrument.name==CHOCALHO))
    || ((indexLED==11) && (instrument.name==AGOGO))
    || ((indexLED==13) && ((instrument.name==SURDO1) || (instrument.name==SURDO2)))
    || (indexLED==15)) {
    scriptSetAll(colorBlue);
  }
  else if (indexLED==17) { // tout le monde crie
    scriptSetAll(colorGreen);
  }
  else {
    scriptSetAll(colorOff);
  }
  currentModulo = 1;
}

void animationShadingOff() {
  scriptShadingOff();
  currentModulo = 1;
}
