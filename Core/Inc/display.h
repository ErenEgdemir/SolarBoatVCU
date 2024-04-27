/*********************************************************************************************************
 *
 *       File: display.h
 *    Purpose: E Paper Display UART Communication Handling
 * Created on: Feb 23, 2024
 *     Author: Eren Egdemir
 *       Team: TU YILDIZ SOLAR BOAT TEAM ELECTRONICS AND COMMUNICATIONS DEPARTMENT
 *   Resource: WaveShare epd Library
 *
 *********************************************************************************************************/

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_


//libraries

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


//hal variables

//extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
//extern DMA_HandleTypeDef hdma_usart1_tx;
extern TIM_HandleTypeDef htim1;


extern volatile uint8_t isSend;



//buffer size define

#define    CMD_SIZE                           512

//frame header and end format define

#define    FRAME_BEGINE                       0xA5
#define    FRAME_END0                         0xCC
#define    FRAME_END1                         0x33
#define    FRAME_END2                         0xC3
#define    FRAME_END3                         0x3C


//color define

#define    WHITE                              0x03
#define    GRAY                               0x02
#define    DARK_GRAY                          0x01
#define    BLACK                              0x00


//Command define

#define    CMD_HANDSHAKE                      0x00                                                     //handshake
#define    CMD_SET_BAUD                       0x01                                                     //set baud
#define    CMD_READ_BAUD                      0x02                                                     //read baud
#define    CMD_MEMORYMODE                     0x07                                                     //set memory mode
#define    CMD_STOPMODE                       0x08                                                     //enter stop mode
#define    CMD_UPDATE                         0x0A                                                     //update
#define    CMD_SCREEN_ROTATION                0x0D                                                     //set screen rotation
#define    CMD_LOAD_FONT                      0x0E                                                     //load font
#define    CMD_LOAD_PIC                       0x0F                                                     //load picture

#define    CMD_SET_COLOR                      0x10                                                     //set color
#define    CMD_SET_EN_FONT                    0x1E                                                     //set english font

#define    CMD_DRAW_PIXEL                     0x20                                                     //set pixel
#define    CMD_DRAW_LINE                      0x22                                                     //draw line
#define    CMD_FILL_RECT                      0x24                                                     //fill rectangle
#define    CMD_DRAW_CIRCLE                    0x26                                                     //draw circle
#define    CMD_FILL_CIRCLE                    0x27                                                     //fill circle
#define    CMD_DRAW_TRIANGLE                  0x28                                                     //draw triangle
#define    CMD_FILL_TRIANGLE                  0x29                                                     //fill triangle
#define    CMD_CLEAR                          0x2E                                                     //clear screen use back color

#define    CMD_DRAW_STRING                    0x30                                                     //draw string

#define    CMD_DRAW_BITMAP                    0x70                                                     //draw bitmap

//font define

#define    ASCII32                            0x01
#define    ASCII48                            0x02
#define    ASCII64                            0x03


//memory mode

#define    MEM_NAND                           0
#define    MEM_TF                             1

//Set screen rotation

#define    EPD_NORMAL                         0                                                        //screen normal
#define    EPD_INVERSION                      1                                                        //screen inversion




//Function Prototypes



void myLibraryInit(void);

void display_init(void);
void display_reset(void);
void display_wakeup(void);

void display_handshake(void);
void display_set_baud(long baud);
void display_read_baud(void);
void display_set_memory(unsigned char mode);
void display_enter_stopmode(void);
void display_update(void);
void display_screen_rotation(unsigned char mode);
void display_load_font(void);
void display_load_pic(void);


void display_set_color(unsigned char color, unsigned char bkcolor);
void display_set_en_font(unsigned char font);


void display_draw_pixel(int x0, int y0);
void display_draw_line(int x0, int y0, int x1, int y1);
void display_fill_rect(int x0, int y0, int x1, int y1);
void display_draw_circle(int x0, int y0, int r);
void display_fill_circle(int x0, int y0, int r);
void display_draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2);
void display_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2);
void display_clear(void);

void display_char(unsigned char ch, int x0, int y0);
void display_string(const void * p, int x0, int y0);

void display_bitmap(const void * p, int x0, int y0);



//*********************************************************************************************************************************


#endif /* INC_DISPLAY_H_ */



