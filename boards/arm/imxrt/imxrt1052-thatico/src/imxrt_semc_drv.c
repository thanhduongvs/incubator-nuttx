#include "imxrt_semc_drv.h"
#include <assert.h>
#include <string.h>
#include <syslog.h>

/*! @brief Pointers to SEMC bases for each instance. */
//static SEMC_Type *const s_semcBases[] = SEMC_BASE_PTRS;

//static uint32_t const* s_semcBases[] = (uint32_t*)SEMC_BASE_PTRS;
static uint32_t SEMC_GetInstance()
{
    #if 0
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_semcBases); instance++)
    {
        if (s_semcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_semcBases));

    return instance;
    #endif
    return 0x304;
    
}

static status_t SEMC_CovertMemorySize(uint32_t size_kbytes, uint8_t *sizeConverted)
{
    assert(sizeConverted != NULL);
    uint32_t memsize;
    status_t status = kStatus_Success;

    if ((size_kbytes < SEMC_BR_MEMSIZE_MIN) || (size_kbytes > SEMC_BR_MEMSIZE_MAX))
    {
        status = kStatus_SEMC_InvalidMemorySize;
    }
    else
    {
        *sizeConverted = 0U;
        memsize        = size_kbytes / 8U;
        while (memsize != 0x00U)
        {
            memsize >>= 1U;
            (*sizeConverted)++;
        }
    }

    return status;
}

static uint8_t SEMC_ConvertTiming(uint32_t time_ns, uint32_t clkSrc_Hz)
{
    assert(clkSrc_Hz != 0x00U);

    uint8_t clockCycles = 0;
    uint32_t tClk_ps;

    clkSrc_Hz /= 1000000U;
    /* Using ps for high resolution */
    tClk_ps = 1000000U / clkSrc_Hz;

    while (tClk_ps * clockCycles < time_ns * 1000U)
    {
        clockCycles++;
    }

    return (clockCycles == 0x00U) ? clockCycles : (clockCycles - 0x01U);
}

static status_t SEMC_IsIPCommandDone(void)
{
    uint32_t value;
    status_t status = kStatus_Success;

    /* Poll status bit till command is done*/

    while ((READ_REG(IMXRT_SEMC_INTR) & (uint32_t)SEMC_INTR_IPCMDDONE_MASK) == 0x00U)
    {
    };

    /* Clear status bit */
    //base->INTR |= SEMC_INTR_IPCMDDONE_MASK;
    SET_BIT(IMXRT_SEMC_INTR, SEMC_INTR_IPCMDDONE_MASK);

    /* Check error status */
    value = READ_REG(IMXRT_SEMC_INTR);
    if ((value & (uint32_t)SEMC_INTR_IPCMDERR_MASK) != 0x00U)
    {
        //base->INTR |= SEMC_INTR_IPCMDERR_MASK;
        SET_BIT(IMXRT_SEMC_INTR, SEMC_INTR_IPCMDERR_MASK);
        status = kStatus_SEMC_IpCommandExecutionError;
    }

    return status;
}


