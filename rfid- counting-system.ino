#include <LiquidCrystal_I2C.h>
#include <SPI.h> 
#include <MFRC522.h>
#define SS_PIN 10 
#define RST_PIN 9 
int pulsante=3;       //pulsante di reset
int val=LOW;
int incremento=0;
bool test=false;


LiquidCrystal_I2C lcd(0x27,16,2);
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  Serial.begin(9600); 
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode (pulsante,INPUT);
  lcd.setCursor(0,0);
  lcd.print("accosta la carta");
  lcd.setCursor(2,1);
  lcd.print("per l'accesso");

}

void loop()
{
  val=digitalRead(pulsante);
    if(val==HIGH){
    incremento=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("accosta la carta");
    lcd.setCursor(2,1);
    lcd.print("per l'accesso"); 
  }

  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return; 
}
  Serial.print("Die UID des RFID-TAGS lautet:"); 
  String rfid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
    rfid += String(mfrc522.uid.uidByte[i], HEX);
    
  }
    rfid.trim(); 
    rfid.toUpperCase(); 
  {
    Serial.print(rfid); 
    Serial.println(); 
  }

  
  if (rfid == "13 3C 5A 1B"){
    incremento= incremento + 1;
    Serial.println(incremento);
    delay(200);

    if(incremento>3 and test==false){
      test=true;
      delay(100);
   }

   if(test==true){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("pass negato");
      lcd.setCursor(0,1);
      lcd.print("fare abbonamento");
      test=false;
      delay(10);
   }
   else{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("pass consentito");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("accosta la carta");
    lcd.setCursor(2,1);
    lcd.print("per l'accesso");
  }
 }
}
