
/*
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include <VirtualWire.h>

#define RST_PIN		9		// 
#define SS_PIN		10		//

MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance
uint8_t uid[4];

void setup() {
	pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
 
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_tx_pin(8);
  vw_set_rx_pin(6);
  vw_set_ptt_pin(7);
  vw_setup(2000);
	Serial.println(F("Scan PICC"));
}

void loop() {
  
  delay(500);
  
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

  Serial.println(F("Card detected"));

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  Serial.println("Card UID:");    //Dump UID
 
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid[i] = (uint8_t)mfrc522.uid.uidByte[i];
    Serial.println(uid[i], HEX);
  }
  digitalWrite(3, true);
  //Send UUID
  const char *msg = (char*)mfrc522.uid.uidByte;
  vw_send(uid, 4);
  vw_wait_tx();
  Serial.println("Gesendet");
  delay(6000);
  digitalWrite(3, false);
}


