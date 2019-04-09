/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * License terms: GNU General Public License (GPL) version 2
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/string.h>

#include <asm/mach-types.h>
#include <plat/pincfg.h>
#include <plat/gpio-nomadik.h>
#include <linux/mfd/abx500/ab8500-gpio.h>

#include <mach/hardware.h>
#include <mach/suspend.h>

#include "pins-db8500.h"
#include "pins.h"

#include "board-pins-sleep-force.h"

#include <linux/workqueue.h>
#include <mach/board-sec-ux500.h>
#include "board-skomer-regulators.h"

/*
* Configuration of pins, pull resisitors states
*/
static pin_cfg_t skomer_bringup_pins[] = {
	/* GBF UART */
	/* uart-0 pins gpio configuration should be
	 * kept intact to prevent glitch in tx line
	 * when tty dev is opened. Later these pins
	 * are configured to uart skomer_bringup_pins_uart0
	 *
	 * It will be replaced with uart configuration
	 * once the issue is solved.
	 */
	GPIO0_GPIO		| PIN_INPUT_PULLUP,
	GPIO1_GPIO		| PIN_OUTPUT_HIGH,
	GPIO2_GPIO		| PIN_INPUT_PULLUP,
	GPIO3_GPIO		| PIN_OUTPUT_HIGH,

	GPIO4_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO5_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO6_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO7_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	/* I2C Camera */
	GPIO8_I2C2_SDA,
	GPIO9_I2C2_SCL,

	GPIO10_GPIO		| PIN_INPUT_NOPULL,	/* Accel I2C */
	GPIO11_GPIO		| PIN_INPUT_NOPULL,	/* Accel I2C */

	/* MSP0 (BT) */
	GPIO12_MSP0_TXD,
	GPIO13_MSP0_TFS,
	GPIO14_MSP0_TCK,
	GPIO15_MSP0_RXD,

	GPIO16_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO17_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO18_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO19_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO20_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	/* Debug/Console UART */
	GPIO29_U2_RXD	| PIN_INPUT_PULLUP,
	GPIO30_U2_TXD	| PIN_OUTPUT_HIGH,

	GPIO31_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO32_GPIO		| PIN_INPUT_PULLDOWN,	/* NFC_IRQ */

	/* MSP AB8500 */
	GPIO33_MSP1_TXD,
	GPIO34_MSP1_TFS,
	GPIO35_MSP1_TCK,
	GPIO36_MSP1_RXD,

	GPIO64_GPIO		| PIN_OUTPUT_LOW,	/* VT_CAM_STBY */
	GPIO65_GPIO		| PIN_OUTPUT_LOW,	/* RST_VT_CAM */
	GPIO66_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO67_GPIO		| PIN_INPUT_PULLUP,	/* VOL_UP */
	GPIO68_LCD_VSI0,				/* TE */
	GPIO69_GPIO		| PIN_OUTPUT_HIGH,	/* LCD_BL_CTRL */
	GPIO70_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO71_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO72_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO73_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO74_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO75_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO76_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO77_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO78_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO79_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO80_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO81_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO82_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO83_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO84_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO85_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	GPIO86_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO87_GPIO		| PIN_OUTPUT_LOW,	/* TXS0206-29_EN */
	GPIO88_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO89_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO90_GPIO		| PIN_INPUT_PULLDOWN,	/* SERVICE_AB8505 (OPEN) */

	GPIO91_GPIO		| PIN_INPUT_PULLUP,	/* HOME_KEY */
	GPIO92_GPIO		| PIN_INPUT_PULLUP,	/* VOL_DOWN */
	GPIO93_GPIO		| PIN_INPUT_NOPULL,	/* OLED_DETECT */
	GPIO94_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO95_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO96_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO97_GPIO		| PIN_INPUT_NOPULL,	/* BT_HOST_WAKE */

	/* MMC2 (eMMC) */
	GPIO128_MC2_CLK		| PIN_OUTPUT_LOW,
	GPIO129_MC2_CMD		| PIN_INPUT_PULLUP,
	GPIO130_GPIO			| PIN_INPUT_PULLDOWN, /* NC */
	GPIO131_MC2_DAT0	| PIN_INPUT_PULLUP,
	GPIO132_MC2_DAT1	| PIN_INPUT_PULLUP,
	GPIO133_MC2_DAT2	| PIN_INPUT_PULLUP,
	GPIO134_MC2_DAT3	| PIN_INPUT_PULLUP,
	GPIO135_MC2_DAT4	| PIN_INPUT_PULLUP,
	GPIO136_MC2_DAT5	| PIN_INPUT_PULLUP,
	GPIO137_MC2_DAT6	| PIN_INPUT_PULLUP,
	GPIO138_MC2_DAT7	| PIN_INPUT_PULLUP,

	GPIO139_GPIO		| PIN_OUTPUT_HIGH,	/* MIPI_DSI0_RESET_N */
	GPIO140_GPIO		| PIN_OUTPUT_LOW,	/* CAM_FLASH_EN */
	GPIO141_GPIO		| PIN_OUTPUT_LOW,	/* CAM_FLASH_MODE */
	GPIO142_GPIO		| PIN_OUTPUT_LOW,	/* 5M_CAM_STBY */
	GPIO143_GPIO		| PIN_INPUT_NOPULL,	/* SUBPMU_SCL */
	GPIO144_GPIO		| PIN_INPUT_NOPULL,	/* SUBPMU_SDA */

	GPIO145_GPIO		| PIN_OUTPUT_LOW,	/* SUBPMU_PWRON */
	GPIO146_GPIO		| PIN_INPUT_NOPULL,	/* PS_INT */

	GPIO149_GPIO		| PIN_OUTPUT_LOW,	/* RST_5M_CAM */
	GPIO150_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	GPIO151_GPIO		| PIN_INPUT_PULLDOWN,	/* COMP_SCL */
	GPIO152_GPIO		| PIN_INPUT_PULLDOWN,	/* COMP_SDA */
	GPIO153_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO154_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO155_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO156_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO157_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO158_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO159_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO160_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO161_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO162_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO163_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO164_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO165_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO166_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO167_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO168_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO169_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO170_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO171_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	GPIO192_GPIO		| PIN_INPUT_PULLUP,	/* KEY_CAMERA_H */
	GPIO193_GPIO		| PIN_INPUT_PULLUP,	/* KEY_CAMERA_F */
	GPIO194_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO195_GPIO		| PIN_OUTPUT_LOW,	/* MOT_EN */
	GPIO196_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO197_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO198_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO199_GPIO		| PIN_OUTPUT_LOW,	/* BT_WAKE */
	GPIO200_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO201_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO202_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO203_GPIO		| PIN_INPUT_PULLUP,	/* SMD_ON */
	GPIO204_GPIO		| PIN_INPUT_PULLUP,	/* MENU_KEY */
	GPIO205_GPIO		| PIN_INPUT_PULLUP,	/* BACK_KEY */
	GPIO206_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO207_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */

	GPIO209_GPIO		| PIN_OUTPUT_HIGH,	/* GBF_RESET_N */

	/* SDI1 (SDIO) WLAN */
	GPIO208_MC1_CLK		| PIN_OUTPUT_LOW,	/* WLAN_SDIO_CLK */
	GPIO210_MC1_CMD		| PIN_INPUT_PULLUP,	/* WLAN_SDIO_CMD */
	GPIO211_MC1_DAT0	| PIN_INPUT_PULLUP,	/* WLAN_SDIO_DATA0 */
	GPIO212_MC1_DAT1	| PIN_INPUT_PULLUP,	/* WLAN_SDIO_DATA1 */
	GPIO213_MC1_DAT2	| PIN_INPUT_PULLUP,	/* WLAN_SDIO_DATA2 */
	GPIO214_MC1_DAT3	| PIN_INPUT_PULLUP,	/* WLAN_SDIO_DATA3 */

	GPIO215_GPIO		| PIN_OUTPUT_LOW,	/* WLAN_RST_N */
	GPIO216_GPIO		| PIN_INPUT_PULLDOWN,	/* WL_HOST_WAKE */
	GPIO217_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO218_GPIO		| PIN_INPUT_NOPULL,	/* TSP_INT */
	GPIO219_GPIO		| PIN_INPUT_PULLDOWN, /* NC */
	GPIO220_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO221_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO222_GPIO		| PIN_OUTPUT_LOW,	/* BT_VREG_EN */
	GPIO223_GPIO		| PIN_OUTPUT_HIGH,	/* MEM_LDO_EN */
	GPIO224_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO225_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO226_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO227_GPIO		| PIN_INPUT_PULLDOWN,	/* NC */
	GPIO228_GPIO		| PIN_OUTPUT_LOW,	/* CAM_MCLK */
	GPIO229_GPIO		| PIN_INPUT_NOPULL, /* TSP_SDA_1V8 */
	GPIO230_GPIO		| PIN_INPUT_NOPULL, /* TSP_SCL_1V8 */
};

