SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;D:\stm32cube\;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\Git\cmd;C:\Users\zhangmeiling\AppData\Local\Microsoft\WindowsApps;;C:\Program Files\Java\jre1.8.0_201\bin
SET CPU_TYPE=STM32G070KBTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=g707
SET CPU_CLOCK=0x03D09000
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "g707\startup_stm32g070xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_ll_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_dma_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_pwr_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\stm32g0xx_hal_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "g707\system_stm32g0xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "g707\g707.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "g707\g707.axf" --i32combined --output "g707\g707.hex"
