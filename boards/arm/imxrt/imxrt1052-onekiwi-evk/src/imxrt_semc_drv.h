#ifndef __IMXRT_SEMC_DRV_H
#define __IMXRT_SEMC_DRV_H

#include <stdint.h>
#include <stdbool.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

//#define getreg32(a)    (*(volatile uint32_t *)(a))
//#define putreg32(v,a)  (*(volatile uint32_t *)(a) = (v))

//#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

//#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

//#define READ_BIT(REG, BIT)    ((REG) & (BIT))

//#define CLEAR_REG(REG)        ((REG) = (0x0))

#define READ_REG(REG)         ((*(volatile uint32_t *)(REG)))
#define WRITE_REG(REG, VAL)   (*(volatile uint32_t *)(REG) = (VAL))
#define READ_BIT(REG, BIT)    (READ_REG(REG) & (BIT))
#define SET_BIT(REG, BIT)     WRITE_REG(REG, READ_REG(REG) | (BIT))
#define CLEAR_BIT(REG, BIT)   WRITE_REG(REG, READ_REG(REG) & (~(BIT)))

//base->IOCR &= ~SEMC_IOCR_MUX_A8_MASK;
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

typedef int32_t status_t;

#define SEMC_BASE_ADDRS                 0x402f0000  /* 16KB SEMC */
#define SEMC_BASE_PTRS                  SEMC_BASE_ADDRS
#define IMXRT_SEMC_MCR_OFFSET           0x00    /**< Module Control Register, offset: 0x0 */
#define IMXRT_SEMC_IOCR_OFFSET          0x04    /**< IO Mux Control Register, offset: 0x4 */
#define IMXRT_SEMC_BMCR0_OFFSET         0x08    /**< Bus (AXI) Master Control Register 0, offset: 0x8 */
#define IMXRT_SEMC_BMCR1_OFFSET         0x0c    /**< Bus (AXI) Master Control Register 1, offset: 0xC */
#define IMXRT_SEMC_BR0_OFFSET           0x10    /**< Base Register 0 (For SDRAM CS0 device)..Base Register 8 (For NAND device), array offset: 0x10, array step: 0x4 */
#define IMXRT_SEMC_BR1_OFFSET           0x14
#define IMXRT_SEMC_BR2_OFFSET           0x18
#define IMXRT_SEMC_BR3_OFFSET           0x1c
#define IMXRT_SEMC_BR4_OFFSET           0x20
#define IMXRT_SEMC_BR5_OFFSET           0x24
#define IMXRT_SEMC_BR6_OFFSET           0x28
#define IMXRT_SEMC_BR7_OFFSET           0x2c
#define IMXRT_SEMC_BR8_OFFSET           0x30
#define IMXRT_SEMC_INTEN_OFFSET         0x38    /**< Interrupt Enable Register, offset: 0x38 */
#define IMXRT_SEMC_INTR_OFFSET          0x3c    /**< Interrupt Enable Register, offset: 0x3C */
#define IMXRT_SEMC_SDRAMCR0_OFFSET      0x38    /**< SDRAM control register 0, offset: 0x40 */
#define IMXRT_SEMC_SDRAMCR1_OFFSET      0x44    /**< SDRAM control register 1, offset: 0x44 */
#define IMXRT_SEMC_SDRAMCR2_OFFSET      0x48    /**< SDRAM control register 2, offset: 0x48 */
#define IMXRT_SEMC_SDRAMCR3_OFFSET      0x4c    /**< SDRAM control register 3, offset: 0x4C */
#define IMXRT_SEMC_NANDCR0_OFFSET       0x50    /**< NAND control register 0, offset: 0x50 */
#define IMXRT_SEMC_NANDCR1_OFFSET       0x54    /**< NAND control register 1, offset: 0x54 */
#define IMXRT_SEMC_NANDCR2_OFFSET       0x58    /**< NAND control register 2, offset: 0x58 */
#define IMXRT_SEMC_NANDCR3_OFFSET       0x5c    /**< NAND control register 3, offset: 0x5C */
#define IMXRT_SEMC_NORCR0_OFFSET        0x60    /**< NOR control register 0, offset: 0x60 */
#define IMXRT_SEMC_NORCR1_OFFSET        0x64    /**< NOR control register 1, offset: 0x64 */
#define IMXRT_SEMC_NORCR2_OFFSET        0x68    /**< NOR control register 2, offset: 0x68 */
#define IMXRT_SEMC_NORCR3_OFFSET        0x6c    /**< NOR control register 3, offset: 0x6C */
#define IMXRT_SEMC_SRAMCR0_OFFSET       0x70    /**< SRAM control register 0, offset: 0x70 */
#define IMXRT_SEMC_SRAMCR1_OFFSET       0x74    /**< SRAM control register 1, offset: 0x74 */
#define IMXRT_SEMC_SRAMCR2_OFFSET       0x78    /**< SRAM control register 2, offset: 0x78 */
#define IMXRT_SEMC_SRAMCR3_OFFSET       0x7c    /**< SRAM control register 3, offset: 0x7C */
#define IMXRT_SEMC_DBICR0_OFFSET        0x80    /**< DBI-B control register 0, offset: 0x80 */
#define IMXRT_SEMC_DBICR1_OFFSET        0x84    /**< DBI-B control register 1, offset: 0x84 */
#define IMXRT_SEMC_IPCR0_OFFSET         0x90    /**< IP Command control register 0, offset: 0x90 */
#define IMXRT_SEMC_IPCR1_OFFSET         0x94    /**< IP Command control register 1, offset: 0x94 */
#define IMXRT_SEMC_IPCR2_OFFSET         0x98    /**< IP Command control register 2, offset: 0x98 */
#define IMXRT_SEMC_IPCMD_OFFSET         0x9c    /**< IP Command register, offset: 0x9C */
#define IMXRT_SEMC_IPTXDAT_OFFSET       0xa0    /**< TX DATA register (for IP Command), offset: 0xA0 */
#define IMXRT_SEMC_IPRXDAT_OFFSET       0xb0    /**< RX DATA register (for IP Command), offset: 0xB0 */
#define IMXRT_SEMC_STS0_OFFSET          0xc0    /**< Status register 0, offset: 0xC0 */
#define IMXRT_SEMC_STS1_OFFSET          0xc4    /**< Status register 1, offset: 0xC4 */
#define IMXRT_SEMC_STS2_OFFSET          0xc8    /**< Status register 2, offset: 0xC8 */
#define IMXRT_SEMC_STS3_OFFSET          0xcc    /**< Status register 3, offset: 0xCC */
#define IMXRT_SEMC_STS4_OFFSET          0xd0    /**< Status register 4, offset: 0xD0 */
#define IMXRT_SEMC_STS5_OFFSET          0xd4    /**< Status register 5, offset: 0xD4 */
#define IMXRT_SEMC_STS6_OFFSET          0xd8    /**< Status register 6, offset: 0xD8 */
#define IMXRT_SEMC_STS7_OFFSET          0xdc    /**< Status register 7, offset: 0xDC */
#define IMXRT_SEMC_STS8_OFFSET          0xe0    /**< Status register 8, offset: 0xE0 */
#define IMXRT_SEMC_STS9_OFFSET          0xe4    /**< Status register 9, offset: 0xE4 */
#define IMXRT_SEMC_STS10_OFFSET         0xe8    /**< Status register 10, offset: 0xE8 */
#define IMXRT_SEMC_STS11_OFFSET         0xec    /**< Status register 11, offset: 0xEC */
#define IMXRT_SEMC_STS12_OFFSET         0xf0    /**< Status register 12, offset: 0xF0 */
#define IMXRT_SEMC_STS13_OFFSET         0xf4    /**< Status register 13, offset: 0xF4 */
#define IMXRT_SEMC_STS14_OFFSET         0xf8    /**< Status register 14, offset: 0xF8 */
#define IMXRT_SEMC_STS15_OFFSET         0xfc    /**< Status register 15, offset: 0xFC */

#define IMXRT_SEMC_MCR          (SEMC_BASE_ADDRS + IMXRT_SEMC_MCR_OFFSET)
#define IMXRT_SEMC_IOCR         (SEMC_BASE_ADDRS + IMXRT_SEMC_IOCR_OFFSET)
#define IMXRT_SEMC_BMCR0        (SEMC_BASE_ADDRS + IMXRT_SEMC_BMCR0_OFFSET)
#define IMXRT_SEMC_BMCR1        (SEMC_BASE_ADDRS + IMXRT_SEMC_BMCR1_OFFSET)
#define IMXRT_SEMC_BR0          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR0_OFFSET)
#define IMXRT_SEMC_BR1          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR1_OFFSET)
#define IMXRT_SEMC_BR2          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR2_OFFSET)
#define IMXRT_SEMC_BR3          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR3_OFFSET)
#define IMXRT_SEMC_BR4          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR4_OFFSET)
#define IMXRT_SEMC_BR5          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR5_OFFSET)
#define IMXRT_SEMC_BR6          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR6_OFFSET)
#define IMXRT_SEMC_BR7          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR7_OFFSET)
#define IMXRT_SEMC_BR8          (SEMC_BASE_ADDRS + IMXRT_SEMC_BR8_OFFSET)
#define IMXRT_SEMC_INTEN        (SEMC_BASE_ADDRS + IMXRT_SEMC_INTEN_OFFSET)
#define IMXRT_SEMC_INTR         (SEMC_BASE_ADDRS + IMXRT_SEMC_INTR_OFFSET)
#define IMXRT_SEMC_SDRAMCR0     (SEMC_BASE_ADDRS + IMXRT_SEMC_SDRAMCR0_OFFSET)
#define IMXRT_SEMC_SDRAMCR1     (SEMC_BASE_ADDRS + IMXRT_SEMC_SDRAMCR1_OFFSET)
#define IMXRT_SEMC_SDRAMCR2     (SEMC_BASE_ADDRS + IMXRT_SEMC_SDRAMCR2_OFFSET)
#define IMXRT_SEMC_SDRAMCR3     (SEMC_BASE_ADDRS + IMXRT_SEMC_SDRAMCR3_OFFSET)
#define IMXRT_SEMC_NANDCR0      (SEMC_BASE_ADDRS + IMXRT_SEMC_NANDCR0_OFFSET)
#define IMXRT_SEMC_NANDCR1      (SEMC_BASE_ADDRS + IMXRT_SEMC_NANDCR1_OFFSET)
#define IMXRT_SEMC_NANDCR2      (SEMC_BASE_ADDRS + IMXRT_SEMC_NANDCR2_OFFSET)
#define IMXRT_SEMC_NANDCR3     (SEMC_BASE_ADDRS + IMXRT_SEMC_NANDCR3_OFFSET)
#define IMXRT_SEMC_NORCR0      (SEMC_BASE_ADDRS + IMXRT_SEMC_NORCR0_OFFSET)
#define IMXRT_SEMC_NORCR1      (SEMC_BASE_ADDRS + IMXRT_SEMC_NORCR1_OFFSET)
#define IMXRT_SEMC_NORCR2      (SEMC_BASE_ADDRS + IMXRT_SEMC_NORCR2_OFFSET)
#define IMXRT_SEMC_NORCR3      (SEMC_BASE_ADDRS + IMXRT_SEMC_NORCR3_OFFSET)
#define IMXRT_SEMC_SRAMCR0     (SEMC_BASE_ADDRS + IMXRT_SEMC_SRAMCR0_OFFSET)
#define IMXRT_SEMC_SRAMCR1     (SEMC_BASE_ADDRS + IMXRT_SEMC_SRAMCR1_OFFSET)
#define IMXRT_SEMC_SRAMCR2     (SEMC_BASE_ADDRS + IMXRT_SEMC_SRAMCR2_OFFSET)
#define IMXRT_SEMC_SRAMCR3     (SEMC_BASE_ADDRS + IMXRT_SEMC_SRAMCR3_OFFSET)
#define IMXRT_SEMC_DBICR0      (SEMC_BASE_ADDRS + IMXRT_SEMC_DBICR0_OFFSET)
#define IMXRT_SEMC_DBICR1      (SEMC_BASE_ADDRS + IMXRT_SEMC_DBICR1_OFFSET)
#define IMXRT_SEMC_IPCR0        (SEMC_BASE_ADDRS + IMXRT_SEMC_IPCR0_OFFSET)
#define IMXRT_SEMC_IPCR1        (SEMC_BASE_ADDRS + IMXRT_SEMC_IPCR1_OFFSET)
#define IMXRT_SEMC_IPCR2        (SEMC_BASE_ADDRS + IMXRT_SEMC_IPCR2_OFFSET)
#define IMXRT_SEMC_IPCMD        (SEMC_BASE_ADDRS + IMXRT_SEMC_IPCMD_OFFSET)
#define IMXRT_SEMC_IPTXDAT      (SEMC_BASE_ADDRS + IMXRT_SEMC_IPTXDAT_OFFSET)
#define IMXRT_SEMC_IPRXDAT      (SEMC_BASE_ADDRS + IMXRT_SEMC_IPRXDAT_OFFSET)
#define IMXRT_SEMC_STS0         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS0_OFFSET)
#define IMXRT_SEMC_STS1         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS1_OFFSET)
#define IMXRT_SEMC_STS2         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS2_OFFSET)
#define IMXRT_SEMC_STS3         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS3_OFFSET)
#define IMXRT_SEMC_STS4         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS4_OFFSET)
#define IMXRT_SEMC_STS5         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS5_OFFSET)
#define IMXRT_SEMC_STS6         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS6_OFFSET)
#define IMXRT_SEMC_STS7         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS7_OFFSET)
#define IMXRT_SEMC_STS8         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS8_OFFSET)
#define IMXRT_SEMC_STS9         (SEMC_BASE_ADDRS + IMXRT_SEMC_STS9_OFFSET)
#define IMXRT_SEMC_STS10        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS10_OFFSET)
#define IMXRT_SEMC_STS11        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS11_OFFSET)
#define IMXRT_SEMC_STS12        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS12_OFFSET)
#define IMXRT_SEMC_STS13        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS13_OFFSET)
#define IMXRT_SEMC_STS14        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS14_OFFSET)
#define IMXRT_SEMC_STS15        (SEMC_BASE_ADDRS + IMXRT_SEMC_STS15_OFFSET)

/*! @brief Define macros for SEMC driver. */
#define SEMC_IPCOMMANDDATASIZEBYTEMAX (4U)
#define SEMC_IPCOMMANDMAGICKEY        (0xA55A)
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
#define SEMC_IOCR_PINMUXBITWIDTH (0x4UL)
#else
#define SEMC_IOCR_PINMUXBITWIDTH (0x3UL)
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */
#define SEMC_IOCR_NAND_CE   (4UL)
#define SEMC_IOCR_NOR_CE    (5UL)
#define SEMC_IOCR_NOR_CE_A8 (2UL)
#define SEMC_IOCR_PSRAM_CE  (6UL)
#if defined(SEMC_IOCR_PINMUXBITWIDTH) && (SEMC_IOCR_PINMUXBITWIDTH == 0x4UL)
#define SEMC_IOCR_PSRAM_CE_A8 (6UL)
#else
#define SEMC_IOCR_PSRAM_CE_A8 (3UL)
#endif /* SEMC_IOCR_PINMUXBITWIDTH */
#define SEMC_IOCR_DBI_CSX                     (7UL)
#define SEMC_IOCR_DBI_CSX_A8                  (4UL)
#define SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE (24U)
#define SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHMAX  (28U)
#define SEMC_BMCR0_TYPICAL_WQOS               (5U)
#define SEMC_BMCR0_TYPICAL_WAGE               (8U)
#define SEMC_BMCR0_TYPICAL_WSH                (0x40U)
#define SEMC_BMCR0_TYPICAL_WRWS               (0x10U)
#define SEMC_BMCR1_TYPICAL_WQOS               (5U)
#define SEMC_BMCR1_TYPICAL_WAGE               (8U)
#define SEMC_BMCR1_TYPICAL_WPH                (0x60U)
#define SEMC_BMCR1_TYPICAL_WBR                (0x40U)
#define SEMC_BMCR1_TYPICAL_WRWS               (0x24U)
#define SEMC_STARTADDRESS                     (0x80000000UL)
#define SEMC_ENDADDRESS                       (0xDFFFFFFFUL)
#define SEMC_BR_MEMSIZE_MIN                   (4U)
#define SEMC_BR_MEMSIZE_OFFSET                (2U)
#define SEMC_BR_MEMSIZE_MAX                   (4UL * 1024UL * 1024UL)
#define SEMC_SDRAM_MODESETCAL_OFFSET          (4U)
#define SEMC_BR_REG_NUM                       (9U)
#define SEMC_BYTE_NUMBIT                      (8U)

#define SEMC_IPCMD_KEY_MASK                      (0xFFFF0000U)
#define SEMC_IPCMD_KEY_SHIFT                     (16U)

#define CCM_CCGR0_CG0_MASK                       (0x3U)
#define CCM_CCGR0_CG0_SHIFT                      (0U)
#define CCM_CCGR0_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG0_SHIFT)) & CCM_CCGR0_CG0_MASK)

#define CCM_CCGR0_CG1_MASK                       (0xCU)
#define CCM_CCGR0_CG1_SHIFT                      (2U)
#define CCM_CCGR0_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG1_SHIFT)) & CCM_CCGR0_CG1_MASK)

#define CCM_CCGR0_CG2_MASK                       (0x30U)
#define CCM_CCGR0_CG2_SHIFT                      (4U)
#define CCM_CCGR0_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG2_SHIFT)) & CCM_CCGR0_CG2_MASK)

#define CCM_CCGR0_CG3_MASK                       (0xC0U)
#define CCM_CCGR0_CG3_SHIFT                      (6U)
#define CCM_CCGR0_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG3_SHIFT)) & CCM_CCGR0_CG3_MASK)

#define CCM_CCGR0_CG4_MASK                       (0x300U)
#define CCM_CCGR0_CG4_SHIFT                      (8U)
#define CCM_CCGR0_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG4_SHIFT)) & CCM_CCGR0_CG4_MASK)

#define CCM_CCGR0_CG5_MASK                       (0xC00U)
#define CCM_CCGR0_CG5_SHIFT                      (10U)
#define CCM_CCGR0_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG5_SHIFT)) & CCM_CCGR0_CG5_MASK)

#define CCM_CCGR0_CG6_MASK                       (0x3000U)
#define CCM_CCGR0_CG6_SHIFT                      (12U)
#define CCM_CCGR0_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG6_SHIFT)) & CCM_CCGR0_CG6_MASK)

#define CCM_CCGR0_CG7_MASK                       (0xC000U)
#define CCM_CCGR0_CG7_SHIFT                      (14U)
#define CCM_CCGR0_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG7_SHIFT)) & CCM_CCGR0_CG7_MASK)

#define CCM_CCGR0_CG8_MASK                       (0x30000U)
#define CCM_CCGR0_CG8_SHIFT                      (16U)
#define CCM_CCGR0_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG8_SHIFT)) & CCM_CCGR0_CG8_MASK)

#define CCM_CCGR0_CG9_MASK                       (0xC0000U)
#define CCM_CCGR0_CG9_SHIFT                      (18U)
#define CCM_CCGR0_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG9_SHIFT)) & CCM_CCGR0_CG9_MASK)

#define CCM_CCGR0_CG10_MASK                      (0x300000U)
#define CCM_CCGR0_CG10_SHIFT                     (20U)
#define CCM_CCGR0_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG10_SHIFT)) & CCM_CCGR0_CG10_MASK)

