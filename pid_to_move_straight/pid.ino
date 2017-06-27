#define Kp            1700L
#define Ki            20L
#define Kd            0L

int16_t pid_lastErr;
int16_t pid_sumErrs;

//----------------------------------------
//
//----------------------------------------

void resetPID()
{
  pid_lastErr = 0;
  pid_sumErrs = 0;
  adjustLMotor = adjustRMotor = 0;
  
  clear_ticks();
}

//----------------------------------------
//
//----------------------------------------

void PID1()
{
 // static int16_t lticks = 0, rticks = 0;
  static uint16_t ms = 0;
  int16_t  diff;
  int32_t delta;
  uint16_t dms;
  
  get_ticks_since_last( &dlticks, &drticks);

  

    // we assume wheels are turning in the same direction
    int16_t dir = ( dlticks < 0 || drticks < 0) ? -1 : 1;

    // make the values positive
    dlticks *= dir;
    rticks *= dir;
    
    //int16_t bias = 0L;
    diff = dlticks  - drticks ;
    

    // we want the difference to be 0

    // track the integral 
    pid_sumErrs += diff;

    // get the differential
    delta = (int32_t) (diff - pid_lastErr);

    int16_t P = (int16_t) ((Kp*((int32_t)diff)
                          + Ki*((int32_t)pid_sumErrs)
                          + (Kd*delta))/1000L);

    pid_lastErr = diff;
   // Serial.println(P);
    // a positive error means the left motor is 
    // turning more than the right so adjust 
    // each motor accordingly
    int16_t ladjust = (P+1/2)*dir;
    int16_t radjust = (P/2)*dir;
    adjustLMotor -= ladjust;
    adjustRMotor += radjust;
    
  //  Serial.println("DIFF = ");
    Serial.print(diff);
    Serial.print("\t");
    Serial.println(pid_sumErrs);
//    Serial.print(" ADJ = (");
//    Serial.print(adjustLMotor);
//    Serial.print(", ");
//    Serial.print(adjustRMotor);
//    Serial.println(")");
//    Serial.println(dlticks);
//    Serial.println(drticks);
    constrain( adjustLMotor, -100, 100);
    constrain( adjustRMotor,-100, 100);
    lspeed=LMotorSpeed+adjustLMotor;
    rspeed=RMotorSpeed+adjustRMotor;
//    Serial.println(lspeed);
//    Serial.println(rspeed);
    dlticks = 0;
    drticks = 0;
    en_lft_ticks=0;
    en_rht_ticks=0;
    ms = 0;
  
 
}
