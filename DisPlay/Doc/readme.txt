/********************************************************************/
FMC��дSDRAM

SDRAM�ṹ���ԣ�
оƬ�ͺţ�IS42S16400J-7
ʱ��Ƶ�ʣ�143/133Mhz��429AHB3���ʱ��Ƶ��Ϊ1/2HCLK = 90Mhz�����Ը�оƬ���ʱ��Ƶ��ҲΪ90Mhz
�ڴ�������1M*16bit*4banks = 64Mbit = 8Mbyte
ˢ��Ƶ�ʣ�64ms
�е�ַ��12bit A0~A11�����ã�
�е�ַ��8bit A0~A7�����ã�
Bank ��ַ��BA0,BA1
�����ߣ�16bit DQ0~DQ15����DQM���ʹ�ã�

����˵����
  /** FMC GPIO Configuration
  12���е�ַ����8���е�ַ�߸��ã�
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

  16�������ߣ�
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

  ʱ���ߣ�
  PG8   ------> FMC_SDCLK
  
  ʱ��ʹ���ߣ��洢����2ʱ��ʹ�ܣ������洢����ĵ�ַ��
  PH7   ------> FMC_SDCKE1
  Ƭѡ�ߣ��洢����2оƬʹ��
  
  PH6   ------> FMC_SDNE1
  �е�ַͨѡ��
  PF11   ------> FMC_SDNRAS
  �е�ַͨѡ��
  PG15   ------> FMC_SDNCAS
  д��ʹ���ߣ�
  PC0   ------> FMC_SDNWE
  Bank��ַ�ߣ�4��bank
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  ���������ź��ߣ�
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */

FMC����4��SDRAM���ƼĴ������ֱ�Ϊ��
SDRAM���ƼĴ���1,2��
SDRAMʱ��Ĵ���1,2��
SDRAM����ģʽ�Ĵ�����
SDRAMˢ�¶�ʱ���Ĵ�����

�����д��
1.��ʼ��GPIO
2.����FMC:���ڳ�ʼ��SDRAM�ṹ����timingʱ��
��ˢ����������ʱ txSR = 70ns = 7HCLK; 1HCLK = 11ns; 
����ģʽ�Ĵ����������ʱ TMRD = 2 CYCLE;
��ѭ����ʱ TRC = 63ns = 6HCLK;
��Ԥ�����ʱ TRPD = 15ns = 2hclk��
�е�����ʱ TRCD = 15ns = 2
д�ָ���ʱ TWR = 2
��ˢ��ʱ�� TRAS = 42ns = 4��

FMCbank = FMC_SDRAM_BANK2
hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2; = 133Mhz
hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2; = 90M
hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE; ʹ��ͻ����
hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1; CAS��ȴ���ʱ������

3.��ʼ��SDRAMоƬ��

4.����SDRAM��ˢ�����ڣ�

