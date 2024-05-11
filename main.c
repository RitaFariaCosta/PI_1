/* USER CODE BEGIN Header */
/**
  **************************
  * @file           : main.c
  * @brief          : Main program body
  **************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  **************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7735\st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1_ON HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LED2_ON HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LED3_ON HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LED4_ON HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)

#define LED1_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define LED2_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define LED3_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define LED4_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)

#define BOTAO9_ESQUERDA HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO10 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO11_DIREITA HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO12_CIMA HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)
//char x, o;




/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int jogador = 0;
int posicao = 0;
int contador = 1;
int x=0,y=0;
char matriz[9]={0,0,0,0,0,0,0,0,0};
//char matrizsalva[9]={0,0,0,0,0,0,0,0,0};
int estadocasinha = 0;
int botao = 0;
int condicao = 0;
int pontuacaoX = 0;
int pontuacaoO = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  //if(BOTAO10==0)
	  	 // 	{
	  	  	LED4_ON;
	  	  	HAL_Delay(1000);
	  	  	LED4_OFF;

	  	  	condicao=1;
	  	  	//ControlarJogador(contador);
	  	  	MoverCursor();
	  	    EfetuarJogada();

            contador++;



	  	  	//}



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
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

int MoverCursor() //tem q colocar o cursor piscando // como mudar a vez para o outro jogador
{  //VerificarVencedor();
	char mostrar = ControlarJogador(contador);

    x = 15;
    y = 10;


while(condicao==1){
    	 DesenhoTabuleiro();

	VerificarCasinha();

 do{
	if(mostrar == 'X'){
		jogador = 1;

		ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
		posicao == 0;

			if (BOTAO11_DIREITA == 0){
				botao = 1; //mostra que é a direita

				if(x==15 && y==10){
			ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
			//VerificarCasinha();
			//if(estadocasinha ==4){}
			x = x + 30;
			ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
			posicao=1;
				}
				else if( x==45 && y==10){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
					posicao=2;
				}
				else if(x==15 && y==35){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
					posicao=4;
					}
				else if(x==45 && y==35){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
					posicao=5;
					}
				else if(x==15 && y==60){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
					posicao=7;
					}
				else if(x==45 && y==60){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
					posicao=8;
				}

				else if(x==75 && y==10){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 15;
				y=y+25;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=3;
				}
				else if(x==75 && y==35){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 15;
				y=y+25;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=6;
				}

				else if(x==75 && y==60){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 15;
				y=y-50;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=0;
				}
				VerificarMatriz();
				}


			if(BOTAO9_ESQUERDA == 0){
				botao = 2; //mostra que é a esquerda


				if((x==15 && y==10) || posicao==0){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 75;
				y = 60;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=8;
				}
				else if((x==45 && y==10) || posicao==1){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = x - 30;
				y = 10;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=0;
				}
				else if((x==75 && y==10) || posicao==2){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = x - 30;
				y = 10;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=1;
				}
				else if((x==15 && y==35) || posicao==3){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 75;
				y = 10;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=2;
				}
				else if((x==45 && y==35) || posicao==4){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = x - 30;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=3;
				}
				else if((x==75 && y==35) || posicao==5){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = x - 30;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=4;
				}

				else if((x==15 && y==60) || posicao==6){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = 75;
				y=y-25;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=5;
				}
				else if((x==45 && y==60) || posicao==7){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
			    x = 15;
				y = 60;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=6;
				}

				else if((x==75 && y==60) || posicao==8){
				ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
				x = x - 30;
				y=60;
				ST7735_WriteString(x,y,"X", Font_11x18, WHITE, BLACK);
				posicao=7;
				}
				VerificarCasinha();
				VerificarMatriz();
				}
		}


	else if(mostrar == 'O'){
		jogador=2;
		ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
		if (BOTAO11_DIREITA == 0){
			botao = 1; //mostra que é a direita

						if((x==15 && y==10) || posicao==0){
					ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					x = x + 30;
					ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
					posicao=1;
						}
						else if((x==45 && y==10) || posicao==1){
							ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
							x = x + 30;
							ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
							posicao=2;
						}
						else if((x==15 && y==35) || posicao==3){
							ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
							x = x + 30;
							ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
							posicao=4;
							}
						else if((x==45 && y==35) || posicao==4){
							ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
							x = x + 30;
							ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
							posicao=5;
							}
						else if((x==15 && y==60) || posicao==6){
							ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
							x = x + 30;
							ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
							posicao=7;
							}
						else if((x==45 && y==60) || posicao==7){
							ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
							x = x + 30;
							ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
							posicao=8;
						}

						else if((x==75 && y==10) || posicao==2){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 15;
						y=y+25;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=3;
						}
						else if((x==75 && y==35) || posicao==5){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 15;
						y=y+25;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=6;
						}

						else if((x==75 && y==60) || posicao==8){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 15;
						y=y-50;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=0;
						}
						VerificarCasinha();
						VerificarMatriz();
						}


					if(BOTAO9_ESQUERDA == 0){
						botao = 2; //mostra que é a esquerda
						VerificarCasinha();
						if((x==15 && y==10) || posicao==0){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 75;
						y = 60;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=8;
						}
						else if((x==45 && y==10) || posicao==1){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = x - 30;
						y = 10;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=0;
						}
						else if((x==75 && y==10) || posicao==2){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = x - 30;
						y = 10;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=1;
						}
						else if((x==15 && y==35) || posicao==3){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 75;
						y = 10;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=2;
						}
						else if((x==45 && y==35) || posicao==4){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = x - 30;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=3;
						}
						else if((x==75 && y==35) || posicao==5){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = x - 30;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=4;
						}

						else if((x==15 && y==60) || posicao==6){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = 75;
						y=y-25;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=5;
						}
						else if((x==45 && y==60) || posicao==7){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
					    x = 15;
						y = 60;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=6;
						}

						else if((x==75 && y==60) || posicao==8){
						ST7735_WriteString(x,y," ", Font_11x18, WHITE, BLACK);
						x = x - 30;
						y=60;
						ST7735_WriteString(x,y,"O", Font_11x18, WHITE, BLACK);
						posicao=7;
						}
						VerificarMatriz();
						}
				}
 }while (BOTAO12_CIMA == 1);
 //confirmou
 matriz[posicao]=jogador;


 //return posicao;


	condicao=0;
     }//WHILE TRUE

     }//FIM DA FUNÇAO



int EfetuarJogada(){//COMO REALMENTE SALVAR O CURSOR
//FUNÇÃO PARA APARECER O X SALVO NA CASINHA
	//int posicao1 = MoverCursor();

if(jogador==1){
	 if (posicao == 0){
		 ST7735_WriteString(15,10,"X", Font_11x18, RED, BLACK);
		matriz[posicao]=1;
	 }
	 if(posicao==1){
		 ST7735_WriteString(45,10,"X", Font_11x18, RED, BLACK);
		 matriz[posicao]=1;
	 }
	 if(posicao==2){
	 	 ST7735_WriteString(75,10,"X", Font_11x18, RED, BLACK);
	 	matriz[posicao]=1;
	 	 }
	 if(posicao==3){
	 	 	 ST7735_WriteString(15,35,"X", Font_11x18, RED, BLACK);
	 	 	matriz[posicao]=1;
	 	 	 }
	 if(posicao==4){
	 	 	 ST7735_WriteString(45,35,"X", Font_11x18, RED, BLACK);
	 	 	matriz[posicao]=1;
	 	 	 }
	 if(posicao==5){
	 	 	 ST7735_WriteString(75,35,"X", Font_11x18, RED, BLACK);
	 	 	matriz[posicao]=1;
	 	 	 }
	 if(posicao==6){
		 	 	 ST7735_WriteString(15,60,"X", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=1;
		 	 	 }
	 if(posicao==7){
		 	 	 ST7735_WriteString(45,60,"X", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=1;
		 	 	 }
	if(posicao==8){
		 	 	 ST7735_WriteString(75,60,"X", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=1;
		 	 	 }
         }
if(jogador==2){
	 if (posicao == 0){
			 ST7735_WriteString(15,10,"O", Font_11x18, RED, BLACK);
			 matriz[posicao]=2;
		 }
		if(posicao==1){
			 ST7735_WriteString(45,10,"O", Font_11x18, RED, BLACK);
			 matriz[posicao]=2;
		 }
		 if(posicao==2){
		 	 ST7735_WriteString(75,10,"O", Font_11x18, RED, BLACK);
		 	matriz[posicao]=2;
		 	 }
		 if(posicao==3){
		 	 	 ST7735_WriteString(15,35,"O", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=2;
		 	 	 }
		 if(posicao==4){
		 	 	 ST7735_WriteString(45,35,"O", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=2;
		 	 	 }
		 if(posicao==5){
		 	 	 ST7735_WriteString(75,35,"O", Font_11x18, RED, BLACK);
		 	 	matriz[posicao]=2;
		 	 	 }
		 if(posicao==6){
			 	ST7735_WriteString(15,60,"O", Font_11x18, RED, BLACK);
			 	matriz[posicao]=2;
			 	 	 }
		 if(posicao==7){
			 	ST7735_WriteString(45,60,"O", Font_11x18, RED, BLACK);
			 	matriz[posicao]=2;
			 	 	 }
		if(posicao==8){
			 	ST7735_WriteString(75,60,"O", Font_11x18, RED, BLACK);
			 	matriz[posicao]=2;
			 	 	 }
}

}

int VerificarMatriz(){//COMO REALMENTE SALVAR O CURSOR
//FUNÇÃO PARA CONTINUAR APARECER O X/O SALVO NA CASINHA
char vetor[9] = {0,0,0,0,0,0,0,0,0};
for(int i=0;i<9;i++){
vetor[i] = matriz[i];
}

if(vetor[0]==1){
		 ST7735_WriteString(15,10,"X", Font_11x18, RED, BLACK);
	 }
if(vetor[0]==2){
		 ST7735_WriteString(15,10,"O", Font_11x18, RED, BLACK);
	 }

	 if(vetor[1]==1){
		 ST7735_WriteString(45,10,"X", Font_11x18, RED, BLACK);
	 }
	 if(vetor[1]==2){
	 		 ST7735_WriteString(45,10,"O", Font_11x18, RED, BLACK);
	 	 }

	 if(vetor[2]==1){
	 	 ST7735_WriteString(75,10,"X", Font_11x18, RED, BLACK);
	 	 }
	 if(vetor[2]==2){
	 	 	 ST7735_WriteString(75,10,"O", Font_11x18, RED, BLACK);
	 	 	 }
	 if(vetor[3]==1){
	 	 	 ST7735_WriteString(15,35,"X", Font_11x18, RED, BLACK);
	 	 	 }
	 if(vetor[3]==2){
	 	 	 	 ST7735_WriteString(15,35,"O", Font_11x18, RED, BLACK);
	 	 	 	 }
	 if(vetor[4]==1){
	 	 	 ST7735_WriteString(45,35,"X", Font_11x18, RED, BLACK);
	 	 	 }
	 if(vetor[4]==2){
	 	 	 	 ST7735_WriteString(45,35,"O", Font_11x18, RED, BLACK);
	 	 	 	 }
	 if(vetor[5]==1){
	 	 	 ST7735_WriteString(75,35,"X", Font_11x18, RED, BLACK);
	 	 	 }
	 if(vetor[5]==2){
	 	 	 	 ST7735_WriteString(75,35,"O", Font_11x18, RED, BLACK);
	 	 	 	 }
	 if(vetor[6]==1){
		 	 	 ST7735_WriteString(15,60,"X", Font_11x18, RED, BLACK);
		 	 	 }
	 if(vetor[6]==2){
	 		 	 	 ST7735_WriteString(15,60,"O", Font_11x18, RED, BLACK);
	 		 	 	 }
	 if(vetor[7]==1){
		 	 	 ST7735_WriteString(45,60,"X", Font_11x18, RED, BLACK);
		 	 	 }
	 if(vetor[7]==2){
			 	 	 ST7735_WriteString(45,60,"O", Font_11x18, RED, BLACK);
			 	 	 }
	if(vetor[8]==1){
		 	 	 ST7735_WriteString(75,60,"X", Font_11x18, RED, BLACK);
		 	 	 }
	if(vetor[8]==2){
			 	 	 ST7735_WriteString(75,60,"O", Font_11x18, RED, BLACK);
			 	 }

}


int VerificarCasinha(){ //verificar se a casinha esta ocupada ou nao

	if(botao == 1){
		if((matriz[(posicao + 9)%9] == 1) || (matriz[(posicao + 9)%9] == 2)){
			posicao = (posicao + 18)%9;
		}

		else {

		            posicao = (posicao + 9) % 9;
}
	}
/*
if((matriz[1] == 1) || (matriz[1] == 2)){

     posicao = 2;

}
else if ((matriz[1] != 1) || (matriz[1] != 2)){

	posicao=1;

	}
if((matriz[2] == 1) || (matriz[2] == 2)){

     posicao = 3;

}
else if ((matriz[2] != 1) || (matriz[2] != 2)){

	posicao=2;

	}
if((matriz[3] == 1) || (matriz[3] == 2)){

     posicao = 4;

}
else if ((matriz[3] != 1) || (matriz[3] != 2)){

	posicao=3;

	}
if((matriz[4] == 1) || (matriz[4] == 2)){

     posicao = 5;

}
else if ((matriz[4] != 1) || (matriz[4] != 2)){

	posicao=4;

	}
if((matriz[5] == 1) || (matriz[5] == 2)){

     posicao = 6;

}
else if ((matriz[5] != 1) || (matriz[5] != 2)){

	posicao=5;

	}
if((matriz[6] == 1) || (matriz[6] == 2)){

     posicao = 7;

}
else if ((matriz[6] != 1) || (matriz[6] != 2)){

	posicao=6;

	}
if((matriz[7] == 1) || (matriz[7] == 2)){

     posicao = 8;

}
else if ((matriz[7] != 1) || (matriz[7] != 2)){

	posicao=7;

	}
if((matriz[8] == 1) || (matriz[8] == 2)){

     posicao = 0;

}
else if ((matriz[8] != 1) || (matriz[8] != 2)){

	posicao=8;

	}
	}
*/

	else if (botao == 2) {
	        // Verifica se a posição anterior está ocupada
	        if ((matriz[(posicao - 1 + 9) % 9] == 1) || (matriz[(posicao - 1 + 9) % 9] == 2)) {
	            posicao = (posicao - 1 + 9) % 9;
	        }
	    }
	    //return posicao;
	}

