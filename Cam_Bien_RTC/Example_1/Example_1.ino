#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define SDA_PIN 21
#define SCL_PIN 22

void setup () {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Wire.begin(SDA_PIN, SCL_PIN);

  if (! rtc.begin(&Wire)) {
    Serial.println("Loi: Khong tim thay RTC tai 0x68!");
    while (1) delay(10);
  }
  
  // ==========================================
  // ÉP BUỘC CẬP NHẬT THỜI GIAN (BỎ QUA KIỂM TRA)
  // ==========================================
  Serial.println("Dang ep RTC reset va xoa du lieu rac...");
  
  // Lệnh này lấy thời gian từ máy tính lúc biên dịch (compile) để nạp xuống chip
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  // *** QUAN TRỌNG ***
  // Sau khi code này chạy thành công và số giây đã nhảy bình thường:
  // Bạn PHẢI thêm dấu // vào trước lệnh rtc.adjust(...) ở trên và nạp lại code lần 2.
  // Nếu không, mỗi lần mạch bị reset, nó sẽ tự lùi thời gian về lại đúng cái khoảnh khắc bạn vừa nạp code :v
  // ==========================================
}

void loop () {
  DateTime now = rtc.now();

  Serial.print("Thoi gian: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  if(now.month() < 10) Serial.print('0');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  if(now.day() < 10) Serial.print('0');
  Serial.print(now.day(), DEC);
  Serial.print(" - ");
  
  if(now.hour() < 10) Serial.print('0');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  if(now.minute() < 10) Serial.print('0');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  if(now.second() < 10) Serial.print('0');
  Serial.print(now.second(), DEC);

  Serial.print(" | Nhiet do chip: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" *C");

  delay(1000);
}