static pin_cfg_t skomer_rev05_pins[] = {
	GPIO86_GPIO		| PIN_OUTPUT_LOW,	/* GPS_ON_OFF */
};

/* STM trace or SD Card pin configurations */
static pin_cfg_t skomer_bringup_ape_trace[] = {
	GPIO22_GPIO | PIN_INPUT_NOPULL,	/* CLK-f */

	PIN_CFG(23, ALT_C),	/* APE CLK */
	PIN_CFG(25, ALT_C),	/* APE DAT0 */
	PIN_CFG(26, ALT_C),	/* APE DAT1 */
	PIN_CFG(27, ALT_C),	/* APE DAT2 */
	PIN_CFG(28, ALT_C),	/* APE DAT3 */
};

static pin_cfg_t skomer_bringup_modem_trace[] = {
	GPIO22_GPIO | PIN_INPUT_NOPULL, /* CLK-f */
	GPIO23_STMMOD_CLK | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP,	/* STM CLK */
	GPIO24_UARTMOD_RXD | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP, /* STM UART RXD */
	GPIO25_STMMOD_DAT0 | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP, /* STM DAT0 */
	GPIO26_STMMOD_DAT1 | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP, /* STM DAT0 */
	GPIO27_STMMOD_DAT2 | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP, /* STM DAT0 */
	GPIO28_STMMOD_DAT3 | PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP, /* STM DAT0 */

	GPIO87_GPIO | PIN_OUTPUT_HIGH,  /* TXS0206-29_EN */
};

