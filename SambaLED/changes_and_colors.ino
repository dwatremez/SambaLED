// Changement de couleurs
uint32_t oneColorEach(uint8_t nb)
{
  if(indexLED%nb == 0)
    indexColor++;

  if(indexColor >= NBCOLOR)
    indexColor = 0;

  return sambaColors[indexColor];

}

uint32_t oneColorEachLoop()
{
  return oneColorEach(instrument.nbLED);
}

// Chnagement après un certain temps
uint8_t changeAfterSomeSurdoRevolutions(uint8_t nb, uint8_t rev)
{
  if(indexLED == instrument.nbLED - 1)
    animVariation += 2 * instrument.type;
    
  if(animVariation >= nb * rev * 2 * BIG_CIRCULAR)
    animVariation = 0;
    
  return floor(animVariation / (2 * rev * BIG_CIRCULAR));
}
