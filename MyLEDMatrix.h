/**-----------------------------------------------------------------------------
 * \file    led_matrix.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MY_LED_MATRIX_H_
#define MY_LED_MATRIX_H_

/* global imports ------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <Arduino.h>

/* exported typedef ----------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/
#define NUMBER_OF_ROWS                     8
#define NUMBER_OF_COLUMNS                  8

#define MAX_BRIGHTNESS_VALUE             255     // 0... 255

/* font */
#define FONTSIZE                           5     // in pixels
#define FONTWIDTH                          3     // in pixels
#define CHAR_SPACING_OFFSET                1     // in pixels
#define DEFAULT_Y                          2
#define NUMBER_OF_DIFFERENT_CHARACTERS    97
#define ASCII_FIRST_CHARACTER_OFFSET      32

/* exported types ------------------------------------------------------------*/

/* exported macro ------------------------------------------------------------*/
/* pin and port on base of given pin_nr and port_nr */
#ifndef clearBit
#define clearBit(reg, bit) (_SFR_BYTE(reg) &= ~_BV(bit))
#endif
#ifndef setBit
#define setBit(reg, bit) (_SFR_BYTE(reg) |= _BV(bit))
#endif
#ifndef toggleBit
#define toggleBit(reg, bit) (_SFR_BYTE(reg) ^= _BV(bit))
#endif
#ifndef getBit
#define getBit(reg, bit) ((_SFR_BYTE(reg) & _BV(bit)) != 0)
#endif

/* exported variables --------------------------------------------------------*/
extern byte buffer[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
// buffer[y][x]
// x -> COL0...7
// y -> ROW0...7

/* exported functions --------------------------------------------------------*/
extern void setLED(byte, byte, byte);
extern void clearLED(byte, byte);
extern byte getLED(byte, byte);
extern void moveLED(byte, byte, byte, byte);
extern void animateLED(byte, byte, byte, byte, unsigned int);

extern void fillBuffer();
extern void clearBuffer();
extern void fillBufferArea(byte, byte, byte, byte, byte);
extern void clearBufferArea(byte, byte, byte, byte);
extern void fillRow(byte, byte);
extern void clearRow(byte);
extern void fillColumn(byte, byte);
extern void clearColumn(byte);

extern void drawLine(byte, byte, byte, byte, byte);
extern void drawHLine(byte, byte, byte, byte);
extern void drawVLine(byte, byte, byte, byte);
extern void drawRectangle(byte, byte, byte, byte, byte);
extern void drawFilledRectangle(byte, byte, byte, byte, byte);
extern void drawCircle(byte, byte, byte, byte);
extern void drawFilledCircle(byte, byte, byte, byte);
extern void drawTriangle(byte, byte, byte, byte, byte, byte, byte);
extern void drawFilledTriangle(byte, byte, byte, byte, byte, byte, byte);
extern void drawPicture(byte, byte, byte, byte, const byte[][NUMBER_OF_COLUMNS]);

extern void setChar(byte, byte, char, byte);
extern void drawString(byte, byte, const char*, byte);
extern void runningText(const char*, byte, unsigned int);

extern void rotateBufferContentCW();
extern void rotateBufferContentACW();

/* exported constants --------------------------------------------------------*/
/* Pictures -----------------------------------------------------*/
/* happy smile */
PROGMEM const byte picture0[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 0
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 1
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 2
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 3
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 4
  {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00},  // row 5
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 6
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}   // row 7
};

/* sad smile */
PROGMEM const byte picture1[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 0
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 1
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 2
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 3
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 4
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 5
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 6
  {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00}   // row 7
};

/* tick mark */
PROGMEM const byte picture2[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 0
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 1
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},  // row 2
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF},  // row 3
  {0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF},  // row 4
  {0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF},  // row 5
  {0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 6
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}   // row 7
};

/* cross */
PROGMEM const byte picture3[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 0
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 1
  {0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF},  // row 2
  {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF},  // row 3
  {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF},  // row 4
  {0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF},  // row 5
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 6
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}   // row 7
};

/* ! */
PROGMEM const byte picture4[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 0
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 1
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 2
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 3
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 4
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 5
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 6
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}   // row 7
};

/* ? */
PROGMEM const byte picture5[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 0
  {0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00},  // row 1
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00},  // row 2
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 3
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 4
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 5
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 6
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}   // row 7
};

/* heart */
PROGMEM const byte picture6[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
    // row 0
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 0
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 1
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 2
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 3
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},  // row 4
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 5
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 6
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00}   // row 7
};

/* star */
PROGMEM const byte picture7[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00},  // row 0
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 1
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 2
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},  // row 3
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 4
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 5
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},  // row 6
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF}   // row 7
};

/* sun */
PROGMEM const byte picture8[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF},  // row 0
  {0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},  // row 1
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 2
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 3
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 4
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},  // row 5
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00},  // row 6
  {0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF}   // row 7
};

