#include "imxrt_clock_drv.h"
#include <assert.h>

/* External XTAL (OSC) clock frequency. */
volatile uint32_t g_xtalFreq;
/* External RTC XTAL clock frequency. */
volatile uint32_t g_rtcXtalFreq;


static uint32_t CLOCK_GetPeriphClkFreq(void)
{
    uint32_t freq;
    uint32_t reg;

    /* Periph_clk2_clk ---> Periph_clk */
    if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_PERIPH_CLK_SEL_MASK) != 0U)
    {
        switch (READ_BIT(IMXRT_CCM_CBCMR, CCM_CBCMR_PERIPH_CLK2_SEL_MASK))
        {
            /* Pll3_sw_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(0U):
                freq = CLOCK_GetPllFreq(kCLOCK_PllUsb1);
                break;

            /* Osc_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(1U):
                freq = CLOCK_GetOscFreq();
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(2U):
                freq = CLOCK_GetPllFreq(kCLOCK_PllSys);
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(3U):
            default:
                freq = 0U;
                break;
        }
        freq /= ((READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_PERIPH_CLK2_PODF_MASK) >> CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT) + 1U);
    }
    /* Pre_Periph_clk ---> Periph_clk */
    else
    {
        switch (READ_BIT(IMXRT_CCM_CBCMR, CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK))
        {
            /* PLL2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(0U):
                freq = CLOCK_GetPllFreq(kCLOCK_PllSys);
                break;

            /* PLL2 PFD2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(1U):
                freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd2);
                break;

            /* PLL2 PFD0 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(2U):
                freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd0);
                break;

            /* PLL1 divided(/2) ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(3U):
                reg = READ_REG(IMXRT_CCM_CACRR);
                // CCM_CACRR_ARM_PODF_MASK = 0x07
                freq = CLOCK_GetPllFreq(kCLOCK_PllArm) /
                       (((reg & 0x07) >> CCM_CACRR_ARM_PODF_SHIFT) + 1U);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}

uint32_t CLOCK_GetSemcFreq(void)
{
    uint32_t freq;
    uint32_t CBCDR_SEMC_PODF_MASK = 0x70000;

    /* SEMC alternative clock ---> SEMC Clock */
    if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_SEMC_CLK_SEL) != 0U)
    {
        /* PLL3 PFD1 ---> SEMC alternative clock ---> SEMC Clock */
        if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_SEMC_ALT_CLK_SEL) != 0U)
        {
            freq = CLOCK_GetUsb1PfdFreq(kCLOCK_Pfd1);
        }
        /* PLL2 PFD2 ---> SEMC alternative clock ---> SEMC Clock */
        else
        {
            freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd2);
        }
    }
    /* Periph_clk ---> SEMC Clock */
    else
    {
        freq = CLOCK_GetPeriphClkFreq();
    }

    freq /= ((READ_BIT(IMXRT_CCM_CBCDR, CBCDR_SEMC_PODF_MASK) >> CCM_CBCDR_SEMC_PODF_SHIFT) + 1U);

    return freq;
}

