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
    //syslog(LOG_INFO, "IMXRT_CCM_CBCDR %lx\n", READ_REG(IMXRT_CCM_CBCDR));
    if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_PERIPH_CLK_SEL_MASK) != 0U)
    {   
        //syslog(LOG_INFO, "ha1\n");
        //syslog(LOG_INFO, "IMXRT_CCM_CBCMR %lx\n", READ_REG(IMXRT_CCM_CBCMR));
        switch (READ_BIT(IMXRT_CCM_CBCMR, CCM_CBCMR_PERIPH_CLK2_SEL_MASK))
        {
            /* Pll3_sw_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(0U):
                //syslog(LOG_INFO, "ha2\n");
                freq = CLOCK_GetPllFreq(kCLOCK_PllUsb1);
                break;

            /* Osc_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(1U):
                //syslog(LOG_INFO, "ha3\n");
                freq = CLOCK_GetOscFreq();
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(2U):
                //syslog(LOG_INFO, "ha4\n");
                freq = CLOCK_GetPllFreq(kCLOCK_PllSys);
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(3U):
            default:
                //syslog(LOG_INFO, "ha5\n");
                freq = 0U;
                break;
        }
        freq /= ((READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_PERIPH_CLK2_PODF_MASK) >> CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT) + 1U);
    }
    /* Pre_Periph_clk ---> Periph_clk */
    else
    {   
        //syslog(LOG_INFO, "ha6\n");
        //syslog(LOG_INFO, "IMXRT_CCM_CBCMR %lx\n", READ_REG(IMXRT_CCM_CBCMR));
        switch (READ_BIT(IMXRT_CCM_CBCMR, CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK))
        {
            /* PLL2 ---> Pre_Periph_clk ---> Periph_clk */
             
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(0U):
            //syslog(LOG_INFO, "ha7\n");
                freq = CLOCK_GetPllFreq(kCLOCK_PllSys);
                break;

            /* PLL2 PFD2 ---> Pre_Periph_clk ---> Periph_clk */
             
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(1U):
            //syslog(LOG_INFO, "ha8\n");
                freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd2);
                break;

            /* PLL2 PFD0 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(2U):
             //syslog(LOG_INFO, "ha9\n");
                freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd0);
                break;

            /* PLL1 divided(/2) ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(3U):
                //syslog(LOG_INFO, "ha10\n");
                //syslog(LOG_INFO, "IMXRT_CCM_CACRR %lx\n", READ_REG(IMXRT_CCM_CACRR));
                //syslog(LOG_INFO, "IMXRT_CCM_ANALOG_PLL_ARM %lx\n", READ_REG(IMXRT_CCM_ANALOG_PLL_ARM));
                reg = READ_REG(IMXRT_CCM_CACRR);
                // CCM_CACRR_ARM_PODF_MASK = 0x07
                freq = CLOCK_GetPllFreq(kCLOCK_PllArm) /
                       (((reg & 0x07) >> CCM_CACRR_ARM_PODF_SHIFT) + 1U);
                //syslog(LOG_INFO, "ha10 freq %ld\n", freq);
                break;

            default:
            //syslog(LOG_INFO, "ha11\n");
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
    //syslog(LOG_INFO, "= = = = = = 1zx. %s\n", __func__);

    //syslog(LOG_INFO, "IMXRT_CCM_CBCDR %lx\n", READ_REG(IMXRT_CCM_CBCDR));
    /* SEMC alternative clock ---> SEMC Clock */
    if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_SEMC_CLK_SEL) != 0U)
    {
        //syslog(LOG_INFO, "a1\n");
        /* PLL3 PFD1 ---> SEMC alternative clock ---> SEMC Clock */
        if (READ_BIT(IMXRT_CCM_CBCDR, CCM_CBCDR_SEMC_ALT_CLK_SEL) != 0U)
        {
            //syslog(LOG_INFO, "a2\n");
            freq = CLOCK_GetUsb1PfdFreq(kCLOCK_Pfd1);
        }
        /* PLL2 PFD2 ---> SEMC alternative clock ---> SEMC Clock */
        else
        {
            //syslog(LOG_INFO, "a3\n");
            freq = CLOCK_GetSysPfdFreq(kCLOCK_Pfd2);
        }
    }
    /* Periph_clk ---> SEMC Clock */
    else
    {
        //syslog(LOG_INFO, "a4\n");
        freq = CLOCK_GetPeriphClkFreq();
    }
    //syslog(LOG_INFO, "a5\n");
    freq /= ((READ_BIT(IMXRT_CCM_CBCDR, CBCDR_SEMC_PODF_MASK) >> CCM_CBCDR_SEMC_PODF_SHIFT) + 1U);
    //syslog(LOG_INFO, "= = = = = = 2zx. %s\n", __func__);
    return freq;
}

