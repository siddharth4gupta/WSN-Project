#include <Wire.h> //I2C needed for sensors
#include "SparkFunMPL3115A2.h" //Pressure sensor - Search "SparkFun MPL3115" and install from Library Manager
#include "SparkFunHTU21D.h" //Humidity sensor - Search "SparkFun HTU21D" and install from Library Manager
#include <SoftwareSerial.h>


MPL3115A2 myPressure; //Creating an instance of the pressure sensor
HTU21D myHumidity; //Creating an instance of the humidity sensor


int bluetoothTx = 11;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 10;  // RX-I pin of bluetooth mate, Arduino D3
String a;
int n;

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);

//Hardware pin definitions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
const byte STAT_BLUE = 7;

//Global Variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; //The millis counter to see when a second rolls by


void setup()
{
  Serial.begin(9600);
  
  pinMode(STAT_BLUE, OUTPUT); //Status LED Blue

  //Configure the pressure sensor
  myPressure.begin(); // Get sensor started
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  //Configure the humidity sensor
  myHumidity.begin();

  lastSecond = millis();

  bluetooth.begin(9600);  // Start bluetooth serial at 9600

  n=2; //number of seconds for which you need to update values
  
}

void loop()
{
  //Print readings every n seconds
  
  if (millis() - lastSecond >= (n*1000))
  {
    digitalWrite(STAT_BLUE, HIGH); //Blink stat LED

    lastSecond += (n*1000);

    //Check Humidity Sensor
    float humidity = myHumidity.readHumidity();

    if (humidity == 998) //Humidty sensor failed to respond
    {
      Serial.println("I2C communication to sensors is not working. Check solder connections.");

      //Try re-initializing the I2C comm and the sensors
      myPressure.begin(); 
      myPressure.setModeBarometer();
      myPressure.setOversampleRate(7);
      myPressure.enableEventFlags();
      myHumidity.begin();
    }
    else
    {
      Serial.print("Humidity = ");
      Serial.print(humidity);
      Serial.print("%,");
      float tempc = myHumidity.readTemperature();
      Serial.print(" temp_h = ");
      Serial.print(tempc, 2);
      Serial.print("C,");

      //Check Pressure Sensor
      float pressure = myPressure.readPressure();
      Serial.print(" Pressure = ");
      Serial.print(pressure);
      Serial.print("Pa,");

      //Check tempf from pressure sensor
      float tempf = myPressure.readTempF();
      Serial.print(" tempf = ");
      Serial.print(tempf, 2);
      Serial.print("F");

      Serial.println();

      delay(10000);      
      //Sending the humidity, temperature (in C) and pressure values over bluetooth channel
      //bluetooth.write('a');
    
      bluetooth.print(tempc);
      bluetooth.print(",");
      bluetooth.print(humidity);
      bluetooth.print(",");
      bluetooth.print(pressure);

      //bluetooth.print("Pa");
      
    }

    digitalWrite(STAT_BLUE, LOW); //Turn off stat LED
  }

  if(bluetooth.available() > 0)  // If the bluetooth received any characters
  {
    
    a = bluetooth.readString();
    Serial.println("Rx value is : ");
    Serial.print(a);
  }
  
  delay(n*1000);  
}

