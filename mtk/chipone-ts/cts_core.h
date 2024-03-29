#ifndef CTS_CORE_H
#define CTS_CORE_H

#include "cts_config.h"
#include "cts_firmware.h"

/** I2C addresses(7bits), transfer size and bitrate */
#define CTS_NORMAL_MODE_I2CADDR             (0x48)
#define CTS_PROGRAM_MODE_I2CADDR            (0x30)
#define CTS_PROGRAM_MODE_I2CADDR_2        (0x58)
#define CTS_PROGRAM_MODE_I2C_ADDR_WIDTH     (3)

/** Chipone firmware register addresses under normal mode */
enum cts_device_fw_reg {
    CTS_DEVICE_FW_REG_WORK_MODE = 0x0000,
    CTS_DEVICE_FW_REG_DATA_READY = 0x0002,
    CTS_DEVICE_FW_REG_CMD = 0x0004,
    CTS_DEVICE_FW_REG_CHIP_TYPE = 0x000A,
    CTS_DEVICE_FW_REG_VERSION = 0x000C,

    CTS_DEVICE_FW_REG_HW_SENSOR_ID = 0x0010,
    CTS_DEVICE_FW_REG_FW_SENSOR_ID = 0x001E,
    CTS_DEVICE_FW_REG_IS_SENSOR_ID_MATCH = 0x001F,

    CTS_DEVICE_FW_REG_TOUCH_INFO = 0x1000,
    CTS_DEVICE_FW_REG_RAW_DATA = 0x2000,
    CTS_DEVICE_FW_REG_DIFF_DATA = 0x3000,
    CTS_DEVICE_FW_REG_GESTURE_INFO = 0x7000,

    CTS_DEVICE_FW_REG_PANEL_PARAM = 0x8000,
    CTS_DEVICE_FW_REG_X_RESOLUTION = 0x8000,//0x8090,
    CTS_DEVICE_FW_REG_Y_RESOLUTION = 0x8002,//0x8092,
    CTS_DEVICE_FW_REG_NUM_TX = 0x8004,//0x8007,
    CTS_DEVICE_FW_REG_NUM_RX = 0x8005,//0x8008,
    CTS_DEVICE_FW_REG_TX_ORDER = 0x8006,// +27
    CTS_DEVICE_FW_REG_RX_ORDER = (0x8006+27),//+36
    
    CTS_DEVICE_HW_REG_NUM_TX = (0x8000+338),//0x8007,
    CTS_DEVICE_HW_REG_NUM_RX = (0x8000+339),//0x8008,
    
    CTS_DEVICE_FW_REG_DEBUG_INTF = 0xF000,
};

/** Hardware IDs, read from version register */
enum cts_hwid {
    CTS_HWID_ICNT81XX = 0x8b,
    CTS_HWID_ICNT82XX = 0x82,
    CTS_HWID_ICNT85XX = 0x0585,
    CTS_HWID_ICNT86XX = 0x0e85,
    CTS_HWID_ICNT87XX = 0x87,
    CTS_HWID_ICNT88XX = 0x0e85,
    CTS_HWID_ICNT89XX = 0x8900,
    CTS_HWID_ANY = 0,
    CTS_HWID_INVALID = 0xFFFFu,
};

/* Firmware IDs, read from firmware @addrress 0x000A~0x000B under normal mode */
enum cts_fwid {
    CTS_FWID_ICNT81XX = 0x81,
    CTS_FWID_ICNT82XX = 0x82,
    CTS_FWID_ICNT85XX = 0x85,
    CTS_FWID_ICNT86XX = 0x86,
    CTS_FWID_ICNT87XX = 0x87,
    CTS_FWID_ICNT88XX = 0x88,
    CTS_FWID_ICNT89XX = 0x89,
    CTS_FWID_ANY = 0u,
    CTS_FWID_INVALID = 0xFF,
};

