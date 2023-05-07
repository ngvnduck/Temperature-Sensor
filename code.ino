#include <OneWire.h>
#include <DallasTemperature.h>

int redLed = 12;
int greenLed = 11;
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(sensors.getTempCByIndex(0)); 
  
  if (sensors.getTempCByIndex(0) <= 22) {
    //Turn ON heater_out
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.println("Heater on");
  }
  else if (sensors.getTempCByIndex(0) >= 25) {
    //Turn off heater_out
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    Serial.println("Heater off");
  }
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    Serial.println("Maintain");
  }
  delay(2000);
}