static pin_cfg_t skomer_bringup_fidobox_trace[] = {
	/* UARTMOD for FIDO box */
	GPIO153_U2_RXD,
	GPIO154_U2_TXD,
	/* STMMOD for FIDO box */
	GPIO155_STMAPE_CLK,
	GPIO156_STMAPE_DAT3,
	GPIO157_STMAPE_DAT2,
	GPIO158_STMAPE_DAT1,
	GPIO159_STMAPE_DAT0,
};

static pin_cfg_t skomer_bringup_sdmmc[] = {
	/* MMC0 (MicroSD card) */
	GPIO22_MC0_FBCLK	| PIN_INPUT_NOPULL,
	GPIO23_MC0_CLK		| PIN_OUTPUT_LOW,
	GPIO24_MC0_CMD		| PIN_INPUT_PULLUP,
	GPIO25_MC0_DAT0		| PIN_INPUT_PULLUP,
	GPIO26_MC0_DAT1		| PIN_INPUT_PULLUP,
	GPIO27_MC0_DAT2		| PIN_INPUT_PULLUP,
	GPIO28_MC0_DAT3		| PIN_INPUT_PULLUP,
};


/*
 * Pins disabled when not used to save power
 */

	/* Proximity & Light Sensor I2C */
static UX500_PINS(skomer_bringup_i2c0,
	GPIO147_I2C0_SCL |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO148_I2C0_SDA |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
);

	/* TSU6111(micro-USB switch  */
static UX500_PINS(skomer_bringup_i2c1,
	GPIO16_I2C1_SCL |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO17_I2C1_SDA |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
);

	/* MAIN & VT CAMERA I2C */
static UX500_PINS(skomer_bringup_i2c2,
	GPIO8_I2C2_SDA |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO9_I2C2_SCL |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
);

	/* Touchscreen I2C */
static UX500_PINS(skomer_bringup_i2c3,
	GPIO229_I2C3_SDA |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO230_I2C3_SCL |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
);

static UX500_PINS(skomer_bringup_mcde_dpi,
	/* DPI LCD RGB I/F */
);