/** Commands written to firmware register @ref CTS_DEVICE_FW_REG_CMD under normal mode */
enum cts_firmware_cmd {
    CTS_CMD_RESET = 1,
    CTS_CMD_SUSPEND = 2,
    CTS_CMD_ENTER_WRITE_PARA_TO_FLASH_MODE = 3,
    CTS_CMD_WRITE_PARA_TO_FLASH = 4,
    CTS_CMD_WRTITE_INT_HIGH = 5,
    CTS_CMD_WRTITE_INT_LOW = 6,
    CTS_CMD_RELASE_INT_TEST = 7,
    CTS_CMD_RECOVERY_TX_VOL = 0x10,
    CTS_CMD_DEC_TX_VOL_1 = 0x11,
    CTS_CMD_DEC_TX_VOL_2 = 0x12,
    CTS_CMD_DEC_TX_VOL_3 = 0x13,
    CTS_CMD_DEC_TX_VOL_4 = 0x14,
    CTS_CMD_DEC_TX_VOL_5 = 0x15,
    CTS_CMD_DEC_TX_VOL_6 = 0x16,
    CTS_CMD_ENABLE_READ_RAWDATA = 0x20,
    CTS_CMD_DISABLE_READ_RAWDATA = 0x21,
    CTS_CMD_SUSPEND_WITH_GESTURE = 0x40,
    CTS_CMD_QUIT_GESTURE_MONITOR = 0x41,

};

#pragma pack(1)
/** Touch message read back from chip */
struct cts_device_touch_msg {
    u8      id;
    __le16  x;
    __le16  y;
    u8      pressure;
    u8      event;

#define CTS_DEVICE_TOUCH_EVENT_NONE         (0)
#define CTS_DEVICE_TOUCH_EVENT_DOWN         (1)
#define CTS_DEVICE_TOUCH_EVENT_MOVE         (2)
#define CTS_DEVICE_TOUCH_EVENT_STAY         (3)
#define CTS_DEVICE_TOUCH_EVENT_UP           (4)

};

/** Touch information read back from chip */
struct cts_device_touch_info {
    u8  vkey_state;
    u8  num_msg;

#define CTS_DEVICE_MAX_TOUCH_MSG            (10u)
    struct cts_device_touch_msg msgs[CTS_DEVICE_MAX_TOUCH_MSG];

};

/** Gesture trace point read back from chip */
struct cts_device_gesture_point {
    __le16  x;
    __le16  y;
    u8      pressure;
    u8      event;
};

/** Gesture information read back from chip */
struct cts_device_gesture_info {
    u8    gesture_id;
#define CTS_GESTURE_UP                  (0x11)
#define CTS_GESTURE_C                   (0x12)
#define CTS_GESTURE_O                   (0x13)
#define CTS_GESTURE_M                   (0x14)
#define CTS_GESTURE_W                   (0x15)
#define CTS_GESTURE_E                   (0x16)
#define CTS_GESTURE_S                   (0x17)
#define CTS_GESTURE_B                   (0x18)
#define CTS_GESTURE_T                   (0x19)
#define CTS_GESTURE_H                   (0x1A)
#define CTS_GESTURE_F                   (0x1B)
#define CTS_GESTURE_X                   (0x1C)
#define CTS_GESTURE_Z                   (0x1D)
#define CTS_GESTURE_V                   (0x1E)
#define CTS_GESTURE_D_TAP               (0x50)

    u8  num_points;

#define CTS_CHIP_MAX_GESTURE_TRACE_POINT    (64u)
    struct cts_device_gesture_point points[CTS_CHIP_MAX_GESTURE_TRACE_POINT];

};
#pragma pack()


struct cts_device;

enum cts_crc_type {
    CTS_CRC16 = 1,
    CTS_CRC32 = 2,
};

/** Chip hardware data, will never change */
struct cts_device_hwdata {
    char *name;
    u16 hwid;
    u16 fwid;
    u8  num_row;
    u8  num_col;
    u32 sram_size;

    /* Address width under program mode */
    u8  program_addr_width;
    u8  is_with_flash;
    u16  ver_offset;

//    const struct cts_sfctrl *sfctrl;

};

