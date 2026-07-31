#include <Adafruit_LSM6DS3TRC.h>
#include <Wire.h>

Adafruit_LSM6DS3TRC lsm6ds;

// Khai báo chuẩn chân I2C trên bo mạch BANHMI
#define SDA_PIN 21
#define SCL_PIN 22

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("\nKhoi dong chuong trinh test LSM6DS3TR-C...");

  // Khởi tạo bus I2C với cấu hình chân cụ thể
  Wire.begin(SDA_PIN, SCL_PIN);

  // Khởi tạo cảm biến ở địa chỉ 0x6B
  if (!lsm6ds.begin_I2C(0x6B, &Wire)) {
    Serial.println("Khong tim thay chip LSM6DS3TR-C. Kiem tra lai ket noi!");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("Da ket noi thanh cong voi LSM6DS3TR-C!");
  
  // Cấu hình các dải đo tiêu chuẩn
  lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  lsm6ds.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS);
  lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
  lsm6ds.setGyroDataRate(LSM6DS_RATE_104_HZ);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  
  // Lấy dữ liệu mới nhất từ cảm biến
  lsm6ds.getEvent(&accel, &gyro, &temp);

  // In giá trị Gia tốc (X, Y, Z) - m/s^2
  Serial.print("Gia toc (X,Y,Z): ");
  Serial.print(accel.acceleration.x); Serial.print(", ");
  Serial.print(accel.acceleration.y); Serial.print(", ");
  Serial.print(accel.acceleration.z); Serial.print(" m/s^2 | ");

  // In giá trị Gyro (X, Y, Z) - rad/s
  Serial.print("Gyro (X,Y,Z): ");
  Serial.print(gyro.gyro.x); Serial.print(", ");
  Serial.print(gyro.gyro.y); Serial.print(", ");
  Serial.print(gyro.gyro.z); Serial.print(" rad/s | ");

  // In Nhiệt độ
  Serial.print("Nhiet do: ");
  Serial.print(temp.temperature); Serial.println(" °C");

  delay(500);
}