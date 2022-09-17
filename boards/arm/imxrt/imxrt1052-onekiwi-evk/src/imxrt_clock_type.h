#ifndef __IMXRT_CLOCK_TYPE_H
#define __IMXRT_CLOCK_TYPE_H

#include <assert.h>

typedef double clock_64b_t;

typedef enum _clock_pll
{
    kCLOCK_PllArm,     /*!< PLL ARM */
    kCLOCK_PllSys,     /*!< PLL SYS */
    kCLOCK_PllUsb1,   /*!< PLL USB1 */
    kCLOCK_PllAudio, /*!< PLL Audio */
    kCLOCK_PllVideo, /*!< PLL Video */
    kCLOCK_PllEnet, /*!< PLL Enet0 */
    kCLOCK_PllEnet25M, /*!< PLL Enet1 */
    kCLOCK_PllUsb2, /*!< PLL USB2 */
} clock_pll_t;

enum _clock_pll_clk_src
{
    kCLOCK_PllClkSrc24M = 0U, /*!< Pll clock source 24M */
    kCLOCK_PllSrcClkPN  = 1U, /*!< Pll clock source CLK1_P and CLK1_N */
};

typedef enum _clock_pfd
{
    kCLOCK_Pfd0 = 0U, /*!< PLL PFD0 */
    kCLOCK_Pfd1 = 1U, /*!< PLL PFD1 */
    kCLOCK_Pfd2 = 2U, /*!< PLL PFD2 */
    kCLOCK_Pfd3 = 3U, /*!< PLL PFD3 */
} clock_pfd_t;

typedef enum _clock_mux
{
    kCLOCK_Pll3SwMux, /*!< pll3_sw_clk mux name */

    kCLOCK_PeriphMux, /*!< periph mux name */
    kCLOCK_SemcAltMux, /*!< semc mux name */
    kCLOCK_SemcMux, /*!< semc mux name */

    kCLOCK_PrePeriphMux, /*!< pre-periph mux name */
    kCLOCK_TraceMux, /*!< trace mux name */
    kCLOCK_PeriphClk2Mux, /*!< periph clock2 mux name */
    kCLOCK_LpspiMux, /*!< lpspi mux name */

    kCLOCK_FlexspiMux, /*!< flexspi mux name */
    kCLOCK_Usdhc2Mux, /*!< usdhc2 mux name */
    kCLOCK_Usdhc1Mux, /*!< usdhc1 mux name */
    kCLOCK_Sai3Mux, /*!< sai3 mux name */
    kCLOCK_Sai2Mux, /*!< sai2 mux name */
    kCLOCK_Sai1Mux, /*!< sai1 mux name */
    kCLOCK_PerclkMux, /*!< perclk mux name */

    kCLOCK_Flexio2Mux, /*!< flexio2 mux name */
    kCLOCK_CanMux, /*!< can mux name */

    kCLOCK_UartMux, /*!< uart mux name */

    kCLOCK_SpdifMux, /*!< spdif mux name */
    kCLOCK_Flexio1Mux, /*!< flexio1 mux name */

    kCLOCK_Lpi2cMux, /*!< lpi2c mux name */
    kCLOCK_LcdifPreMux, /*!< lcdif pre mux name */

    kCLOCK_CsiMux, /*!< csi mux name */
} clock_mux_t;

/*!
 * @brief DIV control names for clock div setting.
 *
 * These constants define div control names for clock div setting.\n
 * - 0:7: REG offset to CCM_BASE in bytes.
 * - 8:15: Root clock setting bit field shift.
 * - 16:31: Root clock setting bit field width.
 */
