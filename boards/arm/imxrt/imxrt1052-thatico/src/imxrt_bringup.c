/****************************************************************************
 * boards/arm/imxrt/imxrt1050-evk/src/imxrt_bringup.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <debug.h>

#include <syslog.h>
#include <nuttx/fs/fs.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/video/fb.h>
#include <imxrt_lpi2c.h>
#include <imxrt_lpspi.h>

#ifdef CONFIG_IMXRT_USDHC
#  include "imxrt_usdhc.h"
#endif

#include "imxrt1052-thatico.h"
#include "hardware/imxrt_ccm.h"
#include "imxrt_periphclks.h"
#include "hardware/imxrt_pinmux.h"
#include "imxrt_common_drv.h"
#include <arch/board/board.h>  /* Must always be included last */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Checking needed by MMC/SDCard */

#ifdef CONFIG_NSH_MMCSDMINOR
#  define MMCSD_MINOR CONFIG_NSH_MMCSDMINOR
#else
#  define MMCSD_MINOR 0
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/


#define GPIO_SEMC_DATA00    (GPIO_SEMC_DATA00_1)
#define GPIO_SEMC_DATA01    GPIO_SEMC_DATA01_1
#define GPIO_SEMC_DATA02    GPIO_SEMC_DATA02_1
#define GPIO_SEMC_DATA03    GPIO_SEMC_DATA03_1
#define GPIO_SEMC_DATA04    GPIO_SEMC_DATA04_1
#define GPIO_SEMC_DATA05    GPIO_SEMC_DATA05_1
#define GPIO_SEMC_DATA06    GPIO_SEMC_DATA06_1
#define GPIO_SEMC_DATA07    GPIO_SEMC_DATA07_1
#define GPIO_SEMC_DM00      GPIO_SEMC_DM00_1
#define GPIO_SEMC_WE        GPIO_SEMC_WE_1
#define GPIO_SEMC_CAS       GPIO_SEMC_CAS_1
#define GPIO_SEMC_RAS       GPIO_SEMC_RAS_1
#define GPIO_SEMC_CS0       GPIO_SEMC_CS0_1
#define GPIO_SEMC_BA0       GPIO_SEMC_BA0_1
#define GPIO_SEMC_BA1       GPIO_SEMC_BA1_1
#define GPIO_SEMC_ADDR10    GPIO_SEMC_ADDR10_1
#define GPIO_SEMC_ADDR00    GPIO_SEMC_ADDR00_1
#define GPIO_SEMC_ADDR01    GPIO_SEMC_ADDR01_1
#define GPIO_SEMC_ADDR02    GPIO_SEMC_ADDR02_1
#define GPIO_SEMC_ADDR03    GPIO_SEMC_ADDR03_1
#define GPIO_SEMC_ADDR04    GPIO_SEMC_ADDR04_1
#define GPIO_SEMC_ADDR05    GPIO_SEMC_ADDR05_1
#define GPIO_SEMC_ADDR06    GPIO_SEMC_ADDR06_1
#define GPIO_SEMC_ADDR07    GPIO_SEMC_ADDR07_1
#define GPIO_SEMC_ADDR08    GPIO_SEMC_ADDR08_1
#define GPIO_SEMC_ADDR09    GPIO_SEMC_ADDR09_1
#define GPIO_SEMC_ADDR11    GPIO_SEMC_ADDR11_1
#define GPIO_SEMC_ADDR12    GPIO_SEMC_ADDR12_1
#define GPIO_SEMC_DQS       GPIO_SEMC_DQS_1
#define GPIO_SEMC_CKE       GPIO_SEMC_CKE_1
#define GPIO_SEMC_CLK       GPIO_SEMC_CLK_1
#define GPIO_SEMC_DM01      GPIO_SEMC_DM01_1
#define GPIO_SEMC_DATA08    GPIO_SEMC_DATA08_1
#define GPIO_SEMC_DATA09    GPIO_SEMC_DATA09_1
#define GPIO_SEMC_DATA10    GPIO_SEMC_DATA10_1
#define GPIO_SEMC_DATA11    GPIO_SEMC_DATA11_1
#define GPIO_SEMC_DATA12    GPIO_SEMC_DATA12_1
#define GPIO_SEMC_DATA13    GPIO_SEMC_DATA13_1
#define GPIO_SEMC_DATA14    GPIO_SEMC_DATA14_1
#define GPIO_SEMC_DATA15    GPIO_SEMC_DATA15_1
#define GPIO_SEMC_CSX00     GPIO_SEMC_CSX00_1
#define GPIO_SEMC_RDY       GPIO_SEMC_RDY_1

