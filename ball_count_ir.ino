#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // If your screen doesn't use reset pin
#define SCREEN_ADDRESS 0x3D  // Typical I2C address for SSD1306

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR sensor and LED configuration
#define SENSORPIN 12  // IR sensor signal pin
#define LEDPIN 13    // Built-in LED to indicate beam break

// Variable to hold sensor state
int sensorState = 0;
int lastState = 0;
int ballCount = 0;
int breakBeam = 0;

void setup() {
  Serial.begin(9600);  // Start serial monitor for debugging

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

  // Setup IR sensor and LED pins
  pinMode(SENSORPIN, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  // Read IR sensor (LOW when beam is broken, HIGH when unbroken)
  sensorState = digitalRead(SENSORPIN);

  display.clearDisplay();  // Clear previous display contents

  // If beam is broken, turn LED on and display "Broken"
  if (sensorState == LOW && lastState == HIGH) {
    breakBeam++;
    if (breakBeam % 2 == 0) {
     ballCount++; // Increment counter
    Serial.print("Ball Count: ");
    Serial.println(ballCount);
    }
    digitalWrite(LEDPIN, HIGH); 
  
  } 
  // If beam is intact, turn LED off and display "Unbroken"
  else {
    digitalWrite(LEDPIN, LOW);  // Turn off LED
  }

   digitalWrite(LEDPIN, HIGH);  // Turn on LED
    display.setCursor(10, 20);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Ball Count: ");
    display.println(ballCount);
    display.display();
    

  display.display();  // Push buffer to OLED screen
  lastState = sensorState;


  delay(100);  // Small delay for stability
}

