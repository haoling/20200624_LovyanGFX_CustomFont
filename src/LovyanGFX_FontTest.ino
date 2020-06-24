#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>

// ビルトインフォント版
// #include "../gui/gui_GSLC_builtin.h"

// カスタムフォント版
#include "../gui/gui_GSLC.h"

#include <TFT_eSPI.h>

// 半角カナをUTF-8からSjisに変換するライブラリ
#include "UTF8toSJIS.h"


//<Save_References !Start!>
gslc_tsElemRef* m_pElemText1      = NULL;
gslc_tsElemRef* m_pElemTextbox1   = NULL;
gslc_tsElemRef* m_pTextSlider1    = NULL;
//<Save_References !End!>

TFT_eSPI* tft;
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// E_ELEM_TEXTBOX1 への出力
#include "TftLogStream.h"
TftLogStream LOG;

// E_ELEM_TEXT1 への出力 と Serial への出力を同時に行うStream
#define TEXT1(str) gslc_ElemSetTxtStr(&m_gui, m_pElemText1, String(str).c_str()); gslc_Update(&m_gui);

void setup() {
  delay(1000);
  Serial.begin(921600);

  // 液晶の初期化
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
  tft = (TFT_eSPI*)gslc_GetDriverDisp(&m_gui);
  TEXT1(String("LovyanGFX Font Test: ") + UTF8toSJIS("ﾃｽﾄ ﾃﾞｽ"));
}

void loop() {
  LOG.printf("millis: %lu ms\n", millis());
  delay(3000);
}
