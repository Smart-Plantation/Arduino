#define RELAY_PIN 7
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int temp_pin = 1;
int soil_pin = 3;

const int AirValue = 740;
const int WaterValue = 340; 

int temperature;
int moisture;
bool watering;

unsigned long prev_lcd_time;
unsigned long prev_water_time;

void turn_relay_on() {
  digitalWrite(RELAY_PIN, HIGH);}

void turn_relay_off() {
  digitalWrite(RELAY_PIN, LOW);}

int get_temp() {
  analogRead(temp_pin);
  delay(100);
  return (float(analogRead(temp_pin))*5/(1023))/0.01; }

int get_moisture() {
  return map(analogRead(soil_pin), WaterValue, AirValue, 100, 0); }

void lcd_write_data(int temperature, int moisture) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + (String)temperature + "oC");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: " + (String)moisture + "%");
}
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  temperature = get_temp();
  moisture = get_moisture();
  lcd_write_data(temperature,moisture);
  prev_lcd_time = millis();
}

void loop() {
  //Display LCD each 5 seconds
  if ( (millis() - prev_lcd_time) >= 5000 ){
    temperature = get_temp();
    moisture = get_moisture();
    Serial.println(moisture);
    lcd_write_data(temperature,moisture);
    prev_lcd_time = millis();
  }

  //Turn off water after 3 seconds
  if(watering == true){
    if( millis() - prev_water_time >= 3000)
      turn_relay_off();    
  }
  
  //TODO Send data with three digits always
  if (Serial.available() > 0){
     if (Serial.read() == 'a'){
      /*
       Serial.print("T" + (String)temperature);
       Serial.print("M" + (String)moisture);
       Serial.print("W_" + (String)watering); */
       Serial.print((String)temperature + " ");
       Serial.print((String)moisture + " ");
       Serial.println((String)watering);
     }
     if (Serial.read() == 'b'){
       watering = true;
       /*
       Serial.print("T" + (String)temperature);
       Serial.print("M" + (String)moisture);
       Serial.print("W_" + (String)watering);  */
       Serial.print((String)temperature + " ");
       Serial.print((String)moisture + " ");
       Serial.println((String)watering);
       turn_relay_on();
       prev_water_time = millis();
     }     
  }
  
}
