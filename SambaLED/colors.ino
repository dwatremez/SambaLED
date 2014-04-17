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

