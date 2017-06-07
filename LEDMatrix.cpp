/*******************************************************************************
* \file    fileName.cpp
********************************************************************************
* \author  Jascha Haldemann jh@oxon.ch
* \date    01.02.2017
* \version 1.0
*******************************************************************************/

 /* ================================= Imports ================================ */
#include "LEDMatrix.h"

/* ======================= Module constant declaration ====================== */

/* ======================== Module macro declaration ======================== */

/* ====================== Module class instantiations ======================= */

/* ======================== Public member Functions ========================= */
/** -------------------------------------------------------------------------
  * \fn     movePixel
  * \brief  moves given Pixel to anoter given position
  *
  * \param  x0  x of target pixel
  * \param  y0  y of target pixel
  * \param  x1  x of the new position
  * \param  y1  y of the new position
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::movePixel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
  {
    uint8_t led = getPixel(x0, y0);
    clearPixel(x0, y0);
    setPixel(x1, y1, led);
  }

/** -------------------------------------------------------------------------
  * \fn     animatePixel
  * \brief  moves a Pixel step by step to a new position
  *         (uses the Bresenham's line-drawing algorithm)
  *
  * \param  x0        x of target pixel
  * \param  y0        y of target pixel
  * \param  x1        x of the new position
  * \param  y1        y of the new position
  * \param  stepSpeed step speed in millis
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::animatePixel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t stepSpeed)
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
    delay(stepSpeed);
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
        delay(stepSpeed);
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
        delay(stepSpeed);
        clearPixel(px, py);
      }
    }
    setPixel(px, py, b);
  }

/** -------------------------------------------------------------------------
  * \fn     drawHLine
  * \brief  draws a horizontal line with given lenght and brightness
  *
  * \param  x   start coordinate of the line
  * \param  y   start coordinate of the line
  * \param  l   length of the line
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::drawHLine(uint8_t x, uint8_t y, uint8_t l, uint8_t b)
  {
    drawLine(x, y, x + l - 1, y, b);
  }

/** -------------------------------------------------------------------------
  * \fn     drawVLine
  * \brief  draws a vertical line with given height and brightness
  *
  * \param  x   start coordinate of the line
  * \param  y   start coordinate of the line
  * \param  h   height of the line
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::drawVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t b)
  {
    drawLine(x, y, x, y + h - 1, b);
  }

/** -------------------------------------------------------------------------
  * \fn     drawRectangle
  * \brief  draws a rectangle on given coordinate and brightness
  *
  * \requ   drawHLine(), drawVLine()
  *
  * \param  x   top left coordinate of the rectangle
  * \param  y   top left coordinate of the rectangle
  * \param  l   length of the rectangle
  * \param  h   height of the rectangle
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::drawRectangle(uint8_t x, uint8_t y, uint8_t l, uint8_t h, uint8_t b)
  {
    drawHLine(x, y, l, b);
    drawVLine(x, y, h, b);
    drawHLine(x, y + h - 1, l, b);
    drawVLine(x + l - 1, y, h, b);
  }

/** -------------------------------------------------------------------------
  * \fn     drawFilledRectangle
  * \brief  draws a filled rectangle on given coordinate and brightness
  *
  * \requ   drawHLine()
  *
  * \param  x   top left coordinate of the rectangle
  * \param  y   top left coordinate of the rectangle
  * \param  l   length of the rectangle
  * \param  h   height of the rectangle
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::drawFilledRectangle(uint8_t x, uint8_t y, uint8_t l, uint8_t h, uint8_t b)
  {
    for (uint8_t i = y; i < y + h; i++)
    {
      drawHLine(x, i, l, b);
    }
  }

/** -------------------------------------------------------------------------
  * \fn     drawCircle
  * \brief  draws a circle on given coordinate with given radius and brightness
  *
  * \requ   setPixel()
  *
  * \param  x   origo of the circle
  * \param  y   origo of the circle
  * \param  r   radius of the circle
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     drawFilledCircle
  * \brief  draws a filled circle on given coordinate with given radius and
  *         brightness
  *
  * \requ   drawHLine(), drawLine()
  *
  * \param  x   origo of the circle
  * \param  y   origo of the circle
  * \param  r   radius of the circle
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     drawTriangle
  * \brief  draws a triangle on given coordinates and brightness
  *
  * \requ   drawLine()
  *
  * \param  x0  coordinate of the triangle corner
  * \param  y0  coordinate of the triangle corner
  * \param  x1  coordinate of the triangle corner
  * \param  y1  coordinate of the triangle corner
  * \param  x2  coordinate of the triangle corner
  * \param  y2  coordinate of the triangle corner
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::drawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t b)
  {
    drawLine(x0, y0, x1, y1, b);
    drawLine(x0, y0, x2, y2, b);
    drawLine(x1, y1, x2, y2, b);
  }

/** -------------------------------------------------------------------------
  * \fn     drawFilledTriangle
  * \brief  draws a filled triangle on given coordinates and brightness
  *         (uses the Bresenham's line-drawing algorithm)
  *
  * \requ   drawLine()
  *
  * \param  x0  coordinate of the triangle corner
  * \param  y0  coordinate of the triangle corner
  * \param  x1  coordinate of the triangle corner
  * \param  y1  coordinate of the triangle corner
  * \param  x2  coordinate of the triangle corner
  * \param  y2  coordinate of the triangle corner
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     drawPicture
  * \brief  draws a given picture
  *
  * \requ   <avr/pgmspace.h>, buffer[][], ...
  *
  * \param  x0      top left coordinate of the picture
  * \param  y0      top left coordinate of the picture
  * \param  l       length of the picture
  * \param  h       height of the picture
  * \param  image   constant byte pointer to the picture
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     drawChar
  * \brief  draws a character on given position and brightness
  *
  * \requ   <avr/pgmspace.h>, setPixel()
  *
  * \param  x   top left coordinate of the character
  * \param  y   top left coordinate of the character
  * \param  c   ASCII character
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     drawString
  * \brief  draws a string on given position and brightness
  *
  * \requ   drawChar()
  *
  * \param  x     top left coordinate of the first character
  * \param  y     top left coordinate of the first character
  * \param  str   const string (ASCII char array)
  * \param  b     brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     runningText
  * \brief  draws a string on given position and moves it to the left
  *
  * \requ   drawChar()
  *
  * \param  x0          top left coordinate of the first character
  * \param  y0          top left coordinate of the first character
  * \param  str         const string (ASCII char array)
  * \param  b           brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \param  stepSpeed   step speed in millis
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::runningText(uint8_t x0, uint8_t y0, const char* str, uint8_t b, uint16_t stepSpeed)
  {
    for (uint8_t i = 0; str[i+1] != '\0'; i++)
    {
      for (int16_t x = 0; x > -(LED_MATRIX_FONTWIDTH+CHAR_SPACING_OFFSET); x--)
      {
        drawChar(x+x0, y0, str[i], b);
        drawChar(x+x0+LED_MATRIX_FONTWIDTH+CHAR_SPACING_OFFSET, y0, str[i+1], b);
        delay(stepSpeed);
        clear();
      }
    }
  }

/** -------------------------------------------------------------------------
  * \fn     rotateContentCW
  * \brief  rotates the matrix content by 90° clockwise
  *         (content have to be symmetrically!)
  *         (f(x, y) = (max-y, x))
  --------------------------------------------------------------------------- */
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