uint32_t CLOCK_GetPllFreq(clock_pll_t pll)
{
    #define MISC2_AUDIO_DIV_MSB_0U 0x00
    #define MISC2_AUDIO_DIV_MSB_1U 0x800000
    #define MISC2_AUDIO_DIV_LSB_0U 0x00
    #define MISC2_AUDIO_DIV_LSB_1U 0x8000
    
    uint32_t freq;
    uint32_t divSelect;
    uint32_t reg;
    clock_64b_t freqTmp;

    clock_64b_t pll_num;
    clock_64b_t pll_demon;

    uint32_t PLL_AUDIO_POST_DIV_SELECT_MASK = 0x180000;

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
    //syslog(LOG_INFO, "=============\n");
    freq = CLOCK_GetPllBypassRefClk(pll);
    //syslog(LOG_INFO, "a2 CLOCK_GetPllBypassRefClk %ld\n", freq);

    /* check if pll is bypassed */
    if (CLOCK_IsPllBypassed(pll))
    {
        return freq;
    }

    switch (pll)
    {
        case kCLOCK_PllArm:
            //syslog(LOG_INFO, "kCLOCK_PllArm\n");
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ARM);
            //syslog(LOG_INFO, "PLL_ARM div %ld\n", (reg & CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK));
            freq = ((freq * ((reg & CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK) >>
                             CCM_ANALOG_PLL_ARM_DIV_SELECT_SHIFT)) >>
                    1U);
            break;

        case kCLOCK_PllSys:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            pll_num = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_SYS_NUM);
            pll_demon = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_SYS_DENOM);
            freqTmp = ((clock_64b_t)freq * (pll_num));
            freqTmp /= pll_demon;

            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_SYS);
            //CCM_ANALOG_PLL_SYS_DIV_SELECT_MASK = 1
            if ((reg & 0x01) != 0U)
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
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB1);
            freq = (freq * (((reg & CCM_ANALOG_PLL_USB1_DIV_SELECT_MASK) != 0UL) ? 22U : 20U));
            break;

        case kCLOCK_PllAudio:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO);
            divSelect =
                (reg & CCM_ANALOG_PLL_AUDIO_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_AUDIO_DIV_SELECT_SHIFT;

            pll_num = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO_NUM);
            pll_demon = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO_DENOM);
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
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_AUDIO);
            switch (reg & PLL_AUDIO_POST_DIV_SELECT_MASK)
            {
                //CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(0)
                case 0x00:
                    freq = freq >> 2U;
                    break;

                //CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(1)
                case 0x80000:
                    freq = freq >> 1U;
                    break;

                //CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(1)
                case 0x100000:
                    freq = freq >> 0U;
                    break;

                default:
                    assert(false);
                    break;
            }

            reg = READ_REG(IMXRT_CCM_ANALOG_MISC2);
            switch (reg & (CCM_ANALOG_MISC2_AUDIO_DIV_MSB | CCM_ANALOG_MISC2_AUDIO_DIV_LSB))
            {
                case MISC2_AUDIO_DIV_MSB_1U | MISC2_AUDIO_DIV_LSB_1U:
                    freq >>= 2U;
                    break;

                case MISC2_AUDIO_DIV_MSB_0U | MISC2_AUDIO_DIV_LSB_1U:
                    freq >>= 1U;
                    break;

                case MISC2_AUDIO_DIV_MSB_0U | MISC2_AUDIO_DIV_LSB_0U:
                case MISC2_AUDIO_DIV_MSB_1U | MISC2_AUDIO_DIV_LSB_0U:
                    freq >>= 0U;
                    break;

                default:
                    assert(false);
                    break;
            }
            break;

        case kCLOCK_PllVideo:
            /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO);
            divSelect =
                (reg & CCM_ANALOG_PLL_VIDEO_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_VIDEO_DIV_SELECT_SHIFT;

            pll_num = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO_NUM);
            pll_demon = (clock_64b_t)READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO_DENOM);
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
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_VIDEO);
            // #define CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT_MASK (0x180000U)
            switch (reg & 0x180000U)
            {
                //CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT(0U) = 0x0
                case 0x00:
                    freq = freq >> 2U;
                    break;

                //CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT(1U) = 0x80000
                case 0x80000:
                    freq = freq >> 1U;
                    break;

                //CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT(2U) = 0x100000
                case 0x100000:
                    freq = freq >> 0U;
                    break;

                default:
                    assert(false);
                    break;
            }

            reg = READ_REG(IMXRT_CCM_ANALOG_MISC2);
            switch (reg & CCM_ANALOG_MISC2_VIDEO_DIV_MASK)
            {
                // CCM_ANALOG_MISC2_VIDEO_DIV(3U) = 0xc0000000
                case 0xc0000000:
                    freq >>= 2U;
                    break;
                // CCM_ANALOG_MISC2_VIDEO_DIV(1U) = 0x40000000
                case 0x40000000:
                    freq >>= 1U;
                    break;
                //CCM_ANALOG_MISC2_VIDEO_DIV(0U) = 0x00
                //CCM_ANALOG_MISC2_VIDEO_DIV(2U) = 0x80000000
                case 0x00:
                case 0x80000000:
                    freq >>= 0U;
                    break;

                default:
                    assert(false);
                    break;
            }
            break;

        case kCLOCK_PllEnet:
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_ENET);
            divSelect =
                (reg & CCM_ANALOG_PLL_ENET_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_ENET_DIV_SELECT_SHIFT;
            freq = enetRefClkFreq[divSelect];
            break;

        case kCLOCK_PllEnet25M:
            /* ref_enetpll1 if fixed at 25MHz. */
            freq = 25000000UL;
            break;

        case kCLOCK_PllUsb2:
            reg = READ_REG(IMXRT_CCM_ANALOG_PLL_USB2);
            // CCM_ANALOG_PLL_USB2_DIV_SELECT_MASK = 0x02
            freq = (freq * (((reg & 0x02) != 0U) ? 22U : 20U));
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
    uint32_t reg = READ_REG(IMXRT_CCM_ANALOG_PFD_480);
    
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
    uint32_t reg = READ_REG(IMXRT_CCM_ANALOG_PFD_528);

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
    uint32_t PFD_528_PFD0_FRAC_MASK = 0x3F;

    pfd528 = READ_REG(IMXRT_CCM_ANALOG_PFD_528) &
             ~(((uint32_t)((uint32_t)CCM_ANALOG_PFD_528_PFD0_CLKGATE | PFD_528_PFD0_FRAC_MASK)
                << (8UL * pfdIndex)));

    /* Disable the clock output first. */
    value = pfd528 | ((uint32_t)CCM_ANALOG_PFD_528_PFD0_CLKGATE << (8UL * pfdIndex));
    WRITE_REG(IMXRT_CCM_ANALOG_PFD_528, value);

    /* Set the new value and enable output. */
    value = pfd528 | (CCM_ANALOG_PFD_528_PFD0_FRAC(pfdFrac) << (8UL * pfdIndex));
    WRITE_REG(IMXRT_CCM_ANALOG_PFD_528, value);
}