status_t SEMC_SendIPCommand(
semc_mem_type_t memType, uint32_t address, uint32_t command, uint32_t write, uint32_t *read)
{
    uint32_t cmdMode;
    uint32_t value;
    bool readCmd  = false;
    bool writeCmd = false;
    status_t result;

    /* Clear status bit */
    //base->INTR |= SEMC_INTR_IPCMDDONE_MASK;
    CLEAR_BIT(IMXRT_SEMC_INTR, SEMC_INTR_IPCMDDONE_MASK);
    /* Set address. */
    //base->IPCR0 = address;
    WRITE_REG(IMXRT_SEMC_IPCR0, address);

    /* Check command mode. */
    cmdMode = (uint32_t)command & 0x0FU;
    switch (memType)
    {
        case kSEMC_MemType_NAND:
            readCmd = (cmdMode == (uint32_t)kSEMC_NANDCM_CommandAddressRead) ||
                      (cmdMode == (uint32_t)kSEMC_NANDCM_CommandRead) || (cmdMode == (uint32_t)kSEMC_NANDCM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_NANDCM_CommandAddressWrite) ||
                       (cmdMode == (uint32_t)kSEMC_NANDCM_CommandWrite) || (cmdMode == (uint32_t)kSEMC_NANDCM_Write);
            break;
        case kSEMC_MemType_NOR:
        case kSEMC_MemType_8080:
            readCmd  = (cmdMode == (uint32_t)kSEMC_NORDBICM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_NORDBICM_Write);
            break;
        case kSEMC_MemType_SRAM:
            readCmd  = (cmdMode == (uint32_t)kSEMC_SRAMCM_ArrayRead) || (cmdMode == (uint32_t)kSEMC_SRAMCM_RegRead);
            writeCmd = (cmdMode == (uint32_t)kSEMC_SRAMCM_ArrayWrite) || (cmdMode == (uint32_t)kSEMC_SRAMCM_RegWrite);
            break;
        case kSEMC_MemType_SDRAM:
            readCmd  = (cmdMode == (uint32_t)kSEMC_SDRAMCM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_SDRAMCM_Write) || (cmdMode == (uint32_t)kSEMC_SDRAMCM_Modeset);
            break;
        default:
            assert(false);
            break;
    }

    if (writeCmd)
    {
        /* Set data. */
        //base->IPTXDAT = write;
        WRITE_REG(IMXRT_SEMC_IPTXDAT, write);
    }

    /* Set command code. */
    //base->IPCMD = command | SEMC_IPCMD_KEY(SEMC_IPCOMMANDMAGICKEY);
    value = command | SEMC_IPCMD_KEY(SEMC_IPCOMMANDMAGICKEY);
    WRITE_REG(IMXRT_SEMC_IPCMD, value);

    /* Wait for command done. */
    result = SEMC_IsIPCommandDone();
    if (result != kStatus_Success)
    {
        return result;
    }

    if (readCmd)
    {
        /* Get the read data */
        //*read = base->IPRXDAT;
        *read = READ_REG(IMXRT_SEMC_IPRXDAT);
    }

    return kStatus_Success;
}

void SEMC_GetDefaultConfig(semc_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->queueWeight.queueaEnable          = true;
    semc_queuea_weight_struct_t *queueaWeight = &(config->queueWeight.queueaWeight.queueaConfig);
    config->queueWeight.queuebEnable          = true;
    semc_queueb_weight_struct_t *queuebWeight = &(config->queueWeight.queuebWeight.queuebConfig);

    /* Get default settings. */
    config->dqsMode          = kSEMC_Loopbackinternal;
    config->cmdTimeoutCycles = 0xFF;
    config->busTimeoutCycles = 0x1F;

    queueaWeight->qos              = SEMC_BMCR0_TYPICAL_WQOS;
    queueaWeight->aging            = SEMC_BMCR0_TYPICAL_WAGE;
    queueaWeight->slaveHitSwith    = SEMC_BMCR0_TYPICAL_WSH;
    queueaWeight->slaveHitNoswitch = SEMC_BMCR0_TYPICAL_WRWS;
    queuebWeight->qos              = SEMC_BMCR1_TYPICAL_WQOS;
    queuebWeight->aging            = SEMC_BMCR1_TYPICAL_WAGE;
    queuebWeight->slaveHitSwith    = SEMC_BMCR1_TYPICAL_WRWS;
    queuebWeight->weightPagehit    = SEMC_BMCR1_TYPICAL_WPH;
    queuebWeight->bankRotation     = SEMC_BMCR1_TYPICAL_WBR;
}

