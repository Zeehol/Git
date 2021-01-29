/********************************************************************/
FMC读写SDRAM

SDRAM结构特性：
芯片型号：IS42S16400J-7
时钟频率：143/133Mhz，429AHB3最大时钟频率为1/2HCLK = 90Mhz，所以该芯片最大时钟频率也为90Mhz
内存容量：1M*16bit*4banks = 64Mbit = 8Mbyte
刷新频率：64ms
行地址：12bit A0~A11（复用）
列地址：8bit A0~A7（复用）
Bank 地址：BA0,BA1
数据线：16bit DQ0~DQ15（与DQM配合使用）

引脚说明：
  /** FMC GPIO Configuration
  12根行地址线与8跟列地址线复用：
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PF12   ------> FMC_A6
  PF13   ------> FMC_A7
  PF14   ------> FMC_A8
  PF15   ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11

  16跟数据线：
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3  
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15

  时钟线：
  PG8   ------> FMC_SDCLK
  
  时钟使能线：存储区域2时钟使能（决定存储区域的地址）
  PH7   ------> FMC_SDCKE1
  片选线：存储区域2芯片使能
  
  PH6   ------> FMC_SDNE1
  行地址通选：
  PF11   ------> FMC_SDNRAS
  列地址通选：
  PG15   ------> FMC_SDNCAS
  写入使能线：
  PC0   ------> FMC_SDNWE
  Bank地址线：4个bank
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  数据掩码信号线：
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */

FMC中有4个SDRAM控制寄存器，分别为：
SDRAM控制寄存器1,2；
SDRAM时序寄存器1,2；
SDRAM命令模式寄存器；
SDRAM刷新定时器寄存器；

程序编写：
1.初始化GPIO
2.配置FMC:用于初始化SDRAM结构体与timing时序
自刷新命令后的延时 txSR = 70ns = 7HCLK; 1HCLK = 11ns; 
加载模式寄存器命令的延时 TMRD = 2 CYCLE;
行循环延时 TRC = 63ns = 6HCLK;
行预充电延时 TRPD = 15ns = 2hclk；
行到列延时 TRCD = 15ns = 2
写恢复延时 TWR = 2
自刷新时间 TRAS = 42ns = 4；

FMCbank = FMC_SDRAM_BANK2
hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2; = 133Mhz
hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2; = 90M
hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE; 使能突发读
hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1; CAS后等待的时钟周期

3.初始化SDRAM芯片：

4.设置SDRAM的刷新周期：