#define CCM_CCGR0_CG11_MASK                      (0xC00000U)
#define CCM_CCGR0_CG11_SHIFT                     (22U)
#define CCM_CCGR0_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG11_SHIFT)) & CCM_CCGR0_CG11_MASK)

#define CCM_CCGR0_CG12_MASK                      (0x3000000U)
#define CCM_CCGR0_CG12_SHIFT                     (24U)
#define CCM_CCGR0_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG12_SHIFT)) & CCM_CCGR0_CG12_MASK)

#define CCM_CCGR0_CG13_MASK                      (0xC000000U)
#define CCM_CCGR0_CG13_SHIFT                     (26U)
#define CCM_CCGR0_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG13_SHIFT)) & CCM_CCGR0_CG13_MASK)

#define CCM_CCGR0_CG14_MASK                      (0x30000000U)
#define CCM_CCGR0_CG14_SHIFT                     (28U)
#define CCM_CCGR0_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG14_SHIFT)) & CCM_CCGR0_CG14_MASK)

#define CCM_CCGR0_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR0_CG15_SHIFT                     (30U)
#define CCM_CCGR0_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR0_CG15_SHIFT)) & CCM_CCGR0_CG15_MASK)
/*! @} */

/*! @name CCGR1 - CCM Clock Gating Register 1 */
/*! @{ */

#define CCM_CCGR1_CG0_MASK                       (0x3U)
#define CCM_CCGR1_CG0_SHIFT                      (0U)
#define CCM_CCGR1_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG0_SHIFT)) & CCM_CCGR1_CG0_MASK)

#define CCM_CCGR1_CG1_MASK                       (0xCU)
#define CCM_CCGR1_CG1_SHIFT                      (2U)
#define CCM_CCGR1_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG1_SHIFT)) & CCM_CCGR1_CG1_MASK)

#define CCM_CCGR1_CG2_MASK                       (0x30U)
#define CCM_CCGR1_CG2_SHIFT                      (4U)
#define CCM_CCGR1_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG2_SHIFT)) & CCM_CCGR1_CG2_MASK)

#define CCM_CCGR1_CG3_MASK                       (0xC0U)
#define CCM_CCGR1_CG3_SHIFT                      (6U)
#define CCM_CCGR1_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG3_SHIFT)) & CCM_CCGR1_CG3_MASK)

#define CCM_CCGR1_CG4_MASK                       (0x300U)
#define CCM_CCGR1_CG4_SHIFT                      (8U)
#define CCM_CCGR1_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG4_SHIFT)) & CCM_CCGR1_CG4_MASK)

#define CCM_CCGR1_CG5_MASK                       (0xC00U)
#define CCM_CCGR1_CG5_SHIFT                      (10U)
#define CCM_CCGR1_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG5_SHIFT)) & CCM_CCGR1_CG5_MASK)

#define CCM_CCGR1_CG6_MASK                       (0x3000U)
#define CCM_CCGR1_CG6_SHIFT                      (12U)
#define CCM_CCGR1_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG6_SHIFT)) & CCM_CCGR1_CG6_MASK)

#define CCM_CCGR1_CG7_MASK                       (0xC000U)
#define CCM_CCGR1_CG7_SHIFT                      (14U)
#define CCM_CCGR1_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG7_SHIFT)) & CCM_CCGR1_CG7_MASK)

#define CCM_CCGR1_CG8_MASK                       (0x30000U)
#define CCM_CCGR1_CG8_SHIFT                      (16U)
#define CCM_CCGR1_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG8_SHIFT)) & CCM_CCGR1_CG8_MASK)

#define CCM_CCGR1_CG9_MASK                       (0xC0000U)
#define CCM_CCGR1_CG9_SHIFT                      (18U)
#define CCM_CCGR1_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG9_SHIFT)) & CCM_CCGR1_CG9_MASK)

#define CCM_CCGR1_CG10_MASK                      (0x300000U)
#define CCM_CCGR1_CG10_SHIFT                     (20U)
#define CCM_CCGR1_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG10_SHIFT)) & CCM_CCGR1_CG10_MASK)

#define CCM_CCGR1_CG11_MASK                      (0xC00000U)
#define CCM_CCGR1_CG11_SHIFT                     (22U)
#define CCM_CCGR1_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG11_SHIFT)) & CCM_CCGR1_CG11_MASK)

#define CCM_CCGR1_CG12_MASK                      (0x3000000U)
#define CCM_CCGR1_CG12_SHIFT                     (24U)
#define CCM_CCGR1_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG12_SHIFT)) & CCM_CCGR1_CG12_MASK)

#define CCM_CCGR1_CG13_MASK                      (0xC000000U)
#define CCM_CCGR1_CG13_SHIFT                     (26U)
#define CCM_CCGR1_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG13_SHIFT)) & CCM_CCGR1_CG13_MASK)

#define CCM_CCGR1_CG14_MASK                      (0x30000000U)
#define CCM_CCGR1_CG14_SHIFT                     (28U)
#define CCM_CCGR1_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG14_SHIFT)) & CCM_CCGR1_CG14_MASK)

#define CCM_CCGR1_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR1_CG15_SHIFT                     (30U)
#define CCM_CCGR1_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR1_CG15_SHIFT)) & CCM_CCGR1_CG15_MASK)
/*! @} */

/*! @name CCGR2 - CCM Clock Gating Register 2 */
/*! @{ */

#define CCM_CCGR2_CG0_MASK                       (0x3U)
#define CCM_CCGR2_CG0_SHIFT                      (0U)
#define CCM_CCGR2_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG0_SHIFT)) & CCM_CCGR2_CG0_MASK)

#define CCM_CCGR2_CG1_MASK                       (0xCU)
#define CCM_CCGR2_CG1_SHIFT                      (2U)
#define CCM_CCGR2_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG1_SHIFT)) & CCM_CCGR2_CG1_MASK)

#define CCM_CCGR2_CG2_MASK                       (0x30U)
#define CCM_CCGR2_CG2_SHIFT                      (4U)
#define CCM_CCGR2_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG2_SHIFT)) & CCM_CCGR2_CG2_MASK)

#define CCM_CCGR2_CG3_MASK                       (0xC0U)
#define CCM_CCGR2_CG3_SHIFT                      (6U)
#define CCM_CCGR2_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG3_SHIFT)) & CCM_CCGR2_CG3_MASK)

#define CCM_CCGR2_CG4_MASK                       (0x300U)
#define CCM_CCGR2_CG4_SHIFT                      (8U)
#define CCM_CCGR2_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG4_SHIFT)) & CCM_CCGR2_CG4_MASK)

#define CCM_CCGR2_CG5_MASK                       (0xC00U)
#define CCM_CCGR2_CG5_SHIFT                      (10U)
#define CCM_CCGR2_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG5_SHIFT)) & CCM_CCGR2_CG5_MASK)

#define CCM_CCGR2_CG6_MASK                       (0x3000U)
#define CCM_CCGR2_CG6_SHIFT                      (12U)
#define CCM_CCGR2_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG6_SHIFT)) & CCM_CCGR2_CG6_MASK)

#define CCM_CCGR2_CG7_MASK                       (0xC000U)
#define CCM_CCGR2_CG7_SHIFT                      (14U)
#define CCM_CCGR2_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG7_SHIFT)) & CCM_CCGR2_CG7_MASK)

#define CCM_CCGR2_CG8_MASK                       (0x30000U)
#define CCM_CCGR2_CG8_SHIFT                      (16U)
#define CCM_CCGR2_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG8_SHIFT)) & CCM_CCGR2_CG8_MASK)

#define CCM_CCGR2_CG9_MASK                       (0xC0000U)
#define CCM_CCGR2_CG9_SHIFT                      (18U)
#define CCM_CCGR2_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG9_SHIFT)) & CCM_CCGR2_CG9_MASK)

#define CCM_CCGR2_CG10_MASK                      (0x300000U)
#define CCM_CCGR2_CG10_SHIFT                     (20U)
#define CCM_CCGR2_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG10_SHIFT)) & CCM_CCGR2_CG10_MASK)

#define CCM_CCGR2_CG11_MASK                      (0xC00000U)
#define CCM_CCGR2_CG11_SHIFT                     (22U)
#define CCM_CCGR2_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG11_SHIFT)) & CCM_CCGR2_CG11_MASK)

#define CCM_CCGR2_CG12_MASK                      (0x3000000U)
#define CCM_CCGR2_CG12_SHIFT                     (24U)
#define CCM_CCGR2_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG12_SHIFT)) & CCM_CCGR2_CG12_MASK)

#define CCM_CCGR2_CG13_MASK                      (0xC000000U)
#define CCM_CCGR2_CG13_SHIFT                     (26U)
#define CCM_CCGR2_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG13_SHIFT)) & CCM_CCGR2_CG13_MASK)

#define CCM_CCGR2_CG14_MASK                      (0x30000000U)
#define CCM_CCGR2_CG14_SHIFT                     (28U)
#define CCM_CCGR2_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG14_SHIFT)) & CCM_CCGR2_CG14_MASK)

#define CCM_CCGR2_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR2_CG15_SHIFT                     (30U)
#define CCM_CCGR2_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR2_CG15_SHIFT)) & CCM_CCGR2_CG15_MASK)
/*! @} */

/*! @name CCGR3 - CCM Clock Gating Register 3 */
/*! @{ */

#define CCM_CCGR3_CG0_MASK                       (0x3U)
#define CCM_CCGR3_CG0_SHIFT                      (0U)
#define CCM_CCGR3_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG0_SHIFT)) & CCM_CCGR3_CG0_MASK)

#define CCM_CCGR3_CG1_MASK                       (0xCU)
#define CCM_CCGR3_CG1_SHIFT                      (2U)
#define CCM_CCGR3_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG1_SHIFT)) & CCM_CCGR3_CG1_MASK)

#define CCM_CCGR3_CG2_MASK                       (0x30U)
#define CCM_CCGR3_CG2_SHIFT                      (4U)
#define CCM_CCGR3_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG2_SHIFT)) & CCM_CCGR3_CG2_MASK)

#define CCM_CCGR3_CG3_MASK                       (0xC0U)
#define CCM_CCGR3_CG3_SHIFT                      (6U)
#define CCM_CCGR3_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG3_SHIFT)) & CCM_CCGR3_CG3_MASK)

#define CCM_CCGR3_CG4_MASK                       (0x300U)
#define CCM_CCGR3_CG4_SHIFT                      (8U)
#define CCM_CCGR3_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG4_SHIFT)) & CCM_CCGR3_CG4_MASK)

#define CCM_CCGR3_CG5_MASK                       (0xC00U)
#define CCM_CCGR3_CG5_SHIFT                      (10U)
#define CCM_CCGR3_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG5_SHIFT)) & CCM_CCGR3_CG5_MASK)

#define CCM_CCGR3_CG6_MASK                       (0x3000U)
#define CCM_CCGR3_CG6_SHIFT                      (12U)
#define CCM_CCGR3_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG6_SHIFT)) & CCM_CCGR3_CG6_MASK)

#define CCM_CCGR3_CG7_MASK                       (0xC000U)
#define CCM_CCGR3_CG7_SHIFT                      (14U)
#define CCM_CCGR3_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG7_SHIFT)) & CCM_CCGR3_CG7_MASK)

#define CCM_CCGR3_CG8_MASK                       (0x30000U)
#define CCM_CCGR3_CG8_SHIFT                      (16U)
#define CCM_CCGR3_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG8_SHIFT)) & CCM_CCGR3_CG8_MASK)

#define CCM_CCGR3_CG9_MASK                       (0xC0000U)
#define CCM_CCGR3_CG9_SHIFT                      (18U)
#define CCM_CCGR3_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG9_SHIFT)) & CCM_CCGR3_CG9_MASK)

#define CCM_CCGR3_CG10_MASK                      (0x300000U)
#define CCM_CCGR3_CG10_SHIFT                     (20U)
#define CCM_CCGR3_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG10_SHIFT)) & CCM_CCGR3_CG10_MASK)

#define CCM_CCGR3_CG11_MASK                      (0xC00000U)
#define CCM_CCGR3_CG11_SHIFT                     (22U)
#define CCM_CCGR3_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG11_SHIFT)) & CCM_CCGR3_CG11_MASK)

#define CCM_CCGR3_CG12_MASK                      (0x3000000U)
#define CCM_CCGR3_CG12_SHIFT                     (24U)
#define CCM_CCGR3_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG12_SHIFT)) & CCM_CCGR3_CG12_MASK)

#define CCM_CCGR3_CG13_MASK                      (0xC000000U)
#define CCM_CCGR3_CG13_SHIFT                     (26U)
#define CCM_CCGR3_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG13_SHIFT)) & CCM_CCGR3_CG13_MASK)

#define CCM_CCGR3_CG14_MASK                      (0x30000000U)
#define CCM_CCGR3_CG14_SHIFT                     (28U)
/*! CG14 - The OCRAM clock cannot be turned off when the CM cache is running on this device.
 */
#define CCM_CCGR3_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG14_SHIFT)) & CCM_CCGR3_CG14_MASK)

#define CCM_CCGR3_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR3_CG15_SHIFT                     (30U)
#define CCM_CCGR3_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR3_CG15_SHIFT)) & CCM_CCGR3_CG15_MASK)
/*! @} */

/*! @name CCGR4 - CCM Clock Gating Register 4 */
/*! @{ */

#define CCM_CCGR4_CG0_MASK                       (0x3U)
#define CCM_CCGR4_CG0_SHIFT                      (0U)
#define CCM_CCGR4_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG0_SHIFT)) & CCM_CCGR4_CG0_MASK)

#define CCM_CCGR4_CG1_MASK                       (0xCU)
#define CCM_CCGR4_CG1_SHIFT                      (2U)
#define CCM_CCGR4_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG1_SHIFT)) & CCM_CCGR4_CG1_MASK)

#define CCM_CCGR4_CG2_MASK                       (0x30U)
#define CCM_CCGR4_CG2_SHIFT                      (4U)
#define CCM_CCGR4_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG2_SHIFT)) & CCM_CCGR4_CG2_MASK)

#define CCM_CCGR4_CG3_MASK                       (0xC0U)
#define CCM_CCGR4_CG3_SHIFT                      (6U)
#define CCM_CCGR4_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG3_SHIFT)) & CCM_CCGR4_CG3_MASK)

#define CCM_CCGR4_CG4_MASK                       (0x300U)
#define CCM_CCGR4_CG4_SHIFT                      (8U)
#define CCM_CCGR4_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG4_SHIFT)) & CCM_CCGR4_CG4_MASK)

#define CCM_CCGR4_CG5_MASK                       (0xC00U)
#define CCM_CCGR4_CG5_SHIFT                      (10U)
#define CCM_CCGR4_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG5_SHIFT)) & CCM_CCGR4_CG5_MASK)

#define CCM_CCGR4_CG6_MASK                       (0x3000U)
#define CCM_CCGR4_CG6_SHIFT                      (12U)
#define CCM_CCGR4_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG6_SHIFT)) & CCM_CCGR4_CG6_MASK)

#define CCM_CCGR4_CG7_MASK                       (0xC000U)
#define CCM_CCGR4_CG7_SHIFT                      (14U)
#define CCM_CCGR4_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG7_SHIFT)) & CCM_CCGR4_CG7_MASK)

#define CCM_CCGR4_CG8_MASK                       (0x30000U)
#define CCM_CCGR4_CG8_SHIFT                      (16U)
#define CCM_CCGR4_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG8_SHIFT)) & CCM_CCGR4_CG8_MASK)

#define CCM_CCGR4_CG9_MASK                       (0xC0000U)
#define CCM_CCGR4_CG9_SHIFT                      (18U)
#define CCM_CCGR4_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG9_SHIFT)) & CCM_CCGR4_CG9_MASK)

#define CCM_CCGR4_CG10_MASK                      (0x300000U)
#define CCM_CCGR4_CG10_SHIFT                     (20U)
#define CCM_CCGR4_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG10_SHIFT)) & CCM_CCGR4_CG10_MASK)

#define CCM_CCGR4_CG11_MASK                      (0xC00000U)
#define CCM_CCGR4_CG11_SHIFT                     (22U)
#define CCM_CCGR4_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG11_SHIFT)) & CCM_CCGR4_CG11_MASK)

#define CCM_CCGR4_CG12_MASK                      (0x3000000U)
#define CCM_CCGR4_CG12_SHIFT                     (24U)
#define CCM_CCGR4_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG12_SHIFT)) & CCM_CCGR4_CG12_MASK)

#define CCM_CCGR4_CG13_MASK                      (0xC000000U)
#define CCM_CCGR4_CG13_SHIFT                     (26U)
#define CCM_CCGR4_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG13_SHIFT)) & CCM_CCGR4_CG13_MASK)

#define CCM_CCGR4_CG14_MASK                      (0x30000000U)
#define CCM_CCGR4_CG14_SHIFT                     (28U)
#define CCM_CCGR4_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG14_SHIFT)) & CCM_CCGR4_CG14_MASK)

#define CCM_CCGR4_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR4_CG15_SHIFT                     (30U)
#define CCM_CCGR4_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR4_CG15_SHIFT)) & CCM_CCGR4_CG15_MASK)
/*! @} */

/*! @name CCGR5 - CCM Clock Gating Register 5 */
/*! @{ */

#define CCM_CCGR5_CG0_MASK                       (0x3U)
#define CCM_CCGR5_CG0_SHIFT                      (0U)
#define CCM_CCGR5_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG0_SHIFT)) & CCM_CCGR5_CG0_MASK)

#define CCM_CCGR5_CG1_MASK                       (0xCU)
#define CCM_CCGR5_CG1_SHIFT                      (2U)
#define CCM_CCGR5_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG1_SHIFT)) & CCM_CCGR5_CG1_MASK)

#define CCM_CCGR5_CG2_MASK                       (0x30U)
#define CCM_CCGR5_CG2_SHIFT                      (4U)
#define CCM_CCGR5_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG2_SHIFT)) & CCM_CCGR5_CG2_MASK)

#define CCM_CCGR5_CG3_MASK                       (0xC0U)
#define CCM_CCGR5_CG3_SHIFT                      (6U)
#define CCM_CCGR5_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG3_SHIFT)) & CCM_CCGR5_CG3_MASK)

#define CCM_CCGR5_CG4_MASK                       (0x300U)
#define CCM_CCGR5_CG4_SHIFT                      (8U)
#define CCM_CCGR5_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG4_SHIFT)) & CCM_CCGR5_CG4_MASK)

#define CCM_CCGR5_CG5_MASK                       (0xC00U)
#define CCM_CCGR5_CG5_SHIFT                      (10U)
#define CCM_CCGR5_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG5_SHIFT)) & CCM_CCGR5_CG5_MASK)

#define CCM_CCGR5_CG6_MASK                       (0x3000U)
#define CCM_CCGR5_CG6_SHIFT                      (12U)
#define CCM_CCGR5_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG6_SHIFT)) & CCM_CCGR5_CG6_MASK)

#define CCM_CCGR5_CG7_MASK                       (0xC000U)
#define CCM_CCGR5_CG7_SHIFT                      (14U)
#define CCM_CCGR5_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG7_SHIFT)) & CCM_CCGR5_CG7_MASK)