typedef enum _clock_div
{
    kCLOCK_ArmDiv, /*!< core div name */

    kCLOCK_PeriphClk2Div, /*!< periph clock2 div name */
    kCLOCK_SemcDiv, /*!< semc div name */
    kCLOCK_AhbDiv, /*!< ahb div name */
    kCLOCK_IpgDiv, /*!< ipg div name */

    kCLOCK_LpspiDiv, /*!< lpspi div name */
    kCLOCK_LcdifDiv, /*!< lcdif div name */

    kCLOCK_FlexspiDiv, /*!< flexspi div name */
    kCLOCK_PerclkDiv, /*!< perclk div name */

    kCLOCK_CanDiv, /*!< can div name */

    kCLOCK_TraceDiv, /*!< trace div name */
    kCLOCK_Usdhc2Div, /*!< usdhc2 div name */
    kCLOCK_Usdhc1Div, /*!< usdhc1 div name */
    kCLOCK_UartDiv, /*!< uart div name */

    kCLOCK_Flexio2Div, /*!< flexio2 pre div name */
    kCLOCK_Sai3PreDiv, /*!< sai3 pre div name */
    kCLOCK_Sai3Div, /*!< sai3 div name */
    kCLOCK_Flexio2PreDiv, /*!< sai3 pre div name */
    kCLOCK_Sai1PreDiv, /*!< sai1 pre div name */
    kCLOCK_Sai1Div, /*!< sai1 div name */

    kCLOCK_Sai2PreDiv, /*!< sai2 pre div name */
    kCLOCK_Sai2Div, /*!< sai2 div name */

    kCLOCK_Spdif0PreDiv, /*!< spdif pre div name */
    kCLOCK_Spdif0Div, /*!< spdif div name */
    kCLOCK_Flexio1PreDiv, /*!< flexio1 pre div name */
    kCLOCK_Flexio1Div, /*!< flexio1 div name */

    kCLOCK_Lpi2cDiv, /*!< lpi2c div name */
    kCLOCK_LcdifPreDiv, /*!< lcdif pre div name */

    kCLOCK_CsiDiv, /*!< csi div name */

    kCLOCK_NonePreDiv, /*!< None Pre div. */
} clock_div_t;

#define CLKPN_FREQ 0U

#define CCM_ANALOG_PLL_BYPASS_SHIFT         (16U)
#define CCM_ANALOG_PLL_BYPASS_CLK_SRC_MASK  (0xC000U)
#define CCM_ANALOG_PLL_BYPASS_CLK_SRC_SHIFT (14U)


#define CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT_MASK2 (0x180000U)
#define CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT_SHIFT2 (19U)
/*! POST_DIV_SELECT
 *  0b00..Divide by 4.
 *  0b01..Divide by 2.
 *  0b10..Divide by 1.
 *  0b11..Reserved
 */
#define CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT2(x)  (((uint32_t)(((uint32_t)(x)) << CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT_SHIFT2)) & CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT_MASK2)

#define CCM_ANALOG_PLL_ENET_DIV_SELECT_MASK      (0x3U)
#define CCM_ANALOG_PLL_ENET_DIV_SELECT_SHIFT     (0U)
#define CCM_ANALOG_PLL_ENET_DIV_SELECT(x)        (((uint32_t)(((uint32_t)(x)) << CCM_ANALOG_PLL_ENET_DIV_SELECT_SHIFT)) & CCM_ANALOG_PLL_ENET_DIV_SELECT_MASK)

#define IMXRT_CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK2 (0x180000U)
//#define IMXRT_CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_SHIFT (19U)
/*! POST_DIV_SELECT
 *  0b00..Divide by 4.
 *  0b01..Divide by 2.
 *  0b10..Divide by 1.
 *  0b11..Reserved
 */
#define IMXRT_CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT(x)  (((uint32_t)(((uint32_t)(x)) << IMXRT_CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_SHIFT)) & IMXRT_CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK2)

#define CCM_ANALOG_MISC2_AUDIO_DIV_LSB_MASK      (0x8000U)
#define CCM_ANALOG_MISC2_AUDIO_DIV_LSB_SHIFT     (15U)
/*! AUDIO_DIV_LSB
 *  0b0..divide by 1 (Default)
 *  0b1..divide by 2
 */
#define CCM_ANALOG_MISC2_AUDIO_DIV_LSB2(x)        (((uint32_t)(((uint32_t)(x)) << CCM_ANALOG_MISC2_AUDIO_DIV_LSB_SHIFT)) & CCM_ANALOG_MISC2_AUDIO_DIV_LSB_MASK)

#define CCM_ANALOG_MISC2_AUDIO_DIV_MSB_MASK      (0x800000U)
#define CCM_ANALOG_MISC2_AUDIO_DIV_MSB_SHIFT     (23U)
/*! AUDIO_DIV_MSB
 *  0b0..divide by 1 (Default)
 *  0b1..divide by 2
 */
#define CCM_ANALOG_MISC2_AUDIO_DIV_MSB2(x)        (((uint32_t)(((uint32_t)(x)) << CCM_ANALOG_MISC2_AUDIO_DIV_MSB_SHIFT)) & CCM_ANALOG_MISC2_AUDIO_DIV_MSB_MASK)

#define CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK2 (0x180000U)
#define CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_SHIFT2 (19U)
/*! POST_DIV_SELECT
 *  0b00..Divide by 4.
 *  0b01..Divide by 2.
 *  0b10..Divide by 1.
 *  0b11..Reserved
 */
#define CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT2(x)  (((uint32_t)(((uint32_t)(x)) << CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_SHIFT2)) & CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK2)

#define CCM_NO_BUSY_WAIT (0x20U)

#endif /* __IMXRT_CLOCK_TYPE_H */
