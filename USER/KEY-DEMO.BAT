SET PATH=E:\keil\ARM\aaa\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;E:\Git\cmd;E:\Windows Kits\10\Windows Performance Toolkit\;E:\matlab\runtime\win64;E:\matlab\bin;F:\orcad\OpenAccess\bin\win32\opt;F:\orcad\tools\pcb\bin;F:\orcad\tools\fet\bin;F:\orcad\tools\Capture;F:\orcad\tools\PSpice;F:\orcad\tools\specctra\bin;F:\orcad\tools\bin;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=KEY-DEMO
SET CPU_CLOCK=0x00B71B00
"E:\keil\ARM\aaa\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"E:\keil\ARM\aaa\Bin\ArmAsm" --Via ".\rtos._ia"
"E:\keil\ARM\aaa\Bin\ArmCC" --Via ".\main.__i"
"E:\keil\ARM\aaa\Bin\ArmCC" --Via ".\task.__i"
"E:\keil\ARM\aaa\Bin\ArmCC" --Via ".\semaphore.__i"
"E:\keil\ARM\aaa\Bin\ArmLink" --Via ".\STM32-DEMO.lnp"
"E:\keil\ARM\aaa\Bin\fromelf.exe" ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"
