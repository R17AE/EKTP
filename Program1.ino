/*************************************************************************
GELOBAL VARIABLE
*************************************************************************/
#define banyakTag 7
String idTag[7]={"131141642","41077858","429130146","46828234","41507042","46728234"}; //<< tambah index dan id baru jika ingin menambah id Tag

/*************************************************************************
JEDA (WAKTU TUNGGU) OBJECT
*************************************************************************/
#define Jeda delay(500)
#define Jeda_Lama delay(6000)

/*************************************************************************
BUZZER
*************************************************************************/
//BUZZER_PIN
#define Buzzer_Pin    5
//BUZZER_PARAMETER
#define Buzzer_Init   pinMode(Buzzer_Pin, OUTPUT)
//BUZZER_PROGRAM
#define Buzzer_On   analogWrite(Buzzer_Pin, 100)
#define Buzzer_Off    analogWrite(Buzzer_Pin, 0)

/*************************************************************************
BUTTON
*************************************************************************/
//BUTTON_PIN
#define Button_Pin    2
//BUTTON_PARAMETER
#define Button_Init   pinMode(Button_Pin, INPUT_PULLUP)
//BUTTON_PROGRAM
#define Button_Read   digitalRead(Button_Pin)

/*************************************************************************
SOLENOID_LOCK
*************************************************************************/
//Door_Lock
#define Door_Lock   A5
//LOCK_PARAMETER
#define Door_Lock_Init  pinMode(Door_Lock, OUTPUT)
//LOCK_PROGRAM
#define Door_Lock_On  digitalWrite(Door_Lock, LOW)
#define Door_Lock_Off digitalWrite(Door_Lock, HIGH)

/*************************************************************************
LED_Warning
*************************************************************************/
//LED_Warning_PIN
#define LED_Warning_Pin   4
//LED_Warning_PARAMETER
#define LED_Warning_Init  pinMode(LED_Warning_Pin, OUTPUT)
//LED_Warning_PROGRAM
#define LED_Warning_On    digitalWrite(LED_Warning_Pin, 0)
#define LED_Warning_Off   digitalWrite(LED_Warning_Pin, 1)

/*************************************************************************
LED_Door
**************************************************************************/
//LED_Door_PIN
#define LED_Door_Pin  3
//LED_Door_PARAMETER
#define LED_Door_Init pinMode(LED_Door_Pin, OUTPUT)
//LED_Door_PROGRAM
#define LED_Door_On   digitalWrite(LED_Door_Pin, 0)
#define LED_Door_Off  digitalWrite(LED_Door_Pin, 1) 

/*************************************************************************
RFID
*************************************************************************/
String dataTag;
//LIBRARY
#include <SPI.h>
#include <MFRC522.h>
//RIFD_PIN
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
//RFID_PARAMETER
#define RFID_RC522_Init  SPI.begin(); rfid.PCD_Init();
//RFID_PROGRAM
//perogmram untuk melihat id Tag
void lihat_uID()
{
  for (byte i = 0; i < 4; i++)
  {
    
    Serial.print(rfid.uid.uidByte[i]);
    Serial.print(',');
  }
  Serial.println();
}
//program untuk mengambil data tag, dan memasukkannya kedalam variable
void ambil_dataTag()
{
  dataTag="";
  for (byte i = 0; i < 4; i++)
  {
    dataTag += rfid.uid.uidByte[i];
  }
  Serial.println(dataTag); //<< buka serial monitor dan lihat id yang terdapat pada TAG
}
//program untuk cek apakah id yang di tag sesuai
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

/*************************************************************************
PROGRAM OBJECT
*************************************************************************/
//program jika tombol ditekan untuk mematikan alarm
#define pbPress if(Button_Read==0){Buzzer_Off; return;}
//program untuk menghiudpkan alarm
#define Alarm Buzzer_On; while (1){LED_Warning_On; Jeda; LED_Warning_Off; Jeda; pbPress}
//program jika IDtag tidak valid, hidupkan alarm
#define uID_Invalid if(check_uID(dataTag)==0){Alarm}
//program jika IDtag valid, buka pintu
#define uID_Valid if(check_uID(dataTag)==1){LED_Door_On; Door_Lock_On; Jeda_Lama; Door_Lock_Off; LED_Door_Off;}
  
/*_________________SILAKAN EDIT BAGIAN SETUP ATAU LOOP__________________*/
/*************************************************************************
SETUP
*************************************************************************/
void setup()
{
  Door_Lock_Init; Door_Lock_Off;
  Buzzer_Init;
  Button_Init;
  LED_Warning_Init; LED_Warning_Off;   
  LED_Door_Init; LED_Door_Off; 
  RFID_RC522_Init;
  Serial.begin(9600);
}

/*************************************************************************
ALGORITHYM
*************************************************************************/
void loop()
{
  //cek apakah ada kartu yang di tag ke RFID reader ??
  if (rfid.PICC_IsNewCardPresent())
  {
    if (rfid.PICC_ReadCardSerial())
    {
      //ambil data tag
      ambil_dataTag();    
      //cek apakah ID tag valid ??
      uID_Valid
      //cek apakah ID tag tidak valid ??
      uID_Invalid   
    }
  }
}
