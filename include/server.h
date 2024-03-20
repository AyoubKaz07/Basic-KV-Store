#pragma once

#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>


#define BUFFER_SIZE 1024

class Server {
  public: 
    Server();

    auto RunServerSingleThreaded() -> void;
    auto RunServerMultiThreaded(int n_threads) -> void;


  private:
    auto ReadBytes(int fd, char* bytes) -> void;
    auto ProcessConnection() -> void;


    int server_fd_;
    struct sockaddr_in serverAddr_;
    std::mutex mtx_;
};