#define CCM_CCGR5_CG8_MASK                       (0x30000U)
#define CCM_CCGR5_CG8_SHIFT                      (16U)
#define CCM_CCGR5_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG8_SHIFT)) & CCM_CCGR5_CG8_MASK)

#define CCM_CCGR5_CG9_MASK                       (0xC0000U)
#define CCM_CCGR5_CG9_SHIFT                      (18U)
#define CCM_CCGR5_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG9_SHIFT)) & CCM_CCGR5_CG9_MASK)

#define CCM_CCGR5_CG10_MASK                      (0x300000U)
#define CCM_CCGR5_CG10_SHIFT                     (20U)
#define CCM_CCGR5_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG10_SHIFT)) & CCM_CCGR5_CG10_MASK)

#define CCM_CCGR5_CG11_MASK                      (0xC00000U)
#define CCM_CCGR5_CG11_SHIFT                     (22U)
#define CCM_CCGR5_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG11_SHIFT)) & CCM_CCGR5_CG11_MASK)

#define CCM_CCGR5_CG12_MASK                      (0x3000000U)
#define CCM_CCGR5_CG12_SHIFT                     (24U)
#define CCM_CCGR5_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG12_SHIFT)) & CCM_CCGR5_CG12_MASK)

#define CCM_CCGR5_CG13_MASK                      (0xC000000U)
#define CCM_CCGR5_CG13_SHIFT                     (26U)
#define CCM_CCGR5_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG13_SHIFT)) & CCM_CCGR5_CG13_MASK)

#define CCM_CCGR5_CG14_MASK                      (0x30000000U)
#define CCM_CCGR5_CG14_SHIFT                     (28U)
#define CCM_CCGR5_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG14_SHIFT)) & CCM_CCGR5_CG14_MASK)

#define CCM_CCGR5_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR5_CG15_SHIFT                     (30U)
#define CCM_CCGR5_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR5_CG15_SHIFT)) & CCM_CCGR5_CG15_MASK)
/*! @} */

/*! @name CCGR6 - CCM Clock Gating Register 6 */
/*! @{ */

#define CCM_CCGR6_CG0_MASK                       (0x3U)
#define CCM_CCGR6_CG0_SHIFT                      (0U)
#define CCM_CCGR6_CG0(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG0_SHIFT)) & CCM_CCGR6_CG0_MASK)

#define CCM_CCGR6_CG1_MASK                       (0xCU)
#define CCM_CCGR6_CG1_SHIFT                      (2U)
#define CCM_CCGR6_CG1(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG1_SHIFT)) & CCM_CCGR6_CG1_MASK)

#define CCM_CCGR6_CG2_MASK                       (0x30U)
#define CCM_CCGR6_CG2_SHIFT                      (4U)
#define CCM_CCGR6_CG2(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG2_SHIFT)) & CCM_CCGR6_CG2_MASK)

#define CCM_CCGR6_CG3_MASK                       (0xC0U)
#define CCM_CCGR6_CG3_SHIFT                      (6U)
#define CCM_CCGR6_CG3(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG3_SHIFT)) & CCM_CCGR6_CG3_MASK)

#define CCM_CCGR6_CG4_MASK                       (0x300U)
#define CCM_CCGR6_CG4_SHIFT                      (8U)
#define CCM_CCGR6_CG4(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG4_SHIFT)) & CCM_CCGR6_CG4_MASK)

#define CCM_CCGR6_CG5_MASK                       (0xC00U)
#define CCM_CCGR6_CG5_SHIFT                      (10U)
#define CCM_CCGR6_CG5(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG5_SHIFT)) & CCM_CCGR6_CG5_MASK)

#define CCM_CCGR6_CG6_MASK                       (0x3000U)
#define CCM_CCGR6_CG6_SHIFT                      (12U)
#define CCM_CCGR6_CG6(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG6_SHIFT)) & CCM_CCGR6_CG6_MASK)

#define CCM_CCGR6_CG7_MASK                       (0xC000U)
#define CCM_CCGR6_CG7_SHIFT                      (14U)
#define CCM_CCGR6_CG7(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG7_SHIFT)) & CCM_CCGR6_CG7_MASK)

#define CCM_CCGR6_CG8_MASK                       (0x30000U)
#define CCM_CCGR6_CG8_SHIFT                      (16U)
#define CCM_CCGR6_CG8(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG8_SHIFT)) & CCM_CCGR6_CG8_MASK)

#define CCM_CCGR6_CG9_MASK                       (0xC0000U)
#define CCM_CCGR6_CG9_SHIFT                      (18U)
#define CCM_CCGR6_CG9(x)                         (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG9_SHIFT)) & CCM_CCGR6_CG9_MASK)

#define CCM_CCGR6_CG10_MASK                      (0x300000U)
#define CCM_CCGR6_CG10_SHIFT                     (20U)
#define CCM_CCGR6_CG10(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG10_SHIFT)) & CCM_CCGR6_CG10_MASK)

#define CCM_CCGR6_CG11_MASK                      (0xC00000U)
#define CCM_CCGR6_CG11_SHIFT                     (22U)
#define CCM_CCGR6_CG11(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG11_SHIFT)) & CCM_CCGR6_CG11_MASK)

#define CCM_CCGR6_CG12_MASK                      (0x3000000U)
#define CCM_CCGR6_CG12_SHIFT                     (24U)
#define CCM_CCGR6_CG12(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG12_SHIFT)) & CCM_CCGR6_CG12_MASK)

#define CCM_CCGR6_CG13_MASK                      (0xC000000U)
#define CCM_CCGR6_CG13_SHIFT                     (26U)
#define CCM_CCGR6_CG13(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG13_SHIFT)) & CCM_CCGR6_CG13_MASK)

#define CCM_CCGR6_CG14_MASK                      (0x30000000U)
#define CCM_CCGR6_CG14_SHIFT                     (28U)
#define CCM_CCGR6_CG14(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG14_SHIFT)) & CCM_CCGR6_CG14_MASK)

#define CCM_CCGR6_CG15_MASK                      (0xC0000000U)
#define CCM_CCGR6_CG15_SHIFT                     (30U)
#define CCM_CCGR6_CG15(x)                        (((uint32_t)(((uint32_t)(x)) << CCM_CCGR6_CG15_SHIFT)) & CCM_CCGR6_CG15_MASK)

typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = -1,

    /* CCM CCGR0 */
    kCLOCK_Aips_tz1    = (0U << 8U) | CCM_CCGR0_CG0_SHIFT,  /*!< CCGR0, CG0   */
    kCLOCK_Aips_tz2    = (0U << 8U) | CCM_CCGR0_CG1_SHIFT,  /*!< CCGR0, CG1   */
    kCLOCK_Mqs         = (0U << 8U) | CCM_CCGR0_CG2_SHIFT,  /*!< CCGR0, CG2   */
    kCLOCK_FlexSpiExsc = (0U << 8U) | CCM_CCGR0_CG3_SHIFT,  /*!< CCGR0, CG3   */
    kCLOCK_Sim_M_Main  = (0U << 8U) | CCM_CCGR0_CG4_SHIFT,  /*!< CCGR0, CG4   */
    kCLOCK_Dcp         = (0U << 8U) | CCM_CCGR0_CG5_SHIFT,  /*!< CCGR0, CG5   */
    kCLOCK_Lpuart3     = (0U << 8U) | CCM_CCGR0_CG6_SHIFT,  /*!< CCGR0, CG6   */
    kCLOCK_Can1        = (0U << 8U) | CCM_CCGR0_CG7_SHIFT,  /*!< CCGR0, CG7   */
    kCLOCK_Can1S       = (0U << 8U) | CCM_CCGR0_CG8_SHIFT,  /*!< CCGR0, CG8   */
    kCLOCK_Can2        = (0U << 8U) | CCM_CCGR0_CG9_SHIFT,  /*!< CCGR0, CG9   */
    kCLOCK_Can2S       = (0U << 8U) | CCM_CCGR0_CG10_SHIFT, /*!< CCGR0, CG10  */
    kCLOCK_Trace       = (0U << 8U) | CCM_CCGR0_CG11_SHIFT, /*!< CCGR0, CG11  */
    kCLOCK_Gpt2        = (0U << 8U) | CCM_CCGR0_CG12_SHIFT, /*!< CCGR0, CG12  */
    kCLOCK_Gpt2S       = (0U << 8U) | CCM_CCGR0_CG13_SHIFT, /*!< CCGR0, CG13  */
    kCLOCK_Lpuart2     = (0U << 8U) | CCM_CCGR0_CG14_SHIFT, /*!< CCGR0, CG14  */
    kCLOCK_Gpio2       = (0U << 8U) | CCM_CCGR0_CG15_SHIFT, /*!< CCGR0, CG15  */

    /* CCM CCGR1 */
    kCLOCK_Lpspi1   = (1U << 8U) | CCM_CCGR1_CG0_SHIFT,  /*!< CCGR1, CG0   */
    kCLOCK_Lpspi2   = (1U << 8U) | CCM_CCGR1_CG1_SHIFT,  /*!< CCGR1, CG1   */
    kCLOCK_Lpspi3   = (1U << 8U) | CCM_CCGR1_CG2_SHIFT,  /*!< CCGR1, CG2   */
    kCLOCK_Lpspi4   = (1U << 8U) | CCM_CCGR1_CG3_SHIFT,  /*!< CCGR1, CG3   */
    kCLOCK_Adc2     = (1U << 8U) | CCM_CCGR1_CG4_SHIFT,  /*!< CCGR1, CG4   */
    kCLOCK_Enet     = (1U << 8U) | CCM_CCGR1_CG5_SHIFT,  /*!< CCGR1, CG5   */
    kCLOCK_Pit      = (1U << 8U) | CCM_CCGR1_CG6_SHIFT,  /*!< CCGR1, CG6   */
    kCLOCK_Aoi2     = (1U << 8U) | CCM_CCGR1_CG7_SHIFT,  /*!< CCGR1, CG7   */
    kCLOCK_Adc1     = (1U << 8U) | CCM_CCGR1_CG8_SHIFT,  /*!< CCGR1, CG8   */
    kCLOCK_SemcExsc = (1U << 8U) | CCM_CCGR1_CG9_SHIFT,  /*!< CCGR1, CG9   */
    kCLOCK_Gpt1     = (1U << 8U) | CCM_CCGR1_CG10_SHIFT, /*!< CCGR1, CG10  */
    kCLOCK_Gpt1S    = (1U << 8U) | CCM_CCGR1_CG11_SHIFT, /*!< CCGR1, CG11  */
    kCLOCK_Lpuart4  = (1U << 8U) | CCM_CCGR1_CG12_SHIFT, /*!< CCGR1, CG12  */
    kCLOCK_Gpio1    = (1U << 8U) | CCM_CCGR1_CG13_SHIFT, /*!< CCGR1, CG13  */
    kCLOCK_Csu      = (1U << 8U) | CCM_CCGR1_CG14_SHIFT, /*!< CCGR1, CG14  */
    kCLOCK_Gpio5    = (1U << 8U) | CCM_CCGR1_CG15_SHIFT, /*!< CCGR1, CG15  */

    /* CCM CCGR2 */
    kCLOCK_OcramExsc  = (2U << 8U) | CCM_CCGR2_CG0_SHIFT,  /*!< CCGR2, CG0   */
    kCLOCK_Csi        = (2U << 8U) | CCM_CCGR2_CG1_SHIFT,  /*!< CCGR2, CG1   */
    kCLOCK_IomuxcSnvs = (2U << 8U) | CCM_CCGR2_CG2_SHIFT,  /*!< CCGR2, CG2   */
    kCLOCK_Lpi2c1     = (2U << 8U) | CCM_CCGR2_CG3_SHIFT,  /*!< CCGR2, CG3   */
    kCLOCK_Lpi2c2     = (2U << 8U) | CCM_CCGR2_CG4_SHIFT,  /*!< CCGR2, CG4   */
    kCLOCK_Lpi2c3     = (2U << 8U) | CCM_CCGR2_CG5_SHIFT,  /*!< CCGR2, CG5   */
    kCLOCK_Ocotp      = (2U << 8U) | CCM_CCGR2_CG6_SHIFT,  /*!< CCGR2, CG6   */
    kCLOCK_Xbar3      = (2U << 8U) | CCM_CCGR2_CG7_SHIFT,  /*!< CCGR2, CG7   */
    kCLOCK_Ipmux1     = (2U << 8U) | CCM_CCGR2_CG8_SHIFT,  /*!< CCGR2, CG8   */
    kCLOCK_Ipmux2     = (2U << 8U) | CCM_CCGR2_CG9_SHIFT,  /*!< CCGR2, CG9   */
    kCLOCK_Ipmux3     = (2U << 8U) | CCM_CCGR2_CG10_SHIFT, /*!< CCGR2, CG10  */
    kCLOCK_Xbar1      = (2U << 8U) | CCM_CCGR2_CG11_SHIFT, /*!< CCGR2, CG11  */
    kCLOCK_Xbar2      = (2U << 8U) | CCM_CCGR2_CG12_SHIFT, /*!< CCGR2, CG12  */
    kCLOCK_Gpio3      = (2U << 8U) | CCM_CCGR2_CG13_SHIFT, /*!< CCGR2, CG13  */
    kCLOCK_Lcd        = (2U << 8U) | CCM_CCGR2_CG14_SHIFT, /*!< CCGR2, CG14  */
    kCLOCK_Pxp        = (2U << 8U) | CCM_CCGR2_CG15_SHIFT, /*!< CCGR2, CG15  */

    /* CCM CCGR3 */
    kCLOCK_Flexio2       = (3U << 8U) | CCM_CCGR3_CG0_SHIFT,  /*!< CCGR3, CG0   */
    kCLOCK_Lpuart5       = (3U << 8U) | CCM_CCGR3_CG1_SHIFT,  /*!< CCGR3, CG1   */
    kCLOCK_Semc          = (3U << 8U) | CCM_CCGR3_CG2_SHIFT,  /*!< CCGR3, CG2   */
    kCLOCK_Lpuart6       = (3U << 8U) | CCM_CCGR3_CG3_SHIFT,  /*!< CCGR3, CG3   */
    kCLOCK_Aoi1          = (3U << 8U) | CCM_CCGR3_CG4_SHIFT,  /*!< CCGR3, CG4   */
    kCLOCK_LcdPixel      = (3U << 8U) | CCM_CCGR3_CG5_SHIFT,  /*!< CCGR3, CG5   */
    kCLOCK_Gpio4         = (3U << 8U) | CCM_CCGR3_CG6_SHIFT,  /*!< CCGR3, CG6   */
    kCLOCK_Ewm0          = (3U << 8U) | CCM_CCGR3_CG7_SHIFT,  /*!< CCGR3, CG7   */
    kCLOCK_Wdog1         = (3U << 8U) | CCM_CCGR3_CG8_SHIFT,  /*!< CCGR3, CG8   */
    kCLOCK_FlexRam       = (3U << 8U) | CCM_CCGR3_CG9_SHIFT,  /*!< CCGR3, CG9   */
    kCLOCK_Acmp1         = (3U << 8U) | CCM_CCGR3_CG10_SHIFT, /*!< CCGR3, CG10  */
    kCLOCK_Acmp2         = (3U << 8U) | CCM_CCGR3_CG11_SHIFT, /*!< CCGR3, CG11  */
    kCLOCK_Acmp3         = (3U << 8U) | CCM_CCGR3_CG12_SHIFT, /*!< CCGR3, CG12  */
    kCLOCK_Acmp4         = (3U << 8U) | CCM_CCGR3_CG13_SHIFT, /*!< CCGR3, CG13  */
    kCLOCK_Ocram         = (3U << 8U) | CCM_CCGR3_CG14_SHIFT, /*!< CCGR3, CG14  */
    kCLOCK_IomuxcSnvsGpr = (3U << 8U) | CCM_CCGR3_CG15_SHIFT, /*!< CCGR3, CG15  */

    /* CCM CCGR4 */
    kCLOCK_Sim_m7_clk_r = (4U << 8U) | CCM_CCGR4_CG0_SHIFT,  /*!< CCGR4, CG0   */
    kCLOCK_Iomuxc       = (4U << 8U) | CCM_CCGR4_CG1_SHIFT,  /*!< CCGR4, CG1   */
    kCLOCK_IomuxcGpr    = (4U << 8U) | CCM_CCGR4_CG2_SHIFT,  /*!< CCGR4, CG2   */
    kCLOCK_Bee          = (4U << 8U) | CCM_CCGR4_CG3_SHIFT,  /*!< CCGR4, CG3   */
    kCLOCK_SimM7        = (4U << 8U) | CCM_CCGR4_CG4_SHIFT,  /*!< CCGR4, CG4   */
    kCLOCK_Tsc          = (4U << 8U) | CCM_CCGR4_CG5_SHIFT,  /*!< CCGR4, CG5   */
    kCLOCK_SimM         = (4U << 8U) | CCM_CCGR4_CG6_SHIFT,  /*!< CCGR4, CG6   */
    kCLOCK_SimEms       = (4U << 8U) | CCM_CCGR4_CG7_SHIFT,  /*!< CCGR4, CG7   */
    kCLOCK_Pwm1         = (4U << 8U) | CCM_CCGR4_CG8_SHIFT,  /*!< CCGR4, CG8   */
    kCLOCK_Pwm2         = (4U << 8U) | CCM_CCGR4_CG9_SHIFT,  /*!< CCGR4, CG9   */
    kCLOCK_Pwm3         = (4U << 8U) | CCM_CCGR4_CG10_SHIFT, /*!< CCGR4, CG10  */
    kCLOCK_Pwm4         = (4U << 8U) | CCM_CCGR4_CG11_SHIFT, /*!< CCGR4, CG11  */
    kCLOCK_Enc1         = (4U << 8U) | CCM_CCGR4_CG12_SHIFT, /*!< CCGR4, CG12  */
    kCLOCK_Enc2         = (4U << 8U) | CCM_CCGR4_CG13_SHIFT, /*!< CCGR4, CG13  */
    kCLOCK_Enc3         = (4U << 8U) | CCM_CCGR4_CG14_SHIFT, /*!< CCGR4, CG14  */
    kCLOCK_Enc4         = (4U << 8U) | CCM_CCGR4_CG15_SHIFT, /*!< CCGR4, CG15  */

    /* CCM CCGR5 */
    kCLOCK_Rom      = (5U << 8U) | CCM_CCGR5_CG0_SHIFT,  /*!< CCGR5, CG0   */
    kCLOCK_Flexio1  = (5U << 8U) | CCM_CCGR5_CG1_SHIFT,  /*!< CCGR5, CG1   */
    kCLOCK_Wdog3    = (5U << 8U) | CCM_CCGR5_CG2_SHIFT,  /*!< CCGR5, CG2   */
    kCLOCK_Dma      = (5U << 8U) | CCM_CCGR5_CG3_SHIFT,  /*!< CCGR5, CG3   */
    kCLOCK_Kpp      = (5U << 8U) | CCM_CCGR5_CG4_SHIFT,  /*!< CCGR5, CG4   */
    kCLOCK_Wdog2    = (5U << 8U) | CCM_CCGR5_CG5_SHIFT,  /*!< CCGR5, CG5   */
    kCLOCK_Aips_tz4 = (5U << 8U) | CCM_CCGR5_CG6_SHIFT,  /*!< CCGR5, CG6   */
    kCLOCK_Spdif    = (5U << 8U) | CCM_CCGR5_CG7_SHIFT,  /*!< CCGR5, CG7   */
    kCLOCK_SimMain  = (5U << 8U) | CCM_CCGR5_CG8_SHIFT,  /*!< CCGR5, CG8   */
    kCLOCK_Sai1     = (5U << 8U) | CCM_CCGR5_CG9_SHIFT,  /*!< CCGR5, CG9   */
    kCLOCK_Sai2     = (5U << 8U) | CCM_CCGR5_CG10_SHIFT, /*!< CCGR5, CG10  */
    kCLOCK_Sai3     = (5U << 8U) | CCM_CCGR5_CG11_SHIFT, /*!< CCGR5, CG11  */
    kCLOCK_Lpuart1  = (5U << 8U) | CCM_CCGR5_CG12_SHIFT, /*!< CCGR5, CG12  */
    kCLOCK_Lpuart7  = (5U << 8U) | CCM_CCGR5_CG13_SHIFT, /*!< CCGR5, CG13  */
    kCLOCK_SnvsHp   = (5U << 8U) | CCM_CCGR5_CG14_SHIFT, /*!< CCGR5, CG14  */
    kCLOCK_SnvsLp   = (5U << 8U) | CCM_CCGR5_CG15_SHIFT, /*!< CCGR5, CG15  */

    /* CCM CCGR6 */
    kCLOCK_UsbOh3   = (6U << 8U) | CCM_CCGR6_CG0_SHIFT,  /*!< CCGR6, CG0   */
    kCLOCK_Usdhc1   = (6U << 8U) | CCM_CCGR6_CG1_SHIFT,  /*!< CCGR6, CG1   */
    kCLOCK_Usdhc2   = (6U << 8U) | CCM_CCGR6_CG2_SHIFT,  /*!< CCGR6, CG2   */
    kCLOCK_Dcdc     = (6U << 8U) | CCM_CCGR6_CG3_SHIFT,  /*!< CCGR6, CG3   */
    kCLOCK_Ipmux4   = (6U << 8U) | CCM_CCGR6_CG4_SHIFT,  /*!< CCGR6, CG4   */
    kCLOCK_FlexSpi  = (6U << 8U) | CCM_CCGR6_CG5_SHIFT,  /*!< CCGR6, CG5   */
    kCLOCK_Trng     = (6U << 8U) | CCM_CCGR6_CG6_SHIFT,  /*!< CCGR6, CG6   */
    kCLOCK_Lpuart8  = (6U << 8U) | CCM_CCGR6_CG7_SHIFT,  /*!< CCGR6, CG7   */
    kCLOCK_Timer4   = (6U << 8U) | CCM_CCGR6_CG8_SHIFT,  /*!< CCGR6, CG8   */
    kCLOCK_Aips_tz3 = (6U << 8U) | CCM_CCGR6_CG9_SHIFT,  /*!< CCGR6, CG9   */
    kCLOCK_SimPer   = (6U << 8U) | CCM_CCGR6_CG10_SHIFT, /*!< CCGR6, CG10  */
    kCLOCK_Anadig   = (6U << 8U) | CCM_CCGR6_CG11_SHIFT, /*!< CCGR6, CG11  */
    kCLOCK_Lpi2c4   = (6U << 8U) | CCM_CCGR6_CG12_SHIFT, /*!< CCGR6, CG12  */
    kCLOCK_Timer1   = (6U << 8U) | CCM_CCGR6_CG13_SHIFT, /*!< CCGR6, CG13  */
    kCLOCK_Timer2   = (6U << 8U) | CCM_CCGR6_CG14_SHIFT, /*!< CCGR6, CG14  */
    kCLOCK_Timer3   = (6U << 8U) | CCM_CCGR6_CG15_SHIFT, /*!< CCGR6, CG15  */

} clock_ip_name_t;
#define FSL_FEATURE_SOC_SEMC_COUNT (1)
#define SEMC_CLOCKS \
    {               \
        kCLOCK_Semc \
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to SEMC clocks for each instance. */
static const clock_ip_name_t s_semcClock[FSL_FEATURE_SOC_SEMC_COUNT] = SEMC_CLOCKS;
#if (defined(SEMC_EXSC_CLOCKS))
static const clock_ip_name_t s_semcExtClock[FSL_FEATURE_SOC_SEMC_COUNT] = SEMC_EXSC_CLOCKS;
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! KEY - This field should be written with 0xA55A when trigging an IP command.
 */
#define SEMC_IPCMD_KEY(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCMD_KEY_SHIFT)) & SEMC_IPCMD_KEY_MASK)

#define MAKE_STATUS(group, code) ((((group)*100L) + (code)))
#define kStatusGroup_SEMC   100/*!< Group number for SEMC status codes. */
#define kStatusGroup_Generic 0  /*!< Group number for generic status codes. */
enum
{
    kStatus_SEMC_InvalidDeviceType        = MAKE_STATUS(kStatusGroup_SEMC, 0), /*!< Invalid device type. */
    kStatus_SEMC_IpCommandExecutionError  = MAKE_STATUS(kStatusGroup_SEMC, 1), /*!< IP command execution error. */
    kStatus_SEMC_AxiCommandExecutionError = MAKE_STATUS(kStatusGroup_SEMC, 2), /*!< AXI command execution error. */
    kStatus_SEMC_InvalidMemorySize        = MAKE_STATUS(kStatusGroup_SEMC, 3), /*!< Invalid memory sie. */
    kStatus_SEMC_InvalidIpcmdDataSize     = MAKE_STATUS(kStatusGroup_SEMC, 4), /*!< Invalid IP command data size. */
    kStatus_SEMC_InvalidAddressPortWidth  = MAKE_STATUS(kStatusGroup_SEMC, 5), /*!< Invalid address port width. */
    kStatus_SEMC_InvalidDataPortWidth     = MAKE_STATUS(kStatusGroup_SEMC, 6), /*!< Invalid data port width. */
    kStatus_SEMC_InvalidSwPinmuxSelection = MAKE_STATUS(kStatusGroup_SEMC, 7), /*!< Invalid SW pinmux selection. */
    kStatus_SEMC_InvalidBurstLength       = MAKE_STATUS(kStatusGroup_SEMC, 8), /*!< Invalid burst length */
    /*! Invalid column address bit width. */
    kStatus_SEMC_InvalidColumnAddressBitWidth = MAKE_STATUS(kStatusGroup_SEMC, 9),
    kStatus_SEMC_InvalidBaseAddress           = MAKE_STATUS(kStatusGroup_SEMC, 10), /*!< Invalid base address. */
    kStatus_SEMC_InvalidTimerSetting          = MAKE_STATUS(kStatusGroup_SEMC, 11), /*!< Invalid timer setting. */
};

enum
{
    kStatus_Success         = MAKE_STATUS(kStatusGroup_Generic, 0), /*!< Generic status for Success. */
    kStatus_Fail            = MAKE_STATUS(kStatusGroup_Generic, 1), /*!< Generic status for Fail. */
    kStatus_ReadOnly        = MAKE_STATUS(kStatusGroup_Generic, 2), /*!< Generic status for read only failure. */
    kStatus_OutOfRange      = MAKE_STATUS(kStatusGroup_Generic, 3), /*!< Generic status for out of range access. */
    kStatus_InvalidArgument = MAKE_STATUS(kStatusGroup_Generic, 4), /*!< Generic status for invalid argument check. */
    kStatus_Timeout         = MAKE_STATUS(kStatusGroup_Generic, 5), /*!< Generic status for timeout. */
    kStatus_NoTransferInProgress =
    MAKE_STATUS(kStatusGroup_Generic, 6),            /*!< Generic status for no transfer in progress. */
    kStatus_Busy = MAKE_STATUS(kStatusGroup_Generic, 7), /*!< Generic status for module is busy. */
    kStatus_NoData =
    MAKE_STATUS(kStatusGroup_Generic, 8), /*!< Generic status for no data is found for the operation. */
};

/*! @brief SEMC memory device type. */
typedef enum _semc_mem_type
{
    kSEMC_MemType_SDRAM = 0, /*!< SDRAM */
    kSEMC_MemType_SRAM,      /*!< SRAM */
    kSEMC_MemType_NOR,       /*!< NOR */
    kSEMC_MemType_NAND,      /*!< NAND */
    kSEMC_MemType_8080       /*!< 8080. */
} semc_mem_type_t;

/*! @brief SEMC WAIT/RDY polarity. */
typedef enum _semc_waitready_polarity
{
    kSEMC_LowActive = 0, /*!< Low active. */
    kSEMC_HighActive,    /*!< High active. */
} semc_waitready_polarity_t;

/*! @brief SEMC SDRAM Chip selection . */
typedef enum _semc_sdram_cs
{
    kSEMC_SDRAM_CS0 = 0, /*!< SEMC SDRAM CS0. */
    kSEMC_SDRAM_CS1,     /*!< SEMC SDRAM CS1. */
    kSEMC_SDRAM_CS2,     /*!< SEMC SDRAM CS2. */
    kSEMC_SDRAM_CS3      /*!< SEMC SDRAM CS3. */
} semc_sdram_cs_t;

/*! @brief SEMC SRAM Chip selection . */
typedef enum _semc_sram_cs
{
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT == 0x04U)
    kSEMC_SRAM_CS0 = 0, /*!< SEMC SRAM CS0. */
    kSEMC_SRAM_CS1,     /*!< SEMC SRAM CS1. */
    kSEMC_SRAM_CS2,     /*!< SEMC SRAM CS2. */
    kSEMC_SRAM_CS3      /*!< SEMC SRAM CS3. */
#else
    kSEMC_SRAM_CS0        = 0, /*!< SEMC SRAM CS0. */
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */
} semc_sram_cs_t;

