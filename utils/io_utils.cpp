#include "include/io_utils.h"
#include <unistd.h>
#include <cassert>

int32_t read_full(int fd, char *buf, size_t n)
{
  while (n > 0)
  {
    ssize_t read_bytes = read(fd, buf, n);
    if (read_bytes <= 0)
    {
      return -1; // error, or unexpected EOF
    }
    assert((size_t)read_bytes <= n);
    n -= (size_t)read_bytes;
    buf += read_bytes;
  }
  return 0;
}

int32_t write_all(int fd, const char *buf, size_t n)
{
  while (n > 0)
  {
    ssize_t read_bytes = write(fd, buf, n);
    if (read_bytes <= 0)
    {
      return -1; // error
    }
    assert((size_t)read_bytes <= n);
    n -= (size_t)read_bytes;
    buf += read_bytes;
  }
  return 0;
}
