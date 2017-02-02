/**-----------------------------------------------------------------------------
 * \file    LEDMatrix.cpp
 * \author  jh
 * \date    xx.02.2017
 *
 * @{
 -----------------------------------------------------------------------------*/

 /* Includes --------------------------------------------------- */
#include "LEDMatrix.h"

/* Public ----------------------------------------------------- */
/** ===========================================================
 * \fn      fillScreen
 * \brief   fills the whole LED matrix
 *
 * \param   (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::fillScreen(uint8_t brightness)
{
  for (uint8_t y = 0; y < y_; y++)
  {
    for (uint8_t x = 0; x < x_; x++) drawPixel(x, y, brightness);
  }
}

/** ===========================================================
 * \fn      clear
 * \brief   clears the whole LED matrix
 ============================================================== */
void LEDMatrix::clear()
{
  fillScreen(0);
}

/** ===========================================================
 * \fn      drawLine
 * \brief   draws a line on given coordinates and brightness
 *          (uses the Bresenham's line-drawing algorithm)
 *
 * \param   (byte) x0, y0 start coordinate of the line
 *          (byte) x1, y1 end coordinate of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t b)
{
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t dx_abs = abs(dx);
  int16_t dy_abs = abs(dy);
  int16_t s_dx = sgn(dx);
  int16_t s_dy = sgn(dy);
  int16_t x = dy_abs >> 1;
  int16_t y = dx_abs >> 1;
  int16_t px = x0;
  int16_t py = y0;

  setPixel(x0, y0, b); // draw first pixel

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int16_t i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      setPixel(px, py, b);
    }
  }
  else // the line is more vertical than horizontal
  {
    int16_t i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      setPixel(px, py, b);
    }
  }
}

/** ===========================================================
 * \fn      movePixel
 * \brief   moves given Pixel to anoter given position
 *
 * \param   (byte) x0, y0 target LED
 *          (byte) x1, y1 new positon
 * \return  -
 ============================================================== */
void LEDMatrix::movePixel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  uint8_t led = getPixel(x0, y0);
  clearPixel(x0, y0);
  setPixel(x1, y1, led);
}

/** ===========================================================
 * \fn      animatePixel
 * \brief   moves a Pixel step by step to a new position
 *          (uses the Bresenham's line-drawing algorithm)
 *
 * \param   (byte) x0, y0 target LED
 *          (byte) x1, y1 end position
 *          (uint) step speed in ms
 * \return  -
 ============================================================== */
void LEDMatrix::animatePixel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t stepInMillis)
{
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t dx_abs = abs(dx);
  int16_t dy_abs = abs(dy);
  int16_t s_dx = sgn(dx);
  int16_t s_dy = sgn(dy);
  int16_t x = dy_abs >> 1;
  int16_t y = dx_abs >> 1;
  int16_t px = x0;
  int16_t py = y0;

  uint8_t b = getPixel(x0, y0);
  delay(stepInMillis);
  clearPixel(x0, y0);

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int16_t i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      setPixel(px, py, b);
      delay(stepInMillis);
      clearPixel(px, py);
    }
  }
  else // the line is more vertical than horizontal
  {
    int16_t i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      setPixel(px, py, b);
      delay(stepInMillis);
      clearPixel(px, py);
    }
  }
  setPixel(px, py, b);
}

