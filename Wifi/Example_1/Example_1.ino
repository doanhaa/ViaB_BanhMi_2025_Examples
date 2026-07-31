/*
 * LIBRARIES REQUIRED:
 * - WiFi.h, WebServer.h (Tích hợp sẵn trong ESP32 Core)
 * - Adafruit LSM6DS3TRC, Wire.h (Cài từ Library Manager)
 * 
 * BOARD: Makerbot BANHMI (ESP32-WROVER)
 * CHỨC NĂNG: Tạo Web Server truyền dữ liệu Pitch & Roll theo thời gian thực bằng AJAX
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_LSM6DS3TRC.h>
#include <math.h>

// ==========================================
// THÔNG TIN WIFI CỦA BẠN
// ==========================================
const char* ssid = "WIFI NAME";
const char* password = "WIFI PASSWORD";

// Khởi tạo Server ở cổng 80 và Cảm biến
WebServer server(80);
Adafruit_LSM6DS3TRC lsm6ds;

#define SDA_PIN 21
#define SCL_PIN 22

// Biến lưu trữ góc nghiêng
float pitch = 0.0;
float roll = 0.0;

// ==========================================
// GIAO DIỆN HTML & JAVASCRIPT (AJAX)
// ==========================================
String getHTML() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  // CSS trang trí cho đẹp
  html += "<style>body{font-family:Arial,sans-serif;text-align:center;margin-top:50px;background-color:#f4f4f9;}";
  html += "h1{color:#333;} .card{background:#fff;padding:20px;margin:20px auto;border-radius:10px;box-shadow:0 4px 8px rgba(0,0,0,0.1);max-width:300px;}";
  html += ".value{font-size:32px;font-weight:bold;color:#d32f2f;}</style>";
  
  // JavaScript dùng Fetch API để lấy dữ liệu ngầm mỗi 200ms
  html += "<script>";
  html += "setInterval(function() {";
  html += "  fetch('/data').then(response => response.json()).then(data => {";
  html += "    document.getElementById('pitch').innerHTML = data.pitch.toFixed(2);";
  html += "    document.getElementById('roll').innerHTML = data.roll.toFixed(2);";
  html += "  });";
  html += "}, 200);"; // Cập nhật 5 khung hình/giây
  html += "</script>";
  
  html += "</head><body>";
  html += "<h1>BANHMI Dashboard</h1>";
  html += "<div class=\"card\"><h2>Goc Pitch</h2><p><span class=\"value\" id=\"pitch\">0.00</span> &deg;</p></div>";
  html += "<div class=\"card\"><h2>Goc Roll</h2><p><span class=\"value\" id=\"roll\">0.00</span> &deg;</p></div>";
  html += "</body></html>";
  
  return html;
}

// ==========================================
// CÁC HÀM XỬ LÝ SERVER
// ==========================================

// Hàm trả về giao diện HTML khi truy cập IP
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// Hàm cập nhật và trả về cục dữ liệu JSON cho JavaScript
void handleData() {
  sensors_event_t accel, gyro, temp;
  lsm6ds.getEvent(&accel, &gyro, &temp);

  // Tính góc nghiêng
  pitch = atan2(accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
  roll = atan2(accel.acceleration.y, sqrt(accel.acceleration.x * accel.acceleration.x + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;

  // Đóng gói thành chuỗi JSON: {"pitch": 12.34, "roll": -5.67}
  String json = "{\"pitch\":" + String(pitch) + ", \"roll\":" + String(roll) + "}";
  server.send(200, "application/json", json);
}

// ==========================================
// SETUP & LOOP
// ==========================================
void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("\n--- Khoi dong Example 6: Web Dashboard IMU ---");

  // 1. Khởi tạo Cảm biến
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!lsm6ds.begin_I2C(0x6B, &Wire)) {
    Serial.println("Loi: Khong tim thay linh kien tai 0x6B!");
    while (1) delay(10);
  }
  // Tối ưu tần số quét để truyền qua mạng mượt hơn
  lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
  Serial.println("Cam bien LSM6DS3TR-C san sang.");

  // 2. Kết nối WiFi
  Serial.print("Dang ket noi WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nKet noi WiFi thanh cong! IP: ");
  Serial.println(WiFi.localIP());

  // 3. Định tuyến Web Server
  server.on("/", handleRoot);    // Gửi trang HTML giao diện
  server.on("/data", handleData); // Gửi dữ liệu JSON cảm biến

  server.begin();
  Serial.println("HTTP Server da bat.");
}

void loop() {
  server.handleClient(); // Duy trì lắng nghe trình duyệt
}