#include "imxrt_clock_drv.h"
void SEMC_Init(semc_config_t *configure)
{
    assert(configure != NULL);

    //uint8_t index = 0;
    uint32_t value;
    syslog(LOG_INFO, "SEMC_Init1\n");

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate sdram controller clock. */
    //CLOCK_EnableClock(s_semcClock[SEMC_GetInstance()]);
    CLOCK_EnableClock(0x34);
#if (defined(SEMC_EXSC_CLOCKS))
    //CLOCK_EnableClock(s_semcExtClock[SEMC_GetInstance()]);
    CLOCK_EnableClock(0x112);
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

syslog(LOG_INFO, "SEMC_Init2\n");
    /* Initialize all BR to zero due to the default base address set. */
    /*
    for (index = 0; index < SEMC_BR_REG_NUM; index++)
    {
        base->BR[index] = 0;
    }*/
    syslog(LOG_INFO, "SEMC_Init21\n");
    WRITE_REG(IMXRT_SEMC_BR0, 0x00);
    WRITE_REG(IMXRT_SEMC_BR1, 0x00);
    WRITE_REG(IMXRT_SEMC_BR2, 0x00);
    WRITE_REG(IMXRT_SEMC_BR3, 0x00);
    WRITE_REG(IMXRT_SEMC_BR4, 0x00);
    WRITE_REG(IMXRT_SEMC_BR5, 0x00);
    WRITE_REG(IMXRT_SEMC_BR6, 0x00);
    WRITE_REG(IMXRT_SEMC_BR7, 0x00);
    WRITE_REG(IMXRT_SEMC_BR8, 0x00);

syslog(LOG_INFO, "SEMC_Init3\n");
    /* Software reset for SEMC internal logical . */
    //base->MCR = SEMC_MCR_SWRST_MASK;
    WRITE_REG(IMXRT_SEMC_MCR, SEMC_MCR_SWRST_MASK);
    while ((READ_REG(IMXRT_SEMC_MCR) & (uint32_t)SEMC_MCR_SWRST_MASK) != 0x00U)
    {
    }
syslog(LOG_INFO, "SEMC_Init4\n");
    /* Configure, disable module first. */
    /*
    base->MCR |= SEMC_MCR_MDIS_MASK | SEMC_MCR_BTO(configure->busTimeoutCycles) |
                 SEMC_MCR_CTO(configure->cmdTimeoutCycles) | SEMC_MCR_DQSMD(configure->dqsMode);*/
    value = SEMC_MCR_MDIS_MASK | SEMC_MCR_BTO(configure->busTimeoutCycles) |
            SEMC_MCR_CTO(configure->cmdTimeoutCycles) | SEMC_MCR_DQSMD(configure->dqsMode);
    SET_BIT(IMXRT_SEMC_MCR, value);

    if (configure->queueWeight.queueaEnable == true)
    {
        /* Configure Queue A for AXI bus access to SDRAM, NAND, NOR, SRAM and DBI slaves.*/
        //base->BMCR0 = (uint32_t)(configure->queueWeight.queueaWeight.queueaValue);
        value = (uint32_t)(configure->queueWeight.queueaWeight.queueaValue);
        WRITE_REG(IMXRT_SEMC_BMCR0, value);
    }
    else
    {
        //base->BMCR0 = 0x00U;
        WRITE_REG(IMXRT_SEMC_BMCR0, 0x00);
    }

    if (configure->queueWeight.queuebEnable == true)
    {
        /* Configure Queue B for AXI bus access to SDRAM slave. */
        //base->BMCR1 = (uint32_t)(configure->queueWeight.queuebWeight.queuebValue);
        value = (uint32_t)(configure->queueWeight.queuebWeight.queuebValue);
        WRITE_REG(IMXRT_SEMC_BMCR1, value);
    }
    else
    {
        //base->BMCR1 = 0x00U;
        WRITE_REG(IMXRT_SEMC_BMCR1, 0x00);
    }

    /* Enable SEMC. */
    //base->MCR &= ~SEMC_MCR_MDIS_MASK;
    CLEAR_BIT(IMXRT_SEMC_MCR, SEMC_MCR_MDIS_MASK);
    syslog(LOG_INFO, "SEMC_Init NN\n");
}

