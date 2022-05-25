/*
 * main.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Mina-Ryad
 */

#include "LIB/LSTD_TYPES.h"

#include "MCAL/MDIO/MDIO_Interface.h"
#include "MCAL/MGIE/MGIE_Interface.h"
#include "MCAL/MADC/MADC_Interface.h"
#include "MCAL/Timer/TIMER0_Interface.h"
#include "MCAL/Timer/TIMER0_Private.h"

#include "HAL/HCLCD/HCLCD_Interface.h"
#include "HAL/HMOTOR/HMOTOR_Interface.h"

#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "Free_RTOS/semphr.h"
#include "Free_RTOS/queue.h"
#include "util/delay.h"

/*******************************/
/************ Macros ***********/
/*******************************/
#define Motion_Detection 0
#define Water_Level      1
#define Temp             2
#define LDR              3
#define Servo            4

#define Zero		0b00111111
#define One			0b00000110
#define Two			0b01011011
#define Three		0b01001111
#define Four		0b01100110
#define Five		0b01101101
#define Six			0b01111101
#define Seven		0b00000111
#define Eight		0b01111111
#define Nine		0b01101111
#define Zero_D		0b10111111
#define One_D		0b10000110
#define Two_D		0b11011011
#define Three_D		0b11001111
#define Four_D		0b11100110
#define Five_D		0b11101101
#define Six_D		0b11111101
#define Seven_D		0b10000111
#define Eight_D		0b11111111
#define Nine_D		0b11101111

/*******************************/
/******* Global Variables ******/
/*******************************/
u8 State = Motion_Detection;
s8 Servo_Counter=0;

u8 ARR_7_Seg_Display[10]={Zero,One,Two,Three,Four, Five,Six,Seven,Eight,Nine};
u8 ARR_7_Seg_Display_Point[10]={Zero_D, One_D,Two_D, Three_D,Four_D, Five_D,Six_D, Seven_D,Eight_D, Nine_D};

/*******************************/
/******* Task Declaration ******/
/*******************************/
void Task_Buzzer(void*pv);
void Task_SSD(void*pv);
void Task_Water_Read(void*pv);
void Task_Control(void*pv);
void Task_LDR(void *pv);
void Task_PIR_Motion(void *pv);
void Task_Servo(void *pv);
void DC_Control(void*pv);
void Task_TEMP(void*pv);

/*******************************/
/******* ISR Declaration *******/
/*******************************/
void ADC_SetNotification(void);
void Timer_ISR(void);

/**********************************/
/******* Queues Declaration *******/
/**********************************/
xQueueHandle Temp_Alarm_Buffer;
xQueueHandle Water_Alarm_Buffer;
xQueueHandle Motor_Buffer ;
xQueueHandle Temp_Display_Buffer ;
xQueueHandle Motion_Buffer ;
xQueueHandle Water_Good_Buffer;
xQueueHandle DCBuffer;
xQueueHandle Motor_Start_Buffer;
xQueueHandle Temp_Good_Buffer;
xQueueHandle New_Customer_Buffer;
xQueueHandle Servo_Direction_Buffer;

/**************************************/
/******* Semaphores Declaration *******/
/**************************************/
xSemaphoreHandle ADCSem;

