#include "include/client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>

Client::Client(const char* server_ip, int server_port)
  : server_ip_(server_ip), server_port_(server_port), client_fd_(0) {
  // Creating socket file descriptor
  if ((client_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
}


auto Client::ReadBytes(int fd, char* bytes) -> void {
  read(fd, bytes, BUFFER_SIZE);
}

auto Client::ProcessConnection() -> void {
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE] = {0};

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(server_port_);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, server_ip_, &serv_addr.sin_addr)<=0) {
    printf("\nInvalid address/ Address not supported \n");
    exit(EXIT_FAILURE);
  }

  if (connect(client_fd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    exit(EXIT_FAILURE);
  }

  std::string message;
  std::cout << "Enter message: ";
  std::getline(std::cin, message);
  send(client_fd_ , message.c_str() , message.size() , 0 );
  ReadBytes(client_fd_, buffer);
  printf("Server response: %s\n", buffer);
}

auto Client::RunClientSingleThreaded() -> void {
  ProcessConnection();
}

auto Client::RunClientMultiThreaded(int n_threads) -> void {
  std::vector<std::thread> threads;
  for (int i = 0; i < n_threads; ++i) {
    threads.emplace_back(&Client::ProcessConnection, this);
  }
  for (auto& thread : threads) {
    thread.join();
  }
}