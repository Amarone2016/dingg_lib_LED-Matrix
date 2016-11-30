/**-----------------------------------------------------------------------------
 * \file    led_matrix.c
 * \author  jh
 * \date    xx.05.2016
 *
 * \version 1.0
 *  create this file
 *
 * \brief   functions to control a LED-Matrix
 *
 * @{
 -----------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "MYLEDMatrix.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
byte buffer[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {0};

/* Private function prototypes -----------------------------------------------*/
static void swap(byte*, byte*);
static int sgn(int);

/** ===========================================================
 * \fn      setLED
 * \brief   sets the buffer content of a LED
 *
 * \param   (byte) column number of the LED -> x
 *          (byte) row number of the LED    -> y
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void setLED(byte x, byte y, byte brightness)
{
  buffer[y][x] = brightness;
}

/** ===========================================================
 * \fn      clearLED
 * \brief   clears the buffer content of a LED
 *
 * \param   (byte) column number of the LED -> x
 *          (byte) row number of the LED    -> y
 * \return  -
 ============================================================== */
void clearLED(byte x, byte y)
{
  buffer[y][x] = 0;
}

/** ===========================================================
 * \fn      getLED
 * \brief   gets the buffer content of a LED
 *
 * \param   (byte) column number of the LED -> x
 *          (byte) row number of the LED    -> y
 * \return  (byte) brightness value
 ============================================================== */
byte getLED(byte x, byte y)
{
  return buffer[y][x];
}


/** ===========================================================
 * \fn      moveLED
 * \brief   moves the buffer content of a LED to anoter
 *          position
 *
 * \param   (byte) x0, y0 target LED
 *          (byte) x1, y1 new positon
 * \return  -
 ============================================================== */
void moveLED(byte x0, byte y0, byte x1, byte y1)
{
  byte led = getLED(x0, y0);
  clearLED(x0, y0);
  setLED(x1, y1, led);
}

/** ===========================================================
 * \fn      animateLED
 * \brief   moves a LED step by step to a new position
 *          (uses the Bresenham's line-drawing algorithm)
 *
 * \param   (byte) x0, y0 target LED
 *          (byte) x1, y1 end position
 *          (uint) step speed in ms
 * \return  -
 ============================================================== */
void animateLED(byte x0, byte y0, byte x1, byte y1, unsigned int step)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int dx_abs = abs(dx);
  int dy_abs = abs(dy);
  int s_dx = sgn(dx);
  int s_dy = sgn(dy);
  int x = dy_abs >> 1;
  int y = dx_abs >> 1;
  int px = x0;
  int py = y0;

  byte b = getLED(x0, y0);
  delay(step);
  clearLED(x0, y0);

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      setLED(px, py, b);
      delay(step);
      clearLED(px, py);
    }
  }
  else // the line is more vertical than horizontal
  {
    int i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      setLED(px, py, b);
      delay(step);
      clearLED(px, py);
    }
  }
  setLED(px, py, b);
}

/** ===========================================================
 * \fn      fillBuffer
 * \brief   fills the whole buffer content
 *
 * \param   -
 * \return  -
 ============================================================== */
void fillBuffer()
{
  byte y;
  for (y = 0; y < NUMBER_OF_ROWS; y++)
  {
    byte x;
    for (x = 0; x < NUMBER_OF_COLUMNS; x++)
    {
      buffer[y][x] = MAX_BRIGHTNESS_VALUE;
    }
  }
}

/** ===========================================================
 * \fn      clearBuffer
 * \brief   clears the whole buffer content
 *
 * \param   -
 * \return  -
 ============================================================== */
void clearBuffer()
{
  byte y;
  for (y = 0; y < NUMBER_OF_ROWS; y++)
  {
    byte x;
    for (x = 0; x < NUMBER_OF_COLUMNS; x++)
    {
      buffer[y][x] = 0;
    }
  }
}

/** ===========================================================
 * \fn      fillBufferArea
 * \brief   fills the content of a specific area of the buffer
 *
 * \param   (byte) x0, y0, x1, y1
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void fillBufferArea(byte x0, byte y0, byte x1, byte y1, byte brightness)
{
  if (x0 > x1) swap(&x0, &x1);
  if (y0 > y1) swap(&y0, &y1);

  byte y;
  for (y = y0; y <= y1; y++)
  {
    byte x;
    for (x = x0; x <= x1; x++)
    {
      buffer[y][x] = brightness;
    }
  }
}

/** ===========================================================
 * \fn      clearBufferArea
 * \brief   clears the content of a specific area of the buffer
 *
 * \param   (byte) x0, y0, x1, y1
 * \return  -
 ============================================================== */
