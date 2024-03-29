#ifndef CTS_PLAT_QCOM_CONFIG_H
#define CTS_PLAT_QCOM_CONFIG_H

#define CONFIG_CTS_PM_FB_NOTIFIER
#ifdef CONFIG_DRM_MSM
#define CFG_CTS_DRM_NOTIFIER
#endif/*CONFIG_DRM_MSM*/

#if !defined(CONFIG_CTS_PM_FB_NOTIFIER)
#if defined(CONFIG_PM_SLEEP) && defined(CONFIG_PM_SUSPEND)
    //#define CONFIG_CTS_PM_GENERIC
#endif /* CONFIG_PM_SLEEP */

#if !defined(CONFIG_CTS_PM_GENERIC)
    #define CONFIG_CTS_PM_LEGACY
#endif
#endif

#define CFG_CTS_MAX_I2C_XFER_SIZE           (48u)

//#define CFG_CTS_SWAP_XY
//#define CFG_CTS_WRAP_X
//#define CFG_CTS_WRAP_Y

#define CFG_CTS_DEVICE_NAME                 "chipone-ts"
#define CFG_CTS_DRIVER_NAME                 "chipone-ts"

#if CFG_CTS_MAX_I2C_XFER_SIZE < 8
#error "I2C transfer size should large than 8"
#endif

#ifdef CONFIG_OF
#define CONFIG_CTS_OF
#endif
#ifdef CONFIG_CTS_OF
#define CFG_CTS_OF_DEVICE_ID_NAME           "chipone-ts"

#define CFG_CTS_OF_INT_GPIO_NAME             "chipone,irq-gpio"
#define CFG_CTS_OF_RST_GPIO_NAME             "chipone,rst-gpio"
#define CFG_CTS_OF_X_RESOLUTION_NAME     "chipone,x-res"
#define CFG_CTS_OF_Y_RESOLUTION_NAME     "chipone,y-res"
#endif /* CONFIG_CTS_OF */

#endif /* CTS_PLAT_QCOM_CONFIG_H */