status_t SEMC_ConfigureSDRAM(semc_sdram_cs_t cs, semc_sdram_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);
    assert(clkSrc_Hz > 0x00U);
    assert(config->refreshBurstLen > 0x00U);
    syslog(LOG_INFO, "SEMC_ConfigureSDRAM\n");

    uint8_t memsize;
    status_t result   = kStatus_Success;
    uint16_t prescale = (uint16_t)(config->tPrescalePeriod_Ns / 16U / (1000000000U / clkSrc_Hz));
    uint32_t refresh;
    uint32_t urgentRef;
    uint32_t idle;
    uint32_t mode;
    uint32_t timing;
    uint32_t value;

    if ((config->address < SEMC_STARTADDRESS) || (config->address > SEMC_ENDADDRESS))
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM1\n");
        return kStatus_SEMC_InvalidBaseAddress;
    }

    if (config->csxPinMux == kSEMC_MUXA8)
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM2\n");
        return kStatus_SEMC_InvalidSwPinmuxSelection;
    }

    if (prescale > 256U)
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM3\n");
        return kStatus_SEMC_InvalidTimerSetting;
    }

    refresh   = config->refreshPeriod_nsPerRow / config->tPrescalePeriod_Ns;
    urgentRef = config->refreshUrgThreshold / config->tPrescalePeriod_Ns;
    idle      = config->tIdleTimeout_Ns / config->tPrescalePeriod_Ns;


    //uint32_t iocReg = base->IOCR & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->csxPinMux));
    uint32_t reg = READ_REG(IMXRT_SEMC_IOCR);
    uint32_t iocReg = reg & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->csxPinMux));


    /* Base control. */
    result = SEMC_CovertMemorySize(config->memsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM4\n");
        return result;
    }

    //base->BR[cs] = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;
    value = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;
    //syslog(LOG_INFO, "SEMC_ConfigureSDRAM5\n");
    switch (cs) {
        case kSEMC_SDRAM_CS0:
            WRITE_REG(IMXRT_SEMC_BR0, value);
            //syslog(LOG_INFO, "SEMC_ConfigureSDRAM6\n");
            break;
        case kSEMC_SDRAM_CS1:
            WRITE_REG(IMXRT_SEMC_BR1, value);
            //syslog(LOG_INFO, "SEMC_ConfigureSDRAM7\n");
            break;
        case kSEMC_SDRAM_CS2:
            WRITE_REG(IMXRT_SEMC_BR2, value);
            //syslog(LOG_INFO, "SEMC_ConfigureSDRAM8\n");
            break;
        case kSEMC_SDRAM_CS3:
            WRITE_REG(IMXRT_SEMC_BR3, value);
            //syslog(LOG_INFO, "SEMC_ConfigureSDRAM9\n");
            break;
    }

#if defined(FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT) && (FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT)
    //syslog(LOG_INFO, "SEMC_ConfigureSDRAM10\n");
    if (kSEMC_SdramColunm_8bit == config->columnAddrBitNum)
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM11\n");
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL8(true) | SEMC_SDRAMCR0_CL(config->casLatency);
    }
    else
#endif /* FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT */
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM12\n");
        /*
        syslog(LOG_INFO, "SEMC_ConfigureSDRAM1\n");
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL(config->columnAddrBitNum) | SEMC_SDRAMCR0_CL(config->casLatency);*/
        value = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL(config->columnAddrBitNum) | SEMC_SDRAMCR0_CL(config->casLatency);
        WRITE_REG(IMXRT_SEMC_SDRAMCR0, value);
    }

    /* IOMUX setting. */
    if (cs != kSEMC_SDRAM_CS0)
    {
        //syslog(LOG_INFO, "SEMC_ConfigureSDRAM13\n");
        //base->IOCR = iocReg | ((uint32_t)cs << (uint32_t)config->csxPinMux);
        value = iocReg | ((uint32_t)cs << (uint32_t)config->csxPinMux);
        WRITE_REG(IMXRT_SEMC_IOCR, value);
    }

    //base->IOCR &= ~SEMC_IOCR_MUX_A8_MASK;
    CLEAR_BIT(IMXRT_SEMC_IOCR, SEMC_IOCR_MUX_A8_MASK);

#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
//syslog(LOG_INFO, "SEMC_ConfigureSDRAM14\n");
    uint32_t tempDelayChain = base->DCCR;

    tempDelayChain &= ~(SEMC_DCCR_SDRAMVAL_MASK | SEMC_DCCR_SDRAMEN_MASK);
    /* Configure delay chain. */
    base->DCCR = tempDelayChain | SEMC_DCCR_SDRAMVAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_SDRAMEN_MASK;