/*! @brief SEMC NAND device type. */
typedef enum _semc_nand_access_type
{
    kSEMC_NAND_ACCESS_BY_AXI = 0, /*!< Access to NAND flash by AXI bus. */
    kSEMC_NAND_ACCESS_BY_IPCMD,   /*!< Access to NAND flash by IP bus. */
} semc_nand_access_type_t;

#define SEMC_INTEN_IPCMDDONEEN_MASK              (0x1U)
#define SEMC_INTEN_IPCMDERREN_MASK               (0x2U)
#define SEMC_INTEN_AXICMDERREN_MASK              (0x4U)
#define SEMC_INTEN_AXICMDERREN_SHIFT             (2U)

#define SEMC_INTEN_AXIBUSERREN_MASK              (0x8U)
/*! @brief SEMC interrupts . */
typedef enum _semc_interrupt_enable
{
    kSEMC_IPCmdDoneInterrupt = SEMC_INTEN_IPCMDDONEEN_MASK, /*!< Ip command done interrupt. */
    kSEMC_IPCmdErrInterrupt  = SEMC_INTEN_IPCMDERREN_MASK,  /*!< Ip command error interrupt. */
    kSEMC_AXICmdErrInterrupt = SEMC_INTEN_AXICMDERREN_MASK, /*!< AXI command error interrupt. */
    kSEMC_AXIBusErrInterrupt = SEMC_INTEN_AXIBUSERREN_MASK  /*!< AXI bus error interrupt. */
} semc_interrupt_enable_t;

/*! @brief SEMC IP command data size in bytes. */
typedef enum _semc_ipcmd_datasize
{
    kSEMC_IPcmdDataSize_1bytes = 1, /*!< The IP command data size 1 byte. */
    kSEMC_IPcmdDataSize_2bytes,     /*!< The IP command data size 2 byte. */
    kSEMC_IPcmdDataSize_3bytes,     /*!< The IP command data size 3 byte. */
    kSEMC_IPcmdDataSize_4bytes      /*!< The IP command data size 4 byte. */
} semc_ipcmd_datasize_t;

/*! @brief SEMC auto-refresh timing. */
typedef enum _semc_refresh_time
{
    kSEMC_RefreshThreeClocks = 0x0U, /*!< The refresh timing with three bus clocks. */
    kSEMC_RefreshSixClocks,          /*!< The refresh timing with six bus clocks. */
    kSEMC_RefreshNineClocks          /*!< The refresh timing with nine bus clocks. */
} semc_refresh_time_t;

/*! @brief CAS latency */
typedef enum _semc_caslatency
{
    kSEMC_LatencyOne = 1, /*!< Latency  1. */
    kSEMC_LatencyTwo,     /*!< Latency  2. */
    kSEMC_LatencyThree,   /*!< Latency  3. */
} semc_caslatency_t;

/*! @brief SEMC sdram column address bit number. */
typedef enum _semc_sdram_column_bit_num
{
    kSEMC_SdramColunm_12bit = 0x0U, /*!< 12 bit. */
    kSEMC_SdramColunm_11bit,        /*!< 11 bit. */
    kSEMC_SdramColunm_10bit,        /*!< 10 bit. */
    kSEMC_SdramColunm_9bit,         /*!< 9 bit. */
#if defined(FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT) && (FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT)
    kSEMC_SdramColunm_8bit, /*!< 8 bit. */
#endif                      /* FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT */
} semc_sdram_column_bit_num_t;

/*! @brief SEMC sdram burst length. */
typedef enum _semc_sdram_burst_len
{
/*! According to ERR050577, Auto-refresh command may possibly fail to be triggered during
    long time back-to-back write (or read) when SDRAM controller's burst length is greater than 1. */
#if defined(FSL_FEATURE_SEMC_ERRATA_050577) && (FSL_FEATURE_SEMC_ERRATA_050577 == 0x01U)
    kSEMC_Sdram_BurstLen1 = 0, /*!< Burst length 1*/
#else
    kSEMC_Sdram_BurstLen1 = 0, /*!< Burst length 1*/
    kSEMC_Sdram_BurstLen2,     /*!< Burst length 2*/
    kSEMC_Sdram_BurstLen4,     /*!< Burst length 4*/
    kSEMC_Sdram_BurstLen8      /*!< Burst length 8*/
#endif /* FSL_FEATURE_SEMC_ERRATA_050577 */
} sem_sdram_burst_len_t;

/*! @brief SEMC nand column address bit number. */
typedef enum _semc_nand_column_bit_num
{
    kSEMC_NandColum_16bit = 0x0U, /*!< 16 bit. */
    kSEMC_NandColum_15bit,        /*!< 15 bit. */
    kSEMC_NandColum_14bit,        /*!< 14 bit. */
    kSEMC_NandColum_13bit,        /*!< 13 bit. */
    kSEMC_NandColum_12bit,        /*!< 12 bit. */
    kSEMC_NandColum_11bit,        /*!< 11 bit. */
    kSEMC_NandColum_10bit,        /*!< 10 bit. */
    kSEMC_NandColum_9bit,         /*!< 9 bit. */
} semc_nand_column_bit_num_t;

/*! @brief SEMC nand burst length. */
typedef enum _semc_nand_burst_len
{
    kSEMC_Nand_BurstLen1 = 0, /*!< Burst length 1*/
    kSEMC_Nand_BurstLen2,     /*!< Burst length 2*/
    kSEMC_Nand_BurstLen4,     /*!< Burst length 4*/
    kSEMC_Nand_BurstLen8,     /*!< Burst length 8*/
    kSEMC_Nand_BurstLen16,    /*!< Burst length 16*/
    kSEMC_Nand_BurstLen32,    /*!< Burst length 32*/
    kSEMC_Nand_BurstLen64     /*!< Burst length 64*/
} sem_nand_burst_len_t;

/*! @brief SEMC nor/sram column address bit number. */
typedef enum _semc_norsram_column_bit_num
{
    kSEMC_NorColum_12bit = 0x0U, /*!< 12 bit. */
    kSEMC_NorColum_11bit,        /*!< 11 bit. */
    kSEMC_NorColum_10bit,        /*!< 10 bit. */
    kSEMC_NorColum_9bit,         /*!< 9 bit. */
    kSEMC_NorColum_8bit,         /*!< 8 bit. */
    kSEMC_NorColum_7bit,         /*!< 7 bit. */
    kSEMC_NorColum_6bit,         /*!< 6 bit. */
    kSEMC_NorColum_5bit,         /*!< 5 bit. */
    kSEMC_NorColum_4bit,         /*!< 4 bit. */
    kSEMC_NorColum_3bit,         /*!< 3 bit. */
    kSEMC_NorColum_2bit          /*!< 2 bit. */
} semc_norsram_column_bit_num_t;

/*! @brief SEMC nor/sram burst length. */
typedef enum _semc_norsram_burst_len
{
    kSEMC_Nor_BurstLen1 = 0, /*!< Burst length 1*/
    kSEMC_Nor_BurstLen2,     /*!< Burst length 2*/
    kSEMC_Nor_BurstLen4,     /*!< Burst length 4*/
    kSEMC_Nor_BurstLen8,     /*!< Burst length 8*/
    kSEMC_Nor_BurstLen16,    /*!< Burst length 16*/
    kSEMC_Nor_BurstLen32,    /*!< Burst length 32*/
    kSEMC_Nor_BurstLen64     /*!< Burst length 64*/
} sem_norsram_burst_len_t;

/*! @brief SEMC dbi column address bit number. */
typedef enum _semc_dbi_column_bit_num
{
    kSEMC_Dbi_Colum_12bit = 0x0U, /*!< 12 bit. */
    kSEMC_Dbi_Colum_11bit,        /*!< 11 bit. */
    kSEMC_Dbi_Colum_10bit,        /*!< 10 bit. */
    kSEMC_Dbi_Colum_9bit,         /*!< 9 bit. */
    kSEMC_Dbi_Colum_8bit,         /*!< 8 bit. */
    kSEMC_Dbi_Colum_7bit,         /*!< 7 bit. */
    kSEMC_Dbi_Colum_6bit,         /*!< 6 bit. */
    kSEMC_Dbi_Colum_5bit,         /*!< 5 bit. */
    kSEMC_Dbi_Colum_4bit,         /*!< 4 bit. */
    kSEMC_Dbi_Colum_3bit,         /*!< 3 bit. */
    kSEMC_Dbi_Colum_2bit          /*!< 2 bit. */
} semc_dbi_column_bit_num_t;

/*! @brief SEMC dbi burst length. */
typedef enum _semc_dbi_burst_len
{
    kSEMC_Dbi_BurstLen1 = 0, /*!< Burst length 1*/
    kSEMC_Dbi_BurstLen2,     /*!< Burst length 2*/
    kSEMC_Dbi_Dbi_BurstLen4, /*!< Burst length 4*/
    kSEMC_Dbi_BurstLen8,     /*!< Burst length 8*/
    kSEMC_Dbi_BurstLen16,    /*!< Burst length 16*/
    kSEMC_Dbi_BurstLen32,    /*!< Burst length 32*/
    kSEMC_Dbi_BurstLen64     /*!< Burst length 64*/
} sem_dbi_burst_len_t;

