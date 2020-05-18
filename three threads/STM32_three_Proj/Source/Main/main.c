#define  MAIN_CONFIG


#include "config.h"
#include "stm32f10x.h"


int main(void)
{
	
	SysInit();
	
	while(1)
	{
 // 	LedControl();
		 TaskRun();
	

		
	}
	
}