/********************/
/******* Main *******/
/********************/
int main(void)
{

	/*********************************/
	/********** DIO Init *************/
	/*********************************/
	/*LED DEBUG*/
	MDIO_Error_State_SetPinDirection(PIN5,MDIO_PORTD,PIN_OUTPUT);

	/*SSD Port*/
	MDIO_Error_State_SetPortDirection(MDIO_PORTB,PORT_OUTPUT);

	/*SSD Control Pins*/
	MDIO_Error_State_SetPinDirection(PIN7,MDIO_PORTC,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN6,MDIO_PORTC,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN5,MDIO_PORTC,PIN_OUTPUT);

	/*Servo Motor*/
	MDIO_Error_State_SetPinDirection(PIN0,MDIO_PORTD,PIN_OUTPUT);

	/*Motion Sensor*/
	MDIO_Error_State_SetPinDirection(PIN1,MDIO_PORTC,PIN_INPUT);

	/*Buzzer*/
	MDIO_Error_State_SetPinDirection(PIN0,MDIO_PORTC,PIN_OUTPUT);

	/*DC Motor*/
	MDIO_Error_State_SetPinDirection(PIN3,MDIO_PORTC,PIN_OUTPUT);

	/*********************************/
	/********** ADC Init *************/
	/*********************************/
	/*ADC ISR Set Call Back*/
	MADC_VidADC_SetCallBack(ADC_SetNotification);
	/*ADC Init*/
	MADC_VidInit();
	/*ADC First Trigger*/
	//	MADC_u16ADCStartConversion_ISR(0);
	//	MADC_u16ADCStartConversion_ISR(1);
	//	MADC_u16ADCStartConversion_ISR(2);

	/**********************************/
	/****** Timer 0 Init For Servo ****/
	/**********************************/
	TIMER0_VidOverFlow_SetCallBack(Timer_ISR);
	TIMER0_VidInit();

	/*********************************/
	/********** Task Create **********/
	/*********************************/

	/*Buzzer Task*/
	xTaskCreate(Task_Buzzer,NULL,70,NULL,0,NULL);

	/*SSD Task*/
	xTaskCreate(Task_SSD,NULL,100,NULL,4,NULL);

	/*Water Level Task*/
	xTaskCreate(Task_Water_Read,NULL, 70, NULL, 2, NULL);

	/*LDR Task*/
	xTaskCreate(Task_LDR,NULL,70,NULL,3,NULL);

	/*Control Task*/
	xTaskCreate(Task_Control,NULL,70,NULL,0,NULL);

	/*Servo Motor Task*/
	xTaskCreate(Task_Servo,NULL,70,NULL,5,NULL);

	/*PIR Motion Sensor Task*/
	xTaskCreate(Task_PIR_Motion,NULL,100,NULL,1,NULL);

	/*DC Control Task*/
	xTaskCreate(DC_Control,NULL,100,NULL,3,NULL);

	/*Temp Task*/
	xTaskCreate(Task_TEMP,NULL,100,NULL,0,NULL);

	/**************************************/
	/********** Semaphore Create **********/
	/**************************************/
	ADCSem = xSemaphoreCreateMutex();

	/**********************************/
	/********** Queue Create **********/
	/**********************************/
	Temp_Alarm_Buffer      = xQueueCreate(1,sizeof(u8));
	Water_Alarm_Buffer     = xQueueCreate(1,sizeof(u8));
	Motor_Buffer           = xQueueCreate(1,sizeof(u8));
	Temp_Display_Buffer    = xQueueCreate(3,sizeof(u16));
	Motion_Buffer          = xQueueCreate(1,sizeof(u8));
	Water_Good_Buffer      = xQueueCreate(1,sizeof(u8));
	DCBuffer               = xQueueCreate(1,sizeof(u8));
	Motor_Start_Buffer     = xQueueCreate(1,sizeof(u8));
	Temp_Good_Buffer       = xQueueCreate(1,sizeof(u8));
	New_Customer_Buffer    = xQueueCreate(1,sizeof(u8));
	Servo_Direction_Buffer = xQueueCreate(1,sizeof(u8));

	/*********************************************/
	/********** Global Interrupt Enable **********/
	/*********************************************/
	MGIE_VidEnable();

	/*************************************/
	/********** Start Scheduler **********/
	/*************************************/
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}

/*PIR Motion Sensor Task*/
void Task_PIR_Motion(void *pv)
{
	static u8 Value = 0;
	while(1)
	{
		if(State == Motion_Detection)
		{
			MDIO_Error_State_GetPinValue(PIN1,MDIO_PORTC,&Value);
			if(Value == 0)
			{
				xQueueSend(Motion_Buffer,&Value,0);
				Value=0;
			}
		}
		vTaskDelay(1000);
	}
}

/*DC Control Task*/
void DC_Control(void*pv)
{
	static u8 DC_Counter = 0;
	static u8 Motor_Start=0;
	while(1)
	{
		if(State==LDR)
		{
			xQueueReceive(Motor_Start_Buffer,&Motor_Start,0);
			if(Motor_Start==1)
			{
				if(DC_Counter < 10)
				{
					MDIO_Error_State_SetPinValue(PIN3,MDIO_PORTC,PIN_HIGH);
				}
				else
				{
					MDIO_Error_State_SetPinValue(PIN3,MDIO_PORTC,PIN_LOW);
					xQueueSend(Motor_Buffer,&DC_Counter,0);
					DC_Counter=0;
					Motor_Start=0;
				}
				DC_Counter++;
			}
		}
		vTaskDelay(100);
	}
}