#endif /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */
//syslog(LOG_INFO, "SEMC_ConfigureSDRAM15\n");
    timing = SEMC_SDRAMCR1_PRE2ACT(SEMC_ConvertTiming(config->tPrecharge2Act_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_ACT2RW(SEMC_ConvertTiming(config->tAct2ReadWrite_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_RFRC(SEMC_ConvertTiming(config->tRefreshRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_WRC(SEMC_ConvertTiming(config->tWriteRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_CKEOFF(SEMC_ConvertTiming(config->tCkeOff_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_ACT2PRE(SEMC_ConvertTiming(config->tAct2Prechage_Ns, clkSrc_Hz));
    /* SDRAMCR1 timing setting. */
    //base->SDRAMCR1 = timing;
    WRITE_REG(IMXRT_SEMC_SDRAMCR1, timing);

    timing = SEMC_SDRAMCR2_SRRC(SEMC_ConvertTiming(config->tSelfRefRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR2_REF2REF(SEMC_ConvertTiming(config->tRefresh2Refresh_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR2_ACT2ACT(SEMC_ConvertTiming(config->tAct2Act_Ns, clkSrc_Hz)) | SEMC_SDRAMCR2_ITO(idle);
    /* SDRAMCR2 timing setting. */
    //base->SDRAMCR2 = timing;
    WRITE_REG(IMXRT_SEMC_SDRAMCR2, timing);

    /* SDRAMCR3 timing setting. */
    #if 0
    base->SDRAMCR3 = SEMC_SDRAMCR3_REBL((uint32_t)config->refreshBurstLen - 1UL) |
                     /* N * 16 * 1s / clkSrc_Hz = config->tPrescalePeriod_Ns */
                     SEMC_SDRAMCR3_PRESCALE(prescale) | SEMC_SDRAMCR3_RT(refresh - 1UL) | SEMC_SDRAMCR3_UT(urgentRef);
    #endif
    timing = SEMC_SDRAMCR3_REBL((uint32_t)config->refreshBurstLen - 1UL) |
    SEMC_SDRAMCR3_PRESCALE(prescale) | SEMC_SDRAMCR3_RT(refresh - 1UL) | SEMC_SDRAMCR3_UT(urgentRef);
    WRITE_REG(IMXRT_SEMC_SDRAMCR3, timing);

    //SEMC->IPCR1 = 0x2U;
    //SEMC->IPCR2 = 0U;
    WRITE_REG(IMXRT_SEMC_IPCR1, 0x02);
    WRITE_REG(IMXRT_SEMC_IPCR2, 0x00);

    result =
            SEMC_SendIPCommand(kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_Prechargeall, 0, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }
    result =
            SEMC_SendIPCommand(kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_AutoRefresh, 0, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }
    result =
            SEMC_SendIPCommand(kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_AutoRefresh, 0, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }
    /* Mode setting value. */
    mode = (uint32_t)config->burstLen | (((uint32_t)config->casLatency) << SEMC_SDRAM_MODESETCAL_OFFSET);
    result =
            SEMC_SendIPCommand(kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_Modeset, mode, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }
    /* Enables refresh */
    //base->SDRAMCR3 |= SEMC_SDRAMCR3_REN_MASK;
    SET_BIT(IMXRT_SEMC_SDRAMCR3, SEMC_SDRAMCR3_REN_MASK);

    return kStatus_Success;
}

#define SEMC_EXAMPLE_DATALEN   (0x100U)// (0x1000U)
#define EXAMPLE_SEMC_START_ADDRESS (0x80000000U)
uint32_t sdram_writeBuffer[SEMC_EXAMPLE_DATALEN];
uint32_t sdram_readBuffer[SEMC_EXAMPLE_DATALEN];

#if 0

void SEMC_SDRAMReadWrite32Bit(void)
{
    uint32_t index;
    uint32_t datalen = SEMC_EXAMPLE_DATALEN;
    uint32_t *sdram  = (uint32_t *)EXAMPLE_SEMC_START_ADDRESS; /* SDRAM start address. */
    bool result      = true;

    PRINTF("\r\n SEMC SDRAM Memory 32 bit Write Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);
    /* Prepare data and write to SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_writeBuffer[index] = index;
        sdram[index]             = sdram_writeBuffer[index];
    }

    PRINTF("\r\n SEMC SDRAM Read 32 bit Data Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_SEMC_START_ADDRESS, 4U * SEMC_EXAMPLE_DATALEN);
#endif

    /* Read data from the SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_readBuffer[index] = sdram[index];
    }

    PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Start!\r\n");
    /* Compare the two buffers. */
    while (datalen--)
    {
        if (sdram_writeBuffer[datalen] != sdram_readBuffer[datalen])
        {
            result = false;
            break;
        }
    }

    if (!result)
    {
        PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Failed!\r\n");
    }
    else
    {
        PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Succeed!\r\n");
    }
}

static void SEMC_SDRAMReadWrite16Bit(void)
{
    uint32_t index;
    uint32_t datalen = SEMC_EXAMPLE_DATALEN;
    uint16_t *sdram  = (uint16_t *)EXAMPLE_SEMC_START_ADDRESS; /* SDRAM start address. */
    bool result      = true;

    PRINTF("\r\n SEMC SDRAM Memory 16 bit Write Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);

    memset(sdram_writeBuffer, 0, sizeof(sdram_writeBuffer));
    memset(sdram_readBuffer, 0, sizeof(sdram_readBuffer));

    /* Prepare data and write to SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_writeBuffer[index] = index % 0xFFFF;
        sdram[index]             = sdram_writeBuffer[index];
    }

    PRINTF("\r\n SEMC SDRAM Read 16 bit Data Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_SEMC_START_ADDRESS, 4U * SEMC_EXAMPLE_DATALEN);
#endif

    /* Read data from the SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_readBuffer[index] = sdram[index];
    }

    PRINTF("\r\n SEMC SDRAM 16 bit Data Write and Read Compare Start!\r\n");
    /* Compare the two buffers. */
    while (datalen--)
    {
        if (sdram_writeBuffer[datalen] != sdram_readBuffer[datalen])
        {
            result = false;
            break;
        }
    }

    if (!result)
    {
        PRINTF("\r\n SEMC SDRAM 16 bit Data Write and Read Compare Failed!\r\n");
    }
    else
    {
        PRINTF("\r\n SEMC SDRAM 16 bit Data Write and Read Compare Succeed!\r\n");
    }
}
#endif

void SEMC_SDRAMReadWrite8Bit(void)
{
    uint32_t index;
    uint32_t datalen = SEMC_EXAMPLE_DATALEN;
    uint8_t *sdram   = (uint8_t *)EXAMPLE_SEMC_START_ADDRESS; /* SDRAM start address. */
    bool result      = true;

    syslog(LOG_INFO, "\r\n SEMC SDRAM Memory 8 bit Write Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);

    memset(sdram_writeBuffer, 0, sizeof(sdram_writeBuffer));
    memset(sdram_readBuffer, 0, sizeof(sdram_readBuffer));

    /* Prepare data and write to SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_writeBuffer[index] = index % 0x100;
        sdram[index]             = sdram_writeBuffer[index];
    }

    syslog(LOG_INFO, "\r\n SEMC SDRAM Read 8 bit Data Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_SEMC_START_ADDRESS, 4U * SEMC_EXAMPLE_DATALEN);
#endif

    /* Read data from the SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_readBuffer[index] = sdram[index];
    }

    syslog(LOG_INFO, "\r\n SEMC SDRAM 8 bit Data Write and Read Compare Start!\r\n");
    /* Compare the two buffers. */
    while (datalen--)
    {
        if (sdram_writeBuffer[datalen] != sdram_readBuffer[datalen])
        {
            result = false;
            break;
        }
    }

    if (!result)
    {
        syslog(LOG_INFO, "\r\n SEMC SDRAM 8 bit Data Write and Read Compare Failed!\r\n");
    }
    else
    {
        syslog(LOG_INFO, "\r\n SEMC SDRAM 8 bit Data Write and Read Compare Succeed!\r\n");
    }
}