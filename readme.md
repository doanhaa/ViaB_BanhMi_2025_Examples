# BanhMi MSP v1.4 (2025) - Hardware Test Examples

Bộ example này được tạo ra nhằm giúp các bạn test nhanh các chức năng mở rộng của Board **ViaB BanhMi MSP v1.4 (2025)** (những tính năng mà tài liệu mặc định của Ban tổ chức chưa đề cập chi tiết). 

Việc kiểm tra toàn bộ phần cứng sẽ giúp các bạn tránh hoang mang và tiết kiệm rất nhiều thời gian khi có nhu cầu khai thác các tính năng còn lại của mạch. Bộ tài liệu này dành cho các bạn thí sinh đã và đang tham gia các cuộc thi do MakerViet tổ chức, cũng như những ai có ý định tận dụng lại mạch cho các dự án cá nhân sau này.

---

## ⚙️ Cài đặt Board và Thư viện

Trước khi bắt đầu test, các bạn cần thiết lập môi trường trên Arduino IDE như sau:

*   **Chọn Board:** Khi tiến hành nạp code, các bạn bắt buộc phải chọn tên board là **`ESP32 Dev Module`**.
*   **Cài đặt Thư viện:** Tải các thư viện cần thiết thông qua công cụ **Library Manager** tích hợp sẵn trong Arduino IDE (truy cập *Sketch -> Include Library -> Manage Libraries*):
    *   `Adafruit LSM6DS3TR-C` (Phục vụ đo góc nghiêng/gia tốc).
    *   `RTClib` (Phục vụ module thời gian thực).
    *   *(Lưu ý: Hãy chọn "Install All" nếu phần mềm yêu cầu cài đặt thêm các thư viện phụ thuộc).*

---

## ⚠️ Lưu ý về Cảm biến gia tốc (IMU)

Nếu tham khảo document (sơ đồ nguyên lý) từ những năm trước do Ban tổ chức cung cấp, các bạn sẽ thấy khối IMU ghi thông số sử dụng chip **MPU-6050**. 

Tuy nhiên, trên thực tế của phiên bản board BanhMi MSP v1.4 (2025), linh kiện này đã được thay thế bằng chip **LSM6DS3TR-C**. Do đó, các bạn không thể sử dụng các code mẫu hay thư viện cũ của MPU6050 cho mạch này. Các example trong repo này đã được cấu hình chuẩn xác để làm việc với cảm biến LSM6DS3TR-C.

---

## 📱 Hướng dẫn Test Bluetooth

Để kiểm tra tính năng Bluetooth (gửi lệnh `F` và `S`), hãy lưu ý về thiết bị kết nối:
*   **Đối với Android:** Tải ứng dụng **Serial Bluetooth Terminal** trên Google Play. Tiến hành ghép đôi với mạch trong phần cài đặt Bluetooth của điện thoại, sau đó mở app để kết nối và gửi lệnh test.
*   **Đối với iPhone (iOS):** Hệ điều hành iOS không hỗ trợ chuẩn Bluetooth Classic được sử dụng trong bài test này. Các bạn sẽ không thể dùng iPhone để dò tìm mạch. Vui lòng mượn thiết bị Android hoặc sử dụng Laptop có Bluetooth để kiểm tra.

---

## 🌐 Hướng dẫn Test WiFi

*   Để test các example liên quan đến WiFi, các bạn cần điền chính xác thông tin mạng (Tên WiFi và Mật khẩu) vào code trước khi nạp.
*   Sau khi nạp thành công, hãy mở Serial Monitor để lấy địa chỉ IP cục bộ của mạch.
*   Dùng điện thoại hoặc máy tính **kết nối vào cùng một mạng WiFi** với bo mạch, sau đó nhập địa chỉ IP vừa lấy được vào trình duyệt web để kiểm tra. 
*   *(Lưu ý đối với điện thoại: Hãy tắt tạm thời dữ liệu di động 4G/5G để trình duyệt không tự động chuyển hướng khi truy cập IP nội bộ).*