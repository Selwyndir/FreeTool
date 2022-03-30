#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53//Pin RFID
#define RST_PIN 5//Pin RFID
#define pinMaxX 4//bouton fdc +
#define pinMinX 6//bouton fdc -
#define pinStepX 7
#define pinDirX 8
#define pinEnableX 9
#define IR_output 2//IR
//LEDS
#define REDLED 49
#define GREENLED 48
int pinMax = 0;
int pinMin = 0;

byte CodeVerif2=0; 
byte CodeVerif=0; 
//ALL USERS
byte Code_Acces[4]={0xC3, 0xAA, 0x1F, 0x16}; 

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

// Init array that will store new NUID 
byte nuidPICC[4];

int RFID_CHECK = 2;
int STATE_P = 2;
int i=0;

void setup() {
  //SERIAL PORTE
  Serial.begin(9600);
  SPI.begin();// Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  pinMode(IR_output, INPUT);//IR
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
  READ_RFID();
  if(STATE_P==1){
    READ_RFID2();
  }
   if(digitalRead(IR_output)==HIGH){  //si le signal est a l'etat haut
    Serial.println("0x3");
    if(STATE_P==1){
      Serial.println("0x5");
    }
    else if(STATE_P==0){
      Serial.println("0x4");
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
    closedoor();
    digitalWrite(REDLED, HIGH);
    delay(1000);
    digitalWrite(REDLED, LOW);
    STATE_P=0;
    }
  else if (CodeVerif==1)
  {
    Serial.println("0x1");
    opendoor();
    digitalWrite(GREENLED, HIGH);
    delay(1000);
    digitalWrite(GREENLED, LOW);
    STATE_P=1;
    }
  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}
void READ_RFID2(){
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
  CodeVerif2= GetAccesState(Code_Acces,nuidPICC); 
  if (CodeVerif2==1)
  {
    Serial.println("0x2");//envoi message au serv
    STATE_P=0;
    closedoor();
    digitalWrite(GREENLED, HIGH);
    delay(1000);
    digitalWrite(GREENLED, LOW);
    }
  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
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
  digitalWrite(pinEnableX, LOW);
  digitalWrite(pinDirX, LOW);
  pinMax = digitalRead(pinMaxX);
  while(pinMax != 0){
    digitalWrite(pinStepX, HIGH);
    delay(0.005);
    digitalWrite(pinStepX, LOW);
    delay(0.005);
    pinMax = digitalRead(pinMaxX);
    Serial.print(pinMax);
    }
  }

//FERMETURE PORTE
void closedoor(){
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
  }
