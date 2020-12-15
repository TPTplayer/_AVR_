#include "ST7789V.h"
#include "mega128_SPI.h"
#include "glcd_font.h"

LCD_Attribute lcd_attribute;

void _st7789v_reset(void){
	LCD_RST_HIGH;
	_delay_ms(100);
	LCD_RST_LOW;
	_delay_ms(100);
	LCD_RST_HIGH;
	_delay_ms(150);	
	return;
}

void _st7789v_send_cmd(uint8_t register_val){
	LCD_DC_LOW;
	LCD_CS_LOW;
	SPI_master_com(register_val);	
	return;
}

void _st7789v_send_data_8bit(uint8_t data){
	LCD_DC_HIGH;
	LCD_CS_LOW;
	SPI_master_com(data);
	LCD_CS_HIGH;
	return;	
}

void _st7789v_send_data_16bit(uint16_t data){
	LCD_DC_HIGH;
	LCD_CS_LOW;
	SPI_master_com((data >> 8) & 0xFF);
	SPI_master_com(data & 0xFF);
	LCD_CS_HIGH;
	return;	
}

void _st7789v_set_attribute(uint8_t scan_direction){
	uint8_t memory_access_register;
	
	lcd_attribute.scan_direction = scan_direction;
	memory_access_register = 0x00;
	
	if(scan_direction == LCD_HORIZONTAL){
		lcd_attribute.height = LCD_1IN14_WIDTH;
		lcd_attribute.width = LCD_1IN14_HEIGHT;
		memory_access_register = 0x70;
	}
	else{
		lcd_attribute.height = LCD_1IN14_HEIGHT;
		lcd_attribute.width = LCD_1IN14_WIDTH;
		memory_access_register = 0x00;
	}
	
	_st7789v_send_cmd(0x36);
	_st7789v_send_data_8bit(memory_access_register);
	return;	
}

void _st7789v_init_register(void){
	_st7789v_send_cmd(0x3A);
	_st7789v_send_data_8bit(0x05);
	
	_st7789v_send_cmd(0xB2);
	_st7789v_send_data_8bit(0x0C);
	_st7789v_send_data_8bit(0x0C);
	_st7789v_send_data_8bit(0x00);
	_st7789v_send_data_8bit(0x33);
	_st7789v_send_data_8bit(0x33);
	
	_st7789v_send_cmd(0xB7);
	_st7789v_send_data_8bit(0x35);
	
	_st7789v_send_cmd(0xBB);
	_st7789v_send_data_8bit(0x19);
	
	_st7789v_send_cmd(0xC0);
	_st7789v_send_data_8bit(0x2C);
	
	_st7789v_send_cmd(0xC2);
	_st7789v_send_data_8bit(0x01);
	_st7789v_send_cmd(0xC3);
	_st7789v_send_data_8bit(0x12);
	_st7789v_send_cmd(0xC4);
	_st7789v_send_data_8bit(0x20);
	
	_st7789v_send_cmd(0xC6);
	_st7789v_send_data_8bit(0x0F);
	
	_st7789v_send_cmd(0xD0);
	_st7789v_send_data_8bit(0xA4);
	_st7789v_send_data_8bit(0xA1);
	
	_st7789v_send_cmd(0xE0);
	_st7789v_send_data_8bit(0xD0);
	_st7789v_send_data_8bit(0x04);
	_st7789v_send_data_8bit(0x0D);
	_st7789v_send_data_8bit(0x11);
	_st7789v_send_data_8bit(0x13);
	_st7789v_send_data_8bit(0x2B);
	_st7789v_send_data_8bit(0x3F);
	_st7789v_send_data_8bit(0x54);
	_st7789v_send_data_8bit(0x4C);
	_st7789v_send_data_8bit(0x18);
	_st7789v_send_data_8bit(0x0D);
	_st7789v_send_data_8bit(0x0B);
	_st7789v_send_data_8bit(0x1F);
	_st7789v_send_data_8bit(0x23);
	
	_st7789v_send_cmd(0xE1);
	_st7789v_send_data_8bit(0xD0);
	_st7789v_send_data_8bit(0x04);
	_st7789v_send_data_8bit(0x0C);
	_st7789v_send_data_8bit(0x11);
	_st7789v_send_data_8bit(0x13);
	_st7789v_send_data_8bit(0x2C);
	_st7789v_send_data_8bit(0x3F);
	_st7789v_send_data_8bit(0x44);
	_st7789v_send_data_8bit(0x51);
	_st7789v_send_data_8bit(0x2F);
	_st7789v_send_data_8bit(0x1F);
	_st7789v_send_data_8bit(0x1F);
	_st7789v_send_data_8bit(0x20);
	_st7789v_send_data_8bit(0x23);
	
	_st7789v_send_cmd(0x21);
	_st7789v_send_cmd(0x11);
	_delay_ms(120);
	_st7789v_send_cmd(0x29);
	return;	
}

void _st7789v_set_windows(LCD_Area area){
	uint16_t x, y;
	
	if(lcd_attribute.scan_direction == LCD_HORIZONTAL){
		x = 40;
		y = 53;
	}
	else{
		x = 52;
		y = 40;
	}
	_st7789v_send_cmd(0x2A);
	
	_st7789v_send_data_16bit(area.start_point.x + x);
	_st7789v_send_data_16bit(area.end_point.x + x);
	_st7789v_send_data_16bit(area.start_point.y + y);
	_st7789v_send_data_16bit(area.end_point.y + y);
	_st7789v_send_cmd(0x2C);
	return;
}


