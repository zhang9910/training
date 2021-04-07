SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\Git\cmd;C:\Users\zhangmeiling\AppData\Local\Microsoft\WindowsApps;
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32G070KBTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=DMA_UART
SET CPU_CLOCK=0x03D09000
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "dma_uart\startup_stm32g070xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_uart_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_ll_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_dma_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_pwr_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\stm32g0xx_hal_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "dma_uart\system_stm32g0xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "DMA_UART\DMA_UART.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "DMA_UART\DMA_UART.axf" --i32combined --output "DMA_UART\DMA_UART.hex"
