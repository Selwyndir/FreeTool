#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5
#define pinMaxX 4//bouton fdc +
#define pinMinX 6//bouton fdc -
#define pinStepX 7
#define pinDirX 8
#define pinEnableX 9
//IR
#define IR_output 2
//LEDS
#define REDLED 49
#define GREENLED 48
int pinMax = 666;
int pinMin = 666;

byte CodeVerif=0; 
//ALL USERS
byte Code_Acces[4]={0xC3, 0xAA, 0x1F, 0x16}; 

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

// Init array that will store new NUID 
byte nuidPICC[4];

int RFID_CHECK = 0;
int DETEC_INFRAR = 0;
int CHECKEDOUT = 0;
int STATE_P = 2;
int i=0;

void setup() {
  //SERIAL PORTE
  Serial.begin(9600);
    // Init SPI bus
  SPI.begin();
  // Init MFRC522 
  rfid.PCD_Init(); 
  //IR
  pinMode(IR_output, INPUT);
  //LEDS
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED,OUTPUT);
  //PIN MOTOR
  pinMode(pinStepX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinEnableX, OUTPUT);
  pinMode(pinMinX, INPUT);
  pinMode(pinMaxX, INPUT);
}

void loop() {
  closedoor();
  RC522_CHECK();
  if(STATE_P==1){
    RC522_CHECKOUT();
  }
  detec_infra();
  if(DETEC_INFRAR==HIGH){
    if(STATE_P==1){
      take_pic();
        }
    else if(STATE_P==0){
      fonc_cam();
  }
}
}

//-------------------------------------------------------------- FONCTION --------------------------------------------------------------
//LIRE RFID
void READ_RFID(){
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;

  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  // Enregistrer l’ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  // Vérification du code 
  CodeVerif= GetAccesState(Code_Acces,nuidPICC); 
  if (CodeVerif!=1)
  {
    RFID_CHECK=2;
  }
  else if (CodeVerif==1)
  {
    RFID_CHECK=1;
    CHECKEDOUT=1;
    }
  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}

//CHECK LE RFID
void RC522_CHECK(){
  READ_RFID();
  if(RFID_CHECK==1){
    opendoor();
    digitalWrite(GREENLED, HIGH);
    delay(1000);
    digitalWrite(GREENLED, LOW);
  }
  else if(RFID_CHECK==2){
    closedoor();
    digitalWrite(REDLED, HIGH);
    delay(1000);
    digitalWrite(REDLED, LOW);
  }
}

//CHECK POUR REFERMER LA PORTE
void RC522_CHECKOUT(){
  READ_RFID();
  if(CHECKEDOUT==1){
    closedoor();
    digitalWrite(GREENLED, HIGH);
    delay(1000);
    digitalWrite(GREENLED, LOW);
    CHECKEDOUT=0;
  }
}

//INFRAROUGE
void detec_infra() {
   if(digitalRead(IR_output)==HIGH){  //si le signal est a l'etat haut
   Serial.println("1x1");
   DETEC_INFRAR = 1;
  }
}
byte GetAccesState(byte *CodeAcces,byte *NewCode) 
{
  byte StateAcces=0; 
  if ((CodeAcces[0]==NewCode[0])&&(CodeAcces[1]==NewCode[1])&&
  (CodeAcces[2]==NewCode[2])&& (CodeAcces[3]==NewCode[3]))
    return StateAcces=1; 
  else
    return StateAcces=0; 
}

//OUVERTURE PORTE
void opendoor(){
  Serial.print("0x1");//envoi message au serv
  digitalWrite(pinEnableX, LOW);
  digitalWrite(pinDirX, LOW);
  pinMax = digitalRead(pinMaxX);
  while(pinMax != 0){
    digitalWrite(pinStepX, HIGH);
    delay(0.005);
    digitalWrite(pinStepX, LOW);
    delay(0.005);
    pinMin = digitalRead(pinMaxX);
    }
    STATE_P = 1;
}

//FERMETURE PORTE
void closedoor(){
  Serial.print("0x2");//envoi message au serv
  digitalWrite(pinEnableX, LOW);
  digitalWrite(pinDirX, HIGH);
  pinMin = digitalRead(pinMinX);
  while(pinMin != 0){
    digitalWrite(pinStepX, HIGH);
    delay(0.005);
    digitalWrite(pinStepX, LOW);
    delay(0.005);
    pinMin = digitalRead(pinMinX);
  }
  STATE_P = 0;
}
//ALLUMER CAMERA
//INTRUDER
void fonc_cam() {
 Serial.print("2x1");
}


//PRENDRE PHOTO
//USER DANS L'ABRI
void take_pic() {
 Serial.print("2x2");
}

//--------------------------------------------------------------------------------------------------------------------------------------