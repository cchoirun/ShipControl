// // #include <rclcpp/rclcpp.hpp>
// // #include <sensor_msgs/msg/image.hpp>
// // #include <sensor_msgs/image_encodings.hpp>
// // #include <std_msgs/msg/int32.hpp>
// // #include <opencv2/opencv.hpp>

// // // Nama topik ROS untuk publisher
// // const std::string PUB_TOPIC = "/jumlah_bounding_box";

// // // Fungsi deteksi warna merah dengan HSV
// // int detectRedColor(const cv::Mat& image) {
// //     cv::Mat hsvImage;
// //     cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

// //     cv::Scalar lowerRed(0, 100, 100);
// //     cv::Scalar upperRed(10, 255, 255);

// //     cv::Mat redMask;
// //     cv::inRange(hsvImage, lowerRed, upperRed, redMask);

// //     std::vector<std::vector<cv::Point>> contours;
// //     cv::findContours(redMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

// //     return contours.size();
// // }

// // class ColorDetectionNode : public rclcpp::Node {
// // public:
// //     ColorDetectionNode() : Node("color_detection_node") {
// //         // Membuat publisher dengan tipe pesan std_msgs::Int32
// //         pub_ = this->create_publisher<std_msgs::msg::Int32>(PUB_TOPIC, 1);

// //         // Membuat subscriber untuk menerima citra dari topik sensor_msgs/Image
// //         sub_ = this->create_subscription<sensor_msgs::msg::Image>(
// //             "/camera/image_raw", 1, std::bind(&ColorDetectionNode::imageCallback, this, std::placeholders::_1)
// //         );
// //     }

// // private:
// //     // Callback untuk menerima citra dari topik sensor_msgs/Image
// //     void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
// //         cv::Mat image;
// //         try {
// //             // Mendapatkan informasi citra
// //             int width = msg->width;
// //             int height = msg->height;
// //             int step = msg->step;
// //             const std::string& encoding = msg->encoding;

// //             // Mengonversi data citra ke citra OpenCV
// //             if (encoding == sensor_msgs::image_encodings::BGR8) {
// //                 image = cv::Mat(height, width, CV_8UC3, const_cast<unsigned char*>(msg->data.data()), step);
// //             } else if (encoding == sensor_msgs::image_encodings::RGB8) {
// //                 image = cv::Mat(height, width, CV_8UC3, const_cast<unsigned char*>(msg->data.data()), step);
// //                 cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
// //             } else {
// //                 RCLCPP_ERROR(this->get_logger(), "Unsupported image encoding: %s", encoding.c_str());
// //                 return;
// //             }

// //             // Deteksi warna merah
// //             int numBoundingBoxes = detectRedColor(image);

// //             // Membuat pesan ROS yang berisi jumlah bounding box
// //             auto msgNumBoundingBoxes = std::make_shared<std_msgs::msg::Int32>();
// //             msgNumBoundingBoxes->data = numBoundingBoxes;

// //             // Mengirim pesan melalui publisher
// //             pub_->publish(*msgNumBoundingBoxes);
// //         }
// //         catch (const std::exception& e) {
// //             RCLCPP_ERROR(this->get_logger(), "Exception while processing image: %s", e.what());
// //         }
// //     }

// //     rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_;
// //     rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
// // };

// // int main(int argc, char** argv) {
// //     rclcpp::init(argc, argv);
// //     rclcpp::spin(std::make_shared<ColorDetectionNode>());
// //     rclcpp::shutdown();

// //     return 0;
// // }






// // #include <chrono>
// // #include <memory>
// // #include "rclcpp/rclcpp.hpp"
// // #include "std_msgs/msg/string.hpp"
// // #include "sensor_msgs/msg/image.hpp"
// // #include "cv_bridge/cv_bridge.h"
// // #include "opencv2/opencv.hpp"

// // class ImagePublisher : public rclcpp::Node
// // {
// // public:
// //   ImagePublisher() : Node("image_publisher")
// //   {
// //     publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image_topic", 10);
// //     timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&ImagePublisher::publishImage, this));
// //   }

// // private:
// //   void publishImage()
// //   {
// //     cv::Mat image = cv::imread("path/to/image.jpg");

// //     sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", image).toImageMsg();

// //     publisher_->publish(*img_msg);
// //   }

// //   rclcpp::TimerBase::SharedPtr timer_;
// //   rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
// // };

// // int main(int argc, char **argv)
// // {
// //   rclcpp::init(argc, argv);
// //   rclcpp::spin(std::make_shared<ImagePublisher>());
// //   rclcpp::shutdown();

// //   return 0;
// // }






















#include <iostream>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
// #include "opencv2/highgui.hpp"
// #include "opencv2/imgproc.hpp"
// #include "opencv2/imgcodecs.hpp"

// using namespace std::chrono_literals;
// using namespace cv;

// /* This example creates a subclass of Node and uses std::bind() to register a
//  * member function as a callback from the timer. */

// class MinimalPublisher : public rclcpp::Node
// {
// public:
//   MinimalPublisher()
//   : Node("minimal_publisher"), count_(0)
//   {
//     publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
//     timer_ = this->create_wall_timer(
//       500ms, std::bind(&MinimalPublisher::timer_callback, this));
//   }

// private:
//   void timer_callback()
//   {
//     auto message = std_msgs::msg::String();
//     message.data = "Hello, world! " + std::to_string(count_++);
//     RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//     publisher_->publish(message);
//   }
//   rclcpp::TimerBase::SharedPtr timer_;
//   rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
//   size_t count_;
// };



// int main(int argc, char * argv[])
// {
  

//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalPublisher>());
//   rclcpp::shutdown();
//   return 0;
// }


// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
  std::string ip_penerima = "192.168.33.194";
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Laptop Ni'am";
	struct sockaddr_in	 addrTujuan;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&addrTujuan, 0, sizeof(addrTujuan));
	
	// Filling server information
	addrTujuan.sin_family = AF_INET;
	addrTujuan.sin_port = htons(PORT);
	addrTujuan.sin_addr.s_addr = INADDR_ANY;
	if(inet_pton(AF_INET, ip_penerima.c_str(), &(addrTujuan.sin_addr)) <= 0) {
    std::cerr << "Alamat slah\n";
    return 1;
  }

	int n;
	socklen_t len;
	
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &addrTujuan,
			sizeof(addrTujuan));
	std::cout<<"Hello message sent."<<std::endl;
		
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &addrTujuan,
				&len);
	buffer[n] = '\0';
	std::cout<<"Server :"<<buffer<<std::endl;

	close(sockfd);
	return 0;
}
