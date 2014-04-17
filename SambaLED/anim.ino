// Animations Complètes

void Brasil()
{
  if(instrument.type == BAR)
  {
    if(animDirection == 0)
    {
      colorWipe(sambaYellow);
      if(indexLED == instrument.nbLED - 1)
        animDirection = 1;
    }
    else
    {
      colorWipe(sambaGreen);
      if(indexLED == instrument.nbLED - 1)
        animDirection = 0;
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
    if(animDirection == 0)
    {
      colorPathForward(sambaEmeraud, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        animDirection = 1;
    }
    else
    {
      colorPathBackward(sambaCuisseDeNimpheEmue, off, instrument.lenght);
      if(indexLED == instrument.nbLED - 1)
        animDirection = 0;
    }     
  }

}


void Geo(uint8_t index)
{

  if(instrument.place == FIRST)
    colorPathBackForth(sambaColors[index], off, instrument.lenght);

  if(instrument.place == BETWEEN)
    if(index + 1 < NBCOLOR)
    {
      colorPathForward(sambaColors[index + 1], off, instrument.lenght);
    }
    else
    {
      colorPathForward(sambaColors[index + 1 - NBCOLOR], off, instrument.lenght);
    }

  if(instrument.place == LAST)
    if(index + 7 < NBCOLOR)
    {
      colorPathForward(sambaColors[index + 7], off, instrument.lenght);
    }
    else
    {
      colorPathForward(sambaColors[index + 7 - NBCOLOR], off, instrument.lenght);
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

