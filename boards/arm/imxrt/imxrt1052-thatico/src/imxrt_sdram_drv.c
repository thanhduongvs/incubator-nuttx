#include "imxrt_semc_drv.h"
#include "imxrt_clock_drv.h"
#include <arch/board/board.h>
#include <syslog.h>

status_t init_semc_sdram(void)
{
    semc_config_t config;
    semc_sdram_config_t sdramconfig;
    uint32_t clockFrq = CLOCK_GetSemcFreq();

    syslog(LOG_INFO, "init_semc_sdram\n");

    /* Initializes the MAC configure structure to zero. */
    memset(&config, 0, sizeof(semc_config_t));
    memset(&sdramconfig, 0, sizeof(semc_sdram_config_t));

    /* Initialize SEMC. */
    SEMC_GetDefaultConfig(&config);
    config.dqsMode = kSEMC_Loopbackdqspad; /* For more accurate timing. */
    syslog(LOG_INFO, "init_semc_sdram1\n");
    SEMC_Init(&config);
    syslog(LOG_INFO, "init_semc_sdram2\n");

    /* Configure SDRAM. */
    sdramconfig.csxPinMux           = kSEMC_MUXCSX0;
    sdramconfig.address             = 0x80000000;
    sdramconfig.memsize_kbytes      = 32 * 1024; /* 32MB = 32*1024*1KBytes*/
    sdramconfig.portSize            = kSEMC_PortSize16Bit;
    sdramconfig.burstLen            = kSEMC_Sdram_BurstLen1;
    sdramconfig.columnAddrBitNum    = kSEMC_SdramColunm_9bit;
    sdramconfig.casLatency          = kSEMC_LatencyTwo; //kSEMC_LatencyThree;
    sdramconfig.tPrecharge2Act_Ns   = 18; /* Trp 18ns */
    sdramconfig.tAct2ReadWrite_Ns   = 18; //18; /* Trcd 18ns */
    sdramconfig.tRefreshRecovery_Ns = 64; //63; //67; /* Use the maximum of the (Trfc , Txsr). */

    sdramconfig.tWriteRecovery_Ns   = 12; //12; /* 12ns */

    // check
    sdramconfig.tCkeOff_Ns = 42; /* The minimum cycle of SDRAM CLK off state. CKE is off in self refresh at a minimum period tRAS.*/

    sdramconfig.tAct2Prechage_Ns       = 42; /* Tras 42ns */

    // check
    sdramconfig.tSelfRefRecovery_Ns    = 67;
    // check
    sdramconfig.tRefresh2Refresh_Ns    = 60;

    sdramconfig.tAct2Act_Ns            = 10; //60;

    // check
    sdramconfig.tPrescalePeriod_Ns     = 100 * (1000000000 / clockFrq); //160 * (1000000000 / clockFrq);

    sdramconfig.refreshPeriod_nsPerRow = 64 * 1000000 / 8192; /* 64ms/8192 */
    sdramconfig.refreshUrgThreshold    = sdramconfig.refreshPeriod_nsPerRow;
    sdramconfig.refreshBurstLen        = 1;
    syslog(LOG_INFO, "init_semc_sdram3\n");
    return SEMC_ConfigureSDRAM(kSEMC_SDRAM_CS0, &sdramconfig, clockFrq);
}