void clearBufferArea(byte x0, byte y0, byte x1, byte y1)
{
  if (x0 > x1) swap(&x0, &x1);
  if (y0 > y1) swap(&y0, &y1);

  byte y;
  for (y = y0; y <= y1; y++)
  {
    byte x;
    for (x = x0; x <= x1; x++)
    {
      buffer[y][x] = 0;
    }
  }
}

/** ===========================================================
 * \fn      fillRow
 * \brief   fills a row of the buffer content
 *
 * \param   (byte) row number (0... NUMBER_OF_ROWS - 1)
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void fillRow(byte row, byte brightness)
{
  byte x;
  for (x = 0; x < NUMBER_OF_COLUMNS; x++)
  {
    buffer[row][x] = brightness;
  }
}

/** ===========================================================
 * \fn      clearRow
 * \brief   clears a row of the buffer content
 *
 * \param   (byte) row number (0... NUMBER_OF_ROWS - 1)
 * \return  -
 ============================================================== */
void clearRow(byte row)
{
  byte x;
  for (x = 0; x < NUMBER_OF_COLUMNS; x++)
  {
    buffer[row][x] = 0;
  }
}

/** ===========================================================
 * \fn      fillColumn
 * \brief   fills a column of the buffer content
 *
 * \param   (byte) column number (0... NUMBER_OF_COLUMNS - 1)
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void fillColumn(byte column, byte brightness)
{
  byte y;
  for (y = 0; y < NUMBER_OF_ROWS; y++)
  {
    buffer[y][column] = brightness;
  }
}

/** ===========================================================
 * \fn      clearColumn
 * \brief   clears a column of the buffer content
 *
 * \param   (byte) column number (0... NUMBER_OF_COLUMNS - 1)
 * \return  -
 ============================================================== */
void clearColumn(byte column)
{
  byte y;
  for (y = 0; y < NUMBER_OF_ROWS; y++)
  {
    buffer[y][column] = 0;
  }
}

/** ===========================================================
 * \fn      drawLine
 * \brief   writes a line on given coordinates and brightness
 *          into the buffer
 *          (uses the Bresenham's line-drawing algorithm)
 *
 * \param   (byte) x0, y0 start coordinate of the line
 *          (byte) x1, y1 end coordinate of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawLine(byte x0, byte y0, byte x1, byte y1, byte b)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int dx_abs = abs(dx);
  int dy_abs = abs(dy);
  int s_dx = sgn(dx);
  int s_dy = sgn(dy);
  int x = dy_abs >> 1;
  int y = dx_abs >> 1;
  int px = x0;
  int py = y0;

  setLED(x0, y0, b); // draw first pixel

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int i;
    for(i = 0; i < dx_abs; i++)
    {
      y += dy_abs;
      if (y >= dx_abs)
      {
        y -= dx_abs;
        py += s_dy;
      }
      px += s_dx;
      setLED(px, py, b);
    }
  }
  else // the line is more vertical than horizontal
  {
    int i;
    for(i = 0; i < dy_abs; i++)
    {
      x += dx_abs;
      if (x >= dy_abs)
      {
        x -= dy_abs;
        px += s_dx;
      }
      py += s_dy;
      setLED(px, py, b);
    }
  }
}

/** ===========================================================
 * \fn      drawHLine
 * \brief   writes a horizontal line on given coordinate and
 *          brightness into the buffer
 *
 * \requ    drawLine()
 *
 * \param   (byte) x, y start coordinate of the line
 *          (byte) length of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawHLine(byte x, byte y, byte l, byte b)
{
  drawLine(x, y, x + l - 1, y, b);
}

/** ===========================================================
 * \fn      drawVLine
 * \brief   writes a vertical line on given coordinate and
 *          brightness into the buffer
 *
 * \requ    drawLine()
 *
 * \param   (byte) x, y start coordinate of the line
 *          (byte) height of the line
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawVLine(byte x, byte y, byte h, byte b)
{
  drawLine(x, y, x, y + h - 1, b);
}

/** ===========================================================
 * \fn      drawRectangle
 * \brief   draws a rectangle on given coordinate and
 *          brightness
 *
 * \requ    setLED(), drawHLine(), drawVLine()
 *
 * \param   (byte) x, y top left coordinate of the rectangle
 *          (byte) length of the rectangle
 *          (byte) hight of the rectangle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawRectangle(byte x, byte y, byte l, byte h, byte b)
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
void drawFilledRectangle(byte x, byte y, byte l, byte h, byte b)
{
  byte i;
  for (i = y; i < y + h; i++)
  {
    drawHLine(x, i, l, b);
  }
}

/** ===========================================================
 * \fn      drawCircle
 * \brief   draws a circle on given coordinate with given
 *          radius and brightness
 *
 * \requ    setLED()
 *
 * \param   (byte) x0, y0 origo of the circle
 *          (byte) radius of the circle
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawCircle(byte x0, byte y0, byte r, byte b)
{
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  setLED(x0, y0+r, b);
  setLED(x0, y0-r, b);
  setLED(x0+r, y0, b);
  setLED(x0-r, y0, b);

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

    setLED(x0 + x, y0 + y, b);
    setLED(x0 - x, y0 + y, b);
    setLED(x0 + x, y0 - y, b);
    setLED(x0 - x, y0 - y, b);
    setLED(x0 + y, y0 + x, b);
    setLED(x0 - y, y0 + x, b);
    setLED(x0 + y, y0 - x, b);
    setLED(x0 - y, y0 - x, b);
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
void drawFilledCircle(byte x0, byte y0, byte r, byte b)
{
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

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
void drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b)
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
void drawFilledTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b)
{
  /* do the same as in the drawLine() function but draw lines to
   the static corner x2,y2 instaed of single pixels */
  int dx = x1 - x0;
  int dy = y1 - y0;
  int dx_abs = abs(dx);
  int dy_abs = abs(dy);
  int s_dx = sgn(dx);
  int s_dy = sgn(dy);
  int x = dy_abs >> 1;
  int y = dx_abs >> 1;
  int px = x0;
  int py = y0;

  if (dx_abs >= dy_abs) // the line is more horizontal than vertical
  {
    int i;
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
    int i;
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
    int i;
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
    int i;
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
 *          (byte[][]) constant pointer of the picture
 * \return  -
 ============================================================== */
void drawPicture(byte x0, byte y0, byte l, byte h, const byte pic[][NUMBER_OF_COLUMNS])
{
  if (x0 + l > NUMBER_OF_COLUMNS || y0 + h > NUMBER_OF_ROWS) return;

  byte y;
  for (y = y0; y < y0 + h; y++)
  {
    byte x;
    for (x = x0; x < x0 + l; x++) 
    {
      buffer[y][x] = pgm_read_byte(&(pic[y][x]));
    }
  }
}

/** ===========================================================
 * \fn      setChar
 * \brief   writes a single char into the buffer
 *
 * \requ    <avr/pgmspace.h>, setLED()
 *
 * \param   (byte) x, y top left coordinate of the character
 *          (char) ASCII character
 *          (byte) brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void setChar(byte x, byte y, char c, byte b)
{
  /* write char buffer content into the buffer */
  byte cy;
  for (cy = 0; cy < FONTSIZE; cy++)
  {
    byte cx;
    for (cx = 0; cx < FONTWIDTH; cx++)
    {
      if (pgm_read_byte(&(characters[c - ASCII_FIRST_CHARACTER_OFFSET][cy][cx])) > 0) setLED(x + cx, y + cy, b);
      else clearLED(x + cx, y + cy);
    }
  }
}

/** ===========================================================
 * \fn      drawString
 * \brief   draws a string on given position
 *
 * \requ    setChar()
 *
 * \param   (byte)  x, y top left coordinate of the string
 *          (char*) constant string (char array)
 *          (byte)  brightness value (0... MAX_BRIGHTNESS_VALUE)
 * \return  -
 ============================================================== */
void drawString(byte x, byte y, const char *str, byte b)
{  
  byte ofCnt = 0;  // overflow counter
  
  unsigned int i;
  for (i = 0; str[i] != '\0'; i++)
  {     
    byte currentX = x + i * (FONTWIDTH + CHAR_SPACING_OFFSET);

    /* check if end of row woulde be reached */
    if (currentX + FONTWIDTH > NUMBER_OF_ROWS)
    {
      /* limit owerflow counter */
      ofCnt %=  (NUMBER_OF_ROWS / (FONTWIDTH + CHAR_SPACING_OFFSET));
      if (ofCnt == 0) y += FONTSIZE;
      ofCnt++;

      currentX = ofCnt * (FONTWIDTH + CHAR_SPACING_OFFSET);
    }

    setChar(currentX, y, str[i], b);
  }
}

