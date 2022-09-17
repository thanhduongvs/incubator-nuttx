#ifndef __IMXRT_CLOCK_DRV_H
#define __IMXRT_CLOCK_DRV_H

#include <stdint.h>
#include <stdbool.h>
#include "arm_internal.h"
#include <arch/board/board.h>
#include "hardware/imxrt_ccm.h"

#include "imxrt_clock_type.h"


/*! @brief External XTAL (24M OSC/SYSOSC) clock frequency.
 *
 * The XTAL (24M OSC/SYSOSC) clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetXtalFreq to set the value in to clock driver. For example,
 * if XTAL is 24MHz,
 * @code
 * CLOCK_InitExternalClk(false);
 * CLOCK_SetXtalFreq(240000000);
 * @endcode
 */
extern volatile uint32_t g_xtalFreq;

/*! @brief External RTC XTAL (32K OSC) clock frequency.
 *
 * The RTC XTAL (32K OSC) clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetRtcXtalFreq to set the value in to clock driver.
 */
extern volatile uint32_t g_rtcXtalFreq;

/*!
 * @brief Check if PLL is enabled
 *
 * @param pll PLL control name (see @ref ccm_analog_pll_control_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is enabled.
 *         - false: The PLL is not enabled.
 */
static inline bool CLOCK_IsPllEnabled(clock_pll_t pll)
{
    bool result = false;
    uint32_t reg = 0;
    switch(pll){    
    case kCLOCK_PllArm:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ARM);
        result = ((reg & CCM_ANALOG_PLL_ARM_ENABLE) != 0U);
        break;
    case kCLOCK_PllSys:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_SYS);
        result = ((reg & CCM_ANALOG_PLL_SYS_ENABLE) != 0U);
        break;
    case kCLOCK_PllUsb1:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB1);
        result = ((reg & CCM_ANALOG_PLL_USB1_ENABLE) != 0U);
        break;
    case kCLOCK_PllAudio:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO);
        result = ((reg & CCM_ANALOG_PLL_AUDIO_ENABLE) != 0U);
        break;
    case kCLOCK_PllVideo:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO);
        result = ((reg & CCM_ANALOG_PLL_VIDEO_ENABLE) != 0U);
        break;
    case kCLOCK_PllEnet:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        result = ((reg & CCM_ANALOG_PLL_ENET_BYPASS) != 0U);
        break;
    case kCLOCK_PllEnet25M:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        result = ((reg & CCM_ANALOG_PLL_ENET_BYPASS) != 0U);
        break;
    case kCLOCK_PllUsb2:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB2);
        result = ((reg & CCM_ANALOG_PLL_USB2_ENABLE) != 0U);
        break;     
    }
    return result;
}

/*!
 * @brief Check if PLL is bypassed
 *
 * @param pll PLL control name (see @ref ccm_analog_pll_control_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is bypassed.
 *         - false: The PLL is not bypassed.
 */
static inline bool CLOCK_IsPllBypassed(clock_pll_t pll)
{
    bool result = false;
    uint32_t reg = 0;
    switch(pll){    
    case kCLOCK_PllArm:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ARM);
        result = (bool)(reg & CCM_ANALOG_PLL_ARM_BYPASS);
        break;
    case kCLOCK_PllSys:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_SYS);
        result = (bool)(reg & CCM_ANALOG_PLL_SYS_BYPASS);
        break;
    case kCLOCK_PllUsb1:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB1);
        result = (bool)(reg & CCM_ANALOG_PLL_USB1_BYPASS);
        break;
    case kCLOCK_PllAudio:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO);
        result = (bool)(reg & CCM_ANALOG_PLL_AUDIO_BYPASS);
        break;
    case kCLOCK_PllVideo:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO);
        result = (bool)(reg & CCM_ANALOG_PLL_VIDEO_BYPASS);
        break;
    case kCLOCK_PllEnet:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        result = (bool)(reg & CCM_ANALOG_PLL_ENET_BYPASS);
        break;
    case kCLOCK_PllEnet25M:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        result = (bool)(reg & CCM_ANALOG_PLL_ENET_BYPASS);
        break;
    case kCLOCK_PllUsb2:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB2);
        result = (bool)(reg & CCM_ANALOG_PLL_USB2_BYPASS);
        break;     
    }
    return result;
    //return (bool)(CCM_ANALOG_TUPLE_REG(base, pll) & (1UL << CCM_ANALOG_PLL_BYPASS_SHIFT));
}

