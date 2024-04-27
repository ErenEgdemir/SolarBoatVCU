/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "THROTTLE.h"
#include "THERMALCONTROL.h"
#include "RANGE.h"
#include "gps.h"
#include "display.h"
#include "INTERFACE.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
typedef struct Thr_Veriables {
	uint32_t ADC_THR;
	uint32_t THR_PERC; //CAN
	uint32_t THR_ADC_FILTERED;
	uint32_t THR_DUTY_CYCLE;


}THR_V;

typedef struct Hydrofoil_Veriables{
	uint32_t ADC_HYD;
	uint32_t HYD_PERC;
	uint32_t HYD_ADC_FILTERED;
	uint32_t HYD_DUTY_CYCLE;
}HYD_V;

typedef struct Thermal_Management_Veriables {
	uint32_t ADC_MPPT_1;
	uint32_t ADC_MPPT_2;
	uint32_t ADC_MPPT_3;
	uint32_t ADC_MPPT_4;
	uint32_t ADC_MPPT_5;
	uint32_t ADC_MPPT_6;
	uint32_t ADC_C_MPPT; // MPPT CABLE
	uint32_t ADC_MOTOR;
	uint32_t ADC_ESC;
	uint32_t ADC_CONV_1;
	uint32_t ADC_CONV_2;
	uint32_t ADC_MCU;
	uint32_t ADC_M_TERM; // 48V TERMINAL
	uint32_t ADC_M_CABLE; // BATTERY MAIN OUTPUT CABLE

	float TEMP_MPPT1; //CAN
	float TEMP_MPPT2; //CAN
	float TEMP_MPPT3; //CAN
	float TEMP_MPPT4; //CAN
	float TEMP_MPPT5; //CAN
	float TEMP_MPPT6; //CAN
	float TEMP_C_MPPT;  // MPPT CABLE //CAN
	float TEMP_MOTOR; //CAN
	float TEMP_ESC; //CAN
	float TEMP_CONV_1; //CAN
	float TEMP_CONV_2; //CAN
	float TEMP_MCU; //CAN
	float TEMP_M_TERM;  // 48V TERMINAL  //CAN
	float TEMP_M_CABLE;  // BATTERY MAIN OUTPUT CABLE //CAN

	float TEMP_BAT; // BATTERY TEMP VALUE BY CANBUS LINE  //CAN (BMS)

	float TEMP_CABIN; // TEMP OF CABIN   //CAN
	float HUM_CABIN;  // HUMIDITY OF CABIN  //CAN

}TMA_V;

typedef struct Gps_Veriables{
	float KM_SPEED; // SPEED IN KM
	float KNT_SPEED; // SPEED IN KNOT
	float H_ANGLE; // ANGLE OF HYDROFOIL

}GPS_V;
typedef struct Power_Veriables{
	uint32_t R_ENERGY; // REMAINED ENERGY [Ah]          //CAN (BMS)
	uint32_t CN_CURRENT; // TOTAL CONSAPTED CURRENT [A] //CAN (BMS)
	uint32_t R_TIME; // REMAIED TIME [MINUTE]           //CAN

	uint32_t ADC_C_MPPT_1; // INSTANT CURRENT OF MPPT 1
	uint32_t ADC_C_MPPT_2;
	uint32_t ADC_C_MPPT_3;
	uint32_t ADC_C_MPPT_4;
	uint32_t ADC_C_MPPT_5;
	uint32_t ADC_C_MPPT_6;

	uint32_t C_MPPT_1; //CAN
	uint32_t C_MPPT_2; //CAN
	uint32_t C_MPPT_3; //CAN
	uint32_t C_MPPT_4; //CAN
	uint32_t C_MPPT_5; //CAN
 	uint32_t C_MPPT_6; //CAN

	uint32_t ADC_V_SOLAR_GROUP_1;
	uint32_t ADC_V_SOLAR_GROUP_2;
	uint32_t ADC_V_SOLAR_GROUP_3;
	uint32_t ADC_V_SOLAR_GROUP_4;
	uint32_t ADC_V_SOLAR_GROUP_5;
	uint32_t ADC_V_SOLAR_GROUP_6;

	uint32_t V_SOLAR_GROUP_1; //CAN
	uint32_t V_SOLAR_GROUP_2; //CAN
	uint32_t V_SOLAR_GROUP_3; //CAN
	uint32_t V_SOLAR_GROUP_4; //CAN
	uint32_t V_SOLAR_GROUP_5; //CAN
	uint32_t V_SOLAR_GROUP_6; //CAN

	uint32_t AVARAGE_CN_CURRENT;



}PWR_V;


