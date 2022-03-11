#include <RTClib.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//pin LCD
// com rasp
String nom = "Arduino";
String msg;
// var
int joe = 0;
int moe = 0;
int ane = 0;
int temp_emp = 7;//temps de l'emprunt
int jor = 0;
int jod = 0;
int emp = 0;//obj emprunté ou non
int joa = 0;
int moa = 0;
int ana = 0;
int hb = 0;
int sta = 0;
// var butt
int Button = 10;
int state_button = 0;

RTC_DS1307 rtc;
 
void setup () {
  Serial.begin(9600);
  lcd.setCursor(0, 1);
  while (! rtc.begin()) {
    lcd.print("RTC ...");
    delay(1000);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  lcd.print("RTC a jour");
  pinMode(Button, INPUT_PULLUP);
  delay(1000);
  lcd.clear();
}
 
void loop () {
  DateTime now = rtc.now();
  char heure[10];
  lcd.clear();
  state_button=digitalRead(Button);
  if(state_button==LOW){
    ret();    
    }
  else if(state_button==HIGH){
    gett();
    }
  }


void ret(){
  lcd.print("Outil disponible");
  delay(1000);
  sta = 0;
  Serial.println("Outils disponible");
  }
void gett(){
  DateTime now = rtc.now();
  char heure[10];
  if(sta==0){
    joe = now.day();
    moe = now.month();
    ane = now.year();
    jor = joe + temp_emp;
    sta=1;
    }
  joa = now.day();
  jod = jor-joa;
  sprintf(heure, "%02d/%02d/%02d", jor, moe, ane);
  lcd.print("Retour");
  lcd.print(heure);
  delay(2000);
  lcd.clear();
  lcd.print("Dans ");
  lcd.print(jod);
  lcd.print(" jours");
  delay(2000);
  Serial.print("Outil emprunté le ");
  Serial.print(joe);
  Serial.print("/");
  Serial.print(moe);
  Serial.print("/");
  Serial.print(ane);
  Serial.print(". Il reste ");
  Serial.print(jod);
  Serial.println(" jours pour le ramener");
  } 