#define SEMC_IOCR_MUX_A8_SHIFT                   (0U)
#define SEMC_IOCR_MUX_CSX0_SHIFT                 (3U)
/*! MUX_CSX0 - SEMC_CSX0 output selection
 *  0b000..NOR/PSRAM Address bit 24 (A24)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX0(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX0_SHIFT)) & SEMC_IOCR_MUX_CSX0_MASK)

#define SEMC_IOCR_MUX_CSX1_MASK                  (0x1C0U)
#define SEMC_IOCR_MUX_CSX1_SHIFT                 (6U)
/*! MUX_CSX1 - SEMC_CSX1 output selection
 *  0b000..NOR/PSRAM Address bit 25 (A25)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX1(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX1_SHIFT)) & SEMC_IOCR_MUX_CSX1_MASK)

#define SEMC_IOCR_MUX_CSX2_MASK                  (0xE00U)
#define SEMC_IOCR_MUX_CSX2_SHIFT                 (9U)
/*! MUX_CSX2 - SEMC_CSX2 output selection
 *  0b000..NOR/PSRAM Address bit 26 (A26)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX2(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX2_SHIFT)) & SEMC_IOCR_MUX_CSX2_MASK)

#define SEMC_IOCR_MUX_CSX3_MASK                  (0x7000U)
#define SEMC_IOCR_MUX_CSX3_SHIFT                 (12U)
/*! MUX_CSX3 - SEMC_CSX3 output selection
 *  0b000..NOR/PSRAM Address bit 27 (A27)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX3(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX3_SHIFT)) & SEMC_IOCR_MUX_CSX3_MASK)

#define SEMC_IOCR_MUX_RDY_MASK                   (0x38000U)
#define SEMC_IOCR_MUX_RDY_SHIFT                  (15U)
/*! @brief SEMC IOMUXC. */
typedef enum _semc_iomux_pin
{
    kSEMC_MUXA8   = SEMC_IOCR_MUX_A8_SHIFT,   /*!< MUX A8 pin. */
    kSEMC_MUXCSX0 = SEMC_IOCR_MUX_CSX0_SHIFT, /*!< MUX CSX0 pin */
    kSEMC_MUXCSX1 = SEMC_IOCR_MUX_CSX1_SHIFT, /*!< MUX CSX1 Pin.*/
    kSEMC_MUXCSX2 = SEMC_IOCR_MUX_CSX2_SHIFT, /*!< MUX CSX2 Pin. */
    kSEMC_MUXCSX3 = SEMC_IOCR_MUX_CSX3_SHIFT, /*!< MUX CSX3 Pin. */
    kSEMC_MUXRDY  = SEMC_IOCR_MUX_RDY_SHIFT   /*!< MUX RDY pin. */
} semc_iomux_pin;

/*! @brief SEMC NOR/PSRAM Address bit 27 A27. */
typedef enum _semc_iomux_nora27_pin
{
    kSEMC_MORA27_NONE    = 0,                        /*!< No NOR/SRAM A27 pin. */
    kSEMC_NORA27_MUXCSX3 = SEMC_IOCR_MUX_CSX3_SHIFT, /*!< MUX CSX3 Pin. */
    kSEMC_NORA27_MUXRDY  = SEMC_IOCR_MUX_RDY_SHIFT   /*!< MUX RDY pin. */
} semc_iomux_nora27_pin;

/*! @brief SEMC port size. */
typedef enum _semc_port_size
{
    kSEMC_PortSize8Bit = 0, /*!< 8-Bit port size. */
    kSEMC_PortSize16Bit,    /*!< 16-Bit port size. */
#if defined(FSL_FEATURE_SEMC_SUPPORT_SDRAM_PS_BITWIDTH) && (FSL_FEATURE_SEMC_SUPPORT_SDRAM_PS_BITWIDTH == 0x02U)
    kSEMC_PortSize32Bit /*!< 32-Bit port size. */
#endif                  /* FSL_FEATURE_SEMC_SUPPORT_SDRAM_PS_BITWIDTH */
} smec_port_size_t;

/*! @brief SEMC address mode. */
typedef enum _semc_addr_mode
{
    kSEMC_AddrDataMux = 0, /*!< SEMC address/data mux mode. */
    kSEMC_AdvAddrdataMux,  /*!< Advanced address/data mux mode. */
    kSEMC_AddrDataNonMux   /*!< Address/data non-mux mode. */
} semc_addr_mode_t;

/*! @brief SEMC DQS read strobe mode. */
typedef enum _semc_dqs_mode
{
    kSEMC_Loopbackinternal = 0, /*!< Dummy read strobe loopbacked internally. */
    kSEMC_Loopbackdqspad,       /*!< Dummy read strobe loopbacked from DQS pad. */
} semc_dqs_mode_t;

/*! @brief SEMC ADV signal active polarity. */
typedef enum _semc_adv_polarity
{
    kSEMC_AdvActiveLow = 0, /*!< Adv active low. */
    kSEMC_AdvActiveHigh,    /*!< Adv active high. */
} semc_adv_polarity_t;

/*! @brief SEMC sync mode. */
typedef enum _semc_sync_mode
{
    kSEMC_AsyncMode = 0, /*!< Async mode. */
    kSEMC_SyncMode,      /*!< Sync mode. */
} semc_sync_mode_t;

/*! @brief SEMC ADV signal level control. */
typedef enum _semc_adv_level_control
{
    kSEMC_AdvHigh = 0, /*!< Adv is high during address hold state. */
    kSEMC_AdvLow,      /*!< Adv is low during address hold state. */
} semc_adv_level_control_t;

/*! @brief SEMC RDY signal active polarity. */
typedef enum _semc_rdy_polarity
{
    kSEMC_RdyActiveLow = 0, /*!< Adv active low. */
    kSEMC_RdyActivehigh,    /*!< Adv active low. */
} semc_rdy_polarity_t;

/*! @brief SEMC IP command for NAND: address mode. */
typedef enum _semc_ipcmd_nand_addrmode
{
    kSEMC_NANDAM_ColumnRow = 0x0U, /*!< Address mode: column and row address(5Byte-CA0/CA1/RA0/RA1/RA2). */
    kSEMC_NANDAM_ColumnCA0,        /*!< Address mode: column address only(1 Byte-CA0).  */
    kSEMC_NANDAM_ColumnCA0CA1,     /*!< Address mode: column address only(2 Byte-CA0/CA1). */
    kSEMC_NANDAM_RawRA0,           /*!< Address mode: row address only(1 Byte-RA0). */
    kSEMC_NANDAM_RawRA0RA1,        /*!< Address mode: row address only(2 Byte-RA0/RA1). */
    kSEMC_NANDAM_RawRA0RA1RA2      /*!< Address mode: row address only(3 Byte-RA0).  */
} semc_ipcmd_nand_addrmode_t;

/*! @brief SEMC IP command for NAND： command mode. */
typedef enum _semc_ipcmd_nand_cmdmode
{
    kSEMC_NANDCM_Command = 0x2U,      /*!< command. */
    kSEMC_NANDCM_CommandHold,         /*!< Command hold. */
    kSEMC_NANDCM_CommandAddress,      /*!< Command address. */
    kSEMC_NANDCM_CommandAddressHold,  /*!< Command address hold.  */
    kSEMC_NANDCM_CommandAddressRead,  /*!< Command address read.  */
    kSEMC_NANDCM_CommandAddressWrite, /*!< Command address write.  */
    kSEMC_NANDCM_CommandRead,         /*!< Command read.  */
    kSEMC_NANDCM_CommandWrite,        /*!< Command write.  */
    kSEMC_NANDCM_Read,                /*!< Read.  */
    kSEMC_NANDCM_Write                /*!< Write.  */
} semc_ipcmd_nand_cmdmode_t;

/*! @brief SEMC NAND address option. */
typedef enum _semc_nand_address_option
{
    kSEMC_NandAddrOption_5byte_CA2RA3 = 0U, /*!< CA0+CA1+RA0+RA1+RA2 */
    kSEMC_NandAddrOption_4byte_CA2RA2 = 2U, /*!< CA0+CA1+RA0+RA1 */
    kSEMC_NandAddrOption_3byte_CA2RA1 = 4U, /*!< CA0+CA1+RA0 */
    kSEMC_NandAddrOption_4byte_CA1RA3 = 1U, /*!< CA0+RA0+RA1+RA2 */
    kSEMC_NandAddrOption_3byte_CA1RA2 = 3U, /*!< CA0+RA0+RA1 */
    kSEMC_NandAddrOption_2byte_CA1RA1 = 7U, /*!< CA0+RA0 */
} semc_nand_address_option_t;

/*! @brief SEMC IP command for NOR. */
typedef enum _semc_ipcmd_nor_dbi
{
    kSEMC_NORDBICM_Read = 0x2U, /*!< NOR read. */
    kSEMC_NORDBICM_Write        /*!< NOR write.  */
} semc_ipcmd_nor_dbi_t;

/*! @brief SEMC IP command for SRAM. */
typedef enum _semc_ipcmd_sram
{
    kSEMC_SRAMCM_ArrayRead = 0x2U, /*!< SRAM memory array read. */
    kSEMC_SRAMCM_ArrayWrite,       /*!< SRAM memory array write. */
    kSEMC_SRAMCM_RegRead,          /*!< SRAM memory register read. */
    kSEMC_SRAMCM_RegWrite          /*!< SRAM memory register write. */
} semc_ipcmd_sram_t;

/*! @brief SEMC IP command for SDARM. */
typedef enum _semc_ipcmd_sdram
{
    kSEMC_SDRAMCM_Read = 0x8U, /*!< SDRAM memory read. */
    kSEMC_SDRAMCM_Write,       /*!< SDRAM memory write. */
    kSEMC_SDRAMCM_Modeset,     /*!< SDRAM MODE SET. */
    kSEMC_SDRAMCM_Active,      /*!< SDRAM active. */
    kSEMC_SDRAMCM_AutoRefresh, /*!< SDRAM auto-refresh. */
    kSEMC_SDRAMCM_SelfRefresh, /*!< SDRAM self-refresh. */
    kSEMC_SDRAMCM_Precharge,   /*!< SDRAM precharge. */
    kSEMC_SDRAMCM_Prechargeall /*!< SDRAM precharge all. */
} semc_ipcmd_sdram_t;

/*! @brief SEMC SDRAM configuration structure.
 *
 * 1. The memory size in the configuration is in the unit of KB. So memsize_kbytes
 * should be set as 2^2, 2^3, 2^4 .etc which is base 2KB exponential function.
 * Take refer to BR0~BR3 register in RM for details.
 * 2. The prescalePeriod_N16Cycle is in unit of 16 clock cycle. It is a exception for prescaleTimer_n16cycle = 0,
 * it means the prescaler timer period is 256 * 16 clock cycles. For precalerIf precalerTimer_n16cycle not equal to 0,
 * The  prescaler timer period is prescalePeriod_N16Cycle * 16 clock cycles.
 * idleTimeout_NprescalePeriod,  refreshUrgThreshold_NprescalePeriod, refreshPeriod_NprescalePeriod are
 * similar to prescalePeriod_N16Cycle.
 *
 */
typedef struct _semc_sdram_config
{
    semc_iomux_pin csxPinMux;       /*!< CS pin mux. The kSEMC_MUXA8 is not valid in sdram pin mux setting. */
    uint32_t address;               /*!< The base address. */
    uint32_t memsize_kbytes;        /*!< The memory size in unit of kbytes. */
    smec_port_size_t portSize;      /*!< Port size. */
    sem_sdram_burst_len_t burstLen; /*!< Burst length. */
    semc_sdram_column_bit_num_t columnAddrBitNum; /*!< Column address bit number. */
    semc_caslatency_t casLatency;                 /*!< CAS latency. */
    uint8_t tPrecharge2Act_Ns;                    /*!< Precharge to active wait time in unit of nanosecond. */
    uint8_t tAct2ReadWrite_Ns;                    /*!< Act to read/write wait time in unit of nanosecond. */
    uint8_t tRefreshRecovery_Ns;                  /*!< Refresh recovery time in unit of nanosecond. */
    uint8_t tWriteRecovery_Ns;                    /*!< write recovery time in unit of nanosecond. */
    uint8_t tCkeOff_Ns;                           /*!< CKE off minimum time in unit of nanosecond. */
    uint8_t tAct2Prechage_Ns;                     /*!< Active to precharge in unit of nanosecond. */
    uint8_t tSelfRefRecovery_Ns;                  /*!< Self refresh recovery time in unit of nanosecond. */
    uint8_t tRefresh2Refresh_Ns;                  /*!< Refresh to refresh wait time in unit of nanosecond. */
    uint8_t tAct2Act_Ns;                          /*!< Active to active wait time in unit of nanosecond. */
    uint32_t tPrescalePeriod_Ns;     /*!< Prescaler timer period should not be larger than 256 * 16 * clock cycle. */
    uint32_t tIdleTimeout_Ns;        /*!< Idle timeout in unit of prescale time period. */
    uint32_t refreshPeriod_nsPerRow; /*!< Refresh timer period like 64ms * 1000000/8192 . */
    uint32_t refreshUrgThreshold;    /*!< Refresh urgent threshold. */
    uint8_t refreshBurstLen;         /*!< Refresh burst length. */
#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint8_t delayChain; /*!< Delay chain, which adds delays on DQS clock to compensate timings while DQS is faster than
                           read data. */
#endif                  /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */
} semc_sdram_config_t;

/*! @brief SEMC NAND device timing configuration structure. */
typedef struct _semc_nand_timing_config
{
    uint8_t tCeSetup_Ns;        /*!< CE setup time: tCS. */
    uint8_t tCeHold_Ns;         /*!< CE hold time: tCH. */
    uint8_t tCeInterval_Ns;     /*!< CE interval time:tCEITV. */
    uint8_t tWeLow_Ns;          /*!< WE low time: tWP. */
    uint8_t tWeHigh_Ns;         /*!< WE high time: tWH. */
    uint8_t tReLow_Ns;          /*!< RE low time: tRP. */
    uint8_t tReHigh_Ns;         /*!< RE high time: tREH. */
    uint8_t tTurnAround_Ns;     /*!< Turnaround time for async mode: tTA. */
    uint8_t tWehigh2Relow_Ns;   /*!< WE# high to RE# wait time: tWHR. */
    uint8_t tRehigh2Welow_Ns;   /*!< RE# high to WE# low wait time: tRHW. */
    uint8_t tAle2WriteStart_Ns; /*!< ALE to write start wait time: tADL. */
    uint8_t tReady2Relow_Ns;    /*!< Ready to RE# low min wait time: tRR. */
    uint8_t tWehigh2Busy_Ns;    /*!< WE# high to busy wait time: tWB. */
} semc_nand_timing_config_t;

/*! @brief SEMC NAND configuration structure. */
typedef struct _semc_nand_config
{
    semc_iomux_pin cePinMux;    /*!< The CE pin mux setting. The kSEMC_MUXRDY is not valid for CE pin setting. */
    uint32_t axiAddress;        /*!< The base address for AXI nand. */
    uint32_t axiMemsize_kbytes; /*!< The memory size in unit of kbytes for AXI nand. */
    uint32_t ipgAddress;        /*!< The base address for IPG nand . */
    uint32_t ipgMemsize_kbytes; /*!< The memory size in unit of kbytes for IPG nand. */
    semc_rdy_polarity_t rdyactivePolarity;       /*!< Wait ready polarity. */
    bool edoModeEnabled;                         /*!< EDO mode enabled. */
    semc_nand_column_bit_num_t columnAddrBitNum; /*!< Column address bit number. */
    semc_nand_address_option_t arrayAddrOption;  /*!< Address option. */
    sem_nand_burst_len_t burstLen;               /*!< Burst length. */
    smec_port_size_t portSize;                   /*!< Port size. */
    semc_nand_timing_config_t *timingConfig;     /*!< SEMC nand timing configuration. */
} semc_nand_config_t;

/*! @brief SEMC NOR configuration structure. */
typedef struct _semc_nor_config
{
    semc_iomux_pin cePinMux;                        /*!< The CE# pin mux setting. */
    semc_iomux_nora27_pin addr27;                   /*!< The Addr bit 27 pin mux setting. */
    uint32_t address;                               /*!< The base address. */
    uint32_t memsize_kbytes;                        /*!< The memory size in unit of kbytes. */
    uint8_t addrPortWidth;                          /*!< The address port width. */
    semc_rdy_polarity_t rdyactivePolarity;          /*!< Wait ready polarity. */
    semc_adv_polarity_t advActivePolarity;          /*!< ADV# polarity. */
    semc_norsram_column_bit_num_t columnAddrBitNum; /*!< Column address bit number. */
    semc_addr_mode_t addrMode;                      /*!< Address mode. */
    sem_norsram_burst_len_t burstLen;               /*!< Burst length. */
    smec_port_size_t portSize;                      /*!< Port size. */
    uint8_t tCeSetup_Ns;                            /*!< The CE setup time. */
    uint8_t tCeHold_Ns;                             /*!< The CE hold time. */
    uint8_t tCeInterval_Ns;                         /*!< CE interval minimum time. */
    uint8_t tAddrSetup_Ns;                          /*!< The address setup time. */
    uint8_t tAddrHold_Ns;                           /*!< The address hold time. */
    uint8_t tWeLow_Ns;                              /*!< WE low time for async mode. */
    uint8_t tWeHigh_Ns;                             /*!< WE high time for async mode. */
    uint8_t tReLow_Ns;                              /*!< RE low time for async mode. */
    uint8_t tReHigh_Ns;                             /*!< RE high time for async mode. */
    uint8_t tTurnAround_Ns;                         /*!< Turnaround time for async mode. */
    uint8_t tAddr2WriteHold_Ns;                     /*!< Address to write data hold time for async mode. */
#if defined(FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME)
    uint8_t tWriteSetup_Ns; /*!< Write data setup time for sync mode.*/
#endif
#if defined(FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME)
    uint8_t tWriteHold_Ns; /*!< Write hold time for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_NOR_LC_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_LC_TIME)
    uint8_t latencyCount; /*!< Latency count for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_NOR_RD_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_RD_TIME)
    uint8_t readCycle; /*!< Read cycle time for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint8_t delayChain; /*!< Delay chain, which adds delays on DQS clock to compensate timings while DQS is faster than
                           read data. */
#endif                  /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */
} semc_nor_config_t;

/*! @brief SEMC SRAM  configuration structure. */
typedef struct _semc_sram_config
{
    semc_iomux_pin cePinMux;               /*!< The CE# pin mux setting. */
    semc_iomux_nora27_pin addr27;          /*!< The Addr bit 27 pin mux setting. */
    uint32_t address;                      /*!< The base address. */
    uint32_t memsize_kbytes;               /*!< The memory size in unit of kbytes. */
    uint8_t addrPortWidth;                 /*!< The address port width. */
    semc_adv_polarity_t advActivePolarity; /*!< ADV# polarity 1: active high, 0: active low. */
    semc_addr_mode_t addrMode;             /*!< Address mode. */
    sem_norsram_burst_len_t burstLen;      /*!< Burst length. */
    smec_port_size_t portSize;             /*!< Port size. */
#if defined(SEMC_SRAMCR4_SYNCEN_MASK) && (SEMC_SRAMCR4_SYNCEN_MASK)
    semc_sync_mode_t syncMode; /*!< Sync mode. */
#endif                         /* SEMC_SRAMCR4_SYNCEN_MASK */
#if defined(SEMC_SRAMCR0_WAITEN_MASK) && (SEMC_SRAMCR0_WAITEN_MASK)
    bool waitEnable; /*!< Wait enable. */
#endif               /* SEMC_SRAMCR0_WAITEN_MASK */
#if defined(SEMC_SRAMCR0_WAITSP_MASK) && (SEMC_SRAMCR0_WAITSP_MASK)
    uint8_t waitSample; /*!< Wait sample. */
#endif                  /* SEMC_SRAMCR0_WAITSP_MASK */
#if defined(SEMC_SRAMCR4_ADVH_MASK) && (SEMC_SRAMCR4_ADVH_MASK)
    semc_adv_level_control_t advLevelCtrl; /*!< ADV# level control during address hold state, 1: low, 0: high. */
#endif                                     /* SEMC_SRAMCR4_ADVH_MASK */
    uint8_t tCeSetup_Ns;                   /*!< The CE setup time. */
    uint8_t tCeHold_Ns;                    /*!< The CE hold time. */
    uint8_t tCeInterval_Ns;                /*!< CE interval minimum time. */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME)
    uint8_t readHoldTime_Ns;    /*!< read hold time. */