/* USB */
static UX500_PINS(skomer_pins_usb,
	GPIO256_USB_NXT,
	GPIO257_USB_STP		| PIN_OUTPUT_HIGH,
	GPIO258_USB_XCLK,
	GPIO259_USB_DIR,
	GPIO260_USB_DAT7,
	GPIO261_USB_DAT6,
	GPIO262_USB_DAT5,
	GPIO263_USB_DAT4,
	GPIO264_USB_DAT3,
	GPIO265_USB_DAT2,
	GPIO266_USB_DAT1,
	GPIO267_USB_DAT0,
);

static UX500_PINS(skomer_pins_uart0,
	GPIO0_U0_CTSn	| PIN_INPUT_PULLUP |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO1_U0_RTSn	| PIN_OUTPUT_HIGH |
		PIN_SLPM_GPIO | PIN_SLPM_OUTPUT_HIGH,
	GPIO2_U0_RXD	| PIN_INPUT_PULLUP |
		PIN_SLPM_GPIO | PIN_SLPM_INPUT_NOPULL,
	GPIO3_U0_TXD	| PIN_OUTPUT_HIGH |
		PIN_SLPM_GPIO | PIN_SLPM_OUTPUT_HIGH,
);

static struct ux500_pin_lookup skomer_bringup_lookup_pins[] = {
	PIN_LOOKUP("mcde-dpi", &skomer_bringup_mcde_dpi),
	PIN_LOOKUP("nmk-i2c.0", &skomer_bringup_i2c0),
	//PIN_LOOKUP("nmk-i2c.1", &skomer_bringup_i2c1), // 16, 17, N/C
	PIN_LOOKUP("nmk-i2c.2", &skomer_bringup_i2c2),
	//PIN_LOOKUP("nmk-i2c.3", &skomer_bringup_i2c3),
	PIN_LOOKUP("musb-ux500.0", &skomer_pins_usb),
	PIN_LOOKUP("ab-iddet.0", &skomer_pins_usb),
	PIN_LOOKUP("uart0", &skomer_pins_uart0),
};

static pin_cfg_t skomer_gps_uart_pins[] = {
	GPIO4_U1_RXD | PIN_INPUT_PULLUP,
	GPIO5_U1_TXD | PIN_OUTPUT_HIGH,
	GPIO6_U1_CTSn | PIN_INPUT_PULLUP,
	GPIO7_U1_RTSn | PIN_OUTPUT_HIGH,
};

static void __init gps_pins_init(void)
{
	gps_dev = device_create(sec_class, NULL, 0, NULL, "gps");
	if (!gps_dev)
		pr_err("Failed to create device(gps)!\n");

	BUG_ON(!gps_dev);

#ifdef CONFIG_DEBUG_PRINTK
	printk("gps_pins_init!!\n");
#else
	;
#endif

	nmk_config_pins(skomer_gps_uart_pins,
		ARRAY_SIZE(skomer_gps_uart_pins));

	gpio_request(GPS_RST_N_SKOMER_BRINGUP, "GPS_nRST");
	gpio_direction_output(GPS_RST_N_SKOMER_BRINGUP, 1);
	gpio_request(GPS_ON_OFF_SKOMER_BRINGUP, "GPS_ON_OFF");
	gpio_direction_output(GPS_ON_OFF_SKOMER_BRINGUP, 0);

	gpio_export(GPS_RST_N_SKOMER_BRINGUP, 1);
	gpio_export(GPS_ON_OFF_SKOMER_BRINGUP, 1);

	gpio_export_link(gps_dev, "GPS_nRST", GPS_RST_N_SKOMER_BRINGUP);
	gpio_export_link(gps_dev, "GPS_ON_OFF", GPS_ON_OFF_SKOMER_BRINGUP);

#ifdef CONFIG_DEBUG_PRINTK
	printk("gps_pins_init done!!\n");
#else
	;
#endif
}

