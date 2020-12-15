#ifndef ST7789V_H_
#define ST7789V_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>

#define _LCD_DDR	DDRA
#define _LCD_PORT	PORTA

#define _LCD_RST	1
#define _LCD_DC		2
#define _LCD_CS		3

#define LCD_RST_HIGH	_LCD_PORT |= (1 << _LCD_RST)
#define LCD_RST_LOW		_LCD_PORT &= ~(1 << _LCD_RST)
#define LCD_DC_HIGH		_LCD_PORT |= (1 << _LCD_DC)
#define LCD_DC_LOW		_LCD_PORT &= ~(1 << _LCD_DC)
#define LCD_CS_HIGH		_LCD_PORT |= (1 << _LCD_CS)
#define LCD_CS_LOW		_LCD_PORT &= ~(1 << _LCD_CS)

#define LCD_1IN14_WIDTH		240
#define LCD_1IN14_HEIGHT	135

#define LCD_HORIZONTAL	0
#define LCD_VERTICAL	1

#define LCD_WHITE	0xFFFF
#define LCD_BLACK	0x0000
#define LCD_RED		0xF800
#define LCD_GREEN	0x07E0
#define LCD_BLUE	0x001F

typedef struct{
	uint16_t width;
	uint16_t height;
	uint16_t scan_direction;			
}LCD_Attribute; 

typedef struct{
	uint16_t x;
	uint16_t y;
}LCD_Point;

typedef struct{
	LCD_Point start_point;
	LCD_Point end_point;	
}LCD_Area;

extern LCD_Attribute lcd_attribute;

void _st7789v_reset(void);
void _st7789v_send_cmd(uint8_t register_val);
void _st7789v_send_data_8bit(uint8_t data);
void _st7789v_send_data_16bit(uint16_t data);
void _st7789v_set_attribute(uint8_t scan_direction);
void _st7789v_init_register(void);
void _st7789v_set_windows(LCD_Area area);

void st7789v_glcd_init(uint8_t scan_direction);
void st7789v_glcd_clear(uint16_t color);

void st7789v_glcd_draw_point(LCD_Point coordinate, uint16_t color);
void st7789v_glcd_set_area(LCD_Area draw_area, uint16_t color);

void st7789v_glcd_draw_rectangle(LCD_Area draw_area, uint16_t color, uint8_t thick);
//void st7789v_glcd_draw_image(uint16_t *image);
//void st7789v_glcd_draw_image_windows(LCD_Area draw_area, uint16_t *image);

void st7789v_glcd_draw_font_16x21(LCD_Point coordinate, uint16_t fg_color, uint16_t bg_color, uint8_t ascii);
void st7789v_glcd_draw_string_16x21(LCD_Point coordinate, uint16_t fg_color, uint16_t bg_color, uint8_t *ascii_string);
uint16_t st7789v_glcd_color(uint8_t red, uint8_t green, uint8_t blue);

#endif /* ST7789V_H_ */