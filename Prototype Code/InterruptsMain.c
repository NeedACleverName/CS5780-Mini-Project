/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint16_t TimerToggle = 0;
//const uint8_t sine_table[32] = {127,151,175,197,216,232,244,251,254,251,244,232,216,197,175,151,127,102,78,56,37,21,9,2,0,2,9,21,37,56,78,102};
//const uint8_t zeros_table[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
const uint8_t wave_table[2][32] = {
	{127,151,175,197,216,232,244,251,254,251,244,232,216,197,175,151,127,102,78,56,37,21,9,2,0,2,9,21,37,56,78,102}
	,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
uint16_t Delay = 40;
int HandlerHeartbeat = 0;

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void EXTI0_1_IRQHandler(void){
		GPIOC->ODR ^= 0x00000080;
		
		EXTI->PR |=0x00000001;
	}

void EXTI2_3_IRQHandler(void){
		
		if ((EXTI->PR&0x00000004)>0){
			GPIOC->ODR ^= 0x00000080;
			EXTI->PR |=0x00000004;
		}
		
		if ((EXTI->PR&0x00000008)>0){
			GPIOC->ODR ^= 0x00000100;
			EXTI->PR |=0x00000008;
		}
		
	}


void EXTI4_15_IRQHandler(void){

		if ((EXTI->PR&0x00000010)>0){
			GPIOC->ODR ^= 0x00000100;
			EXTI->PR |=0x00000010;
		}

		if ((EXTI->PR&0x00000020)>0){
			GPIOC->ODR ^= 0x00000100;
			EXTI->PR |=0x00000020;
		}

		if ((EXTI->PR&0x00000040)>0){
			GPIOC->ODR ^= 0x00000100;
			EXTI->PR |=0x00000040;
		}
		
		if ((EXTI->PR&0x00000080)>0){
			GPIOC->ODR ^= 0x00000100;
			EXTI->PR |=0x00000080;
		}
}

		
//		GPIOC->ODR ^= 0x00000100;

//		if (TimerToggle==0){TimerToggle=1;}
//		else if (TimerToggle==1){TimerToggle=0;}
//		
//		Delay = 200;
//		
//		  


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
HAL_Init(); // Reset of all peripherals, init the Flash and Systick
SystemClock_Config(); //Configure the system clock
/* This example uses HAL library calls to control
the GPIOC peripheral. You’ll be redoing this code
with hardware register access. */

RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
GPIOC->MODER |= 0x00055000; 
GPIOC->OTYPER |= 0x00000000;
GPIOC->OSPEEDR |= 0x00000000;
GPIOC->PUPDR |= 0x00000000;
GPIOC->ODR |= 0x00000000; // 0x00000100 for orange pin
	
GPIOB->MODER |= 0x00000000;
GPIOB->OSPEEDR |= 0x00000000;
GPIOB->PUPDR |= 0x0000AAAA;

EXTI->IMR |= 0x000000FF;
EXTI->RTSR |= 0x000000FF;
EXTI->FTSR |= 0x000000FF;

//DAC1->CR |= 0x00000038;
//DAC1->CR |= 0x00000001;


SYSCFG->EXTICR[0] |= 0x00001111; // PG 169? Connects PA0 to EXTI0
SYSCFG->EXTICR[1] |= 0x00001111;

NVIC_EnableIRQ(EXTI0_1_IRQn);
NVIC_EnableIRQ(EXTI2_3_IRQn);
NVIC_EnableIRQ(EXTI4_15_IRQn);
NVIC_SetPriority(EXTI0_1_IRQn, 1);
NVIC_SetPriority(EXTI2_3_IRQn, 1);
NVIC_SetPriority(EXTI4_15_IRQn, 1);

//SysTick_Config(HAL_RCC_GetHCLKFreq()/1000);
//NVIC_SetPriority(SysTick_IRQn, 2);


while (1) {	
	
	HAL_Delay(100);
	GPIOC->ODR ^= 0x00000040; // 300 for orange and red
	
}
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

