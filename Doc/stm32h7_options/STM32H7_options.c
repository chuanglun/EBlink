typedef struct {       //   Reset      Flash control offset
   un32 FLASH_OPTSR;   //0x1416 AAF0  0x20 (alias 0x120)
   un32 FLASH_BOOT;    //0x1FF0 0800  0x44 (alias 0x144)
   un32 FLASH_PRAR_x1; //0x0000 00FF  0x2C
   un32 FLASH_PRAR_x2; //0x0000 00FF  0x12C
   un32 FLASH_SCAR_x1; //0x8000 00FF  0x34
   un32 FLASH_SCAR_x2; //0x8000 00FF  0x134
   un32 FLASH_WPSN_x1; //0x0000 00FF  0x3C
   un32 FLASH_WPSN_x2; //0x0000 00FF  0x13C
} STM32H7_optionsTp;


static const STM32H7_optionsTp STM32H7_options __attribute__((section(".optionBytes"))) =
{
    0x1416AAF0  | (1<<17),
    0x1FF00800,
    0x000000FF,
    0x000000FF,
    0x800000FF,
    0x800000FF,
    0x000000FF,
    0x000000FF } ;