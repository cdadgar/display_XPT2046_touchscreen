/*
 * library sources:
 * XPT2046_Touchscreen.h - https://github.com/PaulStoffregen/XPT2046_Touchscreen
 */



#include <XPT2046_Touchscreen.h>
#include <SPI.h>


/*
 * wemos d1 r1 setup
 * 
 * the touchscreen is attached to 2.8" tft displays
 * VCC and all logic levels are 3.3V
 * 
 * 5 microcontroller lines needed
 */
#define T_IRQ     5
#define T_DO     12
#define T_DIN    13
#define T_CS      4
#define T_CLK    14


XPT2046_Touchscreen ts(T_CS, T_IRQ);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n\XPT2046 Test"); 

  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}


void loop() {
  // tirqTouched() is much faster than touched().  For projects where other SPI chips
  // or other time sensitive tasks are added to loop(), using tirqTouched() can greatly
  // reduce the delay added to loop() when the screen has not been touched.
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      Serial.print("Pressure = ");
      Serial.print(p.z);
      Serial.print(", x = ");
      Serial.print(p.x);
      Serial.print(", y = ");
      Serial.print(p.y);
      delay(30);
      Serial.println();
    }
  }
}