/** ===========================================================
 * \fn      drawHLine
 * \brief   draws a horizontal line with given lenght and
 *          brightness
 *
 * \requ    drawLine()
 *
 * \param   (byte) x, y start coordinate of the line
 *          (byte) length of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawHLine(uint8_t x, uint8_t y, uint8_t l, uint8_t b)
{
  drawLine(x, y, x + l - 1, y, b);
}

/** ===========================================================
 * \fn      drawVLine
 * \brief   draws a vertical line with given height and
 *          brightness
 *
 * \requ    drawLine()
 *
 * \param   (byte) x, y start coordinate of the line
 *          (byte) height of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t b)
{
  drawLine(x, y, x, y + h - 1, b);
}

/** ===========================================================
 * \fn      drawRectangle
 * \brief   draws a rectangle on given coordinate and
 *          brightness
 *
 * \requ    drawHLine(), drawVLine()
 *
 * \param   (byte) x, y top left coordinate of the rectangle
 *          (byte) length of the rectangle
 *          (byte) hight of the rectangle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawRectangle(uint8_t x, uint8_t y, uint8_t l, uint8_t h, uint8_t b)
{
  drawHLine(x, y, l, b);
  drawVLine(x, y, h, b);
  drawHLine(x, y + h - 1, l, b);
  drawVLine(x + l - 1, y, h, b);
}

/** ===========================================================
 * \fn      drawFilledRectangle
 * \brief   draws a filled rectangle on given coordinates and
 *          brightness
 *
 * \requ    drawHLine()
 *
 * \param   (byte) x, y top left coordinate of the rectangle
 *          (byte) length of the rectangle
 *          (byte) hight of the rectangle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawFilledRectangle(uint8_t x, uint8_t y, uint8_t l, uint8_t h, uint8_t b)
{
  for (uint8_t i = y; i < y + h; i++)
  {
    drawHLine(x, i, l, b);
  }
}

/** ===========================================================
 * \fn      drawCircle
 * \brief   draws a circle on given coordinate with given
 *          radius and brightness
 *
 * \requ    setPixel()
 *
 * \param   (byte) x0, y0 origo of the circle
 *          (byte) radius of the circle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t b)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  setPixel(x0, y0+r, b);
  setPixel(x0, y0-r, b);
  setPixel(x0+r, y0, b);
  setPixel(x0-r, y0, b);

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    setPixel(x0 + x, y0 + y, b);
    setPixel(x0 - x, y0 + y, b);
    setPixel(x0 + x, y0 - y, b);
    setPixel(x0 - x, y0 - y, b);
    setPixel(x0 + y, y0 + x, b);
    setPixel(x0 - y, y0 + x, b);
    setPixel(x0 + y, y0 - x, b);
    setPixel(x0 - y, y0 - x, b);
  }
}

/** ===========================================================
 * \fn      drawFilledCircle
 * \brief   draws a filled circle on given coordinate with
 *          given radius and brightness
 *
 * \requ    drawHLine(), drawLine()
 *
 * \param   (byte) x0, y0 origo of the circle
 *          (byte) radius of the circle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawFilledCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t b)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawHLine(x0 - r, y0, 2 * r + 1, b);

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawLine(x0 + x, y0 + y, x0 - x, y0 + y, b);
    drawLine(x0 + x, y0 - y, x0 - x, y0 - y, b);
    drawLine(x0 + y, y0 + x, x0 - y, y0 + x, b);
    drawLine(x0 + y, y0 - x, x0 - y, y0 - x, b);
  }
}

/** ===========================================================
 * \fn      drawTriangle
 * \brief   draws a triangle on given coordinates and
 *          brightness
 *
 * \requ    drawLine()
 *
 * \param   (byte) x0-x2, y0-y2 coordinates of the triangle
 *                 corners
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t b)
{
  drawLine(x0, y0, x1, y1, b);
  drawLine(x0, y0, x2, y2, b);
  drawLine(x1, y1, x2, y2, b);
}

/** ===========================================================
 * \fn      drawFilledTriangle
 * \brief   draws a filled triangle on given coordinates and
 *          brightness
 *          (uses the Bresenham's line-drawing algorithm)
 *
 * \requ    drawLine()
 *
 * \param   (byte) x0-x2, y0-y2 coordinates of the triangle
 *                 corners
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawFilledTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t b)
{
  /* do the same as in the drawLine() function but draw lines to
   the static corner x2,y2 instaed of single pixels */
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t dx_abs = abs(dx);
  int16_t dy_abs = abs(dy);
  int16_t s_dx = sgn(dx);
  int16_t s_dy = sgn(dy);
  int16_t x = dy_abs >> 1;
  int16_t y = dx_abs >> 1;
  int16_t px = x0;
  int16_t py = y0;

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int16_t i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      drawLine(x2, y2, px, py, b);
    }
  }
  else // the line is more vertical than horizontal
  {
    int16_t i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      drawLine(x2, y2, px, py, b);
    }
  }

  /* do the same again, but with x0,y0 as the static corner to get rid of some empty pixels */
  dx = x2 - x1;
  dy = y2 - y1;
  dx_abs = abs(dx);
  dy_abs = abs(dy);
  s_dx = sgn(dx);
  s_dy = sgn(dy);
  x = dy_abs >> 1;
  y = dx_abs >> 1;
  px = x1;
  py = y1;

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int16_t i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      drawLine(x0, y0, px, py, b);
    }
  }
  else // the line is more vertical than horizontal
  {
    int16_t i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      drawLine(x0, y0, px, py, b);
    }
  } 
}

