#include "UTF8toSJIS.h"

String UTF8toSJIS(String utf8) {
  String sjis;
  char buf[2];
  buf[1] = 0x00;
  unsigned int i;
  for (i = 0; i < utf8.length() - 2; i++) {
    unsigned long c = ((utf8.charAt(i) << 16) & 0xFF0000) | ((utf8.charAt(i + 1) << 8) & 0xFF00) | (utf8.charAt(i + 2));
    //LOG.printf("UtoS: 0x%lX", c);

    if (0xEFBDA1 <= c && c <= 0xEFBDBF) {
      buf[0] = (c - 0xEFBD00) & 0xFF;
      sjis += buf;
      //LOG.printf(" => 0x%X (%s)", buf[0], buf);
      i += 2;
    } else if (0xEFBE80 <= c && c <= 0xEFBE9F) {
      // 0xC0～0xDFは認識されないので、0x80～0x9Fにマッピングする
      buf[0] = (c - 0xEFBDC0 - 0x40) & 0xFF;
      sjis += buf;
      //LOG.printf(" => 0x%X (%s)", buf[0], buf);
      i += 2;
    } else {
      c = ((utf8.charAt(i + 1) << 8) & 0xFF00) | (utf8.charAt(i + 2));
      if (c == 0x0020) {
        sjis += 0x20;
      } else {
        sjis += utf8.charAt(i);
      }
    }
    //LOG.println();
  }
  for (; i < utf8.length(); i++) {
    sjis += utf8.charAt(i);
  }

  return sjis;
}
