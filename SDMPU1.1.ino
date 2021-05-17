#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "RTClib.h"
#include "Wire.h"
TaskHandle_t  Task3, Task4;
const int MPU_ADDR = 0x68;
int16_t mpu_data[18000];
int16_t mpu_data2[18000];
int temp, timer1, timer2, timer3, timer4, timer5, timer6, timer7, timer8;
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;
bool flag4 = false;
bool MPU_flag = false;
int N = 1500;
int i, l, val1, val2, val3, val4;
String dataString;
int k = 1;
uint32_t di;
bool nameflag = true;

//int16_t mpufile[k];
char trial[100];

void append_file() {
  while (1) {
    //trial = "/datalog_ESP32.csv";


  }
}
//  sprintf(trial,"%d", }

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
  timer1 = micros();
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
  timer2 = micros();
  val1 = (timer2 - timer1) / N;
  Serial.println(val1);
  flag1 = true;
}

void MpuDataTest2() {
  timer3 = micros();
  for (i = 0; i < N; i++)
  {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(true);
    Wire.beginTransmission(MPU_ADDR);
    Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers

    //esp_task_wdt_feed();
    mpu_data2[i] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    mpu_data2[i + N] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_XOUT_H) & 0x3E (ACCEL_XOUT_L)
    mpu_data2[i + 2 * N] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    temp          = Wire.read() << 8 | Wire.read(); // 0x41 (ACCEL_XOUT_H) & 0x42 (ACCEL_XOUT_L)
    mpu_data2[i + 3 * N] = Wire.read() << 8 | Wire.read(); //0x43 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)
    mpu_data2[i + 4 * N] = Wire.read() << 8 | Wire.read(); //0x45 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)
    mpu_data2[i + 5 * N] = Wire.read() << 8 | Wire.read(); //0x47 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)

  }
  timer4 = micros();
  val2 = (timer4 - timer3) / N;
  Serial.println(val2);
  flag2 = true;
}

void MpuDataTest3() {
  timer5 = micros();
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
  timer6 = micros();
  val3 = (timer6 - timer5) / N;
  Serial.println(val3);
  flag3 = true;
}
void MpuDataTest4() {
  timer7 = micros();
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
  timer8 = micros();
  val4 = (timer8 - timer7) / N;
  Serial.println(val4);
  flag4 = true;
}

void append(void * parameter)
{
  char temp[100];
  Serial.print("inside append:");
  Serial.println((char *)parameter);

  while (1)
  { //Serial.println("i am");

    const char * file_name2 = (char *)parameter;
    if (flag1 == true)
    {
      for (int j = 0; j < N; j++)
      {
        dataString += (String(mpu_data[j]) + "," + String(mpu_data[j + N]) + "," + String(mpu_data[j + 2 * N]) + "," + String(mpu_data[j + 3 * N]) + "," + String(mpu_data[j + 4 * N]) + "," + String(mpu_data[j + 5 * N]) + "\r\n");
        //dataString += "\r\n";
      }

      appendFile(SD, file_name2 , dataString.c_str());
      dataString = "";
      flag1 = false;
    }
    else if (flag2 == true)
    {
      for (int j = 0; j < N; j++)
      {
        dataString += (String(mpu_data2[j]) + "," + String(mpu_data2[j + N]) + "," + String(mpu_data2[j + 2 * N]) + "," + String(mpu_data2[j + 3 * N]) + "," + String(mpu_data2[j + 4 * N]) + "," + String(mpu_data2[j + 5 * N]) + "\r\n");
        //        dataString += "\r\n";
      }

      appendFile(SD, file_name2, dataString.c_str());
      dataString = "";
      flag2 = false;
    }
    else if (flag3 == true)
    {
      for (int j = 0; j < N; j++)
      {
        dataString += (String(mpu_data2[j]) + "," + String(mpu_data2[j + N]) + "," + String(mpu_data2[j + 2 * N]) + "," + String(mpu_data2[j + 3 * N]) + "," + String(mpu_data2[j + 4 * N]) + "," + String(mpu_data2[j + 5 * N]) + "\r\n");
        //        dataString += "\r\n";
      }
      appendFile(SD, file_name2, dataString.c_str());
      dataString = "";
      flag3 = false;
    }
    else if (flag4 == true)
    {
      for (int j = 0; j < N; j++)
      {
        dataString += (String(mpu_data2[j]) + "," + String(mpu_data2[j + N]) + "," + String(mpu_data2[j + 2 * N]) + "," + String(mpu_data2[j + 3 * N]) + "," + String(mpu_data2[j + 4 * N]) + "," + String(mpu_data2[j + 5 * N]) + "\r\n");
        //        dataString += "\r\n";
      }
      appendFile(SD, file_name2, dataString.c_str());
      dataString = "";
      flag4 = false;
    }


    delay(100);
  }
  //delay(50);
}



void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22, 800000); // sda, scl, clock speed
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


  name_change();



  //  writeFile(SD, "/datalog_ESP32.csv", "Ax,Ay,Az,Gx,Gy,Gz\r\n");
  C1();
  //  xTaskCreatePinnedToCore(append, "append", 10000, trial, 1, &Task3, 1);
  //  MpuDataTest1();
  //  //  delay(1);
  //  MpuDataTest2();
  //  MpuDataTest3();
}

void name_change() {
  sprintf(trial, "/datalog_ESP32(%d).csv", k);
  Serial.println(trial);
  const  char* file_name = trial;
  Serial.println(file_name);
  writeFile(SD, file_name, "Ax,Ay,Az,Gx,Gy,Gz\r\n");
  // SD.remove(file_name);
}
void C1() {
  if (nameflag == true) {
    xTaskCreatePinnedToCore(append, "append", 10000, trial, 1, &Task3, 1);
  }
  else {
    Serial.println("task suspendded");
    vTaskSuspend(Task3);

  }

}
void loop() {
  MpuDataTest1();
  // Serial.println("dine1");
  //delay(1);



  MpuDataTest2();
  //delay(10);
  //Serial.println("dine2");
  // delay(1);

  MpuDataTest3();
  //Serial.println("dine3");
  //delay(10);
  MpuDataTest4();
  di = di + 6000;
  Serial.println(di);
  if ( di > 100000) {

    nameflag = false;
    C1();

    k++;
    name_change();
    di = 0;
    nameflag = true;
    C1();
  }
}