/** -------------------------------------------------------------------------
  * \fn     rotateContentCW
  * \brief  rotates the matrix content by 90° against clockwise
  *         (content have to be symmetrically!)
  *         (f(x, y) = (y, max-x))
  --------------------------------------------------------------------------- */
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

/* ======================= Public virtual Functions ========================= */
/** -------------------------------------------------------------------------
  * \fn     fillScreen
  * \brief  fills the screen with the given brightness
  *
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
  void LEDMatrix::fillScreen(uint8_t b)
  {
    uint8_t y;
    for (y = 0 ; y < y_; y++)
    {
      uint8_t x;
      for (x = 0 ; x < x_; x++)
      {
        drawPixel(x, y, b);
      }
    }
  }

/** -------------------------------------------------------------------------
  * \fn     clear
  * \brief  clears the screen
  --------------------------------------------------------------------------- */
  void LEDMatrix::clear()
  {
    fillScreen(0);
  }

/** -------------------------------------------------------------------------
  * \fn     drawLine
  * \brief  draws a line on given coordinates and brightness
  *         (uses the Bresenham's line-drawing algorithm)
  *
  * \param  x0  start coordinate of the line
  * \param  y0  start coordinate of the line
  * \param  x1  end coordinate of the line
  * \param  y1  end coordinate of the line
  * \param  b   brightness value (0... MAX_BRIGHTNESS_VALUE)
  * \return None
  --------------------------------------------------------------------------- */
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
