#include <Stream.h>

class TftLogStream : public Stream {
  int available(void) override;
  int peek(void) override;
  int read(void) override;
  void flush(void) override;

  size_t write(uint8_t n) override;
  size_t write(const uint8_t *buffer, size_t size) override;
};
