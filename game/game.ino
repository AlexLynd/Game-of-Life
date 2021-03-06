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

// cell boundary 
int upBoundX; int lowBoundX;
int upBoundY; int lowBoundY;
int neighbors= 0;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.display();
//  memset(cells, 0, sizeof(cells[0][0]) * 128 * 64);
  cells[10][10] = 1;
  cells[120][60] = 1;
  

}

void loop() {
  iterCells();  
  delay(0);
}

void initCells() { // generate random cells
  
}

void iterCells() {
  display.clearDisplay();
  
  for(i=0;i<128;i++){ // update cells
    for(j=0;j<64;j++){    
      if (cells[i][j]==1) {
        display.drawPixel(i,j,WHITE);
      }
    }
  }  
  
  for(i=0;i<128;i++){
    for(j=0;j<64;j++){    
      if (cells[i][j]==1) {
        display.drawPixel(i,j,WHITE);
      }
    }
  }
  display.setCursor(30,30);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("adf");
  display.display();
  delay(200);
  
}

int getCells(int x, int y, int cell) { // 1 = neighbor, 0 = empty
  neighbors = 0;
  if (x>0 and x<128) {
    upBoundX= x-1;
    lowBoundX= x+1;
  }
  else if (x==0){
    upBoundX = x;
    lowBoundX = x+1;
  }
  else if (x==128) {
    upBoundX= x-1;
    lowBoundX = x;
  }
  
  if (y>0 and y<64) {
    upBoundY= y-1;
    lowBoundY= y+1;
  }
  else if (y==0){
    upBoundY = y;
    lowBoundY = y+1;
  }
  else if (y==128) {
    upBoundY= y-1;
    lowBoundY = y;
  }
  
  for(i=upBoundX;i<lowBoundX;i++){
    for(j=upBoundY;j<lowBoundY;j++){    
      if (cells[i][j] == 1) neighbors++;
    }
  }
    
  if (cell) return neighbors;
  else return (lowBoundX-upBoundX)*(lowBoundY-upBoundY)-neighbors;
  
}
