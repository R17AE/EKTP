#define banyakTag 7 
String idTag[7]={"131141642","41077858","429130146","46828234","41507042","46728234"};  
#define Jeda delay(500) 
#define Jeda_Lama delay(6000) 
#define Buzzer_Pin 5 
#define Buzzer_Init pinMode(Buzzer_Pin, OUTPUT) 
#define Buzzer_On analogWrite(Buzzer_Pin, 100) 
#define Buzzer_Off analogWrite(Buzzer_Pin, 0) 
#define Button_Pin 2 
#define Button_Init pinMode(Button_Pin, INPUT_PULLUP) 
#define Button_Read digitalRead(Button_Pin) 
#define Door_Lock A5 
#define Door_Lock_Init pinMode(Door_Lock, OUTPUT) 
#define Door_Lock_On digitalWrite(Door_Lock, LOW) 
#define Door_Lock_Off digitalWrite(Door_Lock, HIGH) 
#define LED_Warning_Pin 4 
#define LED_Warning_Init pinMode(LED_Warning_Pin, OUTPUT) 
#define LED_Warning_On digitalWrite(LED_Warning_Pin, 0) 
#define LED_Warning_Off digitalWrite(LED_Warning_Pin, 1) 
#define LED_Door_Pin 3 
#define LED_Door_Init pinMode(LED_Door_Pin, OUTPUT) 
#define LED_Door_On digitalWrite(LED_Door_Pin, 0) 
#define LED_Door_Off digitalWrite(LED_Door_Pin, 1)  String dataTag; 
#include <SPI.h> 
#include <MFRC522.h> 
#define SS_PIN 10 
#define RST_PIN 9 
MFRC522 rfid(SS_PIN, RST_PIN);  
#define RFID_RC522_Init  SPI.begin(); rfid.PCD_Init(); 
void lihat_uID()
{
  for (byte i = 0; i < 4; i++)
  {
       Serial.print(rfid.uid.uidByte[i]);
    Serial.print(',');
  }
  Serial.println();
}
void ambil_dataTag()
{
  dataTag="";
  for (byte i = 0; i < 4; i++)
  {
    dataTag += rfid.uid.uidByte[i];
  }
  Serial.println(dataTag);
}
byte check_uID(String varCheck)
{
  for (byte i=0; i<banyakTag; i++)
  {
    if (varCheck == idTag[i])
    {
      return 1;
    }
  }
  return 0;
}
#define pbPress if(Button_Read==0){Buzzer_Off; return;}
#define Alarm Buzzer_On; while (1){LED_Warning_On; Jeda; LED_Warning_Off; Jeda; pbPress}
#define uID_Invalid if(check_uID(dataTag)==0){Alarm}
#define uID_Valid if(check_uID(dataTag)==1){LED_Door_On; Door_Lock_On; Jeda_Lama; Door_Lock_Off; LED_Door_Off;
}
void setup() 
{
  Door_Lock_Init;Door_Lock_Off;
  Buzzer_Init;
  Button_Init;
  LED_Warning_Init; LED_Warning_Off;
  LED_Door_Init; LED_Door_Off;
  RFID_RC522_Init;
  Serial.begin(9600);
}
void loop()
{
  if (rfid.PICC_IsNewCardPresent())
  {
    if (rfid.PICC_ReadCardSerial())
    {
      ambil_dataTag();
          uID_Valid
      uID_Invalid
       }
  }
} 