/** ===========================================================
 * \fn      drawPicture
 * \brief   draws a given picture
 *
 * \requ    <avr/pgmspace.h>, buffer[][], ...
 *
 * \param   (byte) x0, y0 top left coordinate of the picture
 *          (byte) length of the picture
 *          (byte) hight of the picture
 *          (byte*) constant byte pointer to the picture
 * \return  -
 ============================================================== */
void LEDMatrix::drawPicture(uint8_t x0, uint8_t y0, uint8_t l, uint8_t h, const uint8_t *image)
{
  if (x0 + l > LED_MATRIX_PICTURE_X || y0 + h > LED_MATRIX_PICTURE_Y) return;

  for (uint8_t y = y0; y < y0 + h; y++)
  {
    for (uint8_t x = x0; x < x0 + l; x++) 
    {
      setPixel(x, y, pgm_read_byte(&image[x+y*LED_MATRIX_PICTURE_X]));
    }
  }
}

/** ===========================================================
 * \fn      drawChar
 * \brief   draws a character on given position and brightness
 *
 * \requ    <avr/pgmspace.h>, setPixel()
 *
 * \param   (byte) x, y top left coordinate of the character
 *          (char) ASCII character
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawChar(uint8_t x, uint8_t y, char c, uint8_t b)
{
  for (uint8_t cy = 0; cy < LED_MATRIX_FONTSIZE; cy++)
  {
    for (uint8_t cx = 0; cx < LED_MATRIX_FONTWIDTH; cx++)
    {
      if (pgm_read_byte(&(characters[c - ASCII_FIRST_CHARACTER_OFFSET][cy][cx])) > 0) setPixel(x + cx, y + cy, b);
      else clearPixel(x + cx, y + cy);
    }
  }
}

/** ===========================================================
 * \fn      drawString
 * \brief   draws a string on given position and brightness
 *
 * \requ    drawChar()
 *
 * \param   (byte)  x, y top left coordinate of the string
 *          (char*) constant string (char array)
 *          (byte)  brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void LEDMatrix::drawString(uint8_t x, uint8_t y, const char *str, uint8_t b)
{  
  uint8_t ofCnt = 0;  // overflow counter
  
  for (uint16_t i = 0; str[i] != '\0'; i++)
  {
    uint8_t currentX = x + i * (LED_MATRIX_FONTWIDTH + CHAR_SPACING_OFFSET);

    /* check if end of row woulde be reached */
    if ((currentX + LED_MATRIX_FONTWIDTH) > y_)
    {
      /* limit owerflow counter */
      ofCnt %=  (y_ / (LED_MATRIX_FONTWIDTH + CHAR_SPACING_OFFSET));
      if (ofCnt == 0) y += LED_MATRIX_FONTSIZE;
      ofCnt++;

      currentX = ofCnt * (LED_MATRIX_FONTWIDTH + CHAR_SPACING_OFFSET);
    }

    drawChar(currentX, y, str[i], b);
  }
}

