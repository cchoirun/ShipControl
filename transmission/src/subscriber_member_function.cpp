// // Copyright 2016 Open Source Robotics Foundation, Inc.
// //
// // Licensed under the Apache License, Version 2.0 (the "License");
// // you may not use this file except in compliance with the License.
// // You may obtain a copy of the License at
// //
// //     http://www.apache.org/licenses/LICENSE-2.0
// //
// // Unless required by applicable law or agreed to in writing, software
// // distributed under the License is distributed on an "AS IS" BASIS,
// // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// // See the License for the specific language governing permissions and
// // limitations under the License.

// #include <functional>
// #include <memory>

// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp"

// using std::placeholders::_1;

// class MinimalSubscriber : public rclcpp::Node
// {
// public:
//   MinimalSubscriber()
//   : Node("minimal_subscriber")
//   {
//     subscription_ = this->create_subscription<std_msgs::msg::String>(
//       "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
//   }

// private:
//   void topic_callback(const std_msgs::msg::String & msg) const
//   {
//     RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
//   }
//   rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
// };

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalSubscriber>());
//   rclcpp::shutdown();
//   return 0;
// }

// Server side implementation of UDP client-server model
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
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Ngirim dari server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	socklen_t len;
int n;

	len = sizeof(cliaddr); //len is value/result

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	std::cout<<"Hello message sent."<<std::endl;
	
	return 0;
}
