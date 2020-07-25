# Smart Plantation Project

To get a full overview of the project, please visit https://github.com/Smart-Plantation/app.

## Arduino

### Description 

The Arduino is responsible for collecting data from the sensors and controlling the pump that irrigates the plant.

### Components:

The following components were used to build the hardware:

* Arduino
* [Temperature sensor (LM35)](https://www.instructables.com/id/ARDUINO-TEMPERATURE-SENSOR-LM35/)
* [Capacitive moisture sensor](https://how2electronics.com/interface-capacitive-soil-moisture-sensor-arduino/)
* [Liquid Cristal Display](https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay)
* [Relay](https://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/)
* Submersibile water pump
* Raspberry Pi

### How it works

The arduino measures the temperature and the moisture of the plant, and displays them on the LCD. Also, it communicates with the raspberry through the serial port.

The raspberry makes the requests to the arudino because it has a much better timing control. While the Arduino only has its internal clock, the Raspberry can import date and time from the operational system. The requests are made each hour and there are two types:
* Only retrieve data
* Retrieve data and water plant

The plants have an spefic time of the day when the irrigation is more appropriate. In this case, the plant is spinach, and the best time to irrigate the plant is around  4 p.m. So, at 4 p.m. the raspberry makes the request to retrieve data and water the plant, and at other times, only retrieves data.