/*else if(botao == 2){
	if((matriz[posicao] == 1) || (matriz[posicao] == 2)){
	    posicao -= 1;
	}

}*/



	/*if((matriz[0] == 1) || (matriz[0] == 2)){

	     posicao = 8;

	}
	else if ((matriz[0] != 1) || (matriz[0] != 2)){

		posicao=0;

		}
	if((matriz[1] == 1) || (matriz[1] == 2)){

	     posicao = 2;

	}
	else if ((matriz[1] != 1) || (matriz[1] != 2)){

		posicao=1;

		}
	if((matriz[2] == 1) || (matriz[2] == 2)){

	     posicao = 3;

	}
	else if ((matriz[2] != 1) || (matriz[2] != 2)){

		posicao=2;

		}
	if((matriz[3] == 1) || (matriz[3] == 2)){

	     posicao = 4;

	}
	else if ((matriz[3] != 1) || (matriz[3] != 2)){

		posicao=3;

		}
	if((matriz[4] == 1) || (matriz[4] == 2)){

	     posicao = 5;

	}
	else if ((matriz[4] != 1) || (matriz[4] != 2)){

		posicao=4;

		}
	if((matriz[5] == 1) || (matriz[5] == 2)){

	     posicao = 6;

	}
	else if ((matriz[5] != 1) || (matriz[5] != 2)){

		posicao=5;

		}
	if((matriz[6] == 1) || (matriz[6] == 2)){

	     posicao = 7;

	}
	else if ((matriz[6] != 1) || (matriz[6] != 2)){

		posicao=6;

		}
	if((matriz[7] == 1) || (matriz[7] == 2)){

	     posicao = 8;

	}
	else if ((matriz[7] != 1) || (matriz[7] != 2)){

		posicao=7;

		}
	if((matriz[8] == 1) || (matriz[8] == 2)){

	     posicao = 0;

	}
	else if ((matriz[8] != 1) || (matriz[8] != 2)){

		posicao=8;

		}



}*/



