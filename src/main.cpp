#include <Arduino.h>
#include <SPI.h>
#include "dw3000.h"

#define APP_NAME "DW3000 - C3 Super Mini Continuous Test\r\n"

// Pin mapping based on Super Mini layout
const uint8_t PIN_RST = 1; 
const uint8_t PIN_IRQ = 0; 
const uint8_t PIN_SS  = 7; 

#define SPI_SCK  4
#define SPI_MISO 5
#define SPI_MOSI 6

void setup() {
  Serial.begin(115200);
  
  // Necessary for C3 internal USB to initialize
  while (!Serial) delay(10); 
  
  Serial.println(APP_NAME);

  // Initialize SPI
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, PIN_SS);

  /* Initialize DW3000 hardware pins */
  spiBegin(PIN_IRQ, PIN_RST);
  spiSelect(PIN_SS);

  Serial.println("Starting continuous scan...");
}

void loop() {
  /* Continuously check Device ID */
  if (dwt_check_dev_id() == DWT_SUCCESS) {
      Serial.println("[OK] DW3000 is ready and responding.");
  } else {
      uint32_t dev_id = dwt_readdevid();
      Serial.print("[FAILED] Device ID mismatch. Read: 0x");
      Serial.println(dev_id, HEX);
      Serial.println("Retrying in 2 seconds...");
  }

  // Wait 2 seconds between checks
  delay(2000); 
}