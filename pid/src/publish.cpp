#include "pid.hpp"
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
int c = 10;
// Fungsi callback untuk mendapatkan feedback aktual dari servo (misalnya, membaca sensor atau data yang dikirim oleh servo)
int getFeedback()
{
    // Contoh: Mendapatkan feedback dari sensor atau data yang dikirim oleh servo
    // Gantikan kode ini dengan implementasi sesuai dengan servo dan sensor yang Anda gunakan
    int feedback = c;
    c+= 10; // Misalnya, sensor memberikan nilai feedback dalam rentang 0-100
    return feedback;
}

int main(int argc, char *argv[])
{
    // Inisialisasi node ROS 2
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("servo_controller");

    // Inisialisasi objek PID
    float kp = 0.5; // Koefisien proporsional
    float ki = 0.2; // Koefisien integral
    float kd = 0.1; // Koefisien derivatif
    int setPoint = 70; // Nilai set point untuk kemiringan servo (misalnya, 90 derajat)
    PID<int> pidController(kp, ki, kd, setPoint);

    // Membuat publisher untuk mengirimkan data ke servo
    auto publisher = node->create_publisher<std_msgs::msg::Int32>("servo_command", 10);

    // Loop utama (misalnya, menggunakan rate loop di ROS 2)
    while (rclcpp::ok())
    {
        // Mendapatkan feedback aktual dari servo
        int feedback = getFeedback();

        // Mengatur feedback ke objek PID
        pidController.setFeedback(feedback);

        // Menghitung output PID
        int output = pidController.calculation();

        // Mengirimkan data output ke servo melalui publisher
        auto message = std_msgs::msg::Int32();
        message.data = output;
        publisher->publish(message);

        // Proses lainnya (misalnya, menerima perintah atau memproses data lainnya)
        // ...

        // Melakukan sleep atau delay (jika menggunakan rate loop di ROS 2)
        rclcpp::spin_some(node);
        // ...
    }

    // Shutdown node ROS 2
    rclcpp::shutdown();

    return 0;
}