//pointer defining

THR_V THROTTLE;
TMA_V TEMP;
GPS_V GPS;
PWR_V POWER;
HYD_V HYDROFOIL;

//general veriable defining
uint32_t ADC_BUFFER[16];
uint8_t gps_flag = 0;
struct gps gps1;
float temp_1;
float temp_2;

/* USER CODE END Variables */
osThreadId Data_Manage_Handle;
osThreadId Throttle_Handle;
osThreadId Temp_Man_Handle;
osThreadId Range_Handle;
osThreadId Display_Handle;
osThreadId HydrofoilHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/**********************************************************************************************
 * Function Name  : void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
 * Description    : interrupt handler for adc
 * Input          : None
 * Output         : Pot variables
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance == ADC1){
	  POWER.ADC_C_MPPT_5 = ADC_BUFFER[0];
	  POWER.ADC_C_MPPT_6 = ADC_BUFFER[1];
	  HYDROFOIL.ADC_HYD = ADC_BUFFER[2];
	  TEMP.ADC_MPPT_2 = ADC_BUFFER[3];
	  TEMP.ADC_MPPT_3 = ADC_BUFFER[4];
	  TEMP.ADC_MPPT_4 = ADC_BUFFER[5];
	  TEMP.ADC_MPPT_5 = ADC_BUFFER[6];
	  TEMP.ADC_MPPT_6 = ADC_BUFFER[7];
	  TEMP.ADC_CONV_1 = ADC_BUFFER[8];
	  THROTTLE.ADC_THR = ADC_BUFFER[9];
	  POWER.ADC_C_MPPT_1 = ADC_BUFFER[10];
	  POWER.ADC_C_MPPT_2 = ADC_BUFFER[11];
	  POWER.ADC_C_MPPT_3 = ADC_BUFFER[12];
	  POWER.ADC_C_MPPT_4 = ADC_BUFFER[13];
	  TEMP.ADC_MOTOR = ADC_BUFFER[14];
	  TEMP.ADC_ESC = ADC_BUFFER[15];
  }
}

/**********************************************************************************************
 * Function Name  : void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 * Description    : interrupt handler for gps communication
 * Input          : None
 * Output         : gps_flag
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		gps_flag=1;
	}

/* USER CODE END FunctionPrototypes */