/** Chip firmware data */
struct cts_device_fwdata {
    u16 version;
    u16 res_x;
    u16 res_y;
    u8  rows;
    u8  cols;

};

/** Chip runtime data */
struct cts_device_rtdata {
    u8   i2c_addr;
    int  addr_width;
    bool program_mode;
    bool is_chip_empty;

    bool suspended;
    bool updating;
    bool testing;
    bool esd_checking;
    bool gesture_wakeup_enabled;
    bool glove_mode_enabled;
    bool proximity_enabled;
};

struct cts_device_confdata {
   
    u8 hw_sensor_id;
    u8 fw_sensor_id;
    u8 is_sensor_matched;
    u8 fw_name_index;
    u8 fw_sensor_id_index;

    u8 prog_i2c_addr;
    // struct cts_device_hwdata   *hwdata;
    //struct cts_device_rtdata     *rtdata;
    struct cts_firmware            firmware;

};

struct cts_device {
    struct cts_platform_data *pdata;

    struct cts_device_hwdata   *hwdata;
    struct cts_device_fwdata          fwdata;
    struct cts_device_rtdata          rtdata;
    struct cts_device_confdata       confdata;
    //const struct cts_flash           *flash;
    bool enabled;

};

struct cts_platform_data;

struct chipone_ts_data {
    struct i2c_client *i2c_client;

    struct cts_device cts_dev;

    struct cts_platform_data *pdata;

    struct workqueue_struct *workqueue;

#ifdef CONFIG_CTS_ESD_PROTECTION
    struct delayed_work esd_work;
    bool                esd_enabled;
    int                 esd_check_fail_cnt;
#endif /* CONFIG_CTS_ESD_PROTECTION */

#ifdef CONFIG_CTS_LEGACY_TOOL
    struct proc_dir_entry *procfs_entry;
#endif /* CONFIG_CTS_LEGACY_TOOL */

};

static inline u32 get_unaligned_le24(const void *p)
{
    const u8 *puc = (const u8 *)p;
    return (puc[0] | (puc[1] << 8) | (puc[2] << 16));
}

static inline u32 get_unaligned_be24(const void *p)
{
    const u8 *puc = (const u8 *)p;
    return (puc[2] | (puc[1] << 8) | (puc[0] << 16));
}

static inline void put_unaligned_be24(u32 v, void *p)
{
    u8 *puc = (u8 *)p;
    
    puc[0] = (v >> 16) & 0xFF;
    puc[1] = (v >> 8 ) & 0xFF;
    puc[2] = (v >> 0 ) & 0xFF;
}

#define wrap(max,x)        ((max) - 1 - (x))

extern void cts_lock_device(const struct cts_device *cts_dev);
extern void cts_unlock_device(const struct cts_device *cts_dev);

extern int cts_sram_writeb_retry(const struct cts_device *cts_dev,
        u32 addr, u8 b, int retry, int delay);
extern int cts_sram_writew_retry(const struct cts_device *cts_dev,
        u32 addr, u16 w, int retry, int delay);
extern int cts_sram_writel_retry(const struct cts_device *cts_dev,
        u32 addr, u32 l, int retry, int delay);
extern int cts_sram_writesb_retry(const struct cts_device *cts_dev,
        u32 addr, const void *src, size_t len, int retry, int delay);
extern int cts_sram_readb_retry(const struct cts_device *cts_dev,
        u32 addr, u8 *b, int retry, int delay);
extern int cts_sram_readw_retry(const struct cts_device *cts_dev,
        u32 addr, u16 *w, int retry, int delay);
extern int cts_sram_readl_retry(const struct cts_device *cts_dev,
        u32 addr, u32 *l, int retry, int delay);
extern int cts_sram_readsb_retry(const struct cts_device *cts_dev,
        u32 addr, void *dst, size_t len, int retry, int delay);

extern int cts_fw_reg_writeb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u8 b, int retry, int delay);
extern int cts_fw_reg_writew_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u16 w, int retry, int delay);
extern int cts_fw_reg_writel_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u32 l, int retry, int delay);
extern int cts_fw_reg_writesb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, const void *src, size_t len, int retry, int delay);