/** ===========================================================
 * \fn      runningText
 * \brief   draws a string on given position and moves it to
 *          the left
 *
 * \requ    drawChar()
 *
 * \param   (byte)  x0, y0 top left coordinate of the string
 *          (char*) constant string (char array)
 *          (byte)  brightness value (0... MAX_BRIGHTNESS_VALUE)
 *          (uint)  step speed in ms
 * \return  -
 ============================================================== */
void LEDMatrix::runningText(uint8_t x0, uint8_t y0, const char* str, uint8_t b, uint16_t stepInMillis)
{
  for (uint8_t i = 0; str[i+1] != '\0'; i++)
  {
    for (int16_t x = 0; x > -(LED_MATRIX_FONTWIDTH+CHAR_SPACING_OFFSET); x--)
    {
      drawChar(x+x0, y0, str[i], b);
      drawChar(x+x0+LED_MATRIX_FONTWIDTH+CHAR_SPACING_OFFSET, y0, str[i+1], b);
      delay(stepInMillis);
      clear();
    }
  }
}

/** ===========================================================
 * \fn      rotateContentCW
 * \brief   rotates the content by 90° clockwise
 *          (content have to be symmetrical!)
 *          (f(x, y) = (max-y, x))
 *
 * \param   -
 * \return  -
 ============================================================== */
void LEDMatrix::rotateContentCW()
{
  uint8_t pixelA, pixelB, currentX, currentY, newX, newY;
  const uint8_t maxXY = (x_ - 1);

  uint8_t y;
  for (y = 0 ; y < x_ / 2; y++)  // 0... 10
  {
    uint8_t x;
    for (x = 0 ; x < y_ / 2; x++)  // 0... 10
    { 
      pixelA = getPixel(x, y);

      currentX = maxXY - y;
      currentY = x;

      pixelB = getPixel(currentX, currentY);  // x,y = 10,0; 10,1; ...
      setPixel(currentX, currentY, pixelA);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getPixel(currentX, currentY);   // 10,10; 9,10; ...
      setPixel(currentX, currentY, pixelB);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelB = getPixel(currentX, currentY);  // 0,10; 0,9; ...
      setPixel(currentX, currentY, pixelA);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getPixel(currentX, currentY);  // 0,0; 1,0; ...
      setPixel(currentX, currentY, pixelB);
    }  
  }
}

/** ===========================================================
 * \fn      rotateContentACW
 * \brief   rotates the content by 90° against clockwise
 *          (content have to be symmetrical!)
 *          (f(x, y) = (y, max-x))
 *
 * \param   -
 * \return  -
 ============================================================== */
void LEDMatrix::rotateContentACW()
{
  uint8_t pixelA, pixelB, currentX, currentY, newX, newY;
  const uint8_t maxXY = (x_ - 1);

  uint8_t y;
  for (y = 0 ; y < x_ / 2; y++)  // 0... 10
  {
    uint8_t x;
    for (x = 0 ; x < y_ / 2; x++)  // 0... 10
    { 
      pixelA = getPixel(x, y);

      currentX = y;
      currentY = maxXY - x;

      pixelB = getPixel(currentX, currentY);  // x,y = 10,0; 10,1; ...
      setPixel(currentX, currentY, pixelA);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getPixel(currentX, currentY);   // 10,10; 9,10; ...
      setPixel(currentX, currentY, pixelB);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelB = getPixel(currentX, currentY);  // 0,10; 0,9; ...
      setPixel(currentX, currentY, pixelA);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getPixel(currentX, currentY);  // 0,0; 1,0; ...
      setPixel(currentX, currentY, pixelB);
    }  
  }
}

/* Private ---------------------------------------------------- */
//...

/**
 * @}
 */