static void __init sdmmc_pins_init(void)
{
	u32 value;
	const void *prcm_gpiocr = __io_address(U8500_PRCMU_BASE) + 0x138;

	if (sec_debug_settings & SEC_DBG_STM_APE_OPT) {

		/* Set GPIO ALT to C3 */
		value = readl(prcm_gpiocr);
		value |= 0x00000200;	/* Set bit 9 */
		writel(value, prcm_gpiocr);

		nmk_config_pins(skomer_bringup_ape_trace,
			ARRAY_SIZE(skomer_bringup_ape_trace));

		/* also need to ensure VAUX3 turned on (defaults to 2.91V) */
		skomer_ab8500_regulators[AB8500_LDO_AUX3].constraints.valid_ops_mask = 0;
		skomer_ab8500_regulators[AB8500_LDO_AUX3].constraints.always_on = 1;
		skomer_ab8505_regulators[AB9540_LDO_AUX3].constraints.valid_ops_mask = 0;
		skomer_ab8505_regulators[AB9540_LDO_AUX3].constraints.always_on = 1;

#ifdef CONFIG_DEBUG_PRINTK
		printk(KERN_INFO "SD Card I/F set for STM APE Trace\n");
#else
		;
#endif

	} else if (sec_debug_settings & SEC_DBG_STM_MODEM_OPT) {

		/* Set GPIO ALT to B */
		value = readl(prcm_gpiocr);
		value &= ~0x00002202; /* For UART_MOD */
		writel(value, prcm_gpiocr);

		nmk_config_pins(skomer_bringup_modem_trace,
			ARRAY_SIZE(skomer_bringup_modem_trace));

		/* also need to ensure VAUX3 turned on (defaults to 2.91V) */
		skomer_ab8500_regulators[AB8500_LDO_AUX3].constraints.valid_ops_mask = 0;
		skomer_ab8500_regulators[AB8500_LDO_AUX3].constraints.always_on = 1;
		skomer_ab8505_regulators[AB9540_LDO_AUX3].constraints.valid_ops_mask = 0;
		skomer_ab8505_regulators[AB9540_LDO_AUX3].constraints.always_on = 1;

#ifdef CONFIG_DEBUG_PRINTK
		printk(KERN_INFO "SD Card I/F set for STM Modem Trace\n");
#else
		;
#endif
	} else if (sec_debug_settings & SEC_DBG_STM_FIDO_OPT) {

		value = readl(prcm_gpiocr);
		value |= 0x00002002;
		writel(value, prcm_gpiocr);

		nmk_config_pins(skomer_bringup_fidobox_trace,
			ARRAY_SIZE(skomer_bringup_fidobox_trace));

#ifdef CONFIG_DEBUG_PRINTK
		printk(KERN_INFO "XTI I/F set for STM Fidobox Trace\n");
#else
		;
#endif
	} else {
		/* Set GPIO ALT to A */
		value = readl(prcm_gpiocr);
		value &= ~0x00000200; /* clear bit 9 */
		writel(value, prcm_gpiocr);

		nmk_config_pins(skomer_bringup_sdmmc,
			ARRAY_SIZE(skomer_bringup_sdmmc));
	}
}

static pin_cfg_t skomer_bringup_power_save_bank0[] = {
	GPIO0_GPIO | PIN_INPUT_PULLUP,	/* GBF_UART_CTS */
	GPIO1_GPIO | PIN_OUTPUT_HIGH,	/* GBF_UART_RTSn */
	GPIO2_GPIO | PIN_INPUT_PULLUP,	/* GBF_UART_RXD */
	GPIO3_GPIO | PIN_OUTPUT_LOW,	/* GBF_UART_TXD */

	GPIO4_GPIO | PIN_INPUT_PULLUP,	/* GPS_UART_RXD */
	GPIO5_GPIO | PIN_OUTPUT_HIGH,	/* GPS_UART_TXD */
	GPIO6_GPIO | PIN_INPUT_PULLUP,	/* GPS_UART_CTS */
	GPIO7_GPIO | PIN_OUTPUT_HIGH,	/* GPS_UART_RTS */

	GPIO8_GPIO | PIN_INPUT_PULLDOWN,	/* CAM_I2C_SDA */
	GPIO9_GPIO | PIN_INPUT_PULLDOWN,	/* CAM_I2C_SCL */
	GPIO10_GPIO | PIN_INPUT_NOPULL,	/* SENSOR_I2C_SDA */
	GPIO11_GPIO | PIN_INPUT_NOPULL,	/* SENSOR_I2C_SCL */

	GPIO12_GPIO | PIN_OUTPUT_LOW,	/* GBF_IOM_DOUT */
	GPIO13_GPIO | PIN_OUTPUT_LOW,	/* GBF_IOM_TFS */
	GPIO14_GPIO | PIN_OUTPUT_LOW,	/* GBF_IOM_CLK */
	GPIO15_GPIO | PIN_INPUT_PULLDOWN,	/* GBF_IOM_DIN */

	GPIO16_GPIO | PIN_INPUT_PULLDOWN, /* NC */
	GPIO17_GPIO | PIN_INPUT_PULLDOWN, /* NC */
	GPIO18_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO19_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO20_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO21_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	/* SD/MMC card pins handled in seperate table (GPIO 22-28) */

	GPIO29_GPIO | PIN_INPUT_PULLUP,	/* IF_RXD */
	GPIO30_GPIO | PIN_OUTPUT_HIGH,	/* IF_TXD */
	GPIO31_GPIO | PIN_INPUT_PULLDOWN, /* NC */
};