void imxrt_semc_io_init(void)
{
  imxrt_config_gpio(GPIO_SEMC_DATA00);
  imxrt_config_gpio(GPIO_SEMC_DATA01);
  imxrt_config_gpio(GPIO_SEMC_DATA02);
  imxrt_config_gpio(GPIO_SEMC_DATA03);
  imxrt_config_gpio(GPIO_SEMC_DATA04);
  imxrt_config_gpio(GPIO_SEMC_DATA05);
  imxrt_config_gpio(GPIO_SEMC_DATA06);
  imxrt_config_gpio(GPIO_SEMC_DATA07);
  imxrt_config_gpio(GPIO_SEMC_DM00);
  imxrt_config_gpio(GPIO_SEMC_WE);
  imxrt_config_gpio(GPIO_SEMC_CAS);
  imxrt_config_gpio(GPIO_SEMC_RAS);
  imxrt_config_gpio(GPIO_SEMC_CS0);
  imxrt_config_gpio(GPIO_SEMC_BA0);
  imxrt_config_gpio(GPIO_SEMC_BA1);
  imxrt_config_gpio(GPIO_SEMC_ADDR10);
  imxrt_config_gpio(GPIO_SEMC_ADDR00);
  imxrt_config_gpio(GPIO_SEMC_ADDR01);
  imxrt_config_gpio(GPIO_SEMC_ADDR02);
  imxrt_config_gpio(GPIO_SEMC_ADDR03);
  imxrt_config_gpio(GPIO_SEMC_ADDR04);
  imxrt_config_gpio(GPIO_SEMC_ADDR05);
  imxrt_config_gpio(GPIO_SEMC_ADDR06);
  imxrt_config_gpio(GPIO_SEMC_ADDR07);
  imxrt_config_gpio(GPIO_SEMC_ADDR08);
  imxrt_config_gpio(GPIO_SEMC_ADDR09);
  imxrt_config_gpio(GPIO_SEMC_ADDR11);
  imxrt_config_gpio(GPIO_SEMC_ADDR12);
  imxrt_config_gpio(GPIO_SEMC_DQS);
  imxrt_config_gpio(GPIO_SEMC_CKE);
  imxrt_config_gpio(GPIO_SEMC_CLK);
  imxrt_config_gpio(GPIO_SEMC_DM01);
  imxrt_config_gpio(GPIO_SEMC_DATA08);
  imxrt_config_gpio(GPIO_SEMC_DATA09);
  imxrt_config_gpio(GPIO_SEMC_DATA10);
  imxrt_config_gpio(GPIO_SEMC_DATA11);
  imxrt_config_gpio(GPIO_SEMC_DATA12);
  imxrt_config_gpio(GPIO_SEMC_DATA13);
  imxrt_config_gpio(GPIO_SEMC_DATA14);
  imxrt_config_gpio(GPIO_SEMC_DATA15);
  imxrt_config_gpio(GPIO_SEMC_CSX00);
  imxrt_config_gpio(GPIO_SEMC_RDY);
  imxrt_clockall_semc();
}

#if defined(CONFIG_I2C_DRIVER) && defined(CONFIG_IMXRT_LPI2C)
static void imxrt_i2c_register(int bus)
{
  FAR struct i2c_master_s *i2c;
  int ret;

  i2c = imxrt_i2cbus_initialize(bus);
  if (i2c == NULL)
    {
      serr("ERROR: Failed to get I2C%d interface\n", bus);
    }
  else
    {
      ret = i2c_register(i2c, bus);
      if (ret < 0)
        {
          serr("ERROR: Failed to register I2C%d driver: %d\n", bus, ret);
          imxrt_i2cbus_uninitialize(i2c);
        }
    }
}
#endif

#ifdef CONFIG_IMXRT_USDHC
static int nsh_sdmmc_initialize(void)
{
    syslog(LOG_INFO, "= = = = = = 1. %s\n", __func__);
  struct sdio_dev_s *sdmmc;
  int ret = 0;

  /* Get an instance of the SDIO interface */

  sdmmc = imxrt_usdhc_initialize(0);
  if (!sdmmc)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SD/MMC\n");
    }
  else
    {
      /* Bind the SDIO interface to the MMC/SD driver */

      ret = mmcsd_slotinitialize(0, sdmmc);
      if (ret != OK)
        {
          syslog(LOG_ERR,
                 "ERROR: Failed to bind SDIO to the MMC/SD driver: %d\n",
                 ret);
        }
    }

  return OK;
}
#else
#  define nsh_sdmmc_initialize() (OK)
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imxrt_bringup
 *
 * Description:
 *   Bring up board features
 *
 ****************************************************************************/

int imxrt_bringup(void)
{
  int ret;
  syslog(LOG_INFO, "= = = = = = 1. %s\n", __func__);
  /* If we got here then perhaps not all initialization was successful, but
   * at least enough succeeded to bring-up NSH with perhaps reduced
   * capabilities.
   */

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, "/proc", "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount procfs at /proc: %d\n", ret);
    }
#endif

#if defined(CONFIG_I2C_DRIVER) && defined(CONFIG_IMXRT_LPI2C1)
  imxrt_i2c_register(1);
#endif

#ifdef CONFIG_IMXRT_USDHC
  /* Initialize SDHC-base MMC/SD card support */

  nsh_sdmmc_initialize();
#endif

#ifdef CONFIG_MMCSD_SPI
  /* Initialize SPI-based MMC/SD card support */

  imxrt_spidev_initialize();

  ret = imxrt_mmcsd_spi_initialize(MMCSD_MINOR);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SD slot %d: %d\n", ret);
    }
#endif

#ifdef CONFIG_DEV_GPIO
  ret = imxrt_gpio_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize GPIO Driver: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_VIDEO_FB
  /* Initialize and register the framebuffer driver */

  ret = fb_register(0, 0);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: fb_register() failed: %d\n", ret);
    }
#endif

  syslog(LOG_INFO, "IMXRT_CCM_CBCDR %lx\n", READ_REG(IMXRT_CCM_CBCDR));
  syslog(LOG_INFO, "IMXRT_CCM_ANALOG_PLL_ARM %lx\n", READ_REG(IMXRT_CCM_ANALOG_PLL_ARM));
  imxrt_semc_io_init();
  init_semc_sdram();
  SEMC_SDRAMReadWrite8Bit();
  //syslog(LOG_INFO, "CLOCK_GetSemcFreq %ld\n", CLOCK_GetSemcFreq());
  syslog(LOG_INFO, "= = = = = = 22. %s\n", __func__);
  UNUSED(ret);
  return OK;
}