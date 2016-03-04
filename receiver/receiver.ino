// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <string.h>

byte toCheck[2][4] = { {0x00, 0x00, 0x00, 0x00},
};

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");



  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(11);
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    if (isValid(buflen, buf)) {
      Serial.println("Granted");
      delay(3000);
      digitalWrite(12, true);
      delay(5000);
      digitalWrite(12, false);
    }
    else {
      Serial.println("Error! Card not recognized!");
    }

  }
}

boolean isValid(byte size, byte *uid) {
  Serial.println("isValid");
  boolean isValid = true;

  int row = sizeof(toCheck) / sizeof(toCheck[0]); //Anzahl der gespeicherten UIDs
  int col = sizeof(toCheck[0]) / sizeof(byte); //Größe der UIDs

  for (int i = 0; i < row; i++) {
    isValid = false;
    for (int j = 0; j < col; j++) {
      Serial.print("i: ");
      Serial.println(i);
      Serial.print("j: ");
      Serial.println(j);
      Serial.print("toCheck[i][j]");
      Serial.println(toCheck[i][j], HEX);
      Serial.print("uid[i]");
      Serial.println(uid[j], HEX);
      if (toCheck[i][j] != uid[j]) {
        Serial.println("Ungleich!");
        isValid = false;
        break;
      }
      isValid = true;
    }
    if (isValid) return true;
  }

  return isValid;

}
