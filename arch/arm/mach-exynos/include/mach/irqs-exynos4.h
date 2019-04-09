/* linux/arch/arm/mach-exynos/include/mach/irqs-exynos4.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - IRQ definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_IRQS_EXYNOS4_H
#define __ASM_ARCH_IRQS_EXYNOS4_H __FILE__

#define IRQ_EINT0		IRQ_SPI(16)
#define IRQ_EINT1		IRQ_SPI(17)
#define IRQ_EINT2		IRQ_SPI(18)
#define IRQ_EINT3		IRQ_SPI(19)
#define IRQ_EINT4		IRQ_SPI(20)
#define IRQ_EINT5		IRQ_SPI(21)
#define IRQ_EINT6		IRQ_SPI(22)
#define IRQ_EINT7		IRQ_SPI(23)
#define IRQ_EINT8		IRQ_SPI(24)
#define IRQ_EINT9		IRQ_SPI(25)
#define IRQ_EINT10		IRQ_SPI(26)
#define IRQ_EINT11		IRQ_SPI(27)
#define IRQ_EINT12		IRQ_SPI(28)
#define IRQ_EINT13		IRQ_SPI(29)
#define IRQ_EINT14		IRQ_SPI(30)
#define IRQ_EINT15		IRQ_SPI(31)
#define IRQ_EINT16_31		IRQ_SPI(32)
#define IRQ_MDMA0		IRQ_SPI(33)
#define IRQ_C2C_SSCM0		IRQ_SPI(33)
#define IRQ_MDMA1		IRQ_SPI(34)
#define IRQ_PDMA0		IRQ_SPI(35)
#define IRQ_PDMA1		IRQ_SPI(36)
#define IRQ_TIMER0_VIC		IRQ_SPI(37)
#define IRQ_TIMER1_VIC		IRQ_SPI(38)
#define IRQ_TIMER2_VIC		IRQ_SPI(39)
#define IRQ_TIMER3_VIC		IRQ_SPI(40)
#define IRQ_TIMER4_VIC		IRQ_SPI(41)
#define IRQ_MCT_L0		IRQ_SPI(42)
#define IRQ_WDT			IRQ_SPI(43)
#define IRQ_RTC_ALARM		IRQ_SPI(44)
#define IRQ_RTC_TIC		IRQ_SPI(45)

#define IRQ_GPIO_XB		IRQ_SPI(46)
#define IRQ_GPIO_XA		IRQ_SPI(47)

#define IRQ_MCT_L1		IRQ_SPI(48)

#define IRQ_UART0		IRQ_SPI(52)
#define IRQ_UART1		IRQ_SPI(53)
#define IRQ_UART2		IRQ_SPI(54)
#define IRQ_UART3		IRQ_SPI(55)
#define IRQ_UART4		IRQ_SPI(56)
#define IRQ_MCT_G0		IRQ_SPI(57)
#define IRQ_IIC			IRQ_SPI(58)
#define IRQ_IIC1		IRQ_SPI(59)
#define IRQ_IIC2		IRQ_SPI(60)
#define IRQ_IIC3		IRQ_SPI(61)
#define IRQ_IIC4		IRQ_SPI(62)
#define IRQ_IIC5		IRQ_SPI(63)
#define IRQ_IIC6		IRQ_SPI(64)
#define IRQ_IIC7		IRQ_SPI(65)
#define IRQ_SPI0		IRQ_SPI(66)
#define IRQ_SPI1		IRQ_SPI(67)
#define IRQ_SPI2		IRQ_SPI(68)

#define IRQ_USB_HOST		IRQ_SPI(70)
#define IRQ_USB_HSOTG		IRQ_SPI(71)
#define IRQ_MODEM_IF		IRQ_SPI(72)
#define IRQ_GPIO_C2C		IRQ_SPI(72)
#define IRQ_HSMMC0		IRQ_SPI(73)
#define IRQ_HSMMC1		IRQ_SPI(74)
#define IRQ_HSMMC2		IRQ_SPI(75)
#define IRQ_HSMMC3		IRQ_SPI(76)
#define IRQ_DWMCI		IRQ_SPI(77)

#define IRQ_MIPICSI0		IRQ_SPI(78)
#define IRQ_MIPIDSI0		IRQ_SPI(79)
#define IRQ_MIPICSI1		IRQ_SPI(80)
#define IRQ_MIPIDSI1		IRQ_SPI(81)

#define IRQ_ONENAND_AUDI	IRQ_SPI(82)
#define IRQ_ROTATOR		IRQ_SPI(83)
#define IRQ_FIMC0		IRQ_SPI(84)
#define IRQ_FIMC1		IRQ_SPI(85)
#define IRQ_FIMC2		IRQ_SPI(86)
#define IRQ_FIMC3		IRQ_SPI(87)
#define IRQ_JPEG		IRQ_SPI(88)
#define IRQ_2D			IRQ_SPI(89)
#define IRQ_PCIE		IRQ_SPI(90)
#define IRQ_FIMC_IS0		IRQ_SPI(90)
#define IRQ_MIXER		IRQ_SPI(91)
#define IRQ_HDMI		IRQ_SPI(92)
#define IRQ_HDMI_I2C		IRQ_SPI(93)
#define IRQ_IIC_HDMIPHY		IRQ_SPI(93)
#define IRQ_MFC			IRQ_SPI(94)
#define IRQ_TVENC		IRQ_SPI(95)
#define IRQ_SDO			IRQ_SPI(95)
#define IRQ_FIMC_IS1		IRQ_SPI(95)
#define IRQ_AUDIO_SS		IRQ_SPI(96)
#define IRQ_I2S0		IRQ_SPI(97)
#define IRQ_I2S1		IRQ_SPI(98)
#define IRQ_I2S2		IRQ_SPI(99)
#define IRQ_AC97		IRQ_SPI(100)

#define IRQ_SPDIF		IRQ_SPI(104)
#define IRQ_ADC0		IRQ_SPI(105)
#define IRQ_PEN0		IRQ_SPI(106)
#define IRQ_FIMC_LITE0		IRQ_SPI(105)
#define IRQ_FIMC_LITE1		IRQ_SPI(106)
#define IRQ_ADC1		IRQ_SPI(107)
#define IRQ_PEN1		IRQ_SPI(108)
#define IRQ_KEYPAD		IRQ_SPI(109)
#define IRQ_POWER_PMU		IRQ_SPI(110)
#define IRQ_GPS			IRQ_SPI(111)
#define IRQ_INTFEEDCTRL_SSS	IRQ_SPI(112)
#define IRQ_SLIMBUS		IRQ_SPI(113)
#define IRQ_CEC		IRQ_SPI(114)
#define IRQ_TSI			IRQ_SPI(115)
#define IRQ_SATA		IRQ_SPI(116)
#define IRQ_C2C_SSCM1		IRQ_SPI(116)

#define IRQ_PPMMU0_3D		IRQ_SPI(118)
#define IRQ_PPMMU1_3D		IRQ_SPI(119)
#define IRQ_PPMMU2_3D		IRQ_SPI(120)
#define IRQ_PPMMU3_3D		IRQ_SPI(121)
#define IRQ_GPMMU_3D		IRQ_SPI(122)

#define IRQ_PP0_3D		IRQ_SPI(123)
#define IRQ_PP1_3D		IRQ_SPI(124)
#define IRQ_PP2_3D		IRQ_SPI(125)
#define IRQ_PP3_3D		IRQ_SPI(126)
#define IRQ_GP_3D		IRQ_SPI(127)
#define IRQ_PMU_3D		IRQ_SPI(117)

#define IRQ_MCT_LOCALTIMER	IRQ_PPI(12)
#define MAX_IRQ_IN_COMBINER	8
#define COMBINER_GROUP(x)	((x) * MAX_IRQ_IN_COMBINER + IRQ_SPI(128))
#define COMBINER_IRQ(x, y)	(COMBINER_GROUP(x) + y)

#define IRQ_LCD_LITE0		COMBINER_IRQ(0, 0)
#define IRQ_LCD_LITE1		COMBINER_IRQ(0, 1)

#define IRQ_PMU_CPU0		COMBINER_IRQ(2, 2)
#define IRQ_PMU			IRQ_PMU_CPU0
#define IRQ_TMU			COMBINER_IRQ(2, 4)

#define IRQ_PMU_CPU1		COMBINER_IRQ(3, 2)

#define IRQ_SYSMMU_MDMA0_0	COMBINER_IRQ(4, 0)
#define IRQ_SYSMMU_SSS_0	COMBINER_IRQ(4, 1)
#define IRQ_SYSMMU_FIMC0_0	COMBINER_IRQ(4, 2)
#define IRQ_SYSMMU_FIMC1_0	COMBINER_IRQ(4, 3)
#define IRQ_SYSMMU_FIMC2_0	COMBINER_IRQ(4, 4)
#define IRQ_SYSMMU_FIMC3_0	COMBINER_IRQ(4, 5)
#define IRQ_SYSMMU_JPEG_0	COMBINER_IRQ(4, 6)
#define IRQ_SYSMMU_2D_0		COMBINER_IRQ(4, 7)

#define IRQ_SYSMMU_ROTATOR_0	COMBINER_IRQ(5, 0)
#define IRQ_SYSMMU_MDMA1_0	COMBINER_IRQ(5, 1)
#define IRQ_SYSMMU_FIMD0_0	COMBINER_IRQ(5, 2)
#define IRQ_SYSMMU_FIMD1_0	COMBINER_IRQ(5, 3)
#define IRQ_SYSMMU_TV_0		COMBINER_IRQ(5, 4)
#define IRQ_SYSMMU_MFC_R_0	COMBINER_IRQ(5, 5)
#define IRQ_SYSMMU_MFC_L_0	COMBINER_IRQ(5, 6)
#define IRQ_SYSMMU_PCIE_0	COMBINER_IRQ(5, 7)

#define IRQ_EXYNOS4412_ADC	COMBINER_IRQ(10, 3)

#define IRQ_FIMD0_FIFO		COMBINER_IRQ(11, 0)
#define IRQ_FIMD0_VSYNC		COMBINER_IRQ(11, 1)
#define IRQ_FIMD0_SYSTEM	COMBINER_IRQ(11, 2)

#define IRQ_FIMD1_FIFO		COMBINER_IRQ(12, 0)
#define IRQ_FIMD1_VSYNC		COMBINER_IRQ(12, 1)
#define IRQ_FIMD1_SYSTEM	COMBINER_IRQ(12, 2)

#define IRQ_SYSMMU_LITE0_0	COMBINER_IRQ(16, 0)
#define IRQ_SYSMMU_LITE1_0	COMBINER_IRQ(16, 1)
#define IRQ_SYSMMU_ISP_0	COMBINER_IRQ(16, 2)
#define IRQ_SYSMMU_DRC_0	COMBINER_IRQ(16, 3)
#define IRQ_SYSMMU_FD_0		COMBINER_IRQ(16, 4)
#define IRQ_SYSMMU_MCUISP_0	COMBINER_IRQ(16, 5)

#define IRQ_PMU_CPU2		COMBINER_IRQ(18, 2)
#define IRQ_PMU_CPU3		COMBINER_IRQ(19, 2)

#define COMMON_COMBINER_NR	16
#define MAX_COMBINER_NR		20

#define S5P_IRQ_EINT_BASE	COMBINER_IRQ(MAX_COMBINER_NR, 0)

#define S5P_EINT_BASE1		(S5P_IRQ_EINT_BASE + 0)
#define S5P_EINT_BASE2		(S5P_IRQ_EINT_BASE + 16)

#define IRQ_TVOUT_HPD		(S5P_IRQ_EINT_BASE + 31)

#if defined(CONFIG_CPU_EXYNOS4210)
#if defined(CONFIG_S3C_DEV_ADC)
#define IRQ_ADC		IRQ_ADC0
#define IRQ_TC		IRQ_PEN0
#else
#define IRQ_ADC		IRQ_ADC1
#define IRQ_TC		IRQ_PEN1
#endif
#elif defined(CONFIG_CPU_EXYNOS4412)
#define IRQ_ADC		IRQ_EXYNOS4412_ADC
#define IRQ_TC		IRQ_PEN0
#endif

/* optional GPIO interrupts */
#define S5P_GPIOINT_BASE	(S5P_IRQ_EINT_BASE + 32)
#define IRQ_GPIO1_NR_GROUPS	16
#define IRQ_GPIO2_NR_GROUPS	12
#define IRQ_GPIO_END		(S5P_GPIOINT_BASE + S5P_GPIOINT_COUNT)

