#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

MPU6050 mpu6050(Wire);

/* Private define ------------------------------------------------------------*/
#define NUM_SAMPLES     50
#define NUM_GESTURES    15
#define G               9.80665f
#define ACC_THRESHOLD   (2.5f*G)

int samplesRead   = NUM_SAMPLES;
int gesturesRead  = 0;
//=============================================MOTION SENSOR DEVICE ID==============================================
String id = "sensor 1";
//==================================================================================================================
int prevstate = LOW;
String d;
String data;
//============================================WIFI CREDENTIALS OF HUB================================================
const char* ssid = "hotspotison";
const char* password = "qwerpoiu";
String host = "http://192.168.248.151:5000/feed";
//============================================defining the object====================================================
WiFiClient client;
HTTPClient http;
//============================================defining the IP Address of the sensor==================================


//============================================SETUP PART=============================================================
void setup() {
  pinMode(2, INPUT);
 
 Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
   Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

//   init IMU sensor
//    if (!mpu.begin()) {
//      Serial.println("Failed to initialize IMU!");
//      while (1) {
//        delay(10);
//      }
//    }
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.println("SET ESP IN STA MODE");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
//  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println(".");
  Serial.println("- wifi connected");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());

}
//============================================READ THE STATE OF SENSOR================================================
void readdata(){
  String message = "";
 for (int k = 0; k < 1; k++) {
  mpu6050.update();

      digitalWrite(0, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(14, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      message += String(analogRead(A0)) + ",";
      digitalWrite(0, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(14, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      message += String(analogRead(A0)) + ",";
      digitalWrite(0, LOW);
      digitalWrite(2, LOW);
      digitalWrite(14, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      message += String(analogRead(A0)) + ",";
      digitalWrite(0, LOW);
      digitalWrite(2, LOW);
      digitalWrite(14, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      message += String(analogRead(A0)) + ",";
      digitalWrite(0, LOW);
      digitalWrite(2, LOW);
      digitalWrite(14, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      message += String(analogRead(A0)) + ",";
      message += String(mpu6050.getAccX()) + ",";
      message +=  String(mpu6050.getAccY()) + ",";
      message +=  String(mpu6050.getAccZ()) + ",";
      message +=  String(mpu6050.getGyroX())  + ",";
      message +=  String(mpu6050.getGyroY())  + ",";
      message +=  String(mpu6050.getGyroZ()) + ",";
      message +=  String(mpu6050.getAccAngleX()) + ",";
      message +=  String(mpu6050.getAccAngleY()) + ",";
      message +=  String(mpu6050.getGyroAngleX()) + ",";
      message +=  String(mpu6050.getGyroAngleY()) + ",";
      message +=  String(mpu6050.getGyroAngleZ()) + ",";
      message +=  String(mpu6050.getAngleX()) + ",";
      message +=  String(mpu6050.getAngleY()) + ",";
      message +=  String(mpu6050.getAngleZ()) + ",";
      // message +=  String("-----------------------------------") + "\n";
//      message +=  "\n";
 }

      http.begin(client, host);
      http.addHeader("Content-Type", "text/plain");
      http.POST(message);
      http.writeToStream(&Serial);
      http.end();
      Serial.println("data stream: "+message);
 
}


//============================================LOOP PART================================================
void loop () {
  readdata();
  delay(200);
}
