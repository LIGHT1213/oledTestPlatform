#ifndef _SSD1306_H
#define _SSD1306_H

#include "stm32g0xx_hal.h"
#include "oledfont.h"
#define OLED_MODE 0 //spi mode
#if OLED_MODE == 1
// I2c address
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR        0x78
#endif // SSD1306_I2C_ADDR
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif // SSD1306_WIDTH

// SSD1306 LCD height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif // SSD1306_HEIGHT

#ifndef SSD1306_COM_LR_REMAP
#define SSD1306_COM_LR_REMAP    0
#endif // SSD1306_COM_LR_REMAP

#ifndef SSD1306_COM_ALTERNATIVE_PIN_CONFIG
#define SSD1306_COM_ALTERNATIVE_PIN_CONFIG    1
#endif // SSD1306_COM_ALTERNATIVE_PIN_CONFIG


//
//  Enumeration for screen colors
//
typedef enum {
    Black = 0x00,   // Black color, no pixel
    White = 0x01,   // Pixel is set. Color depends on LCD
} SSD1306_COLOR;

//
//  Struct to store transformations
//
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1306_t;

//
//  Function definitions
//

uint8_t ssd1306_Init(SPI_HandleTypeDef *hspi);
void ssd1306_UpdateScreen(SPI_HandleTypeDef *hspi);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(const char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_InvertColors(void);

#endif  // _SSD1306_H