/*!
 * @brief Gets the OSC clock frequency.
 *
 * This function will return the external XTAL OSC frequency if it is selected as the source of OSC,
 * otherwise internal 24MHz RC OSC frequency will be returned.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetOscFreq(void)
{
    uint32_t reg;
    #define XTALOSC24M_LOWPWR_CTRL 0x400d8270
    #define XTALOSC24M_LOWPWR_CTRL_OSC_SEL (1 << 4)
    reg = getreg32(XTALOSC24M_LOWPWR_CTRL);

    return ((reg & XTALOSC24M_LOWPWR_CTRL_OSC_SEL) != 0UL) ? 24000000UL : g_xtalFreq;
}

/*!
 * @brief Get PLL bypass clock value, it is PLL reference clock actually.
 * If CLOCK1_P,CLOCK1_N is choose as the pll bypass clock source, please implement the CLKPN_FREQ define, otherwise 0
 * will be returned.
 * @param pll PLL control name (see @ref ccm_analog_pll_control_t enumeration)
 * @retval bypass reference clock frequency value.
 */
static inline uint32_t CLOCK_GetPllBypassRefClk(clock_pll_t pll)
{
    uint32_t reg = 0;
    switch(pll){    
    case kCLOCK_PllArm:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ARM);
        break;
    case kCLOCK_PllSys:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_SYS);
        break;
    case kCLOCK_PllUsb1:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB1);
        break;
    case kCLOCK_PllAudio:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO);
        break;
    case kCLOCK_PllVideo:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO);
        break;
    case kCLOCK_PllEnet:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        break;
    case kCLOCK_PllEnet25M:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
        break;
    case kCLOCK_PllUsb2:
        reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB2);
        break;     
    }
    return (((reg & CCM_ANALOG_PLL_BYPASS_CLK_SRC_MASK) >>
             CCM_ANALOG_PLL_BYPASS_CLK_SRC_SHIFT) == (uint32_t)kCLOCK_PllClkSrc24M) ?
               CLOCK_GetOscFreq() :
               CLKPN_FREQ;
}

/*!
 * @brief Set CCM MUX node to certain value.
 *
 * @param mux   Which mux node to set, see \ref clock_mux_t.
 * @param value Clock mux value to set, different mux has different value range.
 */
static inline void CLOCK_SetMux(clock_mux_t mux, uint32_t value)
{
    uint32_t busyShift;

    busyShift               = (uint32_t)CCM_TUPLE_BUSY_SHIFT(mux);
    CCM_TUPLE_REG(CCM, mux) = (CCM_TUPLE_REG(CCM, mux) & (~CCM_TUPLE_MASK(mux))) |
                              (((uint32_t)((value) << CCM_TUPLE_SHIFT(mux))) & CCM_TUPLE_MASK(mux));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        while ((CCM->CDHIPR & ((1UL << busyShift))) != 0UL)
        {
        }
    }
}

static inline void CLOCK_SetDiv(clock_div_t divider, uint32_t value)
{
    uint32_t busyShift;

    busyShift                   = CCM_TUPLE_BUSY_SHIFT(divider);
    CCM_TUPLE_REG(CCM, divider) = (CCM_TUPLE_REG(CCM, divider) & (~CCM_TUPLE_MASK(divider))) |
                                  (((uint32_t)((value) << CCM_TUPLE_SHIFT(divider))) & CCM_TUPLE_MASK(divider));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        while ((CCM->CDHIPR & ((uint32_t)(1UL << busyShift))) != 0UL)
        {
        }
    }
}

uint32_t CLOCK_GetSemcFreq(void);
uint32_t CLOCK_GetPllFreq(clock_pll_t pll);
uint32_t CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd);
uint32_t CLOCK_GetSysPfdFreq(clock_pfd_t pfd);

void CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac);

#endif /* __IMXRT_CLOCK_DRV_H */