void Data_Management_Algorithm(void const * argument);
void Throttle_Algorithm(void const * argument);
void Temperature_Manegement_Algorithm(void const * argument);
void Range_Algorithm(void const * argument);
void Display_Algorithm(void const * argument);
void Hydrofoil_Algorithm(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Data_Manage_ */
  osThreadDef(Data_Manage_, Data_Management_Algorithm, osPriorityHigh, 0, 1024);
  Data_Manage_Handle = osThreadCreate(osThread(Data_Manage_), NULL);

  /* definition and creation of Throttle_ */
  osThreadDef(Throttle_, Throttle_Algorithm, osPriorityHigh, 0, 256);
  Throttle_Handle = osThreadCreate(osThread(Throttle_), NULL);

  /* definition and creation of Temp_Man_ */
  osThreadDef(Temp_Man_, Temperature_Manegement_Algorithm, osPriorityBelowNormal, 0, 2048);
  Temp_Man_Handle = osThreadCreate(osThread(Temp_Man_), NULL);

  /* definition and creation of Range_ */
  osThreadDef(Range_, Range_Algorithm, osPriorityAboveNormal, 0, 1024);
  Range_Handle = osThreadCreate(osThread(Range_), NULL);

  /* definition and creation of Display_ */
  osThreadDef(Display_, Display_Algorithm, osPriorityBelowNormal, 0, 1024);
  Display_Handle = osThreadCreate(osThread(Display_), NULL);

  /* definition and creation of Hydrofoil */
  osThreadDef(Hydrofoil, Hydrofoil_Algorithm, osPriorityHigh, 0, 256);
  HydrofoilHandle = osThreadCreate(osThread(Hydrofoil), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Data_Management_Algorithm */
/**
  * @brief  Function implementing the Data_Manage_ thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Data_Management_Algorithm */
void Data_Management_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Data_Management_Algorithm */
  /* Infinite loop */

	HAL_ADC_Start_DMA(&hadc1, ADC_BUFFER, 16);




  for(;;)
  {
	  GPS_get_location1();
	  GPS_get_location2();






    osDelay(5);
  }
  /* USER CODE END Data_Management_Algorithm */
}

/* USER CODE BEGIN Header_Throttle_Algorithm */
/**
* @brief Function implementing the Throttle_ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Throttle_Algorithm */
void Throttle_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Throttle_Algorithm */
  /* Infinite loop */
// uint32_t THR_ADC_PREVIOUS = 0;


  for(;;)
  {
	  //THR_ADC_PREVIOUS = THROTTLE.ADC_THR;

	  THROTTLE.THR_ADC_FILTERED = THR_pt1Filter_2(THROTTLE.ADC_THR, 20, 1.0, 0.001);

	  THROTTLE.THR_DUTY_CYCLE = THR_map(THROTTLE.THR_ADC_FILTERED, 0, 4096, 100, 300);

	  TIM2->CCR2 = THROTTLE.THR_DUTY_CYCLE;

    osDelay(10);
  }
  /* USER CODE END Throttle_Algorithm */
}

/* USER CODE BEGIN Header_Temperature_Manegement_Algorithm */
/**
* @brief Function implementing the Temp_Man_ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Temperature_Manegement_Algorithm */
void Temperature_Manegement_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Temperature_Manegement_Algorithm */
  /* Infinite loop */

  for(;;)
  {

//	  TEMP.TEMP_MPPT1 = TMA_calc_temperature(TEMP.ADC_MPPT_1);
//	  TEMP.TEMP_MPPT2 = TMA_calc_temperature(TEMP.ADC_MPPT_2);
//	  TEMP.TEMP_MPPT3 = TMA_calc_temperature(TEMP.ADC_MPPT_3);
//	  TEMP.TEMP_MPPT4 = TMA_calc_temperature(TEMP.ADC_MPPT_4);
//	  TEMP.TEMP_MPPT5 = TMA_calc_temperature(TEMP.ADC_MPPT_5);
//	  TEMP.TEMP_MPPT6 = TMA_calc_temperature(TEMP.ADC_MPPT_6);
//	  TEMP.TEMP_CONV_1 = TMA_calc_temperature(TEMP.ADC_CONV_1);
//	  TEMP.TEMP_ESC = TMA_calc_temperature(TEMP.ADC_ESC);
//	  TEMP.TEMP_MOTOR = TMA_calc_temperature(TEMP.ADC_MOTOR);
//
//
//	  SELECTED_TEMP = temp_select(TEMP->TEMP_ESC, TEMP->TEMP_MOTOR);
//
//	  TMA_cooling_automation(GPIOD, W_COOL_Pin, SELECTED_TEMP, 45, 3, 1);

	  TEMP.TEMP_MPPT1 = 35.0;
      TEMP.TEMP_MPPT2 = 36.0;
      TEMP.TEMP_MPPT3 = 34.0;
	  TEMP.TEMP_MPPT4 = 38.0;
	  TEMP.TEMP_MPPT5 = 34.0;
	  TEMP.TEMP_MPPT6 = 32.0;
	  TEMP.TEMP_CONV_1 = 38.0;
	  TEMP.TEMP_ESC = 45.0;
	  TEMP.TEMP_MOTOR = 46.0;

	  temp_1 = 32.0;




//	  osThreadSuspend(Range_Handle);
//	  osThreadSuspend(HydrofoilHandle);
//	  osThreadSuspend(Throttle_Handle);
//	  osThreadSuspend(Data_Manage_Handle);





    osDelay(3000);
  }
  /* USER CODE END Temperature_Manegement_Algorithm */
}

