#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

float RawValue=0;
float RawHigh = 88.62;
float RawLow = 4.56;
float ReferenceHigh = 99.9;
float ReferenceLow = 0;
float RawRange = RawHigh - RawLow;
float ReferenceRange = ReferenceHigh - ReferenceLow;

void setup()
{
  sensors.begin();	// Start up the library
  Serial.begin(9600)
}

void loop()
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  RawValue = sensors.getTempCByIndex(0);
  float CorrectedValue = (((RawValue - RawLow) * ReferenceRange) / RawRange) + ReferenceLow;
  Serial.println(CorrectedValue);
  Serial.println("  Celsius");  
  delay(500);
}
