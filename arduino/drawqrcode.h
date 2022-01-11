#include <qrcode.h>


QRCode qrcode;

void drawQrCode(const char* qrStr, const char* lines[]) {
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, qrStr);

  // Text starting point
  int cursor_start_y = 10;
  int cursor_start_x = 4;
  int font_height = 12;

  // QR Code Starting Point
  int offset_x = 3;
  int offset_y = 62;


  for (int y = 0; y < qrcode.size; y++) {
      for (int x = 0; x < qrcode.size; x++) {
          int newX = offset_x + (x * 2);
          int newY = offset_y + (y * 2);

          if (qrcode_getModule(&qrcode, x, y)) {
              display.fillRect( newX, newY, 2, 2, 1);
          }
          else {
              display.fillRect( newX, newY, 2, 2, 0);
          }
      }
  }
  display.setTextColor(1,0);
  for (int i = 0; i < 4; i++) {
    display.setCursor(cursor_start_x,cursor_start_y+font_height*i);
    display.println(lines[i]);
  }
  display.display();
;

}
