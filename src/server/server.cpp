#include "include/server.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>

Server::Server() : server_fd_(0)
{
  // Creating socket file descriptor
  if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  memset(&serverAddr_, 0, sizeof(serverAddr_));
  serverAddr_.sin_family = AF_INET;
  serverAddr_.sin_addr.s_addr = INADDR_ANY;
  serverAddr_.sin_port = htons(4222);

  if (bind(server_fd_, (struct sockaddr *)&serverAddr_, sizeof(serverAddr_)) == -1)
  {
    std::cerr << "Error binding socket\n";
    return;
  }

  listen(server_fd_, 10);
}

void Server::ReadBytes(int fd, char *bytes)
{
  read(fd, bytes, BUFFER_SIZE);
}

void Server::ProcessConnection()
{
  char buffer[BUFFER_SIZE] = {0};
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);

  while (true)
  {
    std::cout << "Waiting for a new connection\n";
    // Avoid race condition when accepting a new connection
    std::lock_guard<std::mutex> lock(mtx_);
    int new_socket = accept(server_fd_, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (new_socket < 0)
    {
      perror("accept");
      break; // Break out of the loop if an error occurs
    }

    // Keep reading data from the client and sending responses
    while (true)
    {
      int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
      if (bytes_read < 0)
      {
        perror("read");
        break; // Break out of the inner loop if an error occurs
      }
      else if (bytes_read == 0)
      {
        // Client has closed the connection
        std::cout << "Client closed the connection\n";
        break; // Break out of the inner loop
      }

      // Process the received data (echo back in this example)
      send(new_socket, buffer, bytes_read, 0);
    }

    // Close the connection with the current client
    close(new_socket);
  }
}

void Server::RunServerSingleThreaded()
{
  ProcessConnection();
}

void Server::RunServerMultiThreaded(int n_threads)
{
  std::vector<std::thread> threads;
  for (int i = 0; i < n_threads; ++i)
  {
    threads.emplace_back(&Server::ProcessConnection, this);
  }
  for (auto &thread : threads)
  {
    thread.join();
  }
}