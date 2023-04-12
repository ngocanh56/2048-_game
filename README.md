# 2048 Game
**LUẬT CHƠI:**
Người chơi sẽ được cấp cho một bảng kích cỡ 4x4 với 2 ô số mở đầu (có thể là 2 hoặc 4) những ô có cùng giá trị sẽ sát nhập vào nhau và tạo ra một ô có giá trị gấp đôi. Nhiệm vụ của người chơi là sát nhập các ô một cách khéo léo để tạo ra ô chiến thắng 2048. Bằng cách:

* Nhấn *UP* :dồn các ô lên phía trên

* Nhấn *DOWN* :dồn các ô xuống phía dưới

* Nhấn *LEFT* :để dồn các ô sang bên trái

* Nhấn *RIGHT* :để dồn các ô sang bên phải

Mỗi khi 2 ô cùng giá trị và được sát nhập điểm của người chơi sẽ được cộng thêm bằng đúng giá trị của ô mới được tạo ra từ việc sát nhập.

![image](https://user-images.githubusercontent.com/125036596/231375440-1082a946-4cbf-4773-8cc5-67473bc3137d.png)
---

# MÔ TẢ CHỨC NĂNG:

![image](https://user-images.githubusercontent.com/125036596/231380845-966864cf-8fd5-4688-bbb1-b7ec79f19e92.png)![image](https://user-images.githubusercontent.com/125036596/231381316-bb30e9a7-88e1-48f3-a402-5d16d426e311.png)


* Có nút *resart* để bắt đầu/ chơi lại ván game. 

* Có nút *quit* để thoát game. 

* Tính điểm và lưu điểm cao mỗi lần chơi.

* Background thay đổi ngẫu nhiên sau mỗi lần chơi .

* Có hệ thống âm thanh sinh động (khi di chuyển các ô và gameover).

* Có bảng thông báo mỗi khi thua.
---

# **CÁC KĨ THUẬT LẬP TRÌNH ĐƯỢC SỬ DỤNG**

* Class, vector, xâu

* Bắt sự kiện bàn phím, chuột

* Sinh số ngẫu nhiên

* Đọc, ghi file

* Âm thanh,hình ảnh, text trong SDL