#endif                          /* FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME */
    uint8_t tAddrSetup_Ns;      /*!< The address setup time. */
    uint8_t tAddrHold_Ns;       /*!< The address hold time. */
    uint8_t tWeLow_Ns;          /*!< WE low time for async mode. */
    uint8_t tWeHigh_Ns;         /*!< WE high time for async mode. */
    uint8_t tReLow_Ns;          /*!< RE low time for async mode. */
    uint8_t tReHigh_Ns;         /*!< RE high time for async mode. */
    uint8_t tTurnAround_Ns;     /*!< Turnaround time for async mode. */
    uint8_t tAddr2WriteHold_Ns; /*!< Address to write data hold time for async mode. */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME)
    uint8_t tWriteSetup_Ns; /*!<Write data setup time for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME)
    uint8_t tWriteHold_Ns; /*!<Write hold time for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME)
    uint8_t latencyCount; /*!<Latency count for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME)
    uint8_t readCycle; /*!<Read cycle time for sync mode. */
#endif
#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint8_t delayChain; /*!< Delay chain, which adds delays on DQS clock to compensate timings while DQS is faster than
                           read data. */
#endif                  /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */
} semc_sram_config_t;

/*! @brief SEMC DBI configuration structure. */
typedef struct _semc_dbi_config
{
    semc_iomux_pin csxPinMux;                   /*!< The CE# pin mux. */
    uint32_t address;                           /*!< The base address. */
    uint32_t memsize_kbytes;                    /*!< The memory size in unit of 4kbytes. */
    semc_dbi_column_bit_num_t columnAddrBitNum; /*!< Column address bit number. */
    sem_dbi_burst_len_t burstLen;               /*!< Burst length. */
    smec_port_size_t portSize;                  /*!< Port size. */
    uint8_t tCsxSetup_Ns;                       /*!< The CSX setup time. */
    uint8_t tCsxHold_Ns;                        /*!< The CSX hold time. */
    uint8_t tWexLow_Ns;                         /*!< WEX low time. */
    uint8_t tWexHigh_Ns;                        /*!< WEX high time. */
    uint8_t tRdxLow_Ns;                         /*!< RDX low time. */
    uint8_t tRdxHigh_Ns;                        /*!< RDX high time. */
    uint8_t tCsxInterval_Ns;                    /*!< Write data setup time.*/
} semc_dbi_config_t;

/*! @brief SEMC AXI queue a weight setting structure. */
typedef struct _semc_queuea_weight_struct
{
    uint32_t qos : 4;              /*!< weight of qos for queue 0 . */
    uint32_t aging : 4;            /*!< weight of aging for queue 0.*/
    uint32_t slaveHitSwith : 8;    /*!< weight of read/write switch for queue 0.*/
    uint32_t slaveHitNoswitch : 8; /*!< weight of read/write no switch for queue 0  .*/
} semc_queuea_weight_struct_t;

/*! @brief SEMC AXI queue a weight setting union. */
typedef union _semc_queuea_weight
{
    semc_queuea_weight_struct_t queueaConfig; /*!< Structure configuration for queueA. */
    uint32_t queueaValue; /*!< Configuration value for queueA which could directly write to the reg. */
} semc_queuea_weight_t;

/*! @brief SEMC AXI queue b weight setting structure. */
typedef struct _semc_queueb_weight_struct
{
    uint32_t qos : 4;           /*!< weight of qos for queue 1. */
    uint32_t aging : 4;         /*!< weight of aging for queue 1.*/
    uint32_t slaveHitSwith : 8; /*!< weight of read/write switch for queue 1.*/
    uint32_t weightPagehit : 8; /*!< weight of page hit for queue 1 only .*/
    uint32_t bankRotation : 8;  /*!< weight of bank rotation for queue 1 only .*/
} semc_queueb_weight_struct_t;

/*! @brief SEMC AXI queue b weight setting union. */
typedef union _semc_queueb_weight
{
    semc_queueb_weight_struct_t queuebConfig; /*!< Structure configuration for queueB. */
    uint32_t queuebValue; /*!< Configuration value for queueB which could directly write to the reg. */
} semc_queueb_weight_t;

/*! @brief SEMC AXI queue weight setting. */
typedef struct _semc_axi_queueweight
{
    bool queueaEnable;                 /*!< Enable queue a. */
    semc_queuea_weight_t queueaWeight; /*!< Weight settings for queue a. */
    bool queuebEnable;                 /*!< Enable queue b. */
    semc_queueb_weight_t queuebWeight; /*!< Weight settings for queue b. */
} semc_axi_queueweight_t;

/*!
 * @brief SEMC configuration structure.
 *
 * busTimeoutCycles: when busTimeoutCycles is zero, the bus timeout cycle is
 * 255*1024. otherwise the bus timeout cycles is busTimeoutCycles*1024.
 * cmdTimeoutCycles: is used for command execution timeout cycles. it's
 * similar to the busTimeoutCycles.
 */
typedef struct _semc_config_t
{
    semc_dqs_mode_t dqsMode;            /*!< Dummy read strobe mode: use enum in "semc_dqs_mode_t". */
    uint8_t cmdTimeoutCycles;           /*!< Command execution timeout cycles. */
    uint8_t busTimeoutCycles;           /*!< Bus timeout cycles. */
    semc_axi_queueweight_t queueWeight; /*!< AXI queue weight. */
} semc_config_t;

#define SEMC_MCR_SWRST_MASK                      (0x1U)
#define SEMC_MCR_SWRST_SHIFT                     (0U)
/*! SWRST - Software Reset
 */
#define SEMC_MCR_SWRST(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_SWRST_SHIFT)) & SEMC_MCR_SWRST_MASK)

#define SEMC_MCR_MDIS_MASK                       (0x2U)
#define SEMC_MCR_MDIS_SHIFT                      (1U)
/*! MDIS - Module Disable
 *  0b0..Module enabled
 *  0b1..Module disabled
 */
#define SEMC_MCR_MDIS(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_MDIS_SHIFT)) & SEMC_MCR_MDIS_MASK)

#define SEMC_MCR_DQSMD_MASK                      (0x4U)
#define SEMC_MCR_DQSMD_SHIFT                     (2U)
/*! DQSMD - DQS (read strobe) mode
 *  0b0..Dummy read strobe loopbacked internally
 *  0b1..Dummy read strobe loopbacked from DQS pad
 */
#define SEMC_MCR_DQSMD(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_DQSMD_SHIFT)) & SEMC_MCR_DQSMD_MASK)

#define SEMC_MCR_WPOL0_MASK                      (0x40U)
#define SEMC_MCR_WPOL0_SHIFT                     (6U)
/*! WPOL0 - WAIT/RDY# polarity for NOR/PSRAM
 *  0b0..Active low
 *  0b1..Active high
 */
#define SEMC_MCR_WPOL0(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_WPOL0_SHIFT)) & SEMC_MCR_WPOL0_MASK)

#define SEMC_MCR_WPOL1_MASK                      (0x80U)
#define SEMC_MCR_WPOL1_SHIFT                     (7U)
/*! WPOL1 - WAIT/RDY# polarity for NAND
 *  0b0..Active low
 *  0b1..Active high
 */
#define SEMC_MCR_WPOL1(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_WPOL1_SHIFT)) & SEMC_MCR_WPOL1_MASK)

#define SEMC_MCR_CTO_MASK                        (0xFF0000U)
#define SEMC_MCR_CTO_SHIFT                       (16U)
/*! CTO - Command Execution timeout cycles
 */
#define SEMC_MCR_CTO(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_CTO_SHIFT)) & SEMC_MCR_CTO_MASK)

#define SEMC_MCR_BTO_MASK                        (0x1F000000U)
#define SEMC_MCR_BTO_SHIFT                       (24U)
/*! BTO - Bus timeout cycles
 *  0b00000..255*1
 *  0b00001-0b11110..255*2 - 255*2^30
 *  0b11111..255*2^31
 */
#define SEMC_MCR_BTO(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_BTO_SHIFT)) & SEMC_MCR_BTO_MASK)
/*! @} */

/*! @name IOCR - IO Mux Control Register */
/*! @{ */

#define SEMC_IOCR_MUX_A8_MASK                    (0x7U)
#define SEMC_IOCR_MUX_A8_SHIFT                   (0U)
/*! MUX_A8 - SEMC_A8 output selection
 *  0b000..SDRAM Address bit (A8)
 *  0b001..NAND CE#
 *  0b010..NOR CE#
 *  0b011..PSRAM CE#
 *  0b100..DBI CSX
 *  0b101..SDRAM Address bit (A8)
 *  0b110..SDRAM Address bit (A8)
 *  0b111..SDRAM Address bit (A8)
 */
#define SEMC_IOCR_MUX_A8(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_A8_SHIFT)) & SEMC_IOCR_MUX_A8_MASK)

#define SEMC_IOCR_MUX_CSX0_MASK                  (0x38U)
#define SEMC_IOCR_MUX_CSX0_SHIFT                 (3U)
/*! MUX_CSX0 - SEMC_CSX0 output selection
 *  0b000..NOR/PSRAM Address bit 24 (A24)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX0(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX0_SHIFT)) & SEMC_IOCR_MUX_CSX0_MASK)

#define SEMC_IOCR_MUX_CSX1_MASK                  (0x1C0U)
#define SEMC_IOCR_MUX_CSX1_SHIFT                 (6U)
/*! MUX_CSX1 - SEMC_CSX1 output selection
 *  0b000..NOR/PSRAM Address bit 25 (A25)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX1(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX1_SHIFT)) & SEMC_IOCR_MUX_CSX1_MASK)

#define SEMC_IOCR_MUX_CSX2_MASK                  (0xE00U)
#define SEMC_IOCR_MUX_CSX2_SHIFT                 (9U)
/*! MUX_CSX2 - SEMC_CSX2 output selection
 *  0b000..NOR/PSRAM Address bit 26 (A26)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX2(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX2_SHIFT)) & SEMC_IOCR_MUX_CSX2_MASK)

#define SEMC_IOCR_MUX_CSX3_MASK                  (0x7000U)
#define SEMC_IOCR_MUX_CSX3_SHIFT                 (12U)
/*! MUX_CSX3 - SEMC_CSX3 output selection
 *  0b000..NOR/PSRAM Address bit 27 (A27)
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NAND CE#
 *  0b101..NOR CE#
 *  0b110..PSRAM CE#
 *  0b111..DBI CSX
 */
#define SEMC_IOCR_MUX_CSX3(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX3_SHIFT)) & SEMC_IOCR_MUX_CSX3_MASK)

#define SEMC_IOCR_MUX_RDY_MASK                   (0x38000U)
#define SEMC_IOCR_MUX_RDY_SHIFT                  (15U)
/*! MUX_RDY - SEMC_RDY function selection
 *  0b000..NAND Ready/Wait# input
 *  0b001..SDRAM CS1
 *  0b010..SDRAM CS2
 *  0b011..SDRAM CS3
 *  0b100..NOR CE#
 *  0b101..PSRAM CE#
 *  0b110..DBI CSX
 *  0b111..NOR/PSRAM Address bit 27
 */
#define SEMC_IOCR_MUX_RDY(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_RDY_SHIFT)) & SEMC_IOCR_MUX_RDY_MASK)
/*! @} */

/*! @name BMCR0 - Bus (AXI) Master Control Register 0 */
/*! @{ */

#define SEMC_BMCR0_WQOS_MASK                     (0xFU)
#define SEMC_BMCR0_WQOS_SHIFT                    (0U)
/*! WQOS - Weight of QOS calculation. AXI bus access has AxQOS signal set, which is used as a
 *    priority indicator for the associated write or read transaction. A higher value indicates a higher
 *    priority transaction. AxQOS is multiplied by WQOS to get weight score.
 */
#define SEMC_BMCR0_WQOS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WQOS_SHIFT)) & SEMC_BMCR0_WQOS_MASK)

#define SEMC_BMCR0_WAGE_MASK                     (0xF0U)
#define SEMC_BMCR0_WAGE_SHIFT                    (4U)
/*! WAGE - Weight of AGE calculation. Each command in queue has an age signal to indicate its wait
 *    period. It is multiplied by WAGE to get weight score.
 */
#define SEMC_BMCR0_WAGE(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WAGE_SHIFT)) & SEMC_BMCR0_WAGE_MASK)

#define SEMC_BMCR0_WSH_MASK                      (0xFF00U)
#define SEMC_BMCR0_WSH_SHIFT                     (8U)
/*! WSH - Weight of Slave Hit without read/write switch. This weight score is valid when queue
 *    command's slave is same as current executing command without read/write operation switch.
 */
#define SEMC_BMCR0_WSH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WSH_SHIFT)) & SEMC_BMCR0_WSH_MASK)

#define SEMC_BMCR0_WRWS_MASK                     (0xFF0000U)
#define SEMC_BMCR0_WRWS_SHIFT                    (16U)
/*! WRWS - Weight of slave hit with Read/Write Switch. This weight score is valid when queue
 *    command's slave is same as current executing command with read/write operation switch.
 */
#define SEMC_BMCR0_WRWS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WRWS_SHIFT)) & SEMC_BMCR0_WRWS_MASK)
/*! @} */

/*! @name BMCR1 - Bus (AXI) Master Control Register 1 */
/*! @{ */

#define SEMC_BMCR1_WQOS_MASK                     (0xFU)
#define SEMC_BMCR1_WQOS_SHIFT                    (0U)
/*! WQOS - Weight of QOS calculation. AXI bus access has AxQOS signal set, which is used as a
 *    priority indicator for the associated write or read transaction. A higher value indicates a higher
 *    priority transaction. AxQOS is multiplied by WQOS to get weight score.
 */
#define SEMC_BMCR1_WQOS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WQOS_SHIFT)) & SEMC_BMCR1_WQOS_MASK)

#define SEMC_BMCR1_WAGE_MASK                     (0xF0U)
#define SEMC_BMCR1_WAGE_SHIFT                    (4U)
/*! WAGE - Weight of AGE calculation. Each command in queue has an age signal to indicate its wait
 *    period. It is multiplied by WAGE to get weight score.
 */
#define SEMC_BMCR1_WAGE(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WAGE_SHIFT)) & SEMC_BMCR1_WAGE_MASK)

#define SEMC_BMCR1_WPH_MASK                      (0xFF00U)
#define SEMC_BMCR1_WPH_SHIFT                     (8U)
/*! WPH - Weight of Page Hit. This weight score is valid when queue command's page hits current executing command.
 */
#define SEMC_BMCR1_WPH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WPH_SHIFT)) & SEMC_BMCR1_WPH_MASK)

#define SEMC_BMCR1_WRWS_MASK                     (0xFF0000U)
#define SEMC_BMCR1_WRWS_SHIFT                    (16U)
/*! WRWS - Weight of slave hit without Read/Write Switch. This weight score is valid when queue
 *    command's read/write operation is same as current executing command.
 */
#define SEMC_BMCR1_WRWS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WRWS_SHIFT)) & SEMC_BMCR1_WRWS_MASK)

#define SEMC_BMCR1_WBR_MASK                      (0xFF000000U)
#define SEMC_BMCR1_WBR_SHIFT                     (24U)
/*! WBR - Weight of Bank Rotation. This weight score is valid when queue command's bank is not same as current executing command.
 */
#define SEMC_BMCR1_WBR(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WBR_SHIFT)) & SEMC_BMCR1_WBR_MASK)
/*! @} */

/*! @name BR - Base Register 0 (For SDRAM CS0 device)..Base Register 8 (For NAND device) */
/*! @{ */

#define SEMC_BR_VLD_MASK                         (0x1U)
#define SEMC_BR_VLD_SHIFT                        (0U)
/*! VLD - Valid
 */
#define SEMC_BR_VLD(x)                           (((uint32_t)(((uint32_t)(x)) << SEMC_BR_VLD_SHIFT)) & SEMC_BR_VLD_MASK)

#define SEMC_BR_MS_MASK                          (0x3EU)
#define SEMC_BR_MS_SHIFT                         (1U)
/*! MS - Memory size
 *  0b00000..4KB
 *  0b00001..8KB
 *  0b00010..16KB
 *  0b00011..32KB
 *  0b00100..64KB
 *  0b00101..128KB
 *  0b00110..256KB
 *  0b00111..512KB
 *  0b01000..1MB
 *  0b01001..2MB
 *  0b01010..4MB
 *  0b01011..8MB
 *  0b01100..16MB
 *  0b01101..32MB
 *  0b01110..64MB
 *  0b01111..128MB
 *  0b10000..256MB
 *  0b10001..512MB
 *  0b10010..1GB
 *  0b10011..2GB
 *  0b10100-0b11111..4GB
 */
#define SEMC_BR_MS(x)                            (((uint32_t)(((uint32_t)(x)) << SEMC_BR_MS_SHIFT)) & SEMC_BR_MS_MASK)

#define SEMC_BR_BA_MASK                          (0xFFFFF000U)
#define SEMC_BR_BA_SHIFT                         (12U)
/*! BA - Base Address
 */
#define SEMC_BR_BA(x)                            (((uint32_t)(((uint32_t)(x)) << SEMC_BR_BA_SHIFT)) & SEMC_BR_BA_MASK)
/*! @} */

/* The count of SEMC_BR */
#define SEMC_BR_COUNT                            (9U)

/*! @name INTEN - Interrupt Enable Register */
/*! @{ */

#define SEMC_INTEN_IPCMDDONEEN_MASK              (0x1U)
#define SEMC_INTEN_IPCMDDONEEN_SHIFT             (0U)
/*! IPCMDDONEEN - IP command done interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_IPCMDDONEEN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_IPCMDDONEEN_SHIFT)) & SEMC_INTEN_IPCMDDONEEN_MASK)

#define SEMC_INTEN_IPCMDERREN_MASK               (0x2U)
#define SEMC_INTEN_IPCMDERREN_SHIFT              (1U)
/*! IPCMDERREN - IP command error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_IPCMDERREN(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_IPCMDERREN_SHIFT)) & SEMC_INTEN_IPCMDERREN_MASK)

#define SEMC_INTEN_AXICMDERREN_MASK              (0x4U)
#define SEMC_INTEN_AXICMDERREN_SHIFT             (2U)
/*! AXICMDERREN - AXI command error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_AXICMDERREN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_AXICMDERREN_SHIFT)) & SEMC_INTEN_AXICMDERREN_MASK)

#define SEMC_INTEN_AXIBUSERREN_MASK              (0x8U)
#define SEMC_INTEN_AXIBUSERREN_SHIFT             (3U)
/*! AXIBUSERREN - AXI bus error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_AXIBUSERREN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_AXIBUSERREN_SHIFT)) & SEMC_INTEN_AXIBUSERREN_MASK)

#define SEMC_INTEN_NDPAGEENDEN_MASK              (0x10U)
#define SEMC_INTEN_NDPAGEENDEN_SHIFT             (4U)
/*! NDPAGEENDEN - NAND page end interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_NDPAGEENDEN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_NDPAGEENDEN_SHIFT)) & SEMC_INTEN_NDPAGEENDEN_MASK)

#define SEMC_INTEN_NDNOPENDEN_MASK               (0x20U)
#define SEMC_INTEN_NDNOPENDEN_SHIFT              (5U)
/*! NDNOPENDEN - NAND no pending AXI access interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_NDNOPENDEN(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_NDNOPENDEN_SHIFT)) & SEMC_INTEN_NDNOPENDEN_MASK)
/*! @} */

