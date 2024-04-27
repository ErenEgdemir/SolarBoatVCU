/*********************************************************************************************************
 *
 *       File: display.h
 *    Purpose: E Paper Display UART Communication Handling
 * Created on: Feb 23, 2024
 *     Author: Eren Egdemir
 *       Team: TU YILDIZ SOLAR BOAT TEAM ELECTRONICS AND COMMUNICATIONS DEPARTMENT
 *   Resource: rewritten from WaveShare epd Library for stm32f4xx
 *
 *********************************************************************************************************/

#include "interface.h"
#include "display.h"
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include <freertos.h>




/*
command define
*/
static const unsigned char _cmd_handshake[8] = {0xA5, 0x00, 0x09, CMD_HANDSHAKE, 0xCC, 0x33, 0xC3, 0x3C};               //CMD_HANDSHAKE
static const unsigned char _cmd_read_baud[8] = {0xA5, 0x00, 0x09, CMD_READ_BAUD, 0xCC, 0x33, 0xC3, 0x3C};               //CMD_READ_BAUD
static const unsigned char _cmd_stopmode[8] = {0xA5, 0x00, 0x09, CMD_STOPMODE, 0xCC, 0x33, 0xC3, 0x3C};                 //CMD_STOPMODE
static const unsigned char _cmd_update[8] = {0xA5, 0x00, 0x09, CMD_UPDATE, 0xCC, 0x33, 0xC3, 0x3C};                     //CMD_UPDATE
static const unsigned char _cmd_load_font[8] = {0xA5, 0x00, 0x09, CMD_LOAD_FONT, 0xCC, 0x33, 0xC3, 0x3C};               //CMD_LOAD_FONT
static const unsigned char _cmd_load_pic[8] = {0xA5, 0x00, 0x09, CMD_LOAD_PIC, 0xCC, 0x33, 0xC3, 0x3C};                 //CMD_LOAD_PIC



static unsigned char _cmd_buff[CMD_SIZE];



/*
private function
*/

static unsigned char _verify(const void * ptr, int n);
void USART1_SendChar(char c);
//static void _putchars(const unsigned char * ptr, int n);


/*******************************************************************************
* Function Name  : static void _delay(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void _delay(void)
{
	uint32_t i;
	uint32_t count = 0;
	for(i = 0; i < 999; i++){

		count++;

	}
	count = 0;

}

void delay(uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

/*******************************************************************************
* Function Name  : static unsigned char _verify(const void * ptr, int n)
* Description    :
* Input          : ptr
                   n
* Output         : None
* Return         :
*******************************************************************************/
static unsigned char _verify(const void * ptr, int n)
{
	uint32_t i;
	unsigned char * p = (uint8_t *)ptr;
	unsigned char result;

	for(i = 0, result = 0; i < n; i++)
	{
		result ^= p[i];
	}

	return result;
}