extern int cts_fw_reg_readb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u8 *b, int retry, int delay);
extern int cts_fw_reg_readw_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u16 *w, int retry, int delay);
extern int cts_fw_reg_readl_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u32 *l, int retry, int delay);
extern int cts_fw_reg_readsb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, void *dst, size_t len, int retry, int delay);

extern int cts_hw_reg_writeb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u8 b, int retry, int delay);
extern int cts_hw_reg_writew_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u16 w, int retry, int delay);
extern int cts_hw_reg_writel_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u32 l, int retry, int delay);
extern int cts_hw_reg_writesb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, const void *src, size_t len, int retry, int delay);

extern int cts_hw_reg_readb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u8 *b, int retry, int delay);
extern int cts_hw_reg_readw_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u16 *w, int retry, int delay);
extern int cts_hw_reg_readl_retry(const struct cts_device *cts_dev,
        u32 reg_addr, u32 *l, int retry, int delay);
extern int cts_hw_reg_readsb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, void *dst, size_t len, int retry, int delay);

extern int cts_prog_writesb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, const void *src, size_t len);
extern int cts_prog_readsb_retry(const struct cts_device *cts_dev,
        u32 reg_addr, void *dst, size_t len);
extern int  icn85xx_prog_i2c_txdata(const struct cts_device *cts_dev,
	u32 addr, u8 *txdata, size_t length);
extern int  icn85xx_prog_i2c_rxdata(const struct cts_device *cts_dev,
	u32 addr, u8 *txdata, size_t length);
extern int  icn87xx_prog_i2c_txdata( struct cts_device *cts_dev,
	u32 addr, u8 *txdata, size_t length);
extern int  icn87xx_prog_i2c_rxdata( struct cts_device *cts_dev,
	u32 addr, u8 *txdata, size_t length);


static inline int cts_fw_reg_writeb(const struct cts_device *cts_dev, u32 reg_addr, u8 b)
{
    return cts_fw_reg_writeb_retry(cts_dev, reg_addr, b, 1, 0);
}

static inline int cts_fw_reg_writew(const struct cts_device *cts_dev, u32 reg_addr, u16 w)
{
    return cts_fw_reg_writew_retry(cts_dev, reg_addr, w, 1, 0);
}

static inline int cts_fw_reg_writel(const struct cts_device *cts_dev, u32 reg_addr, u32 l)
{
    return cts_fw_reg_writel_retry(cts_dev, reg_addr, l, 1, 0);
}

static inline int cts_fw_reg_writesb(const struct cts_device *cts_dev, u32 reg_addr,
        const void *src, size_t len)
{
    return cts_fw_reg_writesb_retry(cts_dev, reg_addr, src, len, 1, 0);
}

static inline int cts_fw_reg_readb(const struct cts_device *cts_dev, u32 reg_addr, u8 *b)
{
    return cts_fw_reg_readb_retry(cts_dev, reg_addr, b, 1, 0);
}

static inline int cts_fw_reg_readw(const struct cts_device *cts_dev, u32 reg_addr, u16 *w)
{
    return cts_fw_reg_readw_retry(cts_dev, reg_addr, w, 1, 0);
}

static inline int cts_fw_reg_readl(const struct cts_device *cts_dev, u32 reg_addr, u32 *l)
{
    return cts_fw_reg_readl_retry(cts_dev, reg_addr, l, 1, 0);
}

static inline int cts_fw_reg_readsb(const struct cts_device *cts_dev,
        u32 reg_addr, void *dst, size_t len)
{
    return cts_fw_reg_readsb_retry(cts_dev, reg_addr, dst, len, 1, 0);
}

static inline int cts_hw_reg_writeb(const struct cts_device *cts_dev, u32 reg_addr, u8 b)
{
    return cts_hw_reg_writeb_retry(cts_dev, reg_addr, b, 1, 0);
}

static inline int cts_hw_reg_writew(const struct cts_device *cts_dev, u32 reg_addr, u16 w)
{
    return cts_hw_reg_writew_retry(cts_dev, reg_addr, w, 1, 0);
}