/*! @name INTR - Interrupt Enable Register */
/*! @{ */

#define SEMC_INTR_IPCMDDONE_MASK                 (0x1U)
#define SEMC_INTR_IPCMDDONE_SHIFT                (0U)
/*! IPCMDDONE - IP command normal done interrupt
 */
#define SEMC_INTR_IPCMDDONE(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_IPCMDDONE_SHIFT)) & SEMC_INTR_IPCMDDONE_MASK)

#define SEMC_INTR_IPCMDERR_MASK                  (0x2U)
#define SEMC_INTR_IPCMDERR_SHIFT                 (1U)
/*! IPCMDERR - IP command error done interrupt
 */
#define SEMC_INTR_IPCMDERR(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_IPCMDERR_SHIFT)) & SEMC_INTR_IPCMDERR_MASK)

#define SEMC_INTR_AXICMDERR_MASK                 (0x4U)
#define SEMC_INTR_AXICMDERR_SHIFT                (2U)
/*! AXICMDERR - AXI command error interrupt
 */
#define SEMC_INTR_AXICMDERR(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_AXICMDERR_SHIFT)) & SEMC_INTR_AXICMDERR_MASK)

#define SEMC_INTR_AXIBUSERR_MASK                 (0x8U)
#define SEMC_INTR_AXIBUSERR_SHIFT                (3U)
/*! AXIBUSERR - AXI bus error interrupt
 */
#define SEMC_INTR_AXIBUSERR(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_AXIBUSERR_SHIFT)) & SEMC_INTR_AXIBUSERR_MASK)

#define SEMC_INTR_NDPAGEEND_MASK                 (0x10U)
#define SEMC_INTR_NDPAGEEND_SHIFT                (4U)
/*! NDPAGEEND - NAND page end interrupt
 */
#define SEMC_INTR_NDPAGEEND(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_NDPAGEEND_SHIFT)) & SEMC_INTR_NDPAGEEND_MASK)

#define SEMC_INTR_NDNOPEND_MASK                  (0x20U)
#define SEMC_INTR_NDNOPEND_SHIFT                 (5U)
/*! NDNOPEND - NAND no pending AXI access interrupt
 */
#define SEMC_INTR_NDNOPEND(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_NDNOPEND_SHIFT)) & SEMC_INTR_NDNOPEND_MASK)
/*! @} */

/*! @name SDRAMCR0 - SDRAM control register 0 */
/*! @{ */

#define SEMC_SDRAMCR0_PS_MASK                    (0x1U)
#define SEMC_SDRAMCR0_PS_SHIFT                   (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_SDRAMCR0_PS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_PS_SHIFT)) & SEMC_SDRAMCR0_PS_MASK)

#define SEMC_SDRAMCR0_BL_MASK                    (0x70U)
#define SEMC_SDRAMCR0_BL_SHIFT                   (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..8
 *  0b101..8
 *  0b110..8
 *  0b111..8
 */
#define SEMC_SDRAMCR0_BL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_BL_SHIFT)) & SEMC_SDRAMCR0_BL_MASK)

#define SEMC_SDRAMCR0_COL_MASK                   (0x300U)
#define SEMC_SDRAMCR0_COL_SHIFT                  (8U)
/*! COL - Column address bit number
 *  0b00..12 bit
 *  0b01..11 bit
 *  0b10..10 bit
 *  0b11..9 bit
 */
#define SEMC_SDRAMCR0_COL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_COL_SHIFT)) & SEMC_SDRAMCR0_COL_MASK)

#define SEMC_SDRAMCR0_CL_MASK                    (0xC00U)
#define SEMC_SDRAMCR0_CL_SHIFT                   (10U)
/*! CL - CAS Latency
 *  0b00..1
 *  0b01..1
 *  0b10..2
 *  0b11..3
 */
#define SEMC_SDRAMCR0_CL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_CL_SHIFT)) & SEMC_SDRAMCR0_CL_MASK)
/*! @} */

/*! @name SDRAMCR1 - SDRAM control register 1 */
/*! @{ */

#define SEMC_SDRAMCR1_PRE2ACT_MASK               (0xFU)
#define SEMC_SDRAMCR1_PRE2ACT_SHIFT              (0U)
/*! PRE2ACT - PRECHARGE to ACT/Refresh wait time
 */
#define SEMC_SDRAMCR1_PRE2ACT(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_PRE2ACT_SHIFT)) & SEMC_SDRAMCR1_PRE2ACT_MASK)

#define SEMC_SDRAMCR1_ACT2RW_MASK                (0xF0U)
#define SEMC_SDRAMCR1_ACT2RW_SHIFT               (4U)
/*! ACT2RW - ACT to Read/Write wait time
 */
#define SEMC_SDRAMCR1_ACT2RW(x)                  (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_ACT2RW_SHIFT)) & SEMC_SDRAMCR1_ACT2RW_MASK)

#define SEMC_SDRAMCR1_RFRC_MASK                  (0x1F00U)
#define SEMC_SDRAMCR1_RFRC_SHIFT                 (8U)
/*! RFRC - Refresh recovery time
 */
#define SEMC_SDRAMCR1_RFRC(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_RFRC_SHIFT)) & SEMC_SDRAMCR1_RFRC_MASK)

#define SEMC_SDRAMCR1_WRC_MASK                   (0xE000U)
#define SEMC_SDRAMCR1_WRC_SHIFT                  (13U)
/*! WRC - Write recovery time
 */
#define SEMC_SDRAMCR1_WRC(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_WRC_SHIFT)) & SEMC_SDRAMCR1_WRC_MASK)

#define SEMC_SDRAMCR1_CKEOFF_MASK                (0xF0000U)
#define SEMC_SDRAMCR1_CKEOFF_SHIFT               (16U)
/*! CKEOFF - CKE OFF minimum time
 */
#define SEMC_SDRAMCR1_CKEOFF(x)                  (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_CKEOFF_SHIFT)) & SEMC_SDRAMCR1_CKEOFF_MASK)

#define SEMC_SDRAMCR1_ACT2PRE_MASK               (0xF00000U)
#define SEMC_SDRAMCR1_ACT2PRE_SHIFT              (20U)
/*! ACT2PRE - ACT to Precharge minimum time
 */
#define SEMC_SDRAMCR1_ACT2PRE(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_ACT2PRE_SHIFT)) & SEMC_SDRAMCR1_ACT2PRE_MASK)
/*! @} */

/*! @name SDRAMCR2 - SDRAM control register 2 */
/*! @{ */

#define SEMC_SDRAMCR2_SRRC_MASK                  (0xFFU)
#define SEMC_SDRAMCR2_SRRC_SHIFT                 (0U)
/*! SRRC - Self Refresh Recovery time
 */
#define SEMC_SDRAMCR2_SRRC(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_SRRC_SHIFT)) & SEMC_SDRAMCR2_SRRC_MASK)

#define SEMC_SDRAMCR2_REF2REF_MASK               (0xFF00U)
#define SEMC_SDRAMCR2_REF2REF_SHIFT              (8U)
/*! REF2REF - Refresh to Refresh wait time
 */
#define SEMC_SDRAMCR2_REF2REF(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_REF2REF_SHIFT)) & SEMC_SDRAMCR2_REF2REF_MASK)

#define SEMC_SDRAMCR2_ACT2ACT_MASK               (0xFF0000U)
#define SEMC_SDRAMCR2_ACT2ACT_SHIFT              (16U)
/*! ACT2ACT - ACT to ACT wait time
 */
#define SEMC_SDRAMCR2_ACT2ACT(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_ACT2ACT_SHIFT)) & SEMC_SDRAMCR2_ACT2ACT_MASK)

#define SEMC_SDRAMCR2_ITO_MASK                   (0xFF000000U)
#define SEMC_SDRAMCR2_ITO_SHIFT                  (24U)
/*! ITO - SDRAM Idle timeout
 *  0b00000000..IDLE timeout period is 256*Prescale period.
 *  0b00000001-0b11111111..IDLE timeout period is ITO*Prescale period.
 */
#define SEMC_SDRAMCR2_ITO(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_ITO_SHIFT)) & SEMC_SDRAMCR2_ITO_MASK)
/*! @} */

/*! @name SDRAMCR3 - SDRAM control register 3 */
/*! @{ */

#define SEMC_SDRAMCR3_REN_MASK                   (0x1U)
#define SEMC_SDRAMCR3_REN_SHIFT                  (0U)
/*! REN - Refresh enable
 */
#define SEMC_SDRAMCR3_REN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_REN_SHIFT)) & SEMC_SDRAMCR3_REN_MASK)

#define SEMC_SDRAMCR3_REBL_MASK                  (0xEU)
#define SEMC_SDRAMCR3_REBL_SHIFT                 (1U)
/*! REBL - Refresh burst length
 *  0b000..1
 *  0b001..2
 *  0b010..3
 *  0b011..4
 *  0b100..5
 *  0b101..6
 *  0b110..7
 *  0b111..8
 */
#define SEMC_SDRAMCR3_REBL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_REBL_SHIFT)) & SEMC_SDRAMCR3_REBL_MASK)

#define SEMC_SDRAMCR3_PRESCALE_MASK              (0xFF00U)
#define SEMC_SDRAMCR3_PRESCALE_SHIFT             (8U)
/*! PRESCALE - Prescaler timer period
 *  0b00000000..256*16 clock cycles
 *  0b00000001-0b11111111..PRESCALE*16 clock cycles
 */
#define SEMC_SDRAMCR3_PRESCALE(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_PRESCALE_SHIFT)) & SEMC_SDRAMCR3_PRESCALE_MASK)

#define SEMC_SDRAMCR3_RT_MASK                    (0xFF0000U)
#define SEMC_SDRAMCR3_RT_SHIFT                   (16U)
/*! RT - Refresh timer period
 *  0b00000000..256*Prescaler period
 *  0b00000001-0b11111111..RT*Prescaler period
 */
#define SEMC_SDRAMCR3_RT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_RT_SHIFT)) & SEMC_SDRAMCR3_RT_MASK)

#define SEMC_SDRAMCR3_UT_MASK                    (0xFF000000U)
#define SEMC_SDRAMCR3_UT_SHIFT                   (24U)
/*! UT - Refresh urgent threshold
 *  0b00000000..256*Prescaler period
 *  0b00000001-0b11111111..UT*Prescaler period
 */
#define SEMC_SDRAMCR3_UT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_UT_SHIFT)) & SEMC_SDRAMCR3_UT_MASK)
/*! @} */

/*! @name NANDCR0 - NAND control register 0 */
/*! @{ */

#define SEMC_NANDCR0_PS_MASK                     (0x1U)
#define SEMC_NANDCR0_PS_SHIFT                    (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_NANDCR0_PS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_PS_SHIFT)) & SEMC_NANDCR0_PS_MASK)

#define SEMC_NANDCR0_BL_MASK                     (0x70U)
#define SEMC_NANDCR0_BL_SHIFT                    (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_NANDCR0_BL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_BL_SHIFT)) & SEMC_NANDCR0_BL_MASK)

#define SEMC_NANDCR0_EDO_MASK                    (0x80U)
#define SEMC_NANDCR0_EDO_SHIFT                   (7U)
/*! EDO - EDO mode enabled
 *  0b0..EDO mode disabled
 *  0b1..EDO mode enabled
 */
#define SEMC_NANDCR0_EDO(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_EDO_SHIFT)) & SEMC_NANDCR0_EDO_MASK)

#define SEMC_NANDCR0_COL_MASK                    (0x700U)
#define SEMC_NANDCR0_COL_SHIFT                   (8U)
/*! COL - Column address bit number
 *  0b000..16
 *  0b001..15
 *  0b010..14
 *  0b011..13
 *  0b100..12
 *  0b101..11
 *  0b110..10
 *  0b111..9
 */
#define SEMC_NANDCR0_COL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_COL_SHIFT)) & SEMC_NANDCR0_COL_MASK)
/*! @} */

/*! @name NANDCR1 - NAND control register 1 */
/*! @{ */

#define SEMC_NANDCR1_CES_MASK                    (0xFU)
#define SEMC_NANDCR1_CES_SHIFT                   (0U)
/*! CES - CE setup time
 */
#define SEMC_NANDCR1_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CES_SHIFT)) & SEMC_NANDCR1_CES_MASK)

#define SEMC_NANDCR1_CEH_MASK                    (0xF0U)
#define SEMC_NANDCR1_CEH_SHIFT                   (4U)
/*! CEH - CE hold time
 */
#define SEMC_NANDCR1_CEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CEH_SHIFT)) & SEMC_NANDCR1_CEH_MASK)

#define SEMC_NANDCR1_WEL_MASK                    (0xF00U)
#define SEMC_NANDCR1_WEL_SHIFT                   (8U)
/*! WEL - WE# low time
 */
#define SEMC_NANDCR1_WEL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_WEL_SHIFT)) & SEMC_NANDCR1_WEL_MASK)

#define SEMC_NANDCR1_WEH_MASK                    (0xF000U)
#define SEMC_NANDCR1_WEH_SHIFT                   (12U)
/*! WEH - WE# high time
 */
#define SEMC_NANDCR1_WEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_WEH_SHIFT)) & SEMC_NANDCR1_WEH_MASK)

#define SEMC_NANDCR1_REL_MASK                    (0xF0000U)
#define SEMC_NANDCR1_REL_SHIFT                   (16U)
/*! REL - RE# low time
 */
#define SEMC_NANDCR1_REL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_REL_SHIFT)) & SEMC_NANDCR1_REL_MASK)

#define SEMC_NANDCR1_REH_MASK                    (0xF00000U)
#define SEMC_NANDCR1_REH_SHIFT                   (20U)
/*! REH - RE# high time
 */
#define SEMC_NANDCR1_REH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_REH_SHIFT)) & SEMC_NANDCR1_REH_MASK)

#define SEMC_NANDCR1_TA_MASK                     (0xF000000U)
#define SEMC_NANDCR1_TA_SHIFT                    (24U)
/*! TA - Turnaround time
 */
#define SEMC_NANDCR1_TA(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_TA_SHIFT)) & SEMC_NANDCR1_TA_MASK)

#define SEMC_NANDCR1_CEITV_MASK                  (0xF0000000U)
#define SEMC_NANDCR1_CEITV_SHIFT                 (28U)
/*! CEITV - CE# interval time
 */
#define SEMC_NANDCR1_CEITV(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CEITV_SHIFT)) & SEMC_NANDCR1_CEITV_MASK)
/*! @} */

/*! @name NANDCR2 - NAND control register 2 */
/*! @{ */

#define SEMC_NANDCR2_TWHR_MASK                   (0x3FU)
#define SEMC_NANDCR2_TWHR_SHIFT                  (0U)
/*! TWHR - WE# high to RE# low wait time
 */
#define SEMC_NANDCR2_TWHR(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TWHR_SHIFT)) & SEMC_NANDCR2_TWHR_MASK)

#define SEMC_NANDCR2_TRHW_MASK                   (0xFC0U)
#define SEMC_NANDCR2_TRHW_SHIFT                  (6U)
/*! TRHW - RE# high to WE# low wait time
 */
#define SEMC_NANDCR2_TRHW(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TRHW_SHIFT)) & SEMC_NANDCR2_TRHW_MASK)

#define SEMC_NANDCR2_TADL_MASK                   (0x3F000U)
#define SEMC_NANDCR2_TADL_SHIFT                  (12U)
/*! TADL - ALE to write data start wait time
 */
#define SEMC_NANDCR2_TADL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TADL_SHIFT)) & SEMC_NANDCR2_TADL_MASK)

#define SEMC_NANDCR2_TRR_MASK                    (0xFC0000U)
#define SEMC_NANDCR2_TRR_SHIFT                   (18U)
/*! TRR - Ready to RE# low wait time
 */
#define SEMC_NANDCR2_TRR(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TRR_SHIFT)) & SEMC_NANDCR2_TRR_MASK)

#define SEMC_NANDCR2_TWB_MASK                    (0x3F000000U)
#define SEMC_NANDCR2_TWB_SHIFT                   (24U)
/*! TWB - WE# high to busy wait time
 */
#define SEMC_NANDCR2_TWB(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TWB_SHIFT)) & SEMC_NANDCR2_TWB_MASK)
/*! @} */

/*! @name NANDCR3 - NAND control register 3 */
/*! @{ */

#define SEMC_NANDCR3_NDOPT1_MASK                 (0x1U)
#define SEMC_NANDCR3_NDOPT1_SHIFT                (0U)
/*! NDOPT1 - NAND option bit 1
 */
#define SEMC_NANDCR3_NDOPT1(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT1_SHIFT)) & SEMC_NANDCR3_NDOPT1_MASK)

#define SEMC_NANDCR3_NDOPT2_MASK                 (0x2U)
#define SEMC_NANDCR3_NDOPT2_SHIFT                (1U)
/*! NDOPT2 - NAND option bit 2
 */
#define SEMC_NANDCR3_NDOPT2(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT2_SHIFT)) & SEMC_NANDCR3_NDOPT2_MASK)

#define SEMC_NANDCR3_NDOPT3_MASK                 (0x4U)
#define SEMC_NANDCR3_NDOPT3_SHIFT                (2U)
/*! NDOPT3 - NAND option bit 3
 */
#define SEMC_NANDCR3_NDOPT3(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT3_SHIFT)) & SEMC_NANDCR3_NDOPT3_MASK)
/*! @} */

/*! @name NORCR0 - NOR control register 0 */
/*! @{ */

#define SEMC_NORCR0_PS_MASK                      (0x1U)
#define SEMC_NORCR0_PS_SHIFT                     (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_NORCR0_PS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_PS_SHIFT)) & SEMC_NORCR0_PS_MASK)

#define SEMC_NORCR0_BL_MASK                      (0x70U)
#define SEMC_NORCR0_BL_SHIFT                     (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_NORCR0_BL(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_BL_SHIFT)) & SEMC_NORCR0_BL_MASK)

#define SEMC_NORCR0_AM_MASK                      (0x300U)
#define SEMC_NORCR0_AM_SHIFT                     (8U)
/*! AM - Address Mode
 *  0b00..Address/Data MUX mode (ADMUX)
 *  0b01..Advanced Address/Data MUX mode (AADM)
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define SEMC_NORCR0_AM(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_AM_SHIFT)) & SEMC_NORCR0_AM_MASK)

#define SEMC_NORCR0_ADVP_MASK                    (0x400U)
#define SEMC_NORCR0_ADVP_SHIFT                   (10U)
/*! ADVP - ADV# polarity
 *  0b0..ADV# is active low.
 *  0b1..ADV# is active high.
 */
#define SEMC_NORCR0_ADVP(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_ADVP_SHIFT)) & SEMC_NORCR0_ADVP_MASK)

#define SEMC_NORCR0_COL_MASK                     (0xF000U)
#define SEMC_NORCR0_COL_SHIFT                    (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_NORCR0_COL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_COL_SHIFT)) & SEMC_NORCR0_COL_MASK)
/*! @} */