uint32_t CLOCK_GetPllFreq(clock_pll_t pll)
{
    uint32_t freq;
    uint32_t divSelect;
    uint32_t reg;
    clock_64b_t freqTmp;

    clock_64b_t pll_num;
    clock_64b_t pll_demon;

    static const uint32_t enetRefClkFreq[] = {
        25000000U,  /* 25M */
        50000000U,  /* 50M */
        100000000U, /* 100M */
        125000000U  /* 125M */
    };

    /* check if PLL is enabled */
    if (!CLOCK_IsPllEnabled(pll))
    {
        return 0U;
    }

    /* get pll reference clock */
    freq = CLOCK_GetPllBypassRefClk(pll);

    /* check if pll is bypassed */
    if (CLOCK_IsPllBypassed(pll))
    {
        return freq;
    }

    switch (pll)
    {
        case kCLOCK_PllArm:
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_ARM);
            freq = ((freq * ((reg & CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK) >>
                             CCM_ANALOG_PLL_ARM_DIV_SELECT_SHIFT)) >>
                    1U);
            break;

        case kCLOCK_PllSys:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            pll_num = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_SYS_NUM);
            pll_demon = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_SYS_DENOM);
            freqTmp = ((clock_64b_t)freq * (pll_num));
            freqTmp /= pll_demon;

            reg = getreg32(IMXRT_CCM_ANALOG_PLL_SYS);
            if ((reg & CCM_ANALOG_PLL_SYS_DIV_SELECT_MASK) != 0U)
            {
                freq *= 22U;
            }
            else
            {
                freq *= 20U;
            }

            freq += (uint32_t)freqTmp;
            break;

        case kCLOCK_PllUsb1:
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB1);
            freq = (freq * (((reg & CCM_ANALOG_PLL_USB1_DIV_SELECT_MASK) != 0UL) ? 22U : 20U));
            break;

        case kCLOCK_PllAudio:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO);
            divSelect =
                (reg & CCM_ANALOG_PLL_AUDIO_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_AUDIO_DIV_SELECT_SHIFT;

            pll_num = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO_NUM);
            pll_demon = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO_DENOM);
            freqTmp = ((clock_64b_t)freq * (pll_num));
            freqTmp /= pll_demon;

            freq = freq * divSelect + (uint32_t)freqTmp;

            /* AUDIO PLL output = PLL output frequency / POSTDIV. */

            /*
             * Post divider:
             *
             * PLL_AUDIO[POST_DIV_SELECT]:
             * 0x00: 4
             * 0x01: 2
             * 0x02: 1
             *
             * MISC2[AUDO_DIV]:
             * 0x00: 1
             * 0x01: 2
             * 0x02: 1
             * 0x03: 4
             */
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_AUDIO);
            switch (reg & CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT_MASK2)
            {
                case CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT2(0U):
                    freq = freq >> 2U;
                    break;

                case CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT2(1U):
                    freq = freq >> 1U;
                    break;

                case CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT2(2U):
                    freq = freq >> 0U;
                    break;

                default:
                    assert(false);
                    break;
            }

            reg = getreg32(IMXRT_CCM_ANALOG_MISC2);
            switch (reg & (CCM_ANALOG_MISC2_AUDIO_DIV_MSB | CCM_ANALOG_MISC2_AUDIO_DIV_LSB))
            {
                case CCM_ANALOG_MISC2_AUDIO_DIV_MSB2(1) | CCM_ANALOG_MISC2_AUDIO_DIV_LSB2(1):
                    freq >>= 2U;
                    break;

                case CCM_ANALOG_MISC2_AUDIO_DIV_MSB2(0) | CCM_ANALOG_MISC2_AUDIO_DIV_LSB2(1):
                    freq >>= 1U;
                    break;

                case CCM_ANALOG_MISC2_AUDIO_DIV_MSB2(0) | CCM_ANALOG_MISC2_AUDIO_DIV_LSB2(0):
                case CCM_ANALOG_MISC2_AUDIO_DIV_MSB2(1) | CCM_ANALOG_MISC2_AUDIO_DIV_LSB2(0):
                    freq >>= 0U;
                    break;

                default:
                    assert(false);
                    break;
            }
            break;

        case kCLOCK_PllVideo:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO);
            divSelect =
                (reg & CCM_ANALOG_PLL_VIDEO_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_VIDEO_DIV_SELECT_SHIFT;

            pll_num = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO_NUM);
            pll_demon = (clock_64b_t)getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO_DENOM);
            freqTmp = ((clock_64b_t)freq * (pll_num));
            freqTmp /= pll_demon;
            freq = freq * divSelect + (uint32_t)freqTmp;

            /* VIDEO PLL output = PLL output frequency / POSTDIV. */

            /*
             * Post divider:
             *
             * PLL_VIDEO[POST_DIV_SELECT]:
             * 0x00: 4
             * 0x01: 2
             * 0x02: 1
             *
             * MISC2[VIDEO_DIV]:
             * 0x00: 1
             * 0x01: 2
             * 0x02: 1
             * 0x03: 4
             */
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_VIDEO);
            switch (reg & CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK)
            {
                case CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT2(0U):
                    freq = freq >> 2U;
                    break;

                case CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT2(1U):
                    freq = freq >> 1U;
                    break;

                case CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT2(2U):
                    freq = freq >> 0U;
                    break;

                default:
                    assert(false);
                    break;
            }

            reg = getreg32(IMXRT_CCM_ANALOG_MISC2);
            switch (reg & CCM_ANALOG_MISC2_VIDEO_DIV_MASK)
            {
                case CCM_ANALOG_MISC2_VIDEO_DIV(3U):
                    freq >>= 2U;
                    break;

                case CCM_ANALOG_MISC2_VIDEO_DIV(1U):
                    freq >>= 1U;
                    break;

                case CCM_ANALOG_MISC2_VIDEO_DIV(0U):
                case CCM_ANALOG_MISC2_VIDEO_DIV(2U):
                    freq >>= 0U;
                    break;

                default:
                    assert(false);
                    break;
            }
            break;

        case kCLOCK_PllEnet:
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_ENET);
            divSelect =
                (reg & CCM_ANALOG_PLL_ENET_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_ENET_DIV_SELECT_SHIFT;
            freq = enetRefClkFreq[divSelect];
            break;

        case kCLOCK_PllEnet25M:
            /* ref_enetpll1 if fixed at 25MHz. */
            freq = 25000000UL;
            break;

        case kCLOCK_PllUsb2:
            reg = getreg32(IMXRT_CCM_ANALOG_PLL_USB2);
            freq = (freq * (((reg & CCM_ANALOG_PLL_USB2_DIV_SELECT_MASK) != 0U) ? 22U : 20U));
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}


