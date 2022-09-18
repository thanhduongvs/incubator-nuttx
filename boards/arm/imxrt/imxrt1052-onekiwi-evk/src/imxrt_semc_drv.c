#include "imxrt_semc_drv.h"
#include <assert.h>
#include <string.h>

/*! @brief Pointers to SEMC bases for each instance. */
static SEMC_Type *const s_semcBases[] = SEMC_BASE_PTRS;

static uint32_t SEMC_GetInstance()
{
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

static status_t SEMC_IsIPCommandDone()
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

void SEMC_Init(semc_config_t *configure)
{
    assert(configure != NULL);

    uint8_t index = 0;
    uint32_t value;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate sdram controller clock. */
    CLOCK_EnableClock(s_semcClock[SEMC_GetInstance(base)]);
#if (defined(SEMC_EXSC_CLOCKS))
    CLOCK_EnableClock(s_semcExtClock[SEMC_GetInstance(base)]);
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Initialize all BR to zero due to the default base address set. */
    /*
    for (index = 0; index < SEMC_BR_REG_NUM; index++)
    {
        base->BR[index] = 0;
    }*/
    WRITE_REG(IMXRT_SEMC_BR0, 0x00);
    WRITE_REG(IMXRT_SEMC_BR1, 0x00);
    WRITE_REG(IMXRT_SEMC_BR2, 0x00);
    WRITE_REG(IMXRT_SEMC_BR3, 0x00);
    WRITE_REG(IMXRT_SEMC_BR4, 0x00);
    WRITE_REG(IMXRT_SEMC_BR5, 0x00);
    WRITE_REG(IMXRT_SEMC_BR6, 0x00);
    WRITE_REG(IMXRT_SEMC_BR7, 0x00);
    WRITE_REG(IMXRT_SEMC_BR8, 0x00);


    /* Software reset for SEMC internal logical . */
    //base->MCR = SEMC_MCR_SWRST_MASK;
    WRITE_REG(IMXRT_SEMC_MCR, SEMC_MCR_SWRST_MASK);
    while ((READ_REG(IMXRT_SEMC_MCR) & (uint32_t)SEMC_MCR_SWRST_MASK) != 0x00U)
    {
    }

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
}

status_t SEMC_ConfigureSDRAM(semc_sdram_cs_t cs, semc_sdram_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);
    assert(clkSrc_Hz > 0x00U);
    assert(config->refreshBurstLen > 0x00U);

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
        return kStatus_SEMC_InvalidBaseAddress;
    }

    if (config->csxPinMux == kSEMC_MUXA8)
    {
        return kStatus_SEMC_InvalidSwPinmuxSelection;
    }

    if (prescale > 256U)
    {
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
        return result;
    }

    //base->BR[cs] = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;
    value = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;
    switch (cs) {
        case kSEMC_SDRAM_CS0:
            WRITE_REG(IMXRT_SEMC_BR0, value);
            break;
        case kSEMC_SDRAM_CS1:
            WRITE_REG(IMXRT_SEMC_BR1, value);
            break;
        case kSEMC_SDRAM_CS2:
            WRITE_REG(IMXRT_SEMC_BR2, value);
            break;
        case kSEMC_SDRAM_CS3:
            WRITE_REG(IMXRT_SEMC_BR3, value);
            break;
    }

#if defined(FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT) && (FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT)
    if (kSEMC_SdramColunm_8bit == config->columnAddrBitNum)
    {
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL8(true) | SEMC_SDRAMCR0_CL(config->casLatency);
    }
    else
#endif /* FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT */
    {
        /*
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL(config->columnAddrBitNum) | SEMC_SDRAMCR0_CL(config->casLatency);*/
        value = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL(config->columnAddrBitNum) | SEMC_SDRAMCR0_CL(config->casLatency);
        WRITE_REG(IMXRT_SEMC_SDRAMCR0, value);
    }

    /* IOMUX setting. */
    if (cs != kSEMC_SDRAM_CS0)
    {
        //base->IOCR = iocReg | ((uint32_t)cs << (uint32_t)config->csxPinMux);
        value = iocReg | ((uint32_t)cs << (uint32_t)config->csxPinMux);
        WRITE_REG(IMXRT_SEMC_IOCR, value);
    }

    //base->IOCR &= ~SEMC_IOCR_MUX_A8_MASK;
    CLEAR_BIT(IMXRT_SEMC_IOCR, SEMC_IOCR_MUX_A8_MASK);

#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint32_t tempDelayChain = base->DCCR;

    tempDelayChain &= ~(SEMC_DCCR_SDRAMVAL_MASK | SEMC_DCCR_SDRAMEN_MASK);
    /* Configure delay chain. */
    base->DCCR = tempDelayChain | SEMC_DCCR_SDRAMVAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_SDRAMEN_MASK;
#endif /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */

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