static pin_cfg_t skomer_bringup_sdmmc_sleep[] = {
	/* MMC0 (MicroSD card) */
	GPIO22_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PULL_DOWN,
	GPIO23_GPIO | PIN_SLPM_OUTPUT_LOW |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO24_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO25_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO26_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO27_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO28_GPIO | PIN_SLPM_DIR_INPUT |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
	GPIO87_GPIO | PIN_SLPM_OUTPUT_LOW |
		PIN_SLPM_WAKEUP_ENABLE | PIN_SLPM_PDIS_DISABLED,
};

static pin_cfg_t skomer_common_sleep_table[] = {
	GPIO16_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO17_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO31_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO32_GPIO | PIN_INPUT_PULLDOWN,	/* NFC_IRQ */
	GPIO33_GPIO | PIN_OUTPUT_LOW,
	GPIO34_GPIO | PIN_INPUT_NOPULL,
	GPIO35_GPIO | PIN_INPUT_NOPULL,
	GPIO36_GPIO | PIN_INPUT_NOPULL,

	GPIO64_GPIO | PIN_OUTPUT_LOW,	/* VT_CAM_STBY */
	GPIO65_GPIO | PIN_OUTPUT_LOW,	/* RST_VT_CAM */
	GPIO66_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO67_GPIO | PIN_INPUT_PULLUP,	/* VOL_UP */
	GPIO68_GPIO | PIN_INPUT_NOPULL,	/* FLM */
	GPIO69_GPIO | PIN_OUTPUT_LOW,  /* LCD_BL_CTRL */

	GPIO70_GPIO | PIN_INPUT_PULLDOWN,
	GPIO71_GPIO | PIN_INPUT_PULLDOWN,
	GPIO72_GPIO | PIN_INPUT_PULLDOWN,
	GPIO73_GPIO | PIN_INPUT_PULLDOWN,
	GPIO74_GPIO | PIN_INPUT_PULLDOWN,
	GPIO75_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO76_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO77_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO78_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO79_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO80_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO81_GPIO | PIN_INPUT_PULLDOWN,
	GPIO82_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO83_GPIO | PIN_INPUT_PULLDOWN,
	GPIO84_GPIO | PIN_INPUT_PULLDOWN,
	GPIO85_GPIO | PIN_INPUT_PULLDOWN,
	GPIO86_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	/*GPIO87_GPIO | PIN_OUTPUT_LOW,*/	/* TXS0206-29_EN */
	GPIO88_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO89_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO90_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO91_GPIO | PIN_INPUT_PULLUP,	/* HOME_KEY */
	GPIO92_GPIO | PIN_INPUT_PULLUP,	/* VOL_DOWN */
	GPIO93_GPIO | PIN_INPUT_PULLUP,	/* LCD_DET */
	GPIO94_GPIO | PIN_INPUT_PULLDOWN,
	GPIO95_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO96_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
/*	GPIO97_GPIO | PIN_INPUT_PULLDOWN,*/	/* NC */

/*	GPIO128_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO129_GPIO | PIN_OUTPUT_HIGH, */

	GPIO130_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
/*	GPIO131_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO132_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO133_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO134_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO135_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO136_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO137_GPIO | PIN_OUTPUT_HIGH, */
/*	GPIO138_GPIO | PIN_OUTPUT_HIGH, */
	GPIO139_GPIO | PIN_OUTPUT_LOW,	/* MIPI_DSI0_RESET_N */

	GPIO140_GPIO | PIN_OUTPUT_LOW,	/* CAM_FLASH_EN */
	GPIO141_GPIO | PIN_OUTPUT_LOW,	/* CAM_FLASH_MODE */
	GPIO142_GPIO | PIN_OUTPUT_LOW,	/* 5M_CAM_STBY */
	GPIO143_GPIO | PIN_INPUT_NOPULL,
	GPIO144_GPIO | PIN_INPUT_NOPULL,
	GPIO145_GPIO | PIN_OUTPUT_LOW,	/* SUBPMU_PWRON */
	GPIO146_GPIO | PIN_INPUT_NOPULL,	/* PS_INT */
	GPIO147_GPIO | PIN_INPUT_NOPULL,
	GPIO148_GPIO | PIN_INPUT_NOPULL,
	GPIO149_GPIO | PIN_OUTPUT_LOW,	/* RST_5M_CAM */

	GPIO150_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO151_GPIO | PIN_INPUT_NOPULL,	/* COMP_SCL_1V8 */
	GPIO152_GPIO | PIN_INPUT_NOPULL,	/* COMP_SDA_1V8 */
	GPIO153_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO154_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO155_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO156_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO157_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO158_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO159_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO160_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO161_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO162_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO163_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO164_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO165_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO166_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO167_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO168_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO169_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO170_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO171_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO192_GPIO | PIN_INPUT_PULLUP,	/* KEY_CAMERA_H */
	GPIO193_GPIO | PIN_INPUT_PULLUP,	/* KEY_CAMERA_F */
	GPIO194_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO195_GPIO | PIN_OUTPUT_LOW,	/* MOT_EN */
	GPIO196_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO197_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO198_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
/*	GPIO199_GPIO | PIN_INPUT_PULLDOWN,*//* NC */

	GPIO200_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO201_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO202_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO203_GPIO | PIN_INPUT_PULLUP,	/* SMD_ON */
	GPIO204_GPIO | PIN_INPUT_PULLUP,  /* MENU_KEY */
	GPIO205_GPIO | PIN_INPUT_PULLUP,  /* BACK_KEY */
	GPIO206_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO207_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO208_GPIO | PIN_OUTPUT_LOW,	/* WLAN_SDIO_CLK */
/*	GPIO209_GPIO | PIN_OUTPUT_LOW,*/	/* GBF_RESETN */

	GPIO210_GPIO | PIN_INPUT_PULLUP,
	GPIO211_GPIO | PIN_INPUT_PULLUP,
	GPIO212_GPIO | PIN_INPUT_PULLUP,
	GPIO213_GPIO | PIN_INPUT_PULLUP,
	GPIO214_GPIO | PIN_INPUT_PULLUP,
/*	GPIO215_GPIO | PIN_OUTPUT_LOW,*/	/* WLAN_RST_N */
	GPIO216_GPIO | PIN_INPUT_PULLDOWN,	/* WL_HOST_WAKE */
	GPIO217_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO218_GPIO | PIN_INPUT_PULLUP,  /* TSP_INT_1V8 */
	GPIO219_GPIO | PIN_INPUT_PULLDOWN,	/* NC */

	GPIO220_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO221_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
/*	GPIO222_GPIO | PIN_INPUT_PULLDOWN,*//* NC */
/*	GPIO223_GPIO | PIN_OUTPUT_LOW,*/	/* MEM_LDO_EN */
	GPIO224_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO225_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO226_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
	GPIO227_GPIO | PIN_INPUT_PULLDOWN,
	GPIO228_GPIO | PIN_OUTPUT_LOW,	/* CAM_MCLK */
	GPIO229_GPIO | PIN_INPUT_NOPULL, /* TSP_SDA_1V8 */
	GPIO230_GPIO | PIN_INPUT_NOPULL, /* TSP_SCL_1V8 */

	GPIO256_GPIO | PIN_INPUT_PULLDOWN,
	GPIO257_GPIO | PIN_OUTPUT_HIGH,
	GPIO258_GPIO | PIN_INPUT_PULLDOWN,
	GPIO259_GPIO | PIN_INPUT_PULLDOWN,

	GPIO260_GPIO | PIN_INPUT_PULLDOWN,
	GPIO261_GPIO | PIN_INPUT_PULLDOWN,
	GPIO262_GPIO | PIN_INPUT_PULLDOWN,
	GPIO263_GPIO | PIN_INPUT_PULLDOWN,
	GPIO264_GPIO | PIN_INPUT_PULLDOWN,
	GPIO265_GPIO | PIN_INPUT_PULLDOWN,
	GPIO266_GPIO | PIN_INPUT_PULLDOWN,
	GPIO267_GPIO | PIN_INPUT_PULLDOWN,
};

