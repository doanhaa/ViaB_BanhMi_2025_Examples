/*
 * LIBRARIES REQUIRED:
 * - BluetoothSerial (Đã được tích hợp sẵn trong ESP32 Core)
 * 
 * BOARD: Makerbot BANHMI (ESP32-WROVER)
 * CHỨC NĂNG: Giao tiếp Bluetooth Classic với điện thoại Android/PC
 */

#include "BluetoothSerial.h"

// Khởi tạo đối tượng Bluetooth
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  
  // Đặt tên thiết bị Bluetooth sẽ hiển thị khi dò tìm  
  SerialBT.begin("BANHMI_Robot"); 
  
  Serial.println("\n--- Khoi dong Example 4: Bluetooth Serial ---");
  Serial.println("Bluetooth da bat. Hay dung dien thoai de ghep noi voi ten 'BANHMI_Robot'");
}

void loop() {
  // 1. Đọc dữ liệu từ Điện thoại gửi xuống ESP32
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    Serial.print("Nhan duoc lenh tu dien thoai: ");
    Serial.println(incomingChar);

    // Xử lý lệnh điều khiển cơ bản
    if (incomingChar == 'F' || incomingChar == 'f') {
      Serial.println("-> Lenh: Xe chay toi!");
      SerialBT.println("Da nhan lenh: TOI");
    } 
    else if (incomingChar == 'S' || incomingChar == 's') {
      Serial.println("-> Lenh: Dung xe!");
      SerialBT.println("Da nhan lenh: DUNG");
    }
  }

  // 2. Gõ chữ từ Serial Monitor của máy tính gửi lên Điện thoại
  if (Serial.available()) {
    String outString = Serial.readString();
    SerialBT.print("ESP32 noi: ");
    SerialBT.println(outString);
  }
  
  delay(20);
}