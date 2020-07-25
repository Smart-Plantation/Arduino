#define RELAY_PIN 7
#define temp_pin 1
#define soil_pin 3

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int AirValue = 740;
const int WaterValue = 340; 
const int minimum_moisture = 70;

int temperature;
int moisture;
bool watering;
int serial_data;

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
  analogRead(soil_pin);
  delay(100);
  return map(analogRead(soil_pin), WaterValue, AirValue, 100, 0); }

void lcd_write_data(int temperature, int moisture) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + (String)temperature + "oC");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: " + (String)moisture + "%");
}

void send_data(){
   Serial.print((String)temperature + " ");
   Serial.print((String)moisture + " ");
   Serial.println((String)watering);  
}

void water_plant(){
   if (moisture < minimum_moisture) {
      turn_relay_on();
      prev_water_time = millis();
      watering = true;
   }
}

void get_sensor_data_and_print(){
  temperature = get_temp();
  moisture = get_moisture();
  lcd_write_data(temperature,moisture);
  prev_lcd_time = millis();  
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  get_sensor_data_and_print();
}

void loop() {
  //Display LCD each 5 seconds
  if ( (millis() - prev_lcd_time) >= 5000 ){
    get_sensor_data_and_print();
  }

  //Turn off water after 3 seconds
  if(watering == true){
    if( millis() - prev_water_time >= 15000)
      turn_relay_off();    
  }
  
  if (Serial.available() > 0){
     serial_data = Serial.read();
     if ( serial_data == 'a'){
       send_data(); 
     }
     if (serial_data == 'b'){
       water_plant();
       send_data();
     }     
  }
  
}
