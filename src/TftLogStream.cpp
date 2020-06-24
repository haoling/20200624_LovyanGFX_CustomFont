#include "TftLogStream.h"
#include "GUIslice.h"
#include "elem/XTextbox.h"
#include <HardwareSerial.h>

extern gslc_tsGui m_gui;
extern gslc_tsElemRef* m_pElemTextbox1;

int TftLogStream::available(void) { return 0; }
int TftLogStream::read(void) { return -1; }
void TftLogStream::flush() {}
int TftLogStream::peek() { return -1; }
size_t TftLogStream::write(uint8_t n) {
  return Serial.write(n);
}
size_t TftLogStream::write(const uint8_t *buffer, size_t size) {
  char tftbuf[size + 1];
  memset(tftbuf, 0, size + 1);
  strncpy(tftbuf, (const char*)buffer, size);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextbox1, tftbuf);
  gslc_Update(&m_gui);
  return Serial.write(buffer, size);
}