void st7789v_glcd_init(uint8_t scan_direction){
	_st7789v_reset();
	_delay_ms(1000);
	
	_st7789v_set_attribute(scan_direction);
	_st7789v_init_register();	
	return;
}

void st7789v_glcd_clear(uint16_t color){
	uint16_t idx_x, idx_y;
	LCD_Area area;
	
	area.start_point.x = 0;
	area.start_point.y = 0;
	area.end_point.x = LCD_1IN14_WIDTH - 1;
	area.end_point.y = LCD_1IN14_HEIGHT - 1;
	_st7789v_set_windows(area);
	
	LCD_DC_HIGH;
	for(idx_x = 0; idx_x < LCD_1IN14_WIDTH; idx_x++){
		for(idx_y = 0; idx_y < LCD_1IN14_HEIGHT; idx_y++){
			SPI_master_com((color >> 8) & 0xFF);
			SPI_master_com(color);
		}
	}
	LCD_CS_HIGH;
	return;	
}

void st7789v_glcd_draw_point(LCD_Point coordinate, uint16_t color){
	LCD_Area area;
	area.start_point = coordinate;
	area.end_point = coordinate;
	_st7789v_set_windows(area);
	_st7789v_send_data_16bit(color);
	return;
}

void st7789v_glcd_set_area(LCD_Area draw_area, uint16_t color){
	uint16_t idx_x, idx_y;
	
	_st7789v_set_windows(draw_area);
	LCD_DC_HIGH;
	for(idx_y = draw_area.start_point.x; idx_y < draw_area.end_point.y; idx_y++){
		for(idx_x = draw_area.start_point.y; idx_x < draw_area.end_point.x; idx_x++){
			SPI_master_com((color >> 8) & 0xFF);
			SPI_master_com(color);		
		}
	}
	LCD_CS_HIGH;
	return;
}

void st7789v_glcd_draw_rectangle(LCD_Area draw_area, uint16_t color, uint8_t thick){
	uint16_t idx_x, idx_y;
	uint8_t idx_thick;
	LCD_Point coordinate;
	
	for(idx_thick = 0; idx_thick < thick; idx_thick++){
		for(idx_y = draw_area.start_point.y; idx_y < draw_area.end_point.y; idx_y++){
			if(idx_y == draw_area.start_point.y || idx_y == draw_area.end_point.y - 1){
				for(idx_x = draw_area.start_point.x; idx_x < draw_area.end_point.x; idx_x++){
					coordinate.x = idx_x;
					coordinate.y = idx_y;
					st7789v_glcd_draw_point(coordinate, color);
				}	
				continue;
			}
			
			coordinate.x = draw_area.start_point.x;
			coordinate.y = idx_y;
			st7789v_glcd_draw_point(coordinate, color);
			
			coordinate.x = draw_area.end_point.x - 1;
			coordinate.y = idx_y;
			st7789v_glcd_draw_point(coordinate, color);
		}
	}
	LCD_CS_HIGH;
	return;	
}

/*
void st7789v_glcd_draw_image(uint16_t *image){
	
}

void st7789v_glcd_draw_image_windows(LCD_Area draw_area, uint16_t *image){
	
}
*/

void st7789v_glcd_draw_font_16x21(LCD_Point coordinate, uint16_t fg_color, uint16_t bg_color, uint8_t ascii){
	uint8_t font_width = FONT_CONSOLAS_16X21_WIDTH, font_height = FONT_CONSOLAS_16X21_HEIGHT;
	uint8_t idx_x, idx_y, base = 32;
	uint16_t lines = 0x00, mask = 0x01;
	
	LCD_Point end_point = {coordinate.x + font_width - 1, coordinate.y + font_height - 1};
	LCD_Area draw_area = {coordinate, end_point};
	
	if(ascii < 32 || ascii > 127) return;
	_st7789v_set_windows(draw_area);
	LCD_DC_HIGH;
	
	for(idx_y = 0; idx_y < (font_height * 2); idx_y += 2){
		lines = font_consolas_16x21[((ascii - base) * (font_height * 2)) + idx_y];
		lines |= ((uint16_t) font_consolas_16x21[((ascii - base) * (font_height * 2)) + (idx_y + 1)]) << 8;
		
		for(idx_x = 0; idx_x < font_width; idx_x++){
			if((lines & (mask << idx_x)) != 0){
				SPI_master_com((fg_color >> 8) & 0xFF);
				SPI_master_com(fg_color);
			}
			else{
				SPI_master_com((bg_color >> 8) & 0xFF);
				SPI_master_com(bg_color);
			}
		}
	}
	
	LCD_CS_HIGH;
	return;	
}

void st7789v_glcd_draw_string_16x21(LCD_Point coordinate, uint16_t fg_color, uint16_t bg_color, uint8_t *ascii_string){
	uint16_t string_len, idx, coeff = FONT_CONSOLAS_16X21_WIDTH;
	LCD_Point char_coordinate;
	
	string_len = strlen((char*) ascii_string);
	for(idx = 0; idx < string_len; idx++){
		char_coordinate.x = coordinate.x + (idx * coeff);
		char_coordinate.y = coordinate.y;
		st7789v_glcd_draw_font_16x21(char_coordinate, fg_color, bg_color, ascii_string[idx]);
	}
	
	LCD_CS_HIGH;
	return;
}

uint16_t st7789v_glcd_color(uint8_t red, uint8_t green, uint8_t blue){
	uint16_t color;
	
	if(red > 0x1F) red = 0x1F;
	if(green > 0x3F) green = 0x3F;
	if(blue > 0x1F) blue = 0x3F;
	
	color = (red << 11) | (green << 5) | blue;
	return color;
}
