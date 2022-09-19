#ifndef __IMXRT_CLOCK_DRV_H
#define __IMXRT_CLOCK_DRV_H

#include <stdint.h>
#include <stdbool.h>
#include "arm_internal.h"
#include <arch/board/board.h>
#include "hardware/imxrt_ccm.h"

#include "imxrt_clock_type.h"
#include "imxrt_common_drv.h"
#include <syslog.h>

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

static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    uint32_t index = ((uint32_t)name) >> 8U;
    uint32_t shift = ((uint32_t)name) & 0x1FU;
    volatile uint32_t *reg;

    assert(index <= 6UL);

    //reg = (volatile uint32_t *)(&(((volatile uint32_t *)&CCM->CCGR0)[index]));
    //SDK_ATOMIC_LOCAL_CLEAR_AND_SET(reg, (3UL << shift), (((uint32_t)value) << shift));
}

static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_ClockNeededRunWait);
}

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
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ARM);
        result = ((reg & CCM_ANALOG_PLL_ARM_ENABLE) != 0U);
        break;
    case kCLOCK_PllSys:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_SYS);
        result = ((reg & CCM_ANALOG_PLL_SYS_ENABLE) != 0U);
        break;
    case kCLOCK_PllUsb1:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB1);
        result = ((reg & CCM_ANALOG_PLL_USB1_ENABLE) != 0U);
        break;
    case kCLOCK_PllAudio:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO);
        result = ((reg & CCM_ANALOG_PLL_AUDIO_ENABLE) != 0U);
        break;
    case kCLOCK_PllVideo:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO);
        result = ((reg & CCM_ANALOG_PLL_VIDEO_ENABLE) != 0U);
        break;
    case kCLOCK_PllEnet:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        result = ((reg & CCM_ANALOG_PLL_ENET_BYPASS) != 0U);
        break;
    case kCLOCK_PllEnet25M:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        result = ((reg & CCM_ANALOG_PLL_ENET_BYPASS) != 0U);
        break;
    case kCLOCK_PllUsb2:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB2);
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
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ARM);
        result = (bool)(reg & CCM_ANALOG_PLL_ARM_BYPASS);
        break;
    case kCLOCK_PllSys:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_SYS);
        result = (bool)(reg & CCM_ANALOG_PLL_SYS_BYPASS);
        break;
    case kCLOCK_PllUsb1:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB1);
        result = (bool)(reg & CCM_ANALOG_PLL_USB1_BYPASS);
        break;
    case kCLOCK_PllAudio:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO);
        result = (bool)(reg & CCM_ANALOG_PLL_AUDIO_BYPASS);
        break;
    case kCLOCK_PllVideo:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO);
        result = (bool)(reg & CCM_ANALOG_PLL_VIDEO_BYPASS);
        break;
    case kCLOCK_PllEnet:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        result = (bool)(reg & CCM_ANALOG_PLL_ENET_BYPASS);
        break;
    case kCLOCK_PllEnet25M:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        result = (bool)(reg & CCM_ANALOG_PLL_ENET_BYPASS);
        break;
    case kCLOCK_PllUsb2:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB2);
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
    //syslog(LOG_INFO, "enter CLOCK_GetOscFreq\n");
    reg = READ_REG(XTALOSC24M_LOWPWR_CTRL);
    //syslog(LOG_INFO, "XTALOSC24M_LOWPWR_CTRL: 0x%lx\n", reg);
    //syslog(LOG_INFO, "bit OSC_SEL: 0x%lx\n", (reg & XTALOSC24M_LOWPWR_CTRL_OSC_SEL));

    //return ((reg & XTALOSC24M_LOWPWR_CTRL_OSC_SEL) != 0UL) ? 24000000UL : g_xtalFreq;
    return ((reg & XTALOSC24M_LOWPWR_CTRL_OSC_SEL) == 0UL) ? 24000000UL : g_xtalFreq;
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
    //CLOCK_GetPllBypassRefClk
    
    uint32_t temp;
    uint32_t reg = 0;
    //syslog(LOG_INFO, "xxxxxxxxx enter CLOCK_GetPllBypassRefClk\n");
    switch(pll){    
    case kCLOCK_PllArm:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ARM);
        //syslog(LOG_INFO, "enter IMXRT_CCM_ANALOG_PLL_ARM 0x%lx\n", reg);
        break;
    case kCLOCK_PllSys:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_SYS);
        break;
    case kCLOCK_PllUsb1:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB1);
        break;
    case kCLOCK_PllAudio:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO);
        break;
    case kCLOCK_PllVideo:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO);
        break;
    case kCLOCK_PllEnet:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        break;
    case kCLOCK_PllEnet25M:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
        break;
    case kCLOCK_PllUsb2:
        reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB2);
        break;     
    }
    temp = ((reg & CCM_ANALOG_PLL_BYPASS_CLK_SRC_MASK) >> CCM_ANALOG_PLL_BYPASS_CLK_SRC_SHIFT);
    //syslog(LOG_INFO, "enter2 0x%lx\n", temp);
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
    uint32_t reg;