static inline int cts_hw_reg_writel(const struct cts_device *cts_dev, u32 reg_addr, u32 l)
{
    return cts_hw_reg_writel_retry(cts_dev, reg_addr, l, 1, 0);
}

static inline int cts_hw_reg_writesb(const struct cts_device *cts_dev, u32 reg_addr,
        const void *src, size_t len)
{
    return cts_hw_reg_writesb_retry(cts_dev, reg_addr, src, len, 1, 0);
}

static inline int cts_hw_reg_readb(const struct cts_device *cts_dev, u32 reg_addr, u8 *b)
{
    return cts_hw_reg_readb_retry(cts_dev, reg_addr, b, 1, 0);
}

static inline int cts_hw_reg_readw(const struct cts_device *cts_dev, u32 reg_addr, u16 *w)
{
    return cts_hw_reg_readw_retry(cts_dev, reg_addr, w, 1, 0);
}

static inline int cts_hw_reg_readl(const struct cts_device *cts_dev, u32 reg_addr, u32 *l)
{
    return cts_hw_reg_readl_retry(cts_dev, reg_addr, l, 1, 0);
}

static inline int cts_hw_reg_readsb(const struct cts_device *cts_dev,
        u32 reg_addr, void *dst, size_t len)
{
    return cts_hw_reg_readsb_retry(cts_dev, reg_addr, dst, len, 1, 0);
}

static inline int cts_sram_writeb(const struct cts_device *cts_dev, u32 addr, u8 b)
{
    return cts_sram_writeb_retry(cts_dev, addr, b, 1, 0);
}

static inline int cts_sram_writew(const struct cts_device *cts_dev, u32 addr, u16 w)
{
    return cts_sram_writew_retry(cts_dev, addr, w, 1, 0);
}

static inline int cts_sram_writel(const struct cts_device *cts_dev, u32 addr, u32 l)
{
    return cts_sram_writel_retry(cts_dev, addr, l, 1, 0);
}

static inline int cts_sram_writesb(const struct cts_device *cts_dev, u32 addr,
        const void *src, size_t len)
{
    return cts_sram_writesb_retry(cts_dev, addr, src, len, 1, 0);
}

static inline int cts_sram_readb(const struct cts_device *cts_dev, u32 addr, u8 *b)
{
    return cts_sram_readb_retry(cts_dev, addr, b, 1, 0);
}

static inline int cts_sram_readw(const struct cts_device *cts_dev, u32 addr, u16 *w)
{
    return cts_sram_readw_retry(cts_dev, addr, w, 1, 0);
}

static inline int cts_sram_readl(const struct cts_device *cts_dev, u32 addr, u32 *l)
{
    return cts_sram_readl_retry(cts_dev, addr, l, 1, 0);
}

static inline int cts_sram_readsb(const struct cts_device *cts_dev,
        u32 addr, void *dst, size_t len)
{
    return cts_sram_readsb_retry(cts_dev, addr, dst, len, 1, 0);
}

extern u8 cts_get_program_i2c_addr(struct cts_device *cts_dev);

extern int cts_irq_handler(struct cts_device *cts_dev);

extern bool cts_is_device_suspended(const struct cts_device *cts_dev);
extern int cts_suspend_device(struct cts_device *cts_dev);
extern int cts_resume_device(struct cts_device *cts_dev);

extern bool cts_is_device_program_mode(const struct cts_device *cts_dev);
extern int cts_enter_program_mode(struct cts_device *cts_dev);
extern int cts_enter_normal_mode(struct cts_device *cts_dev);

extern int  cts_probe_device(struct cts_device *cts_dev);
extern int cts_set_work_mode(const struct cts_device *cts_dev, u8 mode);
extern int cts_get_work_mode(const struct cts_device *cts_dev, u8 *mode);
extern int cts_get_firmware_version(const struct cts_device *cts_dev, u16 *version);
extern int cts_get_data_ready_flag(const struct cts_device *cts_dev, u8 *flag);
extern int cts_clr_data_ready_flag(const struct cts_device *cts_dev);
extern int  cts_send_command(const struct cts_device *cts_dev, u8 cmd);
extern int  cts_get_panel_param(const struct cts_device *cts_dev,
        void *param, size_t size);
