
#include <PinChangeInt.h>
volatile int16_t en_lft_ticks = 0;
volatile int16_t en_rht_ticks = 0;
volatile uint16_t en_counter = 0;
volatile bool en_error = false;
char en_lApin;
char en_lBpin;
char en_rApin;
char en_rBpin;

//----------------------------------------
//
//----------------------------------------

void setup_encoder( char lftPinA, char lftPinB, char rhtPinA, char rhtPinB )
{
  pinMode(lftPinA, INPUT_PULLUP);
  pinMode(lftPinB, INPUT_PULLUP);
  pinMode(rhtPinA, INPUT_PULLUP);
  pinMode(rhtPinB, INPUT_PULLUP);
  attachPinChangeInterrupt(11, Demxung, FALLING);
  attachPinChangeInterrupt(10, Demxung1, FALLING);
}


bool get_ticks_since_last( int16_t *lft, int16_t *rht)
{
  cli();
  *lft = en_lft_ticks;
  *rht = en_rht_ticks;
 
 // en_lft_ticks = en_rht_ticks = en_counter = 0;
  char error = en_error;
  en_error = false;
  sei();

  return !error;
}

//----------------------------------------
//
//----------------------------------------

void clear_ticks()
{
  cli();
  en_lft_ticks = en_rht_ticks = en_counter = 0;
  en_error = false;
  sei();
}

//----------------------------------------
//
//----------------------------------------
void Demxung()
{
  if(digitalRead(12)==0)
  {
    en_lft_ticks++;
  }
  else
  {
    en_lft_ticks--;
  }
 
  
}
void Demxung1()
{

  if(digitalRead(9)==0)
 {
    en_rht_ticks++;
  }
 else
 {
   en_rht_ticks--;
 }
  
}


