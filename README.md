# これ is 何
LovyanGFXライブラリをGUIsliceで使ったときに、カスタムフォントを読み込むとExceptionを吐くので、それの検証用のコードです。

# ファイル説明
## [fontconvert/fontconvert.c](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/fontconvert/fontconvert.c)
半角カナに対応した、GFXFontの生成ツールです。<br>
半角カナは、 「｡」～「ｿ」までを 0xA1～0xBFに、「ﾀ」～「ﾟ」を0x80～0x9Fにマッピングしています。<br>
上位側の7bit目 （01000000）が1になると表示できないみたいなので、空いているエリアにマッピングしました。

## [include/Fonts/JF-Dot-Shinonome125pt8b.h](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/include/Fonts/JF-Dot-Shinonome125pt8b.h)
上記fontconverterで変換した、半角カナ対応の東雲フォント（5pt）です。<br>
同じく JF-Dot-Shinonome128pt8b.h は8ptです。

## [lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h)
TFT_eSPIのフリをするLovyanGFXのインクルードファイル。<br>
ライブラリの中をいじりたくなかったので、ここに居る。

## [lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp)
我が家のESP32とTFT液晶（[ST7789](https://amzn.to/37WbnBz)）用のGPIOピンの定義などを書いたヘッダファイル。<br>
TFT_eSPI型はこのファイルで定義されている。

## [src/TftLogStream.cpp](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/src/TftLogStream.cpp)
TFTのpElemTextbox1とSerialに、同時にログを流すStreamクラス

## [src/UTF8toSJIS.cpp](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/src/UTF8toSJIS.cpp)
UTF-8の半角カナを、上記fontconverter用の、おかしなマッピングの半角カナのコードに変換する関数。<br>
これで変換した文字列を `gslc_ElemSetTxtStr` に渡すと（本来であれば）半角カナがTFTに表示される。<br>
（このコードでは変換後の文字列をTftLogStreamに渡しているので、シリアルモニタの表示は化ける。）

## [src/LovyanGFX_FontTest.ino](https://github.com/haoling/20200624_LovyanGFX_CustomFont/blob/master/src/LovyanGFX_FontTest.ino)
mainコード

# 状況説明
## 動画
こうなります。microSDのスロットが見えますが、このコードでは使っていません。<br>
（別のGPIOにささっています。）<br>
[![](https://img.youtube.com/vi/NbPKXDM_hGE/0.jpg)](https://www.youtube.com/watch?v=NbPKXDM_hGE)


## シリアルモニタ

```
--- Miniterm on COM10  921600,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
 � ���� ��  �� ��� �� �� �� � �   �GUIslice version [0.14.0]:
- Init display handler [TFT_eSPI] OK
- No touch handler enabled
Guru Meditation Error: Core  1 panic'ed (InstrFetchProhibited). Exception was unhandled.
Core 1 register dump:
PC      : 0xbb26666f  PS      : 0x00060330  A0      : 0x800d3df1  A1      : 0x3ffb1d50
A2      : 0x3ffc06d4  A3      : 0x3f405494  A4      : 0x00000070  A5      : 0x3ffb1e30
A6      : 0x00000000  A7      : 0x00000000  A8      : 0x800d3c65  A9      : 0x00000001
A10     : 0x3f405494  A11     : 0x3ffc0778  A12     : 0x00000006  A13     : 0x3ffb1d0e
A14     : 0x00000020  A15     : 0x00000000  SAR     : 0x0000001e  EXCCAUSE: 0x00000014
EXCVADDR: 0xbb26666c  LBEG    : 0x4000c46c  LEND    : 0x4000c477  LCOUNT  : 0x00000000

Backtrace: 0x7b26666f:0x3ffb1d50 0x400d3dee:0x3ffb1d70 0x400d63b1:0x3ffb1d90 0x400d1940:0x3ffb1ef0 0x400d1a3c:0x3ffb1f40 0x400d84fb:0x3ffb1fb0 0x40088455:0x3ffb1fd0
  #0  0x7b26666f:0x3ffb1d50 in ?? ??:0
  #1  0x400d3dee:0x3ffb1d70 in lgfx::LGFX_Font_Support<lgfx::LGFX_IMG_Support<lgfx::LGFXBase> >::setFreeFont(lgfx::IFont const*) at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:564
      (inlined by) gslc_DrvGetTxtSize at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:378
  #2  0x400d63b1:0x3ffb1d90 in gslc_ElemXTextboxCreate at .pio\libdeps\ESP-32S\GUIslice_ID5168\src\elem/XTextbox.c:352
  #3  0x400d1940:0x3ffb1ef0 in InitGUIslice_gen() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #4  0x400d1a3c:0x3ffb1f40 in setup() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #5  0x400d84fb:0x3ffb1fb0 in loopTask(void*) at C:\Users\MAYA\.platformio\packages\framework-arduinoespressif32\cores\esp32/main.cpp:14
  #6  0x40088455:0x3ffb1fd0 in vPortTaskWrapper at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/freertos/port.c:355 (discriminator 1)

Rebooting...
�� � ��� �   � ����� ��             �   �        �        � ��� �� ��  � ��  �   �� � �� �    �� �   � � ���������� � ����������  ���� �� ���� � ���� �  �   ������� �� �    ��  ��    � � �� ���  ����  �� �� �� ������  �  �� �� ��  ����  �� �� � ���� � ��  � � ���� ��  �� ��� �� �� �� � �      �   � �� ���  ����� �� �    ��� ��� ���  � � � ���������  �  � �� �    �     � � ����  �  � �� �    �     �   ����  �  � �� �    �     � � �� � 
 ���  �  � �� �    �     �  ��  ����  �  � �� �    �     � ��� ����  �  � �� �    �    ��  � �������  ��� � �   ��  �� � �   � � ������ �����    �� �� �� �    ��  �  ������ �  � �    ��    �  �  �    �     �  ���� � �� 
�  � ��  �  ������ �  � �    ��    �  �  �    �  � � �  ���� � �� � �     �  � ��  �  ������ �  � �    � �     ��          �  ���� � �� �     �   � ��  �  ������ �  � �    � �          �      �  ���� � �� � ���        ��  � �� � �� ��  �� �     � �          � � �� ���  � GUIslice version [0.14.0]:
- Init display handler [TFT_eSPI] OK
- No touch handler enabled
Guru Meditation Error: Core  1 panic'ed (InstrFetchProhibited). Exception was unhandled.
Core 1 register dump:
PC      : 0xbb26666f  PS      : 0x00060330  A0      : 0x800d3df1  A1      : 0x3ffb1d50
A2      : 0x3ffc06d4  A3      : 0x3f405494  A4      : 0x00000070  A5      : 0x3ffb1e30
A6      : 0x00000000  A7      : 0x00000000  A8      : 0x800d3c65  A9      : 0x00000001
A10     : 0x3f405494  A11     : 0x3ffc0778  A12     : 0x00000006  A13     : 0x3ffb1d0e
A14     : 0x00000020  A15     : 0x00000000  SAR     : 0x0000001e  EXCCAUSE: 0x00000014
EXCVADDR: 0xbb26666c  LBEG    : 0x4000c46c  LEND    : 0x4000c477  LCOUNT  : 0x00000000

Backtrace: 0x7b26666f:0x3ffb1d50 0x400d3dee:0x3ffb1d70 0x400d63b1:0x3ffb1d90 0x400d1940:0x3ffb1ef0 0x400d1a3c:0x3ffb1f40 0x400d84fb:0x3ffb1fb0 0x40088455:0x3ffb1fd0
  #0  0x7b26666f:0x3ffb1d50 in ?? ??:0
  #1  0x400d3dee:0x3ffb1d70 in lgfx::LGFX_Font_Support<lgfx::LGFX_IMG_Support<lgfx::LGFXBase> >::setFreeFont(lgfx::IFont const*) at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:564
      (inlined by) gslc_DrvGetTxtSize at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:378
  #2  0x400d63b1:0x3ffb1d90 in gslc_ElemXTextboxCreate at .pio\libdeps\ESP-32S\GUIslice_ID5168\src\elem/XTextbox.c:352
  #3  0x400d1940:0x3ffb1ef0 in InitGUIslice_gen() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #4  0x400d1a3c:0x3ffb1f40 in setup() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #5  0x400d84fb:0x3ffb1fb0 in loopTask(void*) at C:\Users\MAYA\.platformio\packages\framework-arduinoespressif32\cores\esp32/main.cpp:14
  #6  0x40088455:0x3ffb1fd0 in vPortTaskWrapper at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/freertos/port.c:355 (discriminator 1)

Rebooting...
�� � ��� �   � ����� ��             �   �        �        � ��� �� ��  � ��  �   �� � �� �    �� �   � � ���������� � ����������  ���� �� ���� � ���� �  �   ������� �� �    ��  ��    � � �� ���  ����  �� �� �� ������  �  �� �� ��  ����  �� �� � ���� � ��  � � ���� ��  �� ��� �� �� �� � �      �   � �� ���  ����� �� �    ��� ��� ���  � � � ���������  �  � �� �    �     � � ����  �  � �� �    �     �   ����  �  � �� �    �     � � �� � 
 ���  �  � �� �    �     �  ��  ����  �  � �� �    �     � ��� ����  �  � �� �    �    ��  � �������  ��� � �   ��  �� � �   � � ������ �����    �� �� �� �    ��  �  ������ �  � �    ��    �  �  �    �     �  ���� � �� 
�  � ��  �  ������ �  � �    ��    �  �  �    �  � � �  ���� � �� � �     �  � ��  �  ������ �  � �    � �     ��          �  ���� � �� �     �   � ��  �  ������ �  � �    � �          �      �  ���� � �� � ���        ��  � �� � �� ��  �� �     � �          � � �� ���  � GUIslice version [0.14.0]:
- Init display handler [TFT_eSPI] OK
- No touch handler enabled
Guru Meditation Error: Core  1 panic'ed (InstrFetchProhibited). Exception was unhandled.
Core 1 register dump:
PC      : 0xbb26666f  PS      : 0x00060330  A0      : 0x800d3df1  A1      : 0x3ffb1d50
A2      : 0x3ffc06d4  A3      : 0x3f405494  A4      : 0x00000070  A5      : 0x3ffb1e30
A6      : 0x00000000  A7      : 0x00000000  A8      : 0x800d3c65  A9      : 0x00000001
A10     : 0x3f405494  A11     : 0x3ffc0778  A12     : 0x00000006  A13     : 0x3ffb1d0e
A14     : 0x00000020  A15     : 0x00000000  SAR     : 0x0000001e  EXCCAUSE: 0x00000014
EXCVADDR: 0xbb26666c  LBEG    : 0x4000c46c  LEND    : 0x4000c477  LCOUNT  : 0x00000000

Backtrace: 0x7b26666f:0x3ffb1d50 0x400d3dee:0x3ffb1d70 0x400d63b1:0x3ffb1d90 0x400d1940:0x3ffb1ef0 0x400d1a3c:0x3ffb1f40 0x400d84fb:0x3ffb1fb0 0x40088455:0x3ffb1fd0
  #0  0x7b26666f:0x3ffb1d50 in ?? ??:0
  #1  0x400d3dee:0x3ffb1d70 in lgfx::LGFX_Font_Support<lgfx::LGFX_IMG_Support<lgfx::LGFXBase> >::setFreeFont(lgfx::IFont const*) at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:564
      (inlined by) gslc_DrvGetTxtSize at .pio\libdeps\ESP-32S\GUIslice_ID5168\src/GUIslice_drv_tft_espi.cpp:378
  #2  0x400d63b1:0x3ffb1d90 in gslc_ElemXTextboxCreate at .pio\libdeps\ESP-32S\GUIslice_ID5168\src\elem/XTextbox.c:352
  #3  0x400d1940:0x3ffb1ef0 in InitGUIslice_gen() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #4  0x400d1a3c:0x3ffb1f40 in setup() at S:/workspace/Arduino/LovyanGFX_FontTest/src/LovyanGFX_FontTest.ino:48
  #5  0x400d84fb:0x3ffb1fb0 in loopTask(void*) at C:\Users\MAYA\.platformio\packages\framework-arduinoespressif32\cores\esp32/main.cpp:14
  #6  0x40088455:0x3ffb1fd0 in vPortTaskWrapper at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/freertos/port.c:355 (discriminator 1)

Rebooting...
�� � ��� �   � ����� ��             �   �        �        � ��� �� ��  � ��  �   �� � �� �    �� �   � � ���������� � ����������  ���� �� ���� � ���� �  �   ������� �� �    ��  ��    � � �� ���  ����  �� �� �� ������  �  �� �� ��  ����  �� �� � ���� � ��  � � ���� ��  �� ��� �� �� �� � �      �   � �� ���  ����� �� �    ��� ��� ���  � � � ���������  �  � �� �    �     � � ����  �  � �� �    �     �   ����  �  � �� �    �     � � �� � 
 ���  �  � �� �    �     �  ��  ����  �  � �� �    �     � ��� ����  �  � �� �    �    ��  � �������  ��� � �   ��  �� � �   � � ������ �����    �� �� �� �    ��  �  ������ �  � �    ��    �  �  �    �     �  ���� � �� 
�  � ��  �  ������ �  � �    ��    �  �  �    �  � � �  ���� � �� � �     �  � ��  �  ������ �  � �    � �     ��          �  ���� � �� �     �   � ��  �  ������ �  � �    � �          �      �  ���� � �� � ���        ��  � �� � �� ��  �� �     � �          � � �� ���  �
--- exit ---
```

## ビルドログ
<details><summary>長いので畳む</summary><div>

```
Scanning dependencies...
Dependency Graph
|-- <GUIslice> 0.14.0
|   |-- <Adafruit GFX Library> 1.9.0
|   |   |-- <Adafruit BusIO> 1.3.2
|   |   |   |-- <Wire> 1.0.1
|   |   |   |-- <SPI> 1.0
|   |   |-- <SPI> 1.0
|   |   |-- <Wire> 1.0.1
|   |-- <SD(esp32)> 1.0.5
|   |   |-- <FS> 1.0
|   |   |-- <SPI> 1.0
|   |-- <SPI> 1.0
|   |-- <Wire> 1.0.1
|   |-- <FS> 1.0
|   |-- <LovyanGFX_TFT_eSPI>
|   |   |-- <LovyanGFX> 0.1.12 #ef2380c
|   |   |   |-- <ESP32 BLE Arduino> 1.0.1
|   |   |   |-- <SPI> 1.0
|-- <Adafruit GFX Library> 1.9.0
|   |-- <Adafruit BusIO> 1.3.2
|   |   |-- <Wire> 1.0.1
|   |   |-- <SPI> 1.0
|   |-- <SPI> 1.0
|   |-- <Wire> 1.0.1
|-- <LovyanGFX> 0.1.12 #ef2380c
|   |-- <ESP32 BLE Arduino> 1.0.1
|   |-- <SPI> 1.0
|-- <SPI> 1.0
|-- <LovyanGFX_TFT_eSPI>
|   |-- <LovyanGFX> 0.1.12 #ef2380c
|   |   |-- <ESP32 BLE Arduino> 1.0.1
|   |   |-- <SPI> 1.0
|-- <Wire> 1.0.1
Building in release mode
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\Fonts\lgfx_fonts.cpp.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\LGFXBase.cpp.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\platforms\esp32_common.cpp.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\platforms\samd51_common.cpp.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\utility\lgfx_pngle.c.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\utility\lgfx_qrcode.c.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\utility\lgfx_tjpgd.c.o
Compiling .pio\build\ESP-32S\lib6d0\LovyanGFX\lgfx\utility\miniz.c.o
Compiling .pio\build\ESP-32S\src\LovyanGFX_FontTest.ino.cpp.o
Compiling .pio\build\ESP-32S\src\TftLogStream.cpp.o
Compiling .pio\build\ESP-32S\src\UTF8toSJIS.cpp.o
Generating partitions .pio\build\ESP-32S\partitions.bin
Compiling .pio\build\ESP-32S\libe9f\Wire\Wire.cpp.o
Compiling .pio\build\ESP-32S\libbd4\SPI\SPI.cpp.o
Compiling .pio\build\ESP-32S\lib67b\Adafruit BusIO_ID6214\Adafruit_BusIO_Register.cpp.o
Compiling .pio\build\ESP-32S\lib67b\Adafruit BusIO_ID6214\Adafruit_I2CDevice.cpp.o
Compiling .pio\build\ESP-32S\lib67b\Adafruit BusIO_ID6214\Adafruit_SPIDevice.cpp.o
Compiling .pio\build\ESP-32S\lib14b\Adafruit GFX Library_ID13\Adafruit_GFX.cpp.o
Compiling .pio\build\ESP-32S\lib14b\Adafruit GFX Library_ID13\Adafruit_MonoOLED.cpp.o
Compiling .pio\build\ESP-32S\lib14b\Adafruit GFX Library_ID13\Adafruit_SPITFT.cpp.o
Compiling .pio\build\ESP-32S\lib14b\Adafruit GFX Library_ID13\glcdfont.c.o
Compiling .pio\build\ESP-32S\lib0e8\FS\FS.cpp.o
Compiling .pio\build\ESP-32S\lib0e8\FS\vfs_api.cpp.o
Compiling .pio\build\ESP-32S\lib951\SD\SD.cpp.o
Archiving .pio\build\ESP-32S\libbd4\libSPI.a
Compiling .pio\build\ESP-32S\lib951\SD\sd_diskio.cpp.o
Compiling .pio\build\ESP-32S\lib951\SD\sd_diskio_crc.c.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLE2902.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLE2904.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEAddress.cpp.o
Archiving .pio\build\ESP-32S\libe9f\libWire.a
Compiling .pio\build\ESP-32S\libe50\BLE\BLEAdvertisedDevice.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEAdvertising.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEBeacon.cpp.o
Archiving .pio\build\ESP-32S\lib67b\libAdafruit BusIO_ID6214.a
Compiling .pio\build\ESP-32S\libe50\BLE\BLECharacteristic.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLECharacteristicMap.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEClient.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEDescriptor.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEDescriptorMap.cpp.o
Archiving .pio\build\ESP-32S\lib14b\libAdafruit GFX Library_ID13.a
Compiling .pio\build\ESP-32S\libe50\BLE\BLEDevice.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEEddystoneTLM.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEEddystoneURL.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEExceptions.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEHIDDevice.cpp.o
Archiving .pio\build\ESP-32S\lib0e8\libFS.a
Compiling .pio\build\ESP-32S\libe50\BLE\BLERemoteCharacteristic.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLERemoteDescriptor.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLERemoteService.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEScan.cpp.o
Archiving .pio\build\ESP-32S\lib951\libSD.a
Compiling .pio\build\ESP-32S\libe50\BLE\BLESecurity.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEServer.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEService.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEServiceMap.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEUUID.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEUtils.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\BLEValue.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\FreeRTOS.cpp.o
Compiling .pio\build\ESP-32S\libe50\BLE\GeneralUtils.cpp.o
Archiving .pio\build\ESP-32S\lib512\libLovyanGFX_TFT_eSPI.a
C:\Users\MAYA\.platformio\packages\framework-arduinoespressif32\libraries\BLE\src\BLERemoteService.cpp: In member function 'void BLERemoteService::getCharacteristics(std::map<short unsigned int, BLERemoteCharacteristic*>*)':
C:\Users\MAYA\.platformio\packages\framework-arduinoespressif32\libraries\BLE\src\BLERemoteService.cpp:246:89: warning: parameter 'pCharacteristicMap' set but not used [-Wunused-but-set-parameter]
 void BLERemoteService::getCharacteristics(std::map<uint16_t, BLERemoteCharacteristic*>* pCharacteristicMap) {
                                                                                         ^
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_drv_adagfx.cpp.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_drv_m5stack.cpp.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_drv_sdl.c.o
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice.c: In function 'gslc_CollectElemAdd':
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice.c:4453:22: warning: variable 'pElemRam' set but not used [-Wunused-but-set-variable]
   const gslc_tsElem* pElemRam = NULL; // Local element in RAM
                      ^
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_drv_tft_espi.cpp.o
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice.c: In function 'gslc_DebugPrintf':
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice.c:477:9: warning: 'cOut' may be used uninitialized in this function [-Wmaybe-uninitialized]
         (g_pfDebugOut)(cOut);
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_drv_utft.cpp.o
         ^
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\GUIslice_th.cpp.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XCheckbox.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XGauge.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XGlowball.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XGraph.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XKeyPad.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XKeyPad_Alpha.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XKeyPad_Num.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XListbox.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XProgress.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XRadial.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XRamp.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XRingGauge.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XSelNum.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XSlider.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XSpinner.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XTemplate.c.o
Compiling .pio\build\ESP-32S\lib322\GUIslice_ID5168\elem\XTextbox.c.o
Archiving .pio\build\ESP-32S\libFrameworkArduinoVariant.a
Compiling .pio\build\ESP-32S\FrameworkArduino\Esp.cpp.o
Archiving .pio\build\ESP-32S\libe50\libBLE.a
Compiling .pio\build\ESP-32S\FrameworkArduino\FunctionalInterrupt.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\HardwareSerial.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\IPAddress.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\IPv6Address.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\MD5Builder.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\Print.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\Stream.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\StreamString.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\WMath.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\WString.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\base64.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\cbuf.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-adc.c.o
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp: In function 'bool gslc_DrvGetTxtSize(gslc_tsGui*, gslc_tsFont*, const char*, gslc_teTxtFlags, int16_t*, int16_t*, uint16_t*, uint16_t*)':
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:376:25: warning: 'void lgfx::LGFX_Font_Support<Base>::setTextFont(int) [with Base = lgfx::LGFX_IMG_Support<lgfx::LGFXBase>]' is deprecated: use setFont(&fonts::Font0) [-Wdeprecated-declarations]
     m_disp.setTextFont(1);
                         ^
In file included from .pio/libdeps/ESP-32S/LovyanGFX/src/LovyanGFX.hpp:39:0,
                 from lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp:10,
                 from lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h:5,
                 from .pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:47:
.pio/libdeps/ESP-32S/LovyanGFX/src/lgfx/lgfx_font_support.hpp:389:10: note: declared here
     void setTextFont(int f) {
          ^
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:378:54: warning: 'void lgfx::LGFX_Font_Support<Base>::setFreeFont(const lgfx::IFont*) [with Base = lgfx::LGFX_IMG_Support<lgfx::LGFXBase>]' is deprecated: use setFont() [-Wdeprecated-declarations]
     m_disp.setFreeFont((const GFXfont *)pFont->pvFont);
                                                      ^
In file included from .pio/libdeps/ESP-32S/LovyanGFX/src/LovyanGFX.hpp:39:0,
                 from lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp:10,
                 from lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h:5,
                 from .pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:47:
.pio/libdeps/ESP-32S/LovyanGFX/src/lgfx/lgfx_font_support.hpp:399:10: note: declared here
     void setFreeFont(const IFont* font = nullptr) { setFont(font); }
          ^
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-bt.c.o
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp: In function 'bool gslc_DrvDrawTxtAlign(gslc_tsGui*, int16_t, int16_t, int16_t, int16_t, int8_t, gslc_tsFont*, const char*, gslc_teTxtFlags, gslc_tsColor, gslc_tsColor)':
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:406:25: warning: 'void lgfx::LGFX_Font_Support<Base>::setTextFont(int) [with Base = lgfx::LGFX_IMG_Support<lgfx::LGFXBase>]' is deprecated: use setFont(&fonts::Font0) [-Wdeprecated-declarations]
     m_disp.setTextFont(1);
                         ^
In file included from .pio/libdeps/ESP-32S/LovyanGFX/src/LovyanGFX.hpp:39:0,
                 from lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp:10,
                 from lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h:5,
                 from .pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:47:
.pio/libdeps/ESP-32S/LovyanGFX/src/lgfx/lgfx_font_support.hpp:389:10: note: declared here
     void setTextFont(int f) {
          ^
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:415:56: warning: 'void lgfx::LGFX_Font_Support<Base>::setFreeFont(const lgfx::IFont*) [with Base = lgfx::LGFX_IMG_Support<lgfx::LGFXBase>]' is deprecated: use setFont() [-Wdeprecated-declarations]
       m_disp.setFreeFont((const GFXfont *)pFont->pvFont);
                                                        ^
In file included from .pio/libdeps/ESP-32S/LovyanGFX/src/LovyanGFX.hpp:39:0,
                 from lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp:10,
                 from lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h:5,
                 from .pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:47:
.pio/libdeps/ESP-32S/LovyanGFX/src/lgfx/lgfx_font_support.hpp:399:10: note: declared here
     void setFreeFont(const IFont* font = nullptr) { setFont(font); }
          ^
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:438:29: warning: 'void lgfx::LGFX_Font_Support<Base>::setTextDatum(uint8_t) [with Base = lgfx::LGFX_IMG_Support<lgfx::LGFXBase>; uint8_t = unsigned char]' is deprecated: use textdatum_t [-Wdeprecated-declarations]
   m_disp.setTextDatum(nDatum);
                             ^
In file included from .pio/libdeps/ESP-32S/LovyanGFX/src/LovyanGFX.hpp:39:0,
                 from lib/LovyanGFX_TFT_eSPI/src/LGFX_TFT_eSPI.hpp:10,
                 from lib/LovyanGFX_TFT_eSPI/src/TFT_eSPI.h:5,
                 from .pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:47:
.pio/libdeps/ESP-32S/LovyanGFX/src/lgfx/lgfx_font_support.hpp:249:10: note: declared here
     void setTextDatum(std::uint8_t datum) { _text_style.datum = (textdatum_t)datum; }
          ^
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:395:12: warning: unused variable 'nColBgRaw' [-Wunused-variable]
   uint16_t nColBgRaw = gslc_DrvAdaptColorToRaw(colBg);
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-cpu.c.o
            ^
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp: In function 'bool gslc_DrvDrawTxt(gslc_tsGui*, int16_t, int16_t, gslc_tsFont*, const char*, gslc_teTxtFlags, gslc_tsColor, gslc_tsColor)':
.pio\libdeps\ESP-32S\GUIslice_ID5168\src\GUIslice_drv_tft_espi.cpp:469:12: warning: unused variable 'nColBgRaw' [-Wunused-variable]
   uint16_t nColBgRaw = gslc_DrvAdaptColorToRaw(colBg);
            ^
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-dac.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-gpio.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-i2c.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-ledc.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-matrix.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-misc.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-psram.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-rmt.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-sigmadelta.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-spi.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-time.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-timer.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-touch.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\esp32-hal-uart.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\libb64\cdecode.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\libb64\cencode.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\main.cpp.o
Compiling .pio\build\ESP-32S\FrameworkArduino\stdlib_noniso.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\wiring_pulse.c.o
Compiling .pio\build\ESP-32S\FrameworkArduino\wiring_shift.c.o
Archiving .pio\build\ESP-32S\lib322\libGUIslice_ID5168.a
Archiving .pio\build\ESP-32S\libFrameworkArduino.a
Linking .pio\build\ESP-32S\firmware.elf
Building .pio\build\ESP-32S\firmware.bin
Retrieving maximum program size .pio\build\ESP-32S\firmware.elf
Checking size .pio\build\ESP-32S\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [=         ]   5.3% (used 17484 bytes from 327680 bytes)
Flash: [=         ]  14.1% (used 276421 bytes from 1966080 bytes)
```

</div></details>