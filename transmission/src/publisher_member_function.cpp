

#include <std_msgs/msg/int32_multi_array.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#include <iostream>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"
#include <algorithm>

using namespace std::chrono_literals;

// Implementasi fungsi clamp
template <typename T>
const T& clamp(const T& value, const T& minValue, const T& maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}


#define BUF_SIZE 35

std::string my_ip = "0.0.0.0";
int my_port = 8888;
std::string hw_ip = "10.8.9.221";
int hw_port = 8888;

struct sockaddr_in my_address, hw_address;
int sock_hw;

rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_stm;

int low_truster = 1200, high_truster = 1800;
int low_v = 0, high_v = 100;

int ltruster = 1500;
int rtruster = 1500;
int vtruster = 0;

int lt = clamp(ltruster, low_truster, high_truster);
int rt = clamp(ltruster, low_truster, high_truster);
int vt = clamp(vtruster, low_v, high_v);


void servoCallback(const std_msgs::msg::Int32::SharedPtr msg)
{
	lt = msg->data;
}

void PC_2_STM() {
    // uint8_t send_data[16] = {};
    unsigned char send_data[16] = {'i','t','s'};
    std::string data = "";
    
    // std::cout << " manual" << std::endl;
    send_data[3] = (lt >> 8) & 0xFF;
    send_data[4] = lt & 0xFF;
    send_data[5] = (rt >> 8) & 0xFF;
    send_data[6] = rt & 0xFF;
    send_data[7] = (vt >> 8) & 0xFF;
    send_data[8] = vt & 0xFF;
    // send_data[9] = (vrt >> 8) & 0xFF;
    // send_data[10] = vrt & 0xFF;
    
 
    sendto(sock_hw, &send_data, sizeof(send_data), 0, (struct sockaddr*)&hw_address, sizeof(hw_address));
}

void STM_2_PC() {
    int recv_len;
    unsigned char buf[BUF_SIZE] = {};
    socklen_t hw_address_len = sizeof(hw_address);

    while (rclcpp::ok()) {
        // memset(buf, 0, sizeof(buf));
        memset(buf, 0, sizeof(buf));
 		recv_len = recvfrom(sock_hw, buf, sizeof(buf), 0, (struct sockaddr*)&hw_address, &hw_address_len);
        recv_len = recv(sock_hw, buf, sizeof(buf), 0);
        if (recv_len < 0) {
            RCLCPP_INFO(rclcpp::get_logger(""), "No message received");
            // continue;
        }
        // std::string message(reinterpret_cast<char*>(buf), recv_len);
        // std::string its = message.substr(0, 3);
        // std::string mmessage = message.substr(3);
        // if (its != "its") {
        //     RCLCPP_INFO_STREAM(rclcpp::get_logger("STM_2_PC"), "Checksum failed.." );
        //     // continue;
        // }
        uint8_t ltruster = 12;
        uint8_t rtruster = 34;
        uint8_t vel = 10;
        auto to_pub = std_msgs::msg::Int32();
        to_pub.data = ltruster;
        pub_stm->publish(to_pub);
        // RCLCPP_INFO_STREAM(rclcpp::get_logger("STM_2_PC"), "data recv: " << to_pub->data[0] << "/" << to_pub->data[1] << "/" << to_pub->data[2]);
    }
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto nh = rclcpp::Node::make_shared("transmission");



    pub_stm = nh->create_publisher<std_msgs::msg::Int32>("/hardware/stm", 1);
	

    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(my_port);

    hw_address.sin_family = AF_INET;
    hw_address.sin_addr.s_addr = inet_addr("10.8.92.221");
    hw_address.sin_port = htons(hw_port);

    sock_hw = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_hw == -1) {
        RCLCPP_ERROR(rclcpp::get_logger(""), "Failed to create socket");
        return -1;
    }
    int reuse = 1;
    if (setsockopt(sock_hw, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {

        RCLCPP_ERROR(rclcpp::get_logger(""), "Failed to set socket options");
        return -1;
    }
    if (bind(sock_hw, (struct sockaddr*)&my_address, sizeof(my_address)) == -1) {

        RCLCPP_ERROR(rclcpp::get_logger(""), "Failed to bind socket");
        return -1;
    }
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;  // 100 ms
    setsockopt(sock_hw, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    std::thread read_thread(STM_2_PC);
    read_thread.detach();
	auto sub_stm = nh->create_subscription<std_msgs::msg::Int32>(
		"servo_command", 10, servoCallback);
		
    rclcpp::Rate rate(10);
    while (rclcpp::ok()) {
        PC_2_STM();
        
        // rate.sleep();
        rclcpp::spin_some(nh);
    }

    close(sock_hw);

    rclcpp::shutdown();

    return 0;
}