static pin_cfg_t skomer_rev02_sleep_table[] = {
	GPIO193_GPIO | PIN_INPUT_PULLDOWN,	/* NC */
};

static pin_cfg_t skomer_rev05_sleep_table[] = {
	GPIO86_GPIO		| PIN_OUTPUT_LOW,	/* GPS_ON_OFF */
};

/*
 * This function is called to force gpio power save
 * settings during suspend.
 * This is a temporary solution until all drivers are
 * controlling their pin settings when in inactive mode.
 */
static void skomer_pins_suspend_force(void)
{
	nmk_config_pins(skomer_bringup_power_save_bank0,
			ARRAY_SIZE(skomer_bringup_power_save_bank0));

	if (!(sec_debug_settings &
		(SEC_DBG_STM_APE_OPT | SEC_DBG_STM_MODEM_OPT))) {
		/* not using SD card I/F for modem trace */
		sleep_pins_config_pm(skomer_bringup_sdmmc_sleep,
				ARRAY_SIZE(skomer_bringup_sdmmc_sleep));
	}

	/* Apply sleep gpio setting */
	nmk_config_pins(skomer_common_sleep_table,
			ARRAY_SIZE(skomer_common_sleep_table));

	if (system_rev == SKOMER_R0_2)
		nmk_config_pins(skomer_rev02_sleep_table,
				ARRAY_SIZE(skomer_rev02_sleep_table));
	else if (system_rev >= SKOMER_R0_5)
		nmk_config_pins(skomer_rev05_sleep_table,
				ARRAY_SIZE(skomer_rev05_sleep_table));
}

