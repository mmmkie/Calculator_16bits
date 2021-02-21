/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define delay_error 1000
#define delay_negative 300

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t n1 = 0;
uint16_t n2 = 0;
uint8_t operator;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
uint16_t read_number();
uint8_t selector_operation();
void calculate_n(uint16_t num1,uint16_t num2,uint8_t operation);
void negative(uint16_t num1,uint16_t num2);
void null();
void solution(uint16_t num1,uint16_t num2,uint8_t operation);
void printf_solution(uint16_t result);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  while(HAL_GPIO_ReadPin(GPIOA, Operacion_Pin) != 1)
	  {
		  n1 =  read_number();
	  }
	  operator = selector_operation();
	  while(HAL_GPIO_ReadPin(GPIOA, Enter_Reset_Pin) != 1)
	  {
		  n2 = read_number();
	  }
	  calculate_n(n1, n2, operator);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED0_Pin|LED1_Pin|LED9_Pin|LED10_Pin
                          |LED11_Pin|LED12_Pin|LED13_Pin|LED14_Pin
                          |LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin
                          |LED6_Pin|LED7_Pin|LED8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED15_GPIO_Port, LED15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Unidades_Pin Decenas_Pin Centenas_Pin Miles_Pin
                           Operacion_Pin Enter_Reset_Pin */
  GPIO_InitStruct.Pin = Unidades_Pin|Decenas_Pin|Centenas_Pin|Miles_Pin
                          |Operacion_Pin|Enter_Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED9_Pin LED10_Pin
                           LED11_Pin LED12_Pin LED13_Pin LED14_Pin
                           LED2_Pin LED3_Pin LED4_Pin LED5_Pin
                           LED6_Pin LED7_Pin LED8_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED9_Pin|LED10_Pin
                          |LED11_Pin|LED12_Pin|LED13_Pin|LED14_Pin
                          |LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin
                          |LED6_Pin|LED7_Pin|LED8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED15_Pin */
  GPIO_InitStruct.Pin = LED15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED15_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
uint16_t read_number(){
	uint8_t u = 0,c = 0,d = 0,m = 0;
	uint8_t unidades = 0;
	uint8_t decenas = 0;
	uint8_t centenas = 0;
	uint16_t miles = 0;
	uint16_t numero = 0;

	u = HAL_GPIO_ReadPin(GPIOA, Unidades_Pin);
	d = HAL_GPIO_ReadPin(GPIOA, Decenas_Pin);
	c = HAL_GPIO_ReadPin(GPIOA, Centenas_Pin);
	m = HAL_GPIO_ReadPin(GPIOA, Miles_Pin);

	while((u == 1) || (d == 1) || (c == 1) || (m == 1)){

	}

	return numero;
}

uint8_t selector_operation(){
	uint8_t op;
	uint8_t contador = 0;

	if(HAL_GPIO_ReadPin(GPIOA, Operacion_Pin)==1)
	{
		contador++;
	}

	switch (contador)
	{
	case 1:
		op = 2;
		break;
	case 2:
		op = '-';
		break;
	case 3:
		op = '*';
		break;
	case 4:
		op = '/';
		break;
	default:
		break;

	return op;

	}
}

void calculate_n(uint16_t num1,uint16_t num2,uint8_t operation){
	if(num1 < num2){
		negative(num2,num1);
	}else{
		solution(num1,num2);
	}
}

void negative(uint16_t num1,uint16_t num2){

}

void solution(uint16_t num1,uint16_t num2,uint8_t operation){
	uint16_t result = 0;
	switch(operation)
	{
		case '+':
			result = num1 + num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		default:
			break;
	}
	if(result > 65535){
		null();
	}else{
		printf_solution(result);
	}
}

void printf_solution(uinst16_t result){

}

void null(){

}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
