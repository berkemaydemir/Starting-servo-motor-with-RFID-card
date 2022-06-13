#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   
Servo DoorLock;

int rs =7, en=6, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() 
{
 DoorLock.attach(SERVO_PIN);

  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  lcd.begin(16,2);
  Serial.println("Kartinizi okutun");
  Serial.println();

}
void loop() 
{  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lutfen");
  lcd.setCursor(0,1);
  lcd.print("kartinizi okutun");
  delay(500);
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Okutulan kartın tagini serial portta yazdırma
  Serial.print("UID tag :");
  String content= "";

  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "0A B7 C4 A4")
  {DoorLock.write(90); 
          lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gecebilirsiniz ") ;   
    lcd.setCursor(0,1);
    lcd.print("iyi gunler") ;       
            delay(5000);
            DoorLock.write(0);
    Serial.println("Dogru kart");
    delay(1000);
  
       
  }
 
 else   {
    Serial.println(" Yanlis kart");
      lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lutfen dogru");
  lcd.setCursor(0,1);
  lcd.print("karti okutun");
    delay(3000);
  }
} 