#if 0
    uint32_t busyShift;

    busyShift               = (uint32_t)CCM_TUPLE_BUSY_SHIFT(mux);
    CCM_TUPLE_REG(CCM, mux) = (CCM_TUPLE_REG(CCM, mux) & (~CCM_TUPLE_MASK(mux))) |
                              (((uint32_t)((value) << CCM_TUPLE_SHIFT(mux))) & CCM_TUPLE_MASK(mux));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        
        while ((READ_REG(IMXRT_CCM_CDHIPR) & ((1UL << busyShift))) != 0UL)
        {
        }
    }
#endif
    switch(mux){
        case kCLOCK_SemcMux:
            reg = READ_REG(IMXRT_CCM_CBCDR);
            reg &= ~CCM_CBCDR_SEMC_CLK_SEL;
            reg |= CCM_CBCDR_SEMC_PODF(CCM_PODF_FROM_DIVISOR(value));
            putreg32(reg, IMXRT_CCM_CBCDR);

            while ((READ_REG(IMXRT_CCM_CDHIPR) & CCM_CDHIPR_SEMC_PODF_BUSY) != 0)
            {
            }
            break;
    }
}

static inline void CLOCK_SetDiv(clock_div_t divider, uint32_t value)
{
    uint32_t reg;
#if 0
    uint32_t busyShift;

    busyShift                   = CCM_TUPLE_BUSY_SHIFT(divider);
    CCM_TUPLE_REG(CCM, divider) = (CCM_TUPLE_REG(CCM, divider) & (~CCM_TUPLE_MASK(divider))) |
                                  (((uint32_t)((value) << CCM_TUPLE_SHIFT(divider))) & CCM_TUPLE_MASK(divider));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        while ((READ_REG(IMXRT_CCM_CDHIPR) & ((uint32_t)(1UL << busyShift))) != 0UL)
        {
        }
    }
#endif

    switch(divider){
        case kCLOCK_SemcDiv:
            reg = READ_REG(IMXRT_CCM_CBCDR);
            reg &= ~CCM_CBCDR_SEMC_PODF_MASK;
            reg |= CCM_CBCDR_SEMC_PODF(CCM_PODF_FROM_DIVISOR(value));
            putreg32(reg, IMXRT_CCM_CBCDR);

            while ((READ_REG(IMXRT_CCM_CDHIPR) & CCM_CDHIPR_SEMC_PODF_BUSY) != 0)
            {
            }
            break;
    }
}

uint32_t CLOCK_GetSemcFreq(void);
uint32_t CLOCK_GetPllFreq(clock_pll_t pll);
uint32_t CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd);
uint32_t CLOCK_GetSysPfdFreq(clock_pfd_t pfd);

void CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac);

#endif /* __IMXRT_CLOCK_DRV_H */
