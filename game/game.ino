#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int cells[128][64];
int i; int j;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.display();
  memset(cells, 0, sizeof(cells[0][0]) * 128 * 64);
  cells[10][10] = 1;
  

}

void loop() {
  iterCells();  
  delay(100);
}

void initCells() { // generate random cells
  
}

void iterCells() { // iterate cells
//  display.clearDisplay();
  
  for(i=0;i<128;i++){
    for(j=0;j<64;j++){
      Serial.println(cells[i][j]);
    
//      if (cells[i][j]) {
//        Serial.println(i+","+j);
//        display.drawPixel(i,j,WHITE);
//      }
    }
  }
//  display.display();
  delay(200);
  
}
