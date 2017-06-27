#include <PinChangeInt.h>
#include <TimerOne.h>
char lftApin    = 10;
char lftBpin    = 9;
char rhtApin    = 11;
char rhtBpin    = 12;
int16_t dlticks, drticks,lticks=0,rticks=0,dms;
int adjustLMotor  = 0;
int adjustRMotor  = 0;
int LMotorSpeed  = 150;
int RMotorSpeed   = 150;
int lspeed=LMotorSpeed ;int rspeed =RMotorSpeed;
void setup() {
  // put your setup code here, to run once:
  setup_encoder(  lftApin,  lftBpin,  rhtApin,  rhtBpin );
  Serial.begin(9600);
  Timer1.initialize(100000);
  Timer1.attachInterrupt(PID1);
  resetPID();
   pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
}

void loop() {
  
     control_motor();

}

void control_motor()
{

  digitalWrite(3,1);
   digitalWrite(4,0);
   digitalWrite(7,1);
   digitalWrite(8,0);
   analogWrite(5,lspeed);
   analogWrite(6,rspeed);
}