extern int cts_set_panel_param(const struct cts_device *cts_dev,
        const void *param, size_t size);
extern int cts_get_x_resolution(const struct cts_device *cts_dev, u16 *resolution);
extern int cts_get_y_resolution(const struct cts_device *cts_dev, u16 *resolution);
extern int cts_get_num_rows(const struct cts_device *cts_dev, u8 *num_rows);
extern int cts_get_num_cols(const struct cts_device *cts_dev, u8 *num_cols);
extern int  cts_enable_get_rawdata(const struct cts_device *cts_dev);
extern int  cts_disable_get_rawdata(const struct cts_device *cts_dev);
extern int  cts_get_rawdata(const struct cts_device *cts_dev, void *buf);
extern int  cts_get_diffdata(const struct cts_device *cts_dev, void *buf);
extern int  cts_get_fwid(struct cts_device *cts_dev, u16 *fwid);
extern int  cts_get_hwid(struct cts_device *cts_dev, u16 *hwid);
extern int cts_get_para_tx_order(struct cts_device *cts_dev, u8 *tx_order);
extern int cts_get_para_rx_order(struct cts_device *cts_dev, u8 *rx_order);

#ifdef SUPPORT_SENSOR_ID
extern int cts_get_sensor_id_info(struct cts_device *cts_dev);
#endif

#ifdef CONFIG_CTS_GESTURE
extern void cts_enable_gesture_wakeup(struct cts_device *cts_dev);
extern void cts_disable_gesture_wakeup(struct cts_device *cts_dev);
extern bool cts_is_gesture_wakeup_enabled(const struct cts_device *cts_dev);
extern int  cts_get_gesture_info(const struct cts_device *cts_dev,
        void *gesture_info, bool trace_point);
#endif /* CONFIG_CTS_GESTURE */

#ifdef CONFIG_CTS_ESD_PROTECTION
extern void cts_init_esd_protection(struct chipone_ts_data *cts_data);
extern int cts_enable_esd_protection(struct chipone_ts_data *cts_data);
extern int cts_disable_esd_protection(struct chipone_ts_data *cts_data);
extern void cts_deinit_esd_protection(struct chipone_ts_data *cts_data);
#else /* CONFIG_CTS_ESD_PROTECTION */
static inline void cts_init_esd_protection(struct chipone_ts_data *cts_data) {}
static inline int cts_enable_esd_protection(struct chipone_ts_data *cts_data) {return 0;}
static inline int cts_disable_esd_protection(struct chipone_ts_data *cts_data) {return 0;}
static inline void cts_deinit_esd_protection(struct chipone_ts_data *cts_data) {}
#endif /* CONFIG_CTS_ESD_PROTECTION  */

#ifdef CONFIG_CTS_GLOVE
extern int cts_enter_glove_mode(struct cts_device *cts_dev);
extern int cts_exit_glove_mode(struct cts_device *cts_dev);
#else
static inline int cts_enter_glove_mode(struct cts_device *cts_dev) {return 0;}
static inline int cts_exit_glove_mode(struct cts_device *cts_dev) {return 0;}
#endif

#ifdef CONFIG_CTS_LEGACY_TOOL
extern int  cts_tool_init(struct chipone_ts_data *cts_data);
extern void cts_tool_deinit(struct chipone_ts_data *data);
#else /* CONFIG_CTS_LEGACY_TOOL */
static inline int   cts_tool_init(struct chipone_ts_data *cts_data) {return 0;}
static inline void  cts_tool_deinit(struct chipone_ts_data *data) {}
#endif /* CONFIG_CTS_LEGACY_TOOL */

extern bool cts_is_device_enabled(const struct cts_device *cts_dev);
extern int cts_start_device(struct cts_device *cts_dev);
extern int cts_stop_device(struct cts_device *cts_dev);

#endif /* CTS_CORE_H */

