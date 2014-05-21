// Animations Complètes

void Brasil()
{
  if(instrument.type == BAR)
  {
    if(animVariation == 0)
    {
      colorWipe(sambaYellow);
      if(indexLED == instrument.nbLED - 1)
        animVariation = 1;
    }
    else
    {
      colorWipe(sambaGreen);
      if(indexLED == instrument.nbLED - 1)
        animVariation = 0;
    }     
  }

  if(instrument.type == CIRCULAR || instrument.name == SURDO3)
  {
    colorPathForward(sambaYellow, off, instrument.lenght);
    colorPathBackward(sambaGreen, off, instrument.lenght);           

  }

  if(instrument.name == SURDO1)
    colorPathForward(sambaYellow, off, instrument.lenght);

  if(instrument.name == SURDO2)
    colorPathBackward(sambaGreen, off, instrument.lenght);
}

void Mangueira()
{
  if(instrument.type == BAR)
    colorPathBackForth(sambaFuchsia, sambaGreen, 1);

  if(instrument.type == CIRCULAR || instrument.name == SURDO3)
    colorPathForward(sambaGreen, sambaFuchsia, 0.5 * instrument.nbLED);

  if(instrument.name == SURDO1)
    colorPathForward(sambaFuchsia, off, 0.5 * instrument.nbLED);

  if(instrument.name == SURDO2)
    colorPathForward(sambaGreen, off, 0.5 * instrument.nbLED);

}

void Girls()
{

  if(instrument.type == BAR)
    colorGauge(sambaEmeraud, sambaCuisseDeNimpheEmue);
  if(instrument.type == CIRCULAR)
    colorGauge(sambaEmeraud, sambaCuisseDeNimpheEmue);

  if(instrument.name == SURDO1)
    colorPathBackward(sambaEmeraud, off, instrument.lenght);
  if(instrument.name == SURDO2)
    colorPathForward(sambaCuisseDeNimpheEmue, off, instrument.lenght);  

  if(instrument.name == SURDO3)
  {
    if(animVariation == 0)
    {
      colorPathForward(sambaEmeraud, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        animVariation = 1;
    }
    else
    {
      colorPathBackward(sambaCuisseDeNimpheEmue, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        animVariation = 0;
    }     
  }

}


void Geo(uint8_t index)
{
  // Définition GeoColor
  geoColor[0] = sambaColors[index];
  if(index + 1 < NBCOLOR)
  {
    geoColor[1] = sambaColors[index + 1];
  }
  else
  {
    geoColor[1] = sambaColors[index + 1 - NBCOLOR];
  }
  if(index + 7 < NBCOLOR)
  {
    geoColor[2] = sambaColors[index + 7];
  }
  else
  {
    geoColor[2] = sambaColors[index + 7 - NBCOLOR];
  }

  animIndexColor = changeAfterSomeSurdoRevolutions(3,5);

  // Définition par placement
  if(instrument.place == FIRST)
    colorPathBackForth(geoColor[animIndexColor], off, instrument.lenght);


  if(animIndexColor + instrument.place < 3)
  {
    colorPathForward(geoColor[animIndexColor + instrument.place], off, instrument.lenght);
  }
  else
  {
    colorPathForward(geoColor[animIndexColor + instrument.place - 3], off, instrument.lenght);
  }

}

void Sambagogo()
{
  if(instrument.name == AGOGO)
    colorWipe(sambaRed);

  if(instrument.name == TAMBORIM)
    colorWipe(sambaYellow);

  if(instrument.name == CHOCALHO)
    colorWipe(sambaCarrot);

  if(instrument.name == CAIXA)
    colorWipe(sambaCarrot);

  if(instrument.name == REPIQUE)
    colorWipe(sambaYellow);

  if(instrument.type == BIG_CIRCULAR)
    colorWipe(sambaRed);
}

void Drums()
{
  if(instrument.name != CAIXA && instrument.name != REPIQUE)
  {
    colorWipe(off);
  }
  else
  {          
    colorPathForward(sambaCarrot, off, instrument.lenght);
    colorPathBackward(sambaRed, off, instrument.lenght);          
  }


}

void Wave()
{
  if(instrument.type != BIG_CIRCULAR)
  {
    colorWipe(off);
  }
  else
  {
    colorPathForward(sambaEmeraud, off, instrument.lenght);
    colorPathBackward(sambaBlue, off, instrument.lenght);

  }
}

void Line(uint8_t nbColor, uint32_t colors[], uint8_t rev)
{
  animIndexColor = changeAfterSomeSurdoRevolutions(nbColor,rev);
  
  
  if(animIndexColor + LINE < nbColor)
  {
    colorPathForward(colors[animIndexColor + LINE], off, instrument.lenght);
  }
  else
  {
    colorPathForward(colors[animIndexColor + LINE - nbColor], off, instrument.lenght);
  }

  
  
}

void Charlie()
{
  Line(2,charlieColors,3);
}


