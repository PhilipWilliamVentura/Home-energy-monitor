#include <EmonLib.h>      
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Use I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, 16, 2);


EnergyMonitor emon1;        // Current sensor instance
EnergyMonitor emon2;        // Voltage sensor instance

// Calibration values 
float voltageCalibration = 110.0;
float currentCalibration = 60.606; 


void setup() {
  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);

  emon1.current(A0, currentCalibration)
  emon2.voltage(A1, voltageCalibration, 1.7);

  lcd.setCursor(0, 0);
  lcd.print("Energy Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  double Irms = emon1.calcIrms(1480);   // Calculate current (Irms)
  double Vrms = emon2.calcVrms(1480);   // Calculate voltage (Vrms)
  
  
  double power = Vrms * Irms;

  // Display the values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V: ");
  lcd.print(Vrms, 2);
  lcd.print("V ");
  
  lcd.setCursor(8, 0);
  lcd.print("I: ");
  lcd.print(Irms, 2);
  lcd.print("A");
  
  lcd.setCursor(0, 1);
  lcd.print("P: ");
  lcd.print(power, 2);
  lcd.print("W");
  
  // Optionally print to Serial Monitor for debugging
  Serial.print("Voltage: ");
  Serial.print(Vrms);
  Serial.println(" V");
  
  Serial.print("Current: ");
  Serial.print(Irms);
  Serial.println(" A");
  
  Serial.print("Power: ");
  Serial.print(power);
  Serial.println(" W");
  
  delay(1000);

}
