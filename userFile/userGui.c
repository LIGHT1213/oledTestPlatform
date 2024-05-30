#include "userGui.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

u8g2_t u8g2;
extern osSemaphoreId pageBinarySemHandle;
;
u8g2_t *getUserScreen()
{
    return &u8g2;
}
void userGuiInit()
{
    osSemaphoreWait(pageBinarySemHandle, osWaitForever);
    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_gpio_and_delay_stm32);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    u8g2_DrawXBMP(&u8g2, 39, 2, 50, 50, icon[0]); // 50,50为图片尺寸，根据你的图片尺寸修改
    u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
    u8g2_DrawStr(&u8g2, 37, 64, (const char *)"50HZ PWN GEN");
}
void userGuiTask()
{
    u8g2_FirstPage(&u8g2); // 初始化多页绘制
    do
    {
        u8g2_DrawXBMP(&u8g2, 39, 2, 50, 50, icon[getCurPageNum()]); // 50,50为图片尺寸，根据你的图片尺寸修改
        // u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
        // u8g2_DrawStr(&u8g2, 37, 64, (const char *)"50HZ PWN GEN");
        osSemaphoreWait(pageBinarySemHandle, osWaitForever);
    } while (u8g2_NextPage(&u8g2));
}