/*! @name NORCR1 - NOR control register 1 */
/*! @{ */

#define SEMC_NORCR1_CES_MASK                     (0xFU)
#define SEMC_NORCR1_CES_SHIFT                    (0U)
/*! CES - CE setup time
 */
#define SEMC_NORCR1_CES(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_CES_SHIFT)) & SEMC_NORCR1_CES_MASK)

#define SEMC_NORCR1_CEH_MASK                     (0xF0U)
#define SEMC_NORCR1_CEH_SHIFT                    (4U)
/*! CEH - CE hold time
 */
#define SEMC_NORCR1_CEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_CEH_SHIFT)) & SEMC_NORCR1_CEH_MASK)

#define SEMC_NORCR1_AS_MASK                      (0xF00U)
#define SEMC_NORCR1_AS_SHIFT                     (8U)
/*! AS - Address setup time
 */
#define SEMC_NORCR1_AS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_AS_SHIFT)) & SEMC_NORCR1_AS_MASK)

#define SEMC_NORCR1_AH_MASK                      (0xF000U)
#define SEMC_NORCR1_AH_SHIFT                     (12U)
/*! AH - Address hold time
 */
#define SEMC_NORCR1_AH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_AH_SHIFT)) & SEMC_NORCR1_AH_MASK)

#define SEMC_NORCR1_WEL_MASK                     (0xF0000U)
#define SEMC_NORCR1_WEL_SHIFT                    (16U)
/*! WEL - WE low time
 */
#define SEMC_NORCR1_WEL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_WEL_SHIFT)) & SEMC_NORCR1_WEL_MASK)

#define SEMC_NORCR1_WEH_MASK                     (0xF00000U)
#define SEMC_NORCR1_WEH_SHIFT                    (20U)
/*! WEH - WE high time
 */
#define SEMC_NORCR1_WEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_WEH_SHIFT)) & SEMC_NORCR1_WEH_MASK)

#define SEMC_NORCR1_REL_MASK                     (0xF000000U)
#define SEMC_NORCR1_REL_SHIFT                    (24U)
/*! REL - RE low time
 */
#define SEMC_NORCR1_REL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_REL_SHIFT)) & SEMC_NORCR1_REL_MASK)

#define SEMC_NORCR1_REH_MASK                     (0xF0000000U)
#define SEMC_NORCR1_REH_SHIFT                    (28U)
/*! REH - RE high time
 */
#define SEMC_NORCR1_REH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_REH_SHIFT)) & SEMC_NORCR1_REH_MASK)
/*! @} */

/*! @name NORCR2 - NOR control register 2 */
/*! @{ */

#define SEMC_NORCR2_TA_MASK                      (0xF00U)
#define SEMC_NORCR2_TA_SHIFT                     (8U)
/*! TA - Turnaround time
 */
#define SEMC_NORCR2_TA(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_TA_SHIFT)) & SEMC_NORCR2_TA_MASK)

#define SEMC_NORCR2_AWDH_MASK                    (0xF000U)
#define SEMC_NORCR2_AWDH_SHIFT                   (12U)
/*! AWDH - Address to write data hold time
 */
#define SEMC_NORCR2_AWDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_AWDH_SHIFT)) & SEMC_NORCR2_AWDH_MASK)

#define SEMC_NORCR2_CEITV_MASK                   (0xF000000U)
#define SEMC_NORCR2_CEITV_SHIFT                  (24U)
/*! CEITV - CE# interval time
 */
#define SEMC_NORCR2_CEITV(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_CEITV_SHIFT)) & SEMC_NORCR2_CEITV_MASK)
/*! @} */

/*! @name SRAMCR0 - SRAM control register 0 */
/*! @{ */

#define SEMC_SRAMCR0_PS_MASK                     (0x1U)
#define SEMC_SRAMCR0_PS_SHIFT                    (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_SRAMCR0_PS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_PS_SHIFT)) & SEMC_SRAMCR0_PS_MASK)

#define SEMC_SRAMCR0_BL_MASK                     (0x70U)
#define SEMC_SRAMCR0_BL_SHIFT                    (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_SRAMCR0_BL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_BL_SHIFT)) & SEMC_SRAMCR0_BL_MASK)

#define SEMC_SRAMCR0_AM_MASK                     (0x300U)
#define SEMC_SRAMCR0_AM_SHIFT                    (8U)
/*! AM - Address Mode
 *  0b00..Address/Data MUX mode (ADMUX)
 *  0b01..Advanced Address/Data MUX mode (AADM)
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define SEMC_SRAMCR0_AM(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_AM_SHIFT)) & SEMC_SRAMCR0_AM_MASK)

#define SEMC_SRAMCR0_ADVP_MASK                   (0x400U)
#define SEMC_SRAMCR0_ADVP_SHIFT                  (10U)
/*! ADVP - ADV# polarity
 *  0b0..ADV# is active low.
 *  0b1..ADV# is active high.
 */
#define SEMC_SRAMCR0_ADVP(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_ADVP_SHIFT)) & SEMC_SRAMCR0_ADVP_MASK)

#define SEMC_SRAMCR0_COL_MASK                    (0xF000U)
#define SEMC_SRAMCR0_COL_SHIFT                   (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_SRAMCR0_COL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_COL_SHIFT)) & SEMC_SRAMCR0_COL_MASK)
/*! @} */

/*! @name SRAMCR1 - SRAM control register 1 */
/*! @{ */

#define SEMC_SRAMCR1_CES_MASK                    (0xFU)
#define SEMC_SRAMCR1_CES_SHIFT                   (0U)
/*! CES - CE setup time
 */
#define SEMC_SRAMCR1_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_CES_SHIFT)) & SEMC_SRAMCR1_CES_MASK)

#define SEMC_SRAMCR1_CEH_MASK                    (0xF0U)
#define SEMC_SRAMCR1_CEH_SHIFT                   (4U)
/*! CEH - CE hold time
 */
#define SEMC_SRAMCR1_CEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_CEH_SHIFT)) & SEMC_SRAMCR1_CEH_MASK)

#define SEMC_SRAMCR1_AS_MASK                     (0xF00U)
#define SEMC_SRAMCR1_AS_SHIFT                    (8U)
/*! AS - Address setup time
 */
#define SEMC_SRAMCR1_AS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_AS_SHIFT)) & SEMC_SRAMCR1_AS_MASK)

#define SEMC_SRAMCR1_AH_MASK                     (0xF000U)
#define SEMC_SRAMCR1_AH_SHIFT                    (12U)
/*! AH - Address hold time
 */
#define SEMC_SRAMCR1_AH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_AH_SHIFT)) & SEMC_SRAMCR1_AH_MASK)

#define SEMC_SRAMCR1_WEL_MASK                    (0xF0000U)
#define SEMC_SRAMCR1_WEL_SHIFT                   (16U)
/*! WEL - WE low time
 */
#define SEMC_SRAMCR1_WEL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_WEL_SHIFT)) & SEMC_SRAMCR1_WEL_MASK)

#define SEMC_SRAMCR1_WEH_MASK                    (0xF00000U)
#define SEMC_SRAMCR1_WEH_SHIFT                   (20U)
/*! WEH - WE high time
 */
#define SEMC_SRAMCR1_WEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_WEH_SHIFT)) & SEMC_SRAMCR1_WEH_MASK)

#define SEMC_SRAMCR1_REL_MASK                    (0xF000000U)
#define SEMC_SRAMCR1_REL_SHIFT                   (24U)
/*! REL - RE low time
 */
#define SEMC_SRAMCR1_REL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_REL_SHIFT)) & SEMC_SRAMCR1_REL_MASK)

#define SEMC_SRAMCR1_REH_MASK                    (0xF0000000U)
#define SEMC_SRAMCR1_REH_SHIFT                   (28U)
/*! REH - RE high time
 */
#define SEMC_SRAMCR1_REH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_REH_SHIFT)) & SEMC_SRAMCR1_REH_MASK)
/*! @} */

/*! @name SRAMCR2 - SRAM control register 2 */
/*! @{ */

#define SEMC_SRAMCR2_TA_MASK                     (0xF00U)
#define SEMC_SRAMCR2_TA_SHIFT                    (8U)
/*! TA - Turnaround time
 */
#define SEMC_SRAMCR2_TA(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_TA_SHIFT)) & SEMC_SRAMCR2_TA_MASK)

#define SEMC_SRAMCR2_AWDH_MASK                   (0xF000U)
#define SEMC_SRAMCR2_AWDH_SHIFT                  (12U)
/*! AWDH - Address to write data hold time
 */
#define SEMC_SRAMCR2_AWDH(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_AWDH_SHIFT)) & SEMC_SRAMCR2_AWDH_MASK)

#define SEMC_SRAMCR2_CEITV_MASK                  (0xF000000U)
#define SEMC_SRAMCR2_CEITV_SHIFT                 (24U)
/*! CEITV - CE# interval time
 */
#define SEMC_SRAMCR2_CEITV(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_CEITV_SHIFT)) & SEMC_SRAMCR2_CEITV_MASK)
/*! @} */

/*! @name DBICR0 - DBI-B control register 0 */
/*! @{ */

#define SEMC_DBICR0_PS_MASK                      (0x1U)
#define SEMC_DBICR0_PS_SHIFT                     (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_DBICR0_PS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_PS_SHIFT)) & SEMC_DBICR0_PS_MASK)

#define SEMC_DBICR0_BL_MASK                      (0x70U)
#define SEMC_DBICR0_BL_SHIFT                     (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_DBICR0_BL(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_BL_SHIFT)) & SEMC_DBICR0_BL_MASK)

#define SEMC_DBICR0_COL_MASK                     (0xF000U)
#define SEMC_DBICR0_COL_SHIFT                    (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_DBICR0_COL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_COL_SHIFT)) & SEMC_DBICR0_COL_MASK)
/*! @} */

/*! @name DBICR1 - DBI-B control register 1 */
/*! @{ */

#define SEMC_DBICR1_CES_MASK                     (0xFU)
#define SEMC_DBICR1_CES_SHIFT                    (0U)
/*! CES - CSX Setup Time
 */
#define SEMC_DBICR1_CES(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_CES_SHIFT)) & SEMC_DBICR1_CES_MASK)

#define SEMC_DBICR1_CEH_MASK                     (0xF0U)
#define SEMC_DBICR1_CEH_SHIFT                    (4U)
/*! CEH - CSX Hold Time
 */
#define SEMC_DBICR1_CEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_CEH_SHIFT)) & SEMC_DBICR1_CEH_MASK)

#define SEMC_DBICR1_WEL_MASK                     (0xF00U)
#define SEMC_DBICR1_WEL_SHIFT                    (8U)
/*! WEL - WRX Low Time
 */
#define SEMC_DBICR1_WEL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_WEL_SHIFT)) & SEMC_DBICR1_WEL_MASK)

#define SEMC_DBICR1_WEH_MASK                     (0xF000U)
#define SEMC_DBICR1_WEH_SHIFT                    (12U)
/*! WEH - WRX High Time
 */
#define SEMC_DBICR1_WEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_WEH_SHIFT)) & SEMC_DBICR1_WEH_MASK)

#define SEMC_DBICR1_REL_MASK                     (0xF0000U)
#define SEMC_DBICR1_REL_SHIFT                    (16U)
/*! REL - RDX Low Time bit [3:0]
 */
#define SEMC_DBICR1_REL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REL_SHIFT)) & SEMC_DBICR1_REL_MASK)

#define SEMC_DBICR1_REH_MASK                     (0xF00000U)
#define SEMC_DBICR1_REH_SHIFT                    (20U)
/*! REH - RDX High Time bit [3:0]
 */
#define SEMC_DBICR1_REH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REH_SHIFT)) & SEMC_DBICR1_REH_MASK)

#define SEMC_DBICR1_CEITV_MASK                   (0xF000000U)
#define SEMC_DBICR1_CEITV_SHIFT                  (24U)
/*! CEITV - CSX interval time
 */
#define SEMC_DBICR1_CEITV(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_CEITV_SHIFT)) & SEMC_DBICR1_CEITV_MASK)

#define SEMC_DBICR1_REL2_MASK                    (0x30000000U)
#define SEMC_DBICR1_REL2_SHIFT                   (28U)
/*! REL2 - RDX Low Time bit [5:4]
 */
#define SEMC_DBICR1_REL2(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REL2_SHIFT)) & SEMC_DBICR1_REL2_MASK)

#define SEMC_DBICR1_REH2_MASK                    (0xC0000000U)
#define SEMC_DBICR1_REH2_SHIFT                   (30U)
/*! REH2 - RDX High Time bit [5:4]
 */
#define SEMC_DBICR1_REH2(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REH2_SHIFT)) & SEMC_DBICR1_REH2_MASK)
/*! @} */

/*! @name IPCR0 - IP Command control register 0 */
/*! @{ */

#define SEMC_IPCR0_SA_MASK                       (0xFFFFFFFFU)
#define SEMC_IPCR0_SA_SHIFT                      (0U)
/*! SA - Slave address
 */
#define SEMC_IPCR0_SA(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR0_SA_SHIFT)) & SEMC_IPCR0_SA_MASK)
/*! @} */

/*! @name IPCR1 - IP Command control register 1 */
/*! @{ */

#define SEMC_IPCR1_DATSZ_MASK                    (0x7U)
#define SEMC_IPCR1_DATSZ_SHIFT                   (0U)
/*! DATSZ - Data Size in Byte
 *  0b000..4
 *  0b001..1
 *  0b010..2
 *  0b011..3
 *  0b100..4
 *  0b101..4
 *  0b110..4
 *  0b111..4
 */
#define SEMC_IPCR1_DATSZ(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR1_DATSZ_SHIFT)) & SEMC_IPCR1_DATSZ_MASK)
/*! @} */

/*! @name IPCR2 - IP Command control register 2 */
/*! @{ */

#define SEMC_IPCR2_BM0_MASK                      (0x1U)
#define SEMC_IPCR2_BM0_SHIFT                     (0U)
/*! BM0 - Byte Mask for Byte 0 (IPTXD bit 7:0)
 *  0b0..Byte Unmasked
 *  0b1..Byte Masked
 */
#define SEMC_IPCR2_BM0(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM0_SHIFT)) & SEMC_IPCR2_BM0_MASK)

#define SEMC_IPCR2_BM1_MASK                      (0x2U)
#define SEMC_IPCR2_BM1_SHIFT                     (1U)
/*! BM1 - Byte Mask for Byte 1 (IPTXD bit 15:8)
 *  0b0..Byte Unmasked
 *  0b1..Byte Masked
 */
#define SEMC_IPCR2_BM1(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM1_SHIFT)) & SEMC_IPCR2_BM1_MASK)

#define SEMC_IPCR2_BM2_MASK                      (0x4U)
#define SEMC_IPCR2_BM2_SHIFT                     (2U)
/*! BM2 - Byte Mask for Byte 2 (IPTXD bit 23:16)
 *  0b0..Byte Unmasked
 *  0b1..Byte Masked
 */
#define SEMC_IPCR2_BM2(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM2_SHIFT)) & SEMC_IPCR2_BM2_MASK)

#define SEMC_IPCR2_BM3_MASK                      (0x8U)
#define SEMC_IPCR2_BM3_SHIFT                     (3U)
/*! BM3 - Byte Mask for Byte 3 (IPTXD bit 31:24)
 *  0b0..Byte Unmasked
 *  0b1..Byte Masked
 */
#define SEMC_IPCR2_BM3(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM3_SHIFT)) & SEMC_IPCR2_BM3_MASK)
/*! @} */

/*! @name IPCMD - IP Command register */
/*! @{ */

#define SEMC_IPCMD_CMD_MASK                      (0xFFFFU)
#define SEMC_IPCMD_CMD_SHIFT                     (0U)
#define SEMC_IPCMD_CMD(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCMD_CMD_SHIFT)) & SEMC_IPCMD_CMD_MASK)

#define SEMC_IPCMD_KEY_MASK                      (0xFFFF0000U)
#define SEMC_IPCMD_KEY_SHIFT                     (16U)
/*! KEY - This field should be written with 0xA55A when trigging an IP command.
 */
#define SEMC_IPCMD_KEY(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCMD_KEY_SHIFT)) & SEMC_IPCMD_KEY_MASK)
/*! @} */

/*! @name IPTXDAT - TX DATA register (for IP Command) */
/*! @{ */

#define SEMC_IPTXDAT_DAT_MASK                    (0xFFFFFFFFU)
#define SEMC_IPTXDAT_DAT_SHIFT                   (0U)
/*! DAT - data
 */
#define SEMC_IPTXDAT_DAT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPTXDAT_DAT_SHIFT)) & SEMC_IPTXDAT_DAT_MASK)
/*! @} */

/*! @name IPRXDAT - RX DATA register (for IP Command) */
/*! @{ */

#define SEMC_IPRXDAT_DAT_MASK                    (0xFFFFFFFFU)
#define SEMC_IPRXDAT_DAT_SHIFT                   (0U)
/*! DAT - data
 */
#define SEMC_IPRXDAT_DAT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPRXDAT_DAT_SHIFT)) & SEMC_IPRXDAT_DAT_MASK)
/*! @} */

/*! @name STS0 - Status register 0 */
/*! @{ */

#define SEMC_STS0_IDLE_MASK                      (0x1U)
#define SEMC_STS0_IDLE_SHIFT                     (0U)
/*! IDLE - Indicating whether SEMC is in IDLE state.
 */
#define SEMC_STS0_IDLE(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_STS0_IDLE_SHIFT)) & SEMC_STS0_IDLE_MASK)

#define SEMC_STS0_NARDY_MASK                     (0x2U)
#define SEMC_STS0_NARDY_SHIFT                    (1U)
/*! NARDY - Indicating NAND device Ready/WAIT# pin level.
 *  0b0..NAND device is not ready
 *  0b1..NAND device is ready
 */
#define SEMC_STS0_NARDY(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_STS0_NARDY_SHIFT)) & SEMC_STS0_NARDY_MASK)
/*! @} */

/*! @name STS2 - Status register 2 */
/*! @{ */

#define SEMC_STS2_NDWRPEND_MASK                  (0x8U)
#define SEMC_STS2_NDWRPEND_SHIFT                 (3U)
/*! NDWRPEND - This field indicating whether there is pending AXI command (write) to NAND device.
 *  0b0..No pending
 *  0b1..Pending
 */
#define SEMC_STS2_NDWRPEND(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_STS2_NDWRPEND_SHIFT)) & SEMC_STS2_NDWRPEND_MASK)
/*! @} */

/*! @name STS12 - Status register 12 */
/*! @{ */

#define SEMC_STS12_NDADDR_MASK                   (0xFFFFFFFFU)
#define SEMC_STS12_NDADDR_SHIFT                  (0U)
/*! NDADDR - This field indicating the last write address (AXI command) to NAND device (without base address in SEMC_BR4).
 */
#define SEMC_STS12_NDADDR(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_STS12_NDADDR_SHIFT)) & SEMC_STS12_NDADDR_MASK)

void SEMC_GetDefaultConfig(semc_config_t *config);
void SEMC_Init(semc_config_t *configure);
status_t SEMC_ConfigureSDRAM(semc_sdram_cs_t cs, semc_sdram_config_t *config, uint32_t clkSrc_Hz);

#endif /* __IMXRT_SEMC_DRV_H */
