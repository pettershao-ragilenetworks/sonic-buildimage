#ifndef __FIRMWARE_APP_H__
#define __FIRMWARE_APP_H__

#include <sys/ioctl.h>
#include <debug_ispvme.h>

/* Agreement with PKG_MGMT module */
#define ERR_FW_CHECK_CPLD_UPGRADE    (440 - 256)
#define ERR_FW_CHECK_FPGA_UPGRADE    (441 - 256)
#define ERR_FW_DO_CPLD_UPGRADE       (442 - 256)
#define ERR_FW_DO_FPGA_UPGRADE       (443 - 256)
#define ERR_FW_UPGRADE               (444 - 256)

#define FIRMWARE_FAILED              -1
#define FIRMWARE_SUCCESS             0

#define FIRMWARE_ACTION_CHECK        0
#define FIRMWARE_ACTION_UPGRADE      1

#define dbg_print(debug, fmt, arg...)  \
    if (debug == DEBUG_APP_ON || debug == DEBUG_ALL_ON) \
        { do{printf(fmt,##arg);} while(0); }

#define FIRMWARE_FILE_DIR_LEN        128
#define FIRMWARE_NAME_LEN            48
#define FIRMWARE_MAX_SLOT_NUM        32

#define FIRMWARE_CPLD_NAME           "cpld"
#define FIRMWARE_FPGA_NAME           "fpga"

#define FIRMWARE_CPLD_EPM1270F256    "EPM1270F256"
#define FIRMWARE_CPLD_5M1270         "5M1270"
#define FIRMWARE_CPLD_TEST           "test"
#define FIRMWARE_FPGA_TEST           "test"

/* ioctl command */
#define FIRMWARE_TYPE 'F'

#define FIRMWARE_JTAG_TDI                _IOR(FIRMWARE_TYPE, 0, char)
#define FIRMWARE_JTAG_TDO                _IOR(FIRMWARE_TYPE, 1, char)
#define FIRMWARE_JTAG_TCK                _IOR(FIRMWARE_TYPE, 2, char)
#define FIRMWARE_JTAG_TMS                _IOR(FIRMWARE_TYPE, 3, char)
#define FIRMWARE_JTAG_EN                 _IOR(FIRMWARE_TYPE, 4, char)
#define FIRMWARE_SET_DEBUG_ON            _IOW(FIRMWARE_TYPE, 5, int)     /* debug on */
#define FIRMWARE_SET_DEBUG_OFF           _IOW(FIRMWARE_TYPE, 6, int)     /* debug off */
#define FIRMWARE_SET_GPIO_INFO           _IOR(FIRMWARE_TYPE, 7, int)     /* GPIO info */

#define FIRMWARE_MAX_SUB_SLOT_NUM    (8)
#define FIRMWARE_MAX_CARD_SLOT_NUM   ((FIRMWARE_MAX_SUB_SLOT_NUM) + (1))/* max slot num */
#define FIRMWARE_CARD_NAME_MAX_LEN      (64)
#define GPIO(p, v, d) {  \
                   .pin = p,  \
                   .val = v,  \
                   .dir = d, \
              }, 

enum firmware_type_s {
    FIRMWARE_CPLD = 0,
    FIRMWARE_FPGA,
    FIRMWARE_OTHER,
};

typedef struct name_info_s {
    char card_name[FIRMWARE_NAME_LEN];    /* card name */
    int type;                             /* upgrade file type */
    int slot;                             /* slot number correspoding to upgrade file  */
    char chip_name[FIRMWARE_NAME_LEN];    /* chip name */
    char version[FIRMWARE_NAME_LEN];      /* version */
} name_info_t;

typedef struct cmd_info_s {
    int size;
    void *data;
} cmd_info_t;

typedef struct gpio_group_s {
    int pin;
    int val;
    int dir;
} gpio_group_t;

typedef struct firmware_upg_gpio_info_s {
    int tdi;
    int tck;
    int tms;
    int tdo;
    int jtag_en;
	int select;
    gpio_group_t jtag_5;
    gpio_group_t jtag_4;
    gpio_group_t jtag_3;
    gpio_group_t jtag_2;
    gpio_group_t jtag_1;
} firmware_upg_gpio_info_t;

typedef struct firmware_card_info_s {
    int dev_type;                          /* the type of card */
	int slot_num;
	char card_name[FIRMWARE_CARD_NAME_MAX_LEN]; 
    firmware_upg_gpio_info_t gpio_info[FIRMWARE_MAX_CARD_SLOT_NUM];                        /* private data */
} firmware_card_info_t;

typedef enum card_type_e {
    B6510_48VS8CQ  = 0x4040,
    B6520_64CQ     = 0x4041,
    B6930_32CDQ2XS = 0x4043,
    B6920_4C       = 0x4044,
    AS13_48F8H     = 0x4050,
    AS13_32H       = 0x4051,
    AS23_128H      = 0x4052,
    AS14_128H      = 0x4057,
    B6510_32CQ     = 0x4058,
    AS14_32D       = 0x4060,
    BT2575         = 0x4061,
    BC10072        = 0x4062,
    AS14_40D       = 0X4063,
    AS24_128D      = 0x4064,
    AS61_48E4T     = 0X4065,
    AS61_48X4T     = 0X4066,
    AC51_48C2G     = 0x4075,
    TCS81_100F     = 0x4071,
    TCS83_100F     = 0x4072,
    TCS82_100F     = 0x4073,
    B6920_4C_V2    = 0x4076,
    BS100R0        = 0x4048,
    AS61_48E4T_LC  = 0x4087,
    AS61_48E4T_LD  = 0x4088,
} card_type_t;	

extern firmware_card_info_t* firmware_get_card_info(int dev_type);
extern int dfd_fpga_upgrade_do_upgrade(char* upg_file);
extern int dfd_fpga_upgrade_test(void);
extern int ispvme_test(void);
extern int ispvme_main(int argc, char *argv[]);
/* External fpga dump interface */
extern int dfd_fpga_upgrade_dump_flash(int argc, char* argv[]);




#endif /* End of __FIRMWARE_APP_H__ */
