#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
/************************************************
 ALIENTEK 战舰STM32F103开发板 实验13
 LCD显示实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺： http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

	u8 key;
	u8 x=0;
	u16 cursor_x = 100;     //光标初始位x坐标
  u16 cursor_y = 100;     //光标初始y坐标


int main(void)
{
	
	
  HAL_Init();                    	 	//初始化HAL库    
  Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	uart_init(115200);					//初始化串口
	LED_Init();							//初始化LED	
	KEY_Init();
	LCD_Init();
	EXTI_Init();
	
	LCD_Clear(WHITE);                   //全屏刷白 
  POINT_COLOR = BLUE;                 //画笔颜色为蓝色 
  LCD_ShowString(30, 30, 200, 16, 16, "Key Control Cursor:"); //画提示语 

	POINT_COLOR = RED;                  // 光标颜色
  LCD_ShowChar(cursor_x, cursor_y, '1', 24, 0); //（100，100）画1作为光标
	

	while(1)
	{
			if(key != 0)
			{
        LCD_ShowChar(cursor_x, cursor_y, ' ', 24, 0);       
					switch(key)
					{
            case WKUP_PRES: 
                if(cursor_y >= 16)
									{ 
										cursor_y -= 16; 
										
									} break;
                
            case KEY1_PRES: 
                if(cursor_y < (lcddev.height - 16))
										{
											cursor_y += 16; 
											
										} break;
                
            case KEY2_PRES: 
                if(cursor_x >= 8)
										{ 	
											cursor_x -= 8; 
											
										} break;
                
            case KEY0_PRES:
                if(cursor_x < (lcddev.width - 8)) 
										{ 
											cursor_x += 8; 
											
										} break;
					}
        

        key = 0; 
        POINT_COLOR = RED;
        LCD_ShowChar(cursor_x, cursor_y, '1', 24,0);
			}   
    delay_ms(10);
	}
}