#define IRQ_BOARD_START		IRQ_GPIO_END

#if defined(CONFIG_MFD_MAX77693) || defined(CONFIG_MFD_MAX77686) ||\
	defined(CONFIG_MFD_S5M_CORE)
#define IRQ_BOARD_IFIC_START	(IRQ_BOARD_START)
#define IRQ_BOARD_IFIC_NR	29
#define IRQ_BOARD_PMIC_START	(IRQ_BOARD_START + IRQ_BOARD_IFIC_NR)
#define IRQ_BOARD_PMIC_NR	16
#define IRQ_BOARD_CODEC_START	(IRQ_BOARD_PMIC_START + IRQ_BOARD_PMIC_NR)
#define IRQ_BOARD_CODEC_NR	32
#define IRQ_NR_BOARD		(IRQ_BOARD_PMIC_NR + IRQ_BOARD_IFIC_NR \
				 + IRQ_BOARD_CODEC_NR)
#elif defined(CONFIG_MFD_MAX8997)
#define IRQ_BOARD_PMIC_START	(IRQ_BOARD_START)
#define IRQ_BOARD_PMIC_NR	35
#define IRQ_BOARD_FUEL_START	(IRQ_BOARD_PMIC_START + IRQ_BOARD_PMIC_NR)
#define IRQ_BOARD_FUEL_NR	10
#define IRQ_BOARD_CODEC_START	(IRQ_BOARD_FUEL_START + IRQ_BOARD_FUEL_NR)
#define IRQ_BOARD_CODEC_NR	32
#define IRQ_NR_BOARD		(IRQ_BOARD_PMIC_NR + IRQ_BOARD_FUEL_NR \
				 + IRQ_BOARD_CODEC_NR)
#else
#define IRQ_NR_BOARD		40
#endif

/* Set the default NR_IRQS */
#define NR_IRQS			(IRQ_GPIO_END + IRQ_NR_BOARD)

#endif /* __ASM_ARCH_IRQS_EXYNOS4_H */