/*Servo Motor Task*/
void Task_Servo(void *pv)
{
	static u8 Direction=1;
	static u8 Counter=0;
	const u8 Customer=1;
	while(1)
	{
		if(State == Servo){
			if(Counter==0)
			{
				Direction=1;
				xQueueSend(Servo_Direction_Buffer,&Direction,0);
				Counter=1;
			}
			else if(Counter==1)
			{
				Direction=0;
				xQueueSend(Servo_Direction_Buffer,&Direction,0);

				/*Finishing system*/
				xQueueSend(New_Customer_Buffer,&Customer,0);
				Counter=0;
				Direction=1;
			}
		}
		vTaskDelay(100);
	}
}

/*Buzzer Task*/
void Task_Buzzer(void*pv)
{
	static u8 Temp_Data = 1;
	static u8 Water_Data = 101;

	while(1)
	{
		if(State == Water_Level)
		{
			xQueueReceive(Water_Alarm_Buffer,&Water_Data,0);
			if(Water_Data!=101)
			{
				if(Water_Data<101 && Water_Data>50)
				{
					MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_HIGH);
					Water_Data--;
				}
				else if(Water_Data<=50 && Water_Data>0)
				{
					MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_LOW);
					Water_Data--;
					if(Water_Data==0)
					{
						Water_Data=100;
					}
				}
			}
		}
		else
		{
			Water_Data = 101;
		}
		if(State == Temp)
		{
			xQueueReceive(Temp_Alarm_Buffer,&Temp_Data,0);
			if(Temp_Data!=1)
			{
				if(Temp_Data<21 && Temp_Data>10)
				{
					MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_HIGH);
					Temp_Data--;
				}
				else if(Temp_Data<=10 && Temp_Data>0)
				{
					MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_LOW);
					Temp_Data--;
					if(Temp_Data==0)
					{
						Temp_Data=20;
					}
				}
			}
		}
		else
		{
			Temp_Data = 1;
		}
		vTaskDelay(5);
	}
}

/*SSD Task*/
void Task_SSD(void*pv)
{
	static u16 SSDFlag=0;
	static u16 Number = 0;

	while(1)
	{
		xQueueReceive(Temp_Display_Buffer,&Number,0);
		if(SSDFlag==0)
		{
			MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_LOW);
			MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPortValue(MDIO_PORTB, (ARR_7_Seg_Display[Number%10]));
			SSDFlag=1;
		}
		else if(SSDFlag==1)
		{
			MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_LOW);
			MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPortValue(MDIO_PORTB, (ARR_7_Seg_Display_Point[(Number%100)/10]));
			SSDFlag=2;
		}
		else if(SSDFlag==2)
		{
			MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_HIGH);
			MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_LOW);
			MDIO_Error_State_SetPortValue(MDIO_PORTB, (ARR_7_Seg_Display[Number/100]));
			SSDFlag=0;
		}
		if(State== Motion_Detection)
		{
			Number=0;
		}
		vTaskDelay(5);
	}
}

/*Water Level Task*/
void Task_Water_Read(void*pv)
{
	u8 Loc_u8SemState  = 0;
	const u8 WaterAlarm=100;
	const u8 WaterGood=101;
	static u16 Digital = 0xFFFF;
	while(1)
	{
		if(State == Water_Level)
		{
			MADC_u16ADCStartConversion_ISR(0);
			Loc_u8SemState = xSemaphoreTake(ADCSem, 5);
			if (Loc_u8SemState == pdPASS)
			{
				Digital = MADC_VidADC_ReturnADC();
				if(Digital<300)
				{
					xQueueSend(Water_Alarm_Buffer,&WaterAlarm,0);
				}
				else if(Digital==0xFFFF)
				{
				}
				else
				{
					xQueueSend(Water_Alarm_Buffer,&WaterAlarm,0);
					xQueueSend(Water_Good_Buffer,&WaterGood,0);
					Digital = 0xFFFF;
					vTaskDelay(1000);
				}
			}
		}
		vTaskDelay(100);
	}
}

