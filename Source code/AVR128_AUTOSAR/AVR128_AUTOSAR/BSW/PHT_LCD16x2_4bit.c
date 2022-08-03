/*
 * PHT_LCD16x2_4bit.c
 *
 * Created: 26/05/2020 5:26:41 AM
 *  Author: HCMUS-VL-VLKT
 */  
#include <avr/io.h>
#include "PHT_LCD16x2_4bit.h"
#include <util/delay.h>

static void lcd_enable( void )
{
	LCD_PORT |= (1<<LCD_EN);
	_delay_us( LCD_ENABLE_US );
	LCD_PORT &= ~(1<<LCD_EN);
}

static void lcd_out( uint8 data )
{
	data &= 0xF0;
	
	LCD_PORT &= ~(0xF0>>(4-LCD_DB));
	LCD_PORT |= (data>>(4-LCD_DB));
	lcd_enable();
}

void lcd_init( void )
{
	
	uint8 pins = (0x0F << LCD_DB) | (1<<LCD_RS) | (1<<LCD_EN);
	
	LCD_DDR |= pins;
	LCD_DDR |= LCD_RW;
	
	LCD_PORT &= ~(LCD_RW);
	LCD_PORT &= ~pins;
	
	_delay_ms( LCD_BOOTUP_MS );
	
	lcd_out( LCD_SOFT_RESET );
	_delay_ms( LCD_SOFT_RESET_MS1 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS2 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS3 );
	
	lcd_out( LCD_SET_FUNCTION |
	LCD_FUNCTION_4BIT );
	_delay_ms( LCD_SET_4BITMODE_MS );
	
	lcd_command( LCD_SET_FUNCTION |
	LCD_FUNCTION_4BIT |
	LCD_FUNCTION_2LINE |
	LCD_FUNCTION_5X7 );
	
	lcd_command( LCD_SET_DISPLAY |
	LCD_DISPLAY_ON |
	LCD_CURSOR_OFF |
	LCD_BLINKING_OFF);
	
	lcd_command( LCD_SET_ENTRY |
	LCD_ENTRY_INCREASE |
	LCD_ENTRY_NOSHIFT );
	
	lcd_clear();
}

void lcd_data( uint8 data )
{
	LCD_PORT |= (1<<LCD_RS);
	
	lcd_out( data );
	lcd_out( data<<4 );
	
	_delay_us( LCD_WRITEDATA_US );
}

void lcd_command( uint8 data )
{
	LCD_PORT &= ~(1<<LCD_RS);
	
	lcd_out( data );
	lcd_out( data<<4 );
	
	_delay_us( LCD_COMMAND_US );
}

void lcd_clear( void )
{
	lcd_command( LCD_CLEAR_DISPLAY );
	_delay_ms( LCD_CLEAR_DISPLAY_MS );
}

void lcd_home( void )
{
	lcd_command( LCD_CURSOR_HOME );
	_delay_ms( LCD_CURSOR_HOME_MS );
}

void lcd_setcursor( uint8 x, uint8 y )
{
	uint8 data;
	
	switch (y)
	{
		case 1:
		data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
		break;
		
		case 2:
		data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
		break;
		
		case 3:
		data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
		break;
		
		case 4:
		data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
		break;
		
		default:
		return;
	}
	
	lcd_command( data );
}

void lcd_string( const char *data )
{
	while( *data != '\0' )
	lcd_data( *data++ );
}

void lcd_generatechar( uint8 startadresse, const uint8 *data )
{
	lcd_command( LCD_SET_CGADR | (startadresse<<3) );
	
	for ( uint8 i=0; i<8; i++ )
	{
		lcd_data( data[i] );
	}
	lcd_command(LCD_SET_DDADR);
}