/*
 * This function is called to force gpio power save
 * mux settings during suspend.
 * This is a temporary solution until all drivers are
 * controlling their pin settings when in inactive mode.
 */
static void skomer_pins_suspend_force_mux(void)
{
	u32 bankaddr;

	/*
	 * Apply GPIO Config for DeepSleep
	 *
	 * Bank0
	 */
	sleep_pins_config_pm_mux(skomer_bringup_power_save_bank0,
				ARRAY_SIZE(skomer_bringup_power_save_bank0));

	if (!(sec_debug_settings &
		(SEC_DBG_STM_APE_OPT | SEC_DBG_STM_MODEM_OPT))) {
		/* not using SD card I/F for modem trace */
		sleep_pins_config_pm_mux(skomer_bringup_sdmmc_sleep,
					ARRAY_SIZE(skomer_bringup_sdmmc_sleep));
	}

	/* Bank1 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK1_BASE);

	writel(0x60000000, bankaddr + NMK_GPIO_AFSLA);
	writel(0x60000000, bankaddr + NMK_GPIO_AFSLB);

	/* Bank2 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK2_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);

	/* Bank3 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK3_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);

	/* Bank4 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK4_BASE);

	/*
	 * Keep MMC2 (eMMC) alt A. Instability otherwise.
	 */
	writel(0x000007FF, bankaddr + NMK_GPIO_AFSLA);
	writel(0x00000000, bankaddr + NMK_GPIO_AFSLB);

	/* Bank5 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK5_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);

	/* Bank6 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK6_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);

	/* Bank7 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK7_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);

	/* Bank8 */
	bankaddr = IO_ADDRESS(U8500_GPIOBANK8_BASE);

	writel(0         , bankaddr + NMK_GPIO_AFSLA);
	writel(0         , bankaddr + NMK_GPIO_AFSLB);
}

void __init ssg_pins_init(void)
{
	nmk_config_pins(skomer_bringup_pins,
		ARRAY_SIZE(skomer_bringup_pins));

	if (system_rev >= SKOMER_R0_5)
		nmk_config_pins(skomer_rev05_pins, ARRAY_SIZE(skomer_rev05_pins));

	ux500_pins_add(skomer_bringup_lookup_pins,
		ARRAY_SIZE(skomer_bringup_lookup_pins));
	gps_pins_init();
	sdmmc_pins_init();
	suspend_set_pins_force_fn(skomer_pins_suspend_force,
				  skomer_pins_suspend_force_mux);
}

int pins_for_u9500(void)
{
	/* required by STE code */
	return 0;
}
