


















// #include <iostream>
// #include <chrono>
// #include <functional>
// #include <memory>
// #include <string>
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
