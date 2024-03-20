#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define BUFFER_SIZE 1024

class Client {
public:
  Client(const char* server_ip, int server_port);

  auto RunClientSingleThreaded() -> void;
  auto RunClientMultiThreaded(int n_threads) -> void;

private:
  auto ReadBytes(int fd, char* bytes) -> void;
  auto ProcessConnection() -> void;

  const char* server_ip_;
  int server_port_;
  int client_fd_;
};