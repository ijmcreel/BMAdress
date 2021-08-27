#include<LiquidCrystal.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#define Wake 21

int Hour=0;
int Mins=0;
int Lnum=0;
char Letter;
const int button=2;
int Bstate=0;
char zero='0';
int FYBH=0;
int FYBM=0;
volatile int Loop_Count; 
int LCDBL=6;

/*
 * the Loop_Count will incrament for X amount of WatchdogTimer Cycles.
 * the Watch dog timer will trigger the sleep mode when it triggers.  this
 * will put the arduino to sleep which will save batery when the inevitable person forgets to 
 * turn the thing off. 
 */



//              (RS, E, D4, D5, D6, D7)  RW, VSS, K => Ground.  VDD => power. A=> power. 10k pot goes to V0 on LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT);
  pinMode(LCDBL,OUTPUT);
  Bstate=digitalRead(button);
  Serial.begin(9600);
 lcd.begin(16, 2);
   watchdogsetup();
    attachInterrupt(digitalPinToInterrupt(button), Wake_up,RISING);
    digitalWrite(LCDBL,HIGH);
}

void loop() 

{
  lcd.setCursor(0,0);
  lcd.print("    Push The  ");
   lcd.setCursor(0,1);
  lcd.print("     Button  ");
if(Loop_Count>=2){
  SleepNow();
}

 Bstate=digitalRead(button);

  if(Bstate==HIGH){
    Loop_Count=0;
     digitalWrite(LCDBL,HIGH);

    Hour=random(1,13);
    Mins=random(0,4)*15;
    Lnum=random(1,14);

FYBM=0;
FYBH=0;


    switch(Lnum){
      case 1:
      Letter='A';
      break;
      case 2:
      Letter='B';
      break;
      case 3:
      Letter='C';
      break;
      case 4:
      Letter='D';
      break;
      case 5:
      Letter='E';
      break;
      case 6:
      Letter='F';
      break;
      case 7:
      Letter='G';
      break;
      case 8:
      Letter='H';
      break;
      case 9:
      Letter='I';
      break;
      case 10:
      Letter='J';
      break;
      case 11:
      Letter='K';
      break;
      case 12:
      Letter='L';
      break;
      case 13:
      Letter=' ';
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Your Adventure");
    lcd.setCursor(0,1);
    lcd.print("Awaits At:");
 delay(2500);
        lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(Hour);
 lcd.print(":");
lcd.print(Mins);
if(Mins==0){
  lcd.print(0);
}
  

if(Lnum==13){
     lcd.print("&");
     lcd.print("Esplanade  ");
   FYBH=Hour+Lnum;
   FYBM=Hour*Mins;
     
}
if(Hour==10 and Mins<1){
lcd.setCursor(0,1);
lcd.print("HA! FUK YER BURN");
}
if(FYBH<=23 and FYBH>=15){
lcd.setCursor(0,1);
lcd.print("HA! FUK YER BURN");
delay(2500);

}else{

lcd.print(" & ");
lcd.print(Letter);
lcd.setCursor(0,1);
lcd.print("                ");
lcd.setCursor(0,1);
lcd.print("Have Fun  )'( ");

delay(2500);
lcd.clear();

}
  
  }else{

  
}




}//this is the end of the loop.




void SleepNow(){
  lcd.clear();
  digitalWrite(LCDBL,LOW);
  attachInterrupt(2, Wake_up,RISING);
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}



void Wake_up(){
  
  sleep_disable();
  //detachInterrupt(2);
  
}

void watchdogsetup(void){
  cli();
  wdt_reset();
  WDTCSR |=(1<<WDCE) |(1<<WDE);
  WDTCSR = (1<<WDIE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);//this sets WDT to 8s
  WDTCSR |=(1<WDIE);
  sei();

}
ISR(WDT_vect){
   wdt_reset();
   Loop_Count++;
 
}
