# 电动汽车整车热管理台架电控系统开发
## 项目背景

针对课题组的课题`基于R290冷媒热泵的电动汽车整车热管理系统研究`设计了一套的实验台架，该项目用于搭建适配该实验台架的电控系统，以实现实验台架的正常运行和数据采集。

## 项目需求

1. 传感器数据采集；
2. 执行器动作；
3. 采集数据的发送；
4. 部件间的通讯；



## 解决方案

### 硬件设计

主控芯片使用 **国产车规级芯片 云途 `YTM32B1ME0` **。

暂时使用云途公司的评估板 **`YTM32B1ME0 -Q144 评估板`**进行功能的开发。

![评估板](./pic/1.png)

#### 评估板资源

板载资源：

- EVB MCU：YTM32B1ME0-LQFP144 
- EVB 供电：12V/USB-5V 可选
- MCU 供电：5V/3.3V 可选
- 6 通道板载 LED 控制
- 2 通道按键输入 
- 4 通道 CAN 通讯接口 
- 4 通道 LIN 通讯接口 
- 2 通道电位计/模拟量输入 
- 1 个板载 I2C 接口 EEPROM 
- 1 个板载 SPI 接口 FRAM



#### 传感器

##### 流量传感器



##### 水路PT传感器



#### 执行器

##### 水泵







### 软件设计

开发初版使用云途公司提供的配置工具PE进行快速搭建。





#### MCU功能配置

##### 时钟

暂时使用默认时钟配置，外部高速晶振提供三个主时钟频率（CORE_CLK、FAST_CLK、SLOW_CLK）分别为120MHz、120MHz、40MHz。

![时钟配置](./pic/2.png)





##### 串口

串口配置：

|   功能   |  IO   | MCU  Pin  NO. | Direction | Interrupt config | Interrupt Status |
| :------: | :---: | :-----------: | :-------: | :--------------: | :--------------: |
| UART-RXD | PTA_8 |      144      |   Input   |        -         |        -         |
| UART-TXD | PTA_9 |      143      |  Output   |        -         |        -         |

- 波特率：115200
- 无奇偶校验
- 停止位：1
- 字长：8
- 传输类型：中断传输



###### 串口功能函数

`/app/UART`

实现功能：

- 串口初始化
- printf库移植，实现串口输出



###### printf函数移植

为了优化调试和数据串口输出的目的，移植了**[mpaland大佬的printf库](https://github.com/mpaland/printf)**，实现了线程安全的类PC端的输出效果。

![输出结果测试](./pic/3.png)



##### PWM

使用高级定时器eTMR0，并通过channel0输出PWM。

下面是计算：
$$
快速总线时钟频率：f_{FAST\_BUS\_CLK} = \frac{f_{SYS\_CLK}}{CORE\_DIV*FBUS\_DIV} = 120MHz
$$

$$
eTMR所用时钟频率：f_{eTMR\_CLK} = \frac{f_{FAST\_BUS\_CLK}}{Prescaler}
$$

$$
PWM输出频率：f_{PWM\_FREQUENCY} = \frac{f_{eTMR\_CLK}}{(MOD + 1)}
$$

$$
PWM 对应的 eTMR 计数器周期值：Period = MOD+1
$$

根据水泵说明书要求的：**水泵的PWM信号频率额定值为100Hz。设置分频Prescaler为120，则$ f_{eTMR\_CLK}$为1MHz，产生100Hz的PWM波所对应的eTMR计数器周期值Period为10000，对应的计数器周期值MOD为9999。**这个大小小于int16的值（16位eTMR只用15位计时32767），是可以使用的。



PWM配置：

|    功能    |   IO   | MCU  Pin  NO. | Direction | Frequency |       CLK_SRC        | Prescaler |   Align_Mode    |
| :--------: | :----: | :-----------: | :-------: | :-------: | :------------------: | :-------: | :-------------: |
| PWM output | PTB_12 |      98       |  Output   |   100Hz   | $f_{FAST\_BUS\_CLK}$ |    120    | right(向上计数) |



###### PWM功能函数

`/app/PWM`

实现功能：

- PWM初始化
- PWM使能输出
- PWM失能输出
- PWM占空比调节

在`PWM.c`中主要定义的函数：

```c
void PWM_init()
{	// 调用eTMR驱动，严格意义上来讲，这个函数应该定义为eTMR_init()
    eTMR_DRV_Deinit(eTMR_INST);// 清除寄存器的值，恢复默认
    eTMR_DRV_Init(eTMR_INST,ETMR_PWM_USER_CONFIG_info,&etmrState);
    // 使用ETMR_PWM_USER_CONFIG_info结构体中的信息（时钟源、分频系数等）初始化eTMR，并把该实例的状态存到etmrState，有实例状态指针数组会指向etmrState。
    eTMR_DRV_InitPwm(eTMR_INST,&ETMR_PWM_Config0);
    // 使用ETMR_PWM_Config0结构体中的信息（频率、计数方式、技术初始值、通道具体配置（占空比等））初始化PWM mode。
}

// PWM使能，发送信号
void PWM_Start()
{
    eTMR_DRV_Enable(eTMR_INST);
}

// PWM失能，停止发送信号
void PWM_Stop(void)
{
    eTMR_DRV_Disable(eTMR_INST);
}

// PWM占空比调节，输入浮点数的占空比即可
void PWM_Changedutycycle(float duty_cycle)
{
    eTMR_DRV_UpdatePwmChannel(eTMR_INST, ETMR_PWM_Config0IndChConfig[0].hwChannelId, (uint32_t)(duty_cycle * 0x8000), 0x0000U);
    eTMR_DRV_SetLdok(eTMR_INST);
    // OSIF_TimeDelay(10);
}

```



示波器显示结果：

![pwm示波器结果](./pic/4.jpg)





#### 编译与烧录

使用 VS Code 进行代码编辑，Cmake构建项目，JTAG接口烧录。

在 VS Code 中进行debug。