void runningText(const char* str, byte b, unsigned int step)
{
  byte i;
  for (i = 0; str[i+1] != '\0'; i++)
  {
    int x;
    for (x = 0; x > -(FONTWIDTH+CHAR_SPACING_OFFSET); x--)
    {
      setChar(x+1, DEFAULT_Y, str[i], b);
      setChar(x+FONTWIDTH+CHAR_SPACING_OFFSET+1, DEFAULT_Y, str[i+1], b);
      delay(step);
      clearBuffer();
    }
  }
}

/** ===========================================================
 * \fn      rotateBufferContentCW
 * \brief   rotates the buffer content by 90° clockwise
 *          (buffer content have to be symmetrical!)
 *          (f(x, y) = (max-y, x))
 *
 * \param   -
 * \return  -
 ============================================================== */
void rotateBufferContentCW()
{
  byte pixelA, pixelB, currentX, currentY, newX, newY;
  const byte maxXY = (NUMBER_OF_COLUMNS - 1);

  byte y;
  for (y = 0 ; y < NUMBER_OF_COLUMNS / 2; y++)  // 0... 10
  {
    byte x;
    for (x = 0 ; x < NUMBER_OF_ROWS / 2; x++)  // 0... 10
    { 
      pixelA = getLED(x, y);

      currentX = maxXY - y;
      currentY = x;

      pixelB = getLED(currentX, currentY);  // x,y = 10,0; 10,1; ...
      setLED(currentX, currentY, pixelA);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getLED(currentX, currentY);   // 10,10; 9,10; ...
      setLED(currentX, currentY, pixelB);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelB = getLED(currentX, currentY);  // 0,10; 0,9; ...
      setLED(currentX, currentY, pixelA);

      newX = maxXY - currentY;
      newY = currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getLED(currentX, currentY);  // 0,0; 1,0; ...
      setLED(currentX, currentY, pixelB);
    }  
  }
}

/** ===========================================================
 * \fn      rotateBufferContentACW
 * \brief   rotates the buffer content by 90° against clockwise
 *          (buffer content have to be symmetrical!)
 *          (f(x, y) = (y, max-x))
 *
 * \param   -
 * \return  -
 ============================================================== */
void rotateBufferContentACW()
{
  byte pixelA, pixelB, currentX, currentY, newX, newY;
  const byte maxXY = (NUMBER_OF_COLUMNS - 1);

  byte y;
  for (y = 0 ; y < NUMBER_OF_COLUMNS / 2; y++)  // 0... 10
  {
    byte x;
    for (x = 0 ; x < NUMBER_OF_ROWS / 2; x++)  // 0... 10
    { 
      pixelA = getLED(x, y);

      currentX = y;
      currentY = maxXY - x;

      pixelB = getLED(currentX, currentY);  // x,y = 10,0; 10,1; ...
      setLED(currentX, currentY, pixelA);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getLED(currentX, currentY);   // 10,10; 9,10; ...
      setLED(currentX, currentY, pixelB);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelB = getLED(currentX, currentY);  // 0,10; 0,9; ...
      setLED(currentX, currentY, pixelA);

      newX = currentY;
      newY = maxXY - currentX;
      currentX = newX;
      currentY = newY;

      pixelA = getLED(currentX, currentY);  // 0,0; 1,0; ...
      setLED(currentX, currentY, pixelB);
    }  
  }
}

/* private functions: */

/** ===========================================================
 * \fn      swap
 * \brief   swaps two values with each oters
 *
 * \param   (byte*) pointer on first value
 *          (byte*) pointer on second value
 * \return  -
 ============================================================== */
static void swap(byte *a, byte *b)
{
  byte temp = *a;
  *a = *b;
  *b = temp;
}

/** ===========================================================
 * \fn      sgn
 * \brief   signum function
 *
 * \param   (int) value
 * \return  (int) 1 if value > 0
 *                0 if value = 0
 *               -1 if value < 0
 ============================================================== */
static int sgn(int a)
{
  if (a > 0) return 1;
  if (a < 0) return -1;
  return 0;
}

/**
 * @}
 */