/* USER CODE BEGIN Header_Range_Algorithm */
/**
* @brief Function implementing the Range_ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Range_Algorithm */
void Range_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Range_Algorithm */
  /* Infinite loop */




  for(;;)
  {
	  CircularBuffer CB;

	  R_initCircularBuffer(&CB);

	  if(POWER.CN_CURRENT > 0){

		 R_addCurrentReading(&CB, POWER.CN_CURRENT);
	  }

	  POWER.AVARAGE_CN_CURRENT = R_calculateAverage(&CB);

	  POWER.R_ENERGY = 45;

	  POWER.R_TIME = POWER.AVARAGE_CN_CURRENT / POWER.R_ENERGY;

	  temp_2 = temp_1;




    osDelay(10);
  }
  /* USER CODE END Range_Algorithm */
}

/* USER CODE BEGIN Header_Display_Algorithm */
/**
* @brief Function implementing the Display_ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Display_Algorithm */
void Display_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Display_Algorithm */
  /* Infinite loop */
//	 display_reset();

	HAL_TIM_Base_Start(&htim1);

//	 display_wakeup();



  for(;;)
  {

//	  display_reset();
//	  __HAL_TIM_SET_COUNTER(&htim1, 20);
//
//	  TEMP.ADC_MCU = __HAL_TIM_GET_COUNTER(&htim1);
//
//
//	   while(__HAL_TIM_GET_COUNTER(&htim1) < 30){
//
//		   TEMP.ADC_MCU = __HAL_TIM_GET_COUNTER(&htim1);
//
//	   }

	  display_wakeup();

//	  interface_write_logo(0, 0);
	  display_clear();
	  display_fill_circle(40, 40, 20);
	  display_string("Tekrar Merhabalar aq", 100, 100);
	  display_update();

//	  interface_write_power(300, 20, POWER.CN_CURRENT);
//
//	  interface_write_speed(300, 200, GPS.KNT_SPEED);
//
//	  interface_write_hAngle(300, 400, HYDROFOIL.HYD_PERC);
//
//	  interface_write_remaningTime(50, 200, POWER.R_TIME);
//
//	  interface_write_mtrTmp(50, 400, TEMP.TEMP_MOTOR);
//
//	  interface_write_escTmp(550, 400, TEMP.TEMP_ESC);

	  osThreadSuspend(Range_Handle);
	  osThreadSuspend(HydrofoilHandle);
	  osThreadSuspend(Throttle_Handle);
	  osThreadSuspend(Data_Manage_Handle);


    osDelay(5000);
  }
  /* USER CODE END Display_Algorithm */
}

/* USER CODE BEGIN Header_Hydrofoil_Algorithm */
/**
* @brief Function implementing the Hydrofoil thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Hydrofoil_Algorithm */
void Hydrofoil_Algorithm(void const * argument)
{
  /* USER CODE BEGIN Hydrofoil_Algorithm */
  /* Infinite loop */


  for(;;)
  {

	  HYDROFOIL.HYD_ADC_FILTERED = THR_pt1Filter_2(HYDROFOIL.ADC_HYD, 20, 1.0, 0.001);

	  HYDROFOIL.HYD_DUTY_CYCLE = THR_map(HYDROFOIL.HYD_ADC_FILTERED, 0, 4096, 100, 300);

	  TIM3->CCR1 = HYDROFOIL.HYD_DUTY_CYCLE;


    osDelay(10);
  }
  /* USER CODE END Hydrofoil_Algorithm */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
