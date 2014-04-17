// Scripts d'animation

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