/* couvert */
PROGMEM const byte picture9[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // row 0
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 1
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},  // row 2
  {0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF},  // row 3
  {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF},  // row 4
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 5
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 6
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}   // row 7
};

/* couvert */
PROGMEM const byte picture10[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{ /*columns:
      0     1     2     3     4     5     6     7 */
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},  // row 0
  {0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00},  // row 1
  {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00},  // row 2
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // row 3
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 4
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 5
  {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},  // row 6
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}   // row 7
};

/* Simple Font --------------------------------------------------*/
PROGMEM const byte characters[NUMBER_OF_DIFFERENT_CHARACTERS][FONTSIZE][FONTWIDTH] =
{
  {  // ' '
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '!'
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 0},
    {0, 1, 0}
  },
  {  // '"'
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '#'
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1}
  },
  {  // '$'
    {1, 1, 1},
    {1, 1, 0},
    {1, 1, 1},
    {0, 1, 1},
    {1, 1, 1}
  },
  {  // '%'
    {1, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {0, 0, 1}
  },
  {  // '&'
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 1}
  },
  {  // '''
    {0, 1, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '('
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 1}
  },
  {  // ')'
    {1, 0, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 0, 0}
  },
  {  // '*'
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 1},
    {0, 0, 0}
  },
  {  // '+'
    {0, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0},
    {0, 0, 0}
  },
  {  // ','
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0}
  },
  {  // '-'
    {0, 0, 0},
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '.'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {1, 0, 0}
  },
  {  // '/'
    {0, 0, 1},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {1, 0, 0}
  },
  {  // '0'
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  {  // '1'
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  {  // '2'
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // '3'
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  {  // '4'
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  {  // '5'
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  {  // '6'
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  {  // '7'
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  {  // '1'
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  {  // '9'
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  {  // ':'
    {0, 0, 0},
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0},
    {0, 1, 0}
  },
  {  // ';'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0}
  },
  {  // '<'
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  },
  {  // '='
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 0}
  },
  {  // '>'
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0}
  },
  {  // '?'
    {1, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 0},
    {0, 1, 0}
  },
  {  // '@'
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // 'A'
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1}
  },
  {  // 'B'
    {1, 1, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 0, 1},
    {1, 1, 0}
  },
  {  // 'C'
    {1, 1, 1},
    {1, 0, 0},
    {1, 0, 0},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // 'D'
    {1, 1, 0},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 0}
  },
  {  // 'E'
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // 'F'
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 0},
    {1, 0, 0},
    {1, 0, 0}
  },
  {  // 'G'
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 0}
  },
  {  // 'H'
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1}
  },
  {  // 'I'
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  },
  {  // 'J'
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 0}
  },
  {  // 'K'
    {1, 0, 1},
    {1, 1, 0},
    {1, 0, 0},
    {1, 1, 0},
    {1, 0, 1}
  },
  {  // 'L'
    {1, 0, 0},
    {1, 0, 0},
    {1, 0, 0},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // 'M'
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1}
  },
  {  // 'N'
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1}
  },
  {  // 'O'
    {0, 1, 0},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 0}
  },
  {  // 'P'
    {1, 1, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 0, 0},
    {1, 0, 0}
  },
  {  // 'Q'
    {0, 1, 0},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 1}
  },
  {  // 'R'
    {1, 1, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 0},
    {1, 0, 1}
  },
  {  // 'S'
    {0, 1, 1},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 0}
  },
  {  // 'T'
    {1, 1, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  },
  {  // 'U'
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  {  // 'V'
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 0}
  },
  {  // 'W'
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1}
  },
  {  // 'X'
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 1},
    {1, 0, 1}
  },
  {  // 'Y'
    {1, 0, 1},
    {1, 0, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  },
  {  // 'Z'
    {1, 1, 1},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1}
  },
  {  // '['
    {0, 1, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 1}
  },
  {  // '\'
    {1, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {0, 0, 1}
  },
  {  // ']'
    {1, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 1, 0}
  },
  {  // '^'
    {0, 1, 0},
    {1, 0, 1},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '_'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {1, 1, 1}
  },
  {  // '`'
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  //TODO...
  {  // 'a'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'b'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'c'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'd'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'e'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'f'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'g'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'h'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'i'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'j'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'k'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'l'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'm'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'n'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'o'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'p'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'q'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'r'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 's'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 't'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'u'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'v'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'w'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'x'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'y'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // 'z'
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {  // '{'
    {0, 0, 1},
    {0, 1, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 0, 1}
  },
  {  // '|'
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  },
  {  // '}'
    {1, 0, 0},
    {0, 1, 0},
    {0, 1, 1},
    {0, 1, 0},
    {1, 0, 0}
  },
  {  // '~'
    {0, 0, 0},
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 0},
    {0, 0, 0}
  }
};

#endif /* MY_LED_MATRIX_H_ */

/**
 * @}
 */