void DesenhoTabuleiro(){
	ST7735_FillScreen(BLACK);
	ST7735_DrawLine(10,30,90,30,WHITE); //HORIZONTAL 1
	ST7735_DrawLine(10,55,90,55,WHITE); //HORIZONTAL 2
	ST7735_DrawLine(30,10,30,75,WHITE); //vertical 1
	ST7735_DrawLine(70,10,70,75,WHITE); //vertical 2
	VerificarMatriz();

ST7735_WriteString(110,20,"PLACAR", Font_7x10, WHITE, BLACK);
ST7735_WriteString(110,40,"X:", Font_11x18, WHITE, BLACK);
ST7735_WriteString(110,60,"O:", Font_11x18, WHITE, BLACK);

}

int ControlarJogador(contador){ //INDICAR DE QUEM É A VEZ //OLHAR COMO MUDAR O CONTADOR
	char jogador = ' ';
	if(contador%2==0){
		ST7735_FillScreen(BLACK);
		ST7735_WriteString(0,20,"    Vez do        jogador X", Font_11x18, WHITE, BLACK);
		//ST7735_WriteString(0,20,"    ", Font_11x18, WHITE, BLACK);
		jogador = 'X';
		HAL_Delay(1000);

	}
	else if(contador%2==1){
		ST7735_FillScreen(BLACK);
		ST7735_WriteString(0,20,"    Vez do        jogador O", Font_11x18, WHITE, BLACK);
		jogador = 'O';
		HAL_Delay(1000);


	}
	return jogador;
}

