# robotControl_FET
# Indoor Mobile Robot Localization and Navigation Using ArUco

## 1. Giới thiệu

Dự án xây dựng một hệ thống robot di động hai bánh vi sai có khả năng **định vị và dẫn đường trong môi trường trong nhà** dựa trên mã đánh dấu **ArUco**.

Hệ thống sử dụng camera để quan sát khu vực hoạt động của robot. Vị trí của robot được xác định thông qua ArUco marker và chuyển đổi từ hệ tọa độ ảnh sang hệ tọa độ toàn cục bằng phép biến đổi **Homography**.

Để mở rộng vùng quan sát, hệ thống sử dụng **hai camera**. Dữ liệu từ hai camera được đưa về cùng một hệ tọa độ toàn cục, cho phép theo dõi robot khi robot di chuyển từ vùng quan sát của camera thứ nhất sang camera thứ hai.

Thông tin vị trí và hướng của robot sau đó được truyền đến robot thông qua **ESP-NOW**. Bộ điều khiển trên robot sử dụng sai số vị trí và hướng để tính toán vận tốc tuyến tính và vận tốc góc, sau đó chuyển đổi thành vận tốc của hai bánh xe và tín hiệu PWM điều khiển động cơ.

---

## 2. Mục tiêu

Các mục tiêu chính của dự án:

- Phát hiện robot thông qua ArUco marker.
- Xác định vị trí robot trong hệ tọa độ toàn cục.
- Ghép dữ liệu quan sát từ hai camera.
- Duy trì tính liên tục của quỹ đạo khi robot chuyển vùng quan sát.
- Truyền dữ liệu vị trí không dây đến robot.
- Điều khiển robot di chuyển qua các waypoint xác định trước.
- Sử dụng bộ điều khiển PID cho vận tốc tuyến tính và vận tốc góc.
- Điều khiển robot hai bánh vi sai bằng tín hiệu PWM.

---

## 3. Kiến trúc hệ thống

Hệ thống gồm ba thành phần chính:

```text
                 ┌──────────────────────┐
                 │      Camera 1        │
                 │   ArUco Detection    │
                 └──────────┬───────────┘
                            │
                            ▼
                    ┌───────────────┐
                    │   Homography  │
                    │    Mapping    │
                    └───────┬───────┘
                            │
                            │
                 ┌──────────▼──────────┐
                 │   Global Position   │
                 │      X, Y, θ        │
                 └──────────┬──────────┘
                            │
                 ┌──────────┴──────────┐
                 │                     │
                 ▼                     ▼
        ┌────────────────┐    ┌────────────────┐
        │    Camera 2    │    │   ESP-NOW      │
        │ ArUco Detection│    │ Communication  │
        └───────┬────────┘    └───────┬────────┘
                │                     │
                ▼                     ▼
        ┌───────────────┐      ┌───────────────┐
        │   Homography  │      │ ESP32 Robot   │
        │    Mapping    │      │ Communication │
        └───────┬───────┘      └───────┬───────┘
                │                      │
                └──────────┬───────────┘
                           ▼
                  ┌─────────────────┐
                  │  PID Controller │
                  │    v, ω         │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Differential    │
                  │ Drive Kinematics│
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Motor Controller│
                  │      PWM        │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Differential    │
                  │ Drive Robot     │
                  └────────┬────────┘
                           │
                           │
                           ▼
                     Camera observes
                        robot again