/*******************************************************************************
* Function Name  : void epd_reset(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_reset(void)
{
	HAL_GPIO_WritePin(GPIOE, DIS_RESET_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);

	_delay();
	_delay();
	_delay();

	HAL_GPIO_WritePin(GPIOE, DIS_RESET_Pin, GPIO_PIN_SET);

	delay(1);
	HAL_GPIO_WritePin(GPIOE, DIS_RESET_Pin, GPIO_PIN_RESET);


	HAL_Delay(3);
//	HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);

	HAL_Delay(6000);
}




/*******************************************************************************
* Function Name  : void epd_init(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_wakeup(void)
{
//	HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, DIS_WAKEUP_Pin, GPIO_PIN_RESET);
	delay(10);
	HAL_GPIO_WritePin(GPIOE, DIS_WAKEUP_Pin, GPIO_PIN_SET);
	delay(400);
	HAL_GPIO_WritePin(GPIOE, DIS_WAKEUP_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);

	HAL_Delay(500);
}



/*******************************************************************************
* Function Name  : void epd_handshake(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_handshake(void)
{
//	HAL_Init();

	memcpy(_cmd_buff, _cmd_handshake, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//		isSend = 0;
//		while (!isSend){
//
//        }
//	}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);




//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_set_baud(long baud)
* Description    : set uart baud
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
//void display_set_baud(long baud)
//{
//	_cmd_buff[0] = FRAME_BEGINE;
//
//	_cmd_buff[1] = 0x00;
//	_cmd_buff[2] = 0x0D;
//
//	_cmd_buff[3] = CMD_SET_BAUD;
//
//	_cmd_buff[4] = (baud >> 24) & 0xFF;
//	_cmd_buff[5] = (baud >> 16) & 0xFF;
//	_cmd_buff[6] = (baud >> 8) & 0xFF;
//	_cmd_buff[7] = baud & 0xFF;
//
//	_cmd_buff[8] = FRAME_END0;
//	_cmd_buff[9] = FRAME_END1;
//	_cmd_buff[10] = FRAME_END2;
//	_cmd_buff[11] = FRAME_END3;
//	_cmd_buff[12] = _verify(_cmd_buff, 12);
//
//
//	HAL_UART_Transmit_DMA(&huart2, _cmd_buff, 13);
//
//
//
////	_putchars(_cmd_buff, 13);
//
////	wait_ms(10);
////	uart.baud(baud);
//}




/*******************************************************************************
* Function Name  : void epd_read_baud(void)
* Description    : read uart baud
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_read_baud(void)
{
	memcpy(_cmd_buff, _cmd_read_baud, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);


//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_set_memory(unsigned char mode)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_set_memory(unsigned char mode)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;

	_cmd_buff[3] = CMD_MEMORYMODE;

	_cmd_buff[4] = mode;

	_cmd_buff[5] = FRAME_END0;
	_cmd_buff[6] = FRAME_END1;
	_cmd_buff[7] = FRAME_END2;
	_cmd_buff[8] = FRAME_END3;
	_cmd_buff[9] = _verify(_cmd_buff, 9);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 10);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 10, 1000);



//	_putchars(_cmd_buff, 10);
}


/*******************************************************************************
* Function Name  : void epd_enter_stopmode(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_enter_stopmode(void)
{
	memcpy(_cmd_buff, _cmd_stopmode, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);


//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_udpate(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_update(void)
{
	memcpy(_cmd_buff, _cmd_update, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);



//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_screen_rotation(unsigned char mode)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_screen_rotation(unsigned char mode)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;

	_cmd_buff[3] = CMD_SCREEN_ROTATION;

	_cmd_buff[4] = mode;

	_cmd_buff[5] = FRAME_END0;
	_cmd_buff[6] = FRAME_END1;
	_cmd_buff[7] = FRAME_END2;
	_cmd_buff[8] = FRAME_END3;
	_cmd_buff[9] = _verify(_cmd_buff, 9);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 10);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}
	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 10, 1000);



//	_putchars(_cmd_buff, 10);
}



/*******************************************************************************
* Function Name  : void epd_load_font(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_load_font(void)
{
	memcpy(_cmd_buff, _cmd_load_font, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);


//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_load_pic(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_load_pic(void)
{
	memcpy(_cmd_buff, _cmd_load_pic, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);


//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_set_color(unsigned char color, unsigned char bkcolor)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_set_color(unsigned char color, unsigned char bkcolor)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0B;

	_cmd_buff[3] = CMD_SET_COLOR;

	_cmd_buff[4] = color;
	_cmd_buff[5] = bkcolor;

	_cmd_buff[6] = FRAME_END0;
	_cmd_buff[7] = FRAME_END1;
	_cmd_buff[8] = FRAME_END2;
	_cmd_buff[9] = FRAME_END3;
	_cmd_buff[10] = _verify(_cmd_buff, 10);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 11);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 11, 1000);


//	_putchars(_cmd_buff, 11);
}



/*******************************************************************************
* Function Name  : void epd_set_en_font(unsigned char font)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_set_en_font(unsigned char font)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;

	_cmd_buff[3] = CMD_SET_EN_FONT;

	_cmd_buff[4] = font;

	_cmd_buff[5] = FRAME_END0;
	_cmd_buff[6] = FRAME_END1;
	_cmd_buff[7] = FRAME_END2;
	_cmd_buff[8] = FRAME_END3;
	_cmd_buff[9] = _verify(_cmd_buff, 9);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 10);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 10, 1000);


//	_putchars(_cmd_buff, 10);
}



/*******************************************************************************
* Function Name  : void epd_set_ch_font(unsigned char font)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
//void epd_set_ch_font(unsigned char font)
//{
//	_cmd_buff[0] = FRAME_BEGINE;
//
//	_cmd_buff[1] = 0x00;
//	_cmd_buff[2] = 0x0A;
//
//	_cmd_buff[3] = CMD_SET_CH_FONT;
//
//	_cmd_buff[4] = font;
//
//	_cmd_buff[5] = FRAME_END0;
//	_cmd_buff[6] = FRAME_END1;
//	_cmd_buff[7] = FRAME_END2;
//	_cmd_buff[8] = FRAME_END3;
//	_cmd_buff[9] = _verify(_cmd_buff, 9);
//
//	_putchars(_cmd_buff, 10);
//}



/*******************************************************************************
* Function Name  : void epd_draw_pixel(int x0, int y0)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_draw_pixel(int x0, int y0)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0D;

	_cmd_buff[3] = CMD_DRAW_PIXEL;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;

	_cmd_buff[8] = FRAME_END0;
	_cmd_buff[9] = FRAME_END1;
	_cmd_buff[10] = FRAME_END2;
	_cmd_buff[11] = FRAME_END3;
	_cmd_buff[12] = _verify(_cmd_buff, 12);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 13);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 13, 1000);



//	_putchars(_cmd_buff, 13);
}



/*******************************************************************************
* Function Name  : void epd_draw_line(int x0, int y0, int x1, int y1)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_draw_line(int x0, int y0, int x1, int y1)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x11;

	_cmd_buff[3] = CMD_DRAW_LINE;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;

	_cmd_buff[12] = FRAME_END0;
	_cmd_buff[13] = FRAME_END1;
	_cmd_buff[14] = FRAME_END2;
	_cmd_buff[15] = FRAME_END3;
	_cmd_buff[16] = _verify(_cmd_buff, 16);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 17);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 17, 1000);



//	_putchars(_cmd_buff, 17);
}


/*******************************************************************************
* Function Name  : void epd_fill_rect(int x0, int y0, int x1, int y1)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_fill_rect(int x0, int y0, int x1, int y1)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x11;

	_cmd_buff[3] = CMD_FILL_RECT;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;

	_cmd_buff[12] = FRAME_END0;
	_cmd_buff[13] = FRAME_END1;
	_cmd_buff[14] = FRAME_END2;
	_cmd_buff[15] = FRAME_END3;
	_cmd_buff[16] = _verify(_cmd_buff, 16);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 17);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart2, (uint8_t *)_cmd_buff, 17, 1000);



//	_putchars(_cmd_buff, 17);
}



/*******************************************************************************
* Function Name  : void epd_draw_circle(int x0, int y0, int r)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_draw_circle(int x0, int y0, int r)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0F;

	_cmd_buff[3] = CMD_DRAW_CIRCLE;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (r >> 8) & 0xFF;
	_cmd_buff[9] = r & 0xFF;


	_cmd_buff[10] = FRAME_END0;
	_cmd_buff[11] = FRAME_END1;
	_cmd_buff[12] = FRAME_END2;
	_cmd_buff[13] = FRAME_END3;
	_cmd_buff[14] = _verify(_cmd_buff, 14);


//	if (isSend == 1) {
//		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 15);
//		isSend = 0;
//		while (!isSend){
//
//		}
//	}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 15, 1000);

//	_putchars(_cmd_buff, 15);
}


/*******************************************************************************
* Function Name  : void epd_fill_circle(int x0, int y0, int r)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_fill_circle(int x0, int y0, int r)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0F;

	_cmd_buff[3] = CMD_FILL_CIRCLE;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (r >> 8) & 0xFF;
	_cmd_buff[9] = r & 0xFF;


	_cmd_buff[10] = FRAME_END0;
	_cmd_buff[11] = FRAME_END1;
	_cmd_buff[12] = FRAME_END2;
	_cmd_buff[13] = FRAME_END3;
	_cmd_buff[14] = _verify(_cmd_buff, 14);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 15);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 15, 1000);



//	_putchars(_cmd_buff, 15);
}




/*******************************************************************************
* Function Name  : void epd_draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x15;

	_cmd_buff[3] = CMD_DRAW_TRIANGLE;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;
	_cmd_buff[12] = (x2 >> 8) & 0xFF;
	_cmd_buff[13] = x2 & 0xFF;
	_cmd_buff[14] = (y2 >> 8) & 0xFF;
	_cmd_buff[15] = y2 & 0xFF;

	_cmd_buff[16] = FRAME_END0;
	_cmd_buff[17] = FRAME_END1;
	_cmd_buff[18] = FRAME_END2;
	_cmd_buff[19] = FRAME_END3;
	_cmd_buff[20] = _verify(_cmd_buff, 20);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 21);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 21, 1000);


//	_putchars(_cmd_buff, 21);
}



/*******************************************************************************
* Function Name  : void epd_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x15;

	_cmd_buff[3] = CMD_FILL_TRIANGLE;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;
	_cmd_buff[12] = (x2 >> 8) & 0xFF;
	_cmd_buff[13] = x2 & 0xFF;
	_cmd_buff[14] = (y2 >> 8) & 0xFF;
	_cmd_buff[15] = y2 & 0xFF;

	_cmd_buff[16] = FRAME_END0;
	_cmd_buff[17] = FRAME_END1;
	_cmd_buff[18] = FRAME_END2;
	_cmd_buff[19] = FRAME_END3;
	_cmd_buff[20] = _verify(_cmd_buff, 20);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 21);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 21, 1000);



//	_putchars(_cmd_buff, 21);
}



/*******************************************************************************
* Function Name  : void epd_clear(void)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_clear(void)
{
	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x09;

	_cmd_buff[3] = CMD_CLEAR;

	_cmd_buff[4] = FRAME_END0;
	_cmd_buff[5] = FRAME_END1;
	_cmd_buff[6] = FRAME_END2;
	_cmd_buff[7] = FRAME_END3;
	_cmd_buff[8] = _verify(_cmd_buff, 8);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, 9);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, 9, 1000);



//	_putchars(_cmd_buff, 9);
}



/*******************************************************************************
* Function Name  : void epd_disp_char(unsigned char ch, int x0, int y0);
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_char(unsigned char ch, int x0, int y0)
{
	unsigned char buff[2];

	buff[0] = ch;
	buff[1] = 0;

	display_string(buff, x0, y0);
}



/*******************************************************************************
* Function Name  : void epd_disp_string(const void * p, int x0, int y0)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_string(const void * p, int x0, int y0)
{
	uint32_t string_size;
	unsigned char * ptr = (unsigned char *)p;


	string_size = strlen((const char *)ptr);
	string_size += 14;

	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = (string_size >> 8) & 0xFF;
	_cmd_buff[2] = string_size & 0xFF;

	_cmd_buff[3] = CMD_DRAW_STRING;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;

	strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);

	string_size -= 5;

	_cmd_buff[string_size] = FRAME_END0;
	_cmd_buff[string_size + 1] = FRAME_END1;
	_cmd_buff[string_size + 2] = FRAME_END2;
	_cmd_buff[string_size + 3] = FRAME_END3;
	_cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);


//	if (isSend == 1) {
//			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, string_size + 5);
//			isSend = 0;
//			while (!isSend){
//
//			}
//		}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, string_size + 5, 1000);



//	_putchars(_cmd_buff, string_size + 5);
}



/*******************************************************************************
* Function Name  : void epd_disp_bitmap(const void * p, int x0, int y0)
* Description    :
* Input          :
* Output         : None
* Return         :
* Attention		   : None
*******************************************************************************/
void display_bitmap(const void * p, int x0, int y0)
{
	uint32_t string_size;
	unsigned char * ptr = (unsigned char *)p;

	string_size = strlen((const char *)ptr);
	string_size += 14;

	_cmd_buff[0] = FRAME_BEGINE;

	_cmd_buff[1] = (string_size >> 8) & 0xFF;
	_cmd_buff[2] = string_size & 0xFF;

	_cmd_buff[3] = CMD_DRAW_BITMAP;

	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;

	strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);

	string_size -= 5;

	_cmd_buff[string_size] = FRAME_END0;
	_cmd_buff[string_size + 1] = FRAME_END1;
	_cmd_buff[string_size + 2] = FRAME_END2;
	_cmd_buff[string_size + 3] = FRAME_END3;
	_cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);


//	if (isSend == 1) {
//				HAL_UART_Transmit_DMA(&huart1, (uint8_t *)_cmd_buff, string_size + 5);
//				isSend = 0;
//				while (!isSend){
//
//				}
//			}

	HAL_UART_Transmit(&huart1, (uint8_t *)_cmd_buff, string_size + 5, 1000);



//	_putchars(_cmd_buff, string_size + 5);
}

// Privet fonctions
void USART2_SendChar(char c) {
    // Transmit veri beklenir
    while (!(USART2->SR & USART_SR_TXE)){

    }
    USART2->DR = c;  // Veriyi gönder
}