int VerificarVencedor(){
	int vetor0 = matriz[0];
	int vetor1 = matriz[1];
	int vetor2 = matriz[2];
	int vetor3 = matriz[3];
	int vetor4 = matriz[4];
	int vetor5 = matriz[5];
	int vetor6 = matriz[6];
	int vetor7 = matriz[7];
	int vetor8 = matriz[8];
	int matrizcheia = 1;
	int i;
	//char matriz[9]={0,0,0,0,0,0,0,0,0};

	for (i = 0; i < 9; i++) {
	        if (matriz[i] != 0) {
	            matrizcheia = 0; // A matriz não está cheia
	            break;
	        }
	    }


	if(vetor0 == 1 && vetor1 == 1 && vetor2==1){
		ST7735_FillScreen(BLACK);
		ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
		ST7735_FillScreen(BLACK);
		pontuacaoX++;
	}
	else if(vetor3 == 1 && vetor4 == 1 && vetor5==1){
			ST7735_FillScreen(BLACK);
			ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
			ST7735_FillScreen(BLACK);
			pontuacaoX++;
		}
	else if(vetor6 == 1 && vetor7 == 1 && vetor8==1){
				ST7735_FillScreen(BLACK);
				ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
				ST7735_FillScreen(BLACK);
				pontuacaoX++;
			}
	else if(vetor0 == 1 && vetor3 == 1 && vetor6==1){
					ST7735_FillScreen(BLACK);
					ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
					ST7735_FillScreen(BLACK);
					pontuacaoX++;
				}
	else if(vetor1 == 1 && vetor4 == 1 && vetor7==1){
						ST7735_FillScreen(BLACK);
						ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
						ST7735_FillScreen(BLACK);
						pontuacaoX++;
					}
	else if(vetor2 == 1 && vetor5 == 1 && vetor8==1){
							ST7735_FillScreen(BLACK);
							ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
							ST7735_FillScreen(BLACK);
							pontuacaoX++;
						}
	else if(vetor0 == 1 && vetor4 == 1 && vetor8==1){
							ST7735_FillScreen(BLACK);
							ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
							ST7735_FillScreen(BLACK);
							pontuacaoX++;
						}
	else if(vetor2 == 1 && vetor4 == 1 && vetor6==1){
							ST7735_FillScreen(BLACK);
							ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
							ST7735_FillScreen(BLACK);
							pontuacaoX++;
						}


	else if(vetor0 == 2 && vetor1 == 2 && vetor2==2){
			ST7735_FillScreen(BLACK);
			ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
			ST7735_FillScreen(BLACK);
			pontuacaoO++;
		}
		else if(vetor3 == 2 && vetor4 == 2 && vetor5==2){
				ST7735_FillScreen(BLACK);
				ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
				ST7735_FillScreen(BLACK);
				pontuacaoO++;
			}
		else if(vetor6 == 2 && vetor7 == 2 && vetor8==2){
					ST7735_FillScreen(BLACK);
					ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
					ST7735_FillScreen(BLACK);
					pontuacaoO++;
				}
		else if(vetor0 == 2 && vetor3 == 2 && vetor6==2){
						ST7735_FillScreen(BLACK);
						ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
						ST7735_FillScreen(BLACK);
						pontuacaoO++;
					}
		else if(vetor1 == 2 && vetor4 == 2 && vetor7==2){
							ST7735_FillScreen(BLACK);
							ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
							ST7735_FillScreen(BLACK);
							pontuacaoO++;
						}
		else if(vetor2 == 2 && vetor5 == 2 && vetor8==2){
								ST7735_FillScreen(BLACK);
								ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
								ST7735_FillScreen(BLACK);
								pontuacaoO++;
							}
		else if(vetor0 == 2 && vetor4 == 2 && vetor8==2){
								ST7735_FillScreen(BLACK);
								ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
								ST7735_FillScreen(BLACK);
								pontuacaoO++;
							}
		else if(vetor2 == 2 && vetor4 == 2 && vetor6==2){
								ST7735_FillScreen(BLACK);
								ST7735_WriteString(0,20,"Jogador X ganhou a rodada", Font_11x18, WHITE, BLACK);
								ST7735_FillScreen(BLACK);
								pontuacaoO++;
							}
		else if (matrizcheia == 1){
			ST7735_FillScreen(BLACK);
			ST7735_WriteString(0,20,"Deu VELHA!!!", Font_11x18, WHITE, BLACK);
			ST7735_FillScreen(BLACK);
		}

}

/CRIAR AS FUNÇOES AQUI/


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

/******** (C) COPYRIGHT STMicroelectronics **END OF FILE*/