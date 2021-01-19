#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>      // MPU6050 Slave Device Address


// Replace with your network credentials
const char* ssid     = "example"; //Wifi name
const char* password = "example123"; //password wifi

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "https://yusrilhasan777.000webhostapp.com/savedb.php";

const uint8_t MPU6050SlaveAddress = 0x68; // Select SDA and SCL pins for I2C communication 
const uint8_t scl = D1;
const uint8_t sda = D2;     // sensitivity scale factor respective to full scale setting 
        // provided  in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131; // MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;
int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(sda, scl);  
  MPU6050_Init();
  
}

void loop() {
  //Check WiFi connection status
  
  if(WiFi.status()== WL_CONNECTED){
    double Ax, Ay, Az, T;     
    Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);    
    //divide each with their sensitivity scale factor  
    Ax = (double)AccelX/AccelScaleFactor;  
    Ay = (double)AccelY/AccelScaleFactor;  
    Az = (double)AccelZ/AccelScaleFactor;
       
  
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = String("Ax=") + String(Ax) + String("&Ay=") + String(Ay) + String("&Az=") + String(Az);
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(5000);  
}

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  Wire.write(data);  
  Wire.endTransmission();   // read all 14 register
}

void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  
  Wire.endTransmission();  
  Wire.requestFrom(deviceAddress, (uint8_t)14);  
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());  
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());  
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
    
}

//configure MPU6050

void MPU6050_Init()
{   
  delay(150);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);    
  //set +/-250 degree/second full scale  
  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);   // set +/- 2g full scale   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET,   0x00);   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