uint32_t CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetPllFreq(kCLOCK_PllUsb1);
    uint32_t reg = getreg32(IMXRT_CCM_ANALOG_PFD_480);
    
    switch (pfd)
    {
        case kCLOCK_Pfd0:
            freq /= ((reg & CCM_ANALOG_PFD_480_PFD0_FRAC_MASK) >> CCM_ANALOG_PFD_480_PFD0_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd1:
            freq /= ((reg & CCM_ANALOG_PFD_480_PFD1_FRAC_MASK) >> CCM_ANALOG_PFD_480_PFD1_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd2:
            freq /= ((reg & CCM_ANALOG_PFD_480_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_480_PFD2_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd3:
            freq /= ((reg & CCM_ANALOG_PFD_480_PFD3_FRAC_MASK) >> CCM_ANALOG_PFD_480_PFD3_FRAC_SHIFT);
            break;

        default:
            freq = 0U;
            break;
    }
    freq *= 18U;

    return freq;
}


uint32_t CLOCK_GetSysPfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetPllFreq(kCLOCK_PllSys);
    uint32_t reg = getreg32(IMXRT_CCM_ANALOG_PFD_528);

    switch (pfd)
    {
        case kCLOCK_Pfd0:
            freq /= ((reg & CCM_ANALOG_PFD_528_PFD0_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD0_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd1:
            freq /= ((reg & CCM_ANALOG_PFD_528_PFD1_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD1_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd2:
            freq /= ((reg & CCM_ANALOG_PFD_528_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD2_FRAC_SHIFT);
            break;

        case kCLOCK_Pfd3:
            freq /= ((reg & CCM_ANALOG_PFD_528_PFD3_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD3_FRAC_SHIFT);
            break;

        default:
            freq = 0U;
            break;
    }
    freq *= 18U;

    return freq;
}

/*!
 * brief Initialize the System PLL PFD.
 *
 * This function initializes the System PLL PFD. During new value setting,
 * the clock output is disabled to prevent glitch.
 *
 * param pfd Which PFD clock to enable.
 * param pfdFrac The PFD FRAC value.
 * note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t pfd528;
    uint32_t value;

    uint32_t reg = getreg32(IMXRT_CCM_ANALOG_PFD_528);
    pfd528 = reg &
             ~(((uint32_t)((uint32_t)CCM_ANALOG_PFD_528_PFD0_CLKGATE | CCM_ANALOG_PFD_528_PFD0_FRAC_MASK)
                << (8UL * pfdIndex)));

    /* Disable the clock output first. */
    value = pfd528 | ((uint32_t)CCM_ANALOG_PFD_528_PFD0_CLKGATE << (8UL * pfdIndex));
    putreg32(value, IMXRT_CCM_ANALOG_PFD_528);

    /* Set the new value and enable output. */
    value = pfd528 | (CCM_ANALOG_PFD_528_PFD0_FRAC(pfdFrac) << (8UL * pfdIndex));
    putreg32(value, IMXRT_CCM_ANALOG_PFD_528);
}

