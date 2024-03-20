#pragma once

#include <cstdint>
#include <unistd.h>

int32_t read_full(int fd, char *buf, size_t n);
int32_t write_all(int fd, const char *buf, size_t n);