/*LDR Task*/
void Task_LDR(void *pv)
{
	u8 Loc_semState = 0;
	static u16 Analog_LDR = 0xFFFF;
	static u8 LDRFlag=2;
	static u16 Digital = 0;

	while(1)
	{
		if(State==LDR)
		{
			MADC_u16ADCStartConversion_ISR(1);
			Loc_semState = xSemaphoreTake(ADCSem,5);
			if(Loc_semState == pdPASS)
			{
				Digital = MADC_VidADC_ReturnADC();
				Analog_LDR  = ((Digital * 5000UL) / 1024 ) ; /*Remember to update the calculation*/
				if(Analog_LDR < 40)
				{
					LDRFlag = 1;
					xQueueSend(Motor_Start_Buffer,&LDRFlag, 0);
					Analog_LDR=0xFFFF;
					LDRFlag=2;
					Digital = 0;
					vTaskDelay(1000);
				}
				else if(Analog_LDR==0xFFFF)
				{

				}
				else
				{
					LDRFlag=0;
				}
			}
		}
		vTaskDelay(100);
	}
}

/*Temp Task*/
void Task_TEMP(void* pv)
{
	u8 Loc_semState = 0;
	u16 Digital = 0;
	static u16 Analog_TEMP = 0xFFFF;
	const u8 Alarm = 20;
	const u8 Good = 1;

	while(1)
	{
		if(State == Temp)
		{
			MADC_u16ADCStartConversion_ISR(2);
			Loc_semState = xSemaphoreTake(ADCSem,5);
			if(Loc_semState == pdPASS)
			{
				Digital = MADC_VidADC_ReturnADC();
				Analog_TEMP  = ((Digital * 5000UL) / 1024);
				xQueueSend(Temp_Display_Buffer,&Analog_TEMP,0);

				if(Analog_TEMP>250)
				{
					xQueueSend(Temp_Alarm_Buffer,&Alarm,0);
					Analog_TEMP = 0xFFFF;
				}
				else if(Analog_TEMP==0xFFFF)
				{

				}
				else
				{
					/*Finish Temp State*/
					xQueueSend(Temp_Alarm_Buffer,&Good,0);
					xQueueSend(Temp_Good_Buffer,&Good,0);
					Analog_TEMP = 0xFFFF;
				}
			}
		}
		vTaskDelay(100);
	}
}

/*Control Task*/
void Task_Control(void*pv)
{
	static u8 Motion = 0;
	static u8 Level = 0;
	static u8 LDR_1 = 0;
	static u8 Temp_1 =0;
	static u8 Customer = 0;
	while(1)
	{
		switch(State)
		{
		case Motion_Detection:
			xQueueReceive(Motion_Buffer,&Motion,0);
			if(Motion==1)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_LOW);
				State = Water_Level;
			}
			break;
		case Water_Level:
			xQueueReceive(Water_Good_Buffer,&Level,0);
			if(Level==101)
			{
				State = LDR;
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_LOW);
			}
			break;
		case LDR:
			xQueueReceive(Motor_Buffer,&LDR_1,0);
			if(LDR_1==10)
			{
				State=Temp;
			}
			break;
		case Temp:
			xQueueReceive(Temp_Good_Buffer,&Temp_1,0);
			if(Temp_1==1)
			{
				State = Servo;
			}
			break;
		case Servo:
			xQueueReceive(New_Customer_Buffer,&Customer,0);
			if(Customer==1)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_LOW);
				State = Motion_Detection;
				Motion = 0;
				Level = 0;
				LDR_1 = 0;
				Temp_1 =0;
				Customer = 0;
			}
			break;
		}
		vTaskDelay(10);
	}
}

/*ADC ISR*/
void ADC_SetNotification(void)
{
	xSemaphoreGive(ADCSem);
}

/*Timer ISR*/
void Timer_ISR(void)
{
	static u8 Direction=0;
	TCNT0=5;
	if(State == Servo || State == Motion_Detection)
	{
		xQueueReceive(Servo_Direction_Buffer,&Direction,0);
		if(Direction==0)
		{
			if(Servo_Counter<1)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTD,PIN_HIGH);
			}
			else if(Servo_Counter>0 && Servo_Counter<=20)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTD,PIN_LOW);
				if(Servo_Counter==20)
				{
					Servo_Counter=-1;
					Direction=0;
				}
			}
		}
		else if(Direction==1)
		{
			if(Servo_Counter<2)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTD,PIN_HIGH);
			}
			else if(Servo_Counter>1 && Servo_Counter<=20)
			{
				MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTD,PIN_LOW);
				if(Servo_Counter==20)
				{
					Servo_Counter=-1;
					Direction=1;
				}
			}
		}
		Servo_Counter++;
	}
}
