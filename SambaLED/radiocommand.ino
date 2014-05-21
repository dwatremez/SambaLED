void playScript(uint16_t s)
{
  switch(s)
  {
  default:
    break;
  case KEY_0:
    colorFull(off);
    break;
  case KEY_1:
    Mangueira();
    break;
  case KEY_2:
    Girls();
    break;
  case KEY_3:
    Brasil();
    break;
  case KEY_4:
    Geo(1);
    break;
  case KEY_5:
    Geo(3);
    break;
  case KEY_6:
    Geo(9);
    break;
  case KEY_7:
    Drums();
    break;
  case KEY_8:
    Sambagogo();
    break;
  case KEY_9:
    Wave();
    break;
  case KEY_ASTERISK:
    break;
  case KEY_HASH:
    break;
  }
}
