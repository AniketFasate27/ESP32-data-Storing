#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "RTClib.h"
#include "Wire.h"
TaskHandle_t  Task3, Task4;
const int MPU_ADDR = 0x68;
int16_t mpu_data[36000];
int temp, timer1, timer2;
bool MPU_flag = false;
int N = 2000;
int i, val1;
String dataString;

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    //Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    //Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
void MpuDataTest1() {

  for (i = 0; i < N; i++)
  {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(true);
    Wire.beginTransmission(MPU_ADDR);
    Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers

    //esp_task_wdt_feed();
    mpu_data[i] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    mpu_data[i + N] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_XOUT_H) & 0x3E (ACCEL_XOUT_L)
    mpu_data[i + 2 * N] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    temp          = Wire.read() << 8 | Wire.read(); // 0x41 (ACCEL_XOUT_H) & 0x42 (ACCEL_XOUT_L)
    mpu_data[i + 3 * N] = Wire.read() << 8 | Wire.read(); //0x43 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)
    mpu_data[i + 4 * N] = Wire.read() << 8 | Wire.read(); //0x45 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)
    mpu_data[i + 5 * N] = Wire.read() << 8 | Wire.read(); //0x47 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)

  }
}

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22, 400000); // sda, scl, clock speed
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU−6050)
  Wire.endTransmission(true);
  Serial.println("MPU Setup complete");

  //  dht.begin();

  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }


  SD.remove("datalog_ESP32.csv");
  writeFile(SD, "/datalog_ESP32.csv", "Ax,Ay,Az,Gx,Gy,Gz\r\n");
}

void loop() {
  timer1 = micros();
  MpuDataTest();
  for (int j = 0; j < N; j++)
  {
    dataString += (String(mpu_data[j]) + "," + String(mpu_data[j + N]) + "," + String(mpu_data[j + 2 * N]) + "," + String(mpu_data[j + 3 * N]) + "," + String(mpu_data[j + 4 * N]) + "," + String(mpu_data[j + 5 * N]));
    dataString += "\r\n";
  }

  Serial.println(dataString);
  appendFile(SD, "/datalog_ESP32.csv", dataString.c_str());
  dataString = "";
  //delay(100);
  timer2 = micros();
  val1 = (timer2 - timer1) / N;
  Serial.println(val1);

}
