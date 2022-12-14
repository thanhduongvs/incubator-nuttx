/****************************************************************************
 * arch/xtensa/src/esp32s3/esp32s3_gpio.c
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
#include <stdint.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <arch/irq.h>
#include <arch/esp32s3/chip.h>

#include "xtensa.h"
#include "esp32s3_irq.h"
#include "hardware/esp32s3_iomux.h"
#include "hardware/esp32s3_gpio.h"

#include "esp32s3_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: esp32s3_configgpio
 *
 * Description:
 *   Configure a GPIO pin based on encoded pin attributes.
 *
 ****************************************************************************/

int esp32s3_configgpio(int pin, gpio_pinattr_t attr)
{
  uintptr_t regaddr;
  uint32_t func;
  uint32_t cntrl;
  uint32_t pin2func;

  DEBUGASSERT(pin >= 0 && pin <= ESP32S3_NGPIOS);

  func  = 0;
  cntrl = 0;

  /* Handle input pins */

  if ((attr & INPUT) != 0)
    {
      putreg32((1ul << pin), GPIO_ENABLE_W1TC_REG);

      /* Input enable */

      func |= FUN_IE;

      if ((attr & PULLUP) != 0)
        {
          func |= FUN_PU;
        }
      else if ((attr & PULLDOWN) != 0)
        {
          func |= FUN_PD;
        }
    }

  /* Handle output pins */

  if ((attr & OUTPUT) != 0)
    {
      putreg32((1ul << pin), GPIO_ENABLE_W1TS_REG);
    }

  /* Add drivers */

  func |= (uint32_t)(2ul << FUN_DRV_S);

  /* Select the pad's function. If no function was given, consider it a
   * normal input or output (i.e. function1).
   */

  if ((attr & FUNCTION_MASK) != 0)
    {
      func |= (uint32_t)(((attr >> FUNCTION_SHIFT) - 1) << MCU_SEL_S);
    }
  else
    {
      func |= (uint32_t)(PIN_FUNC_GPIO << MCU_SEL_S);
    }

  if ((attr & OPEN_DRAIN) != 0)
    {
      cntrl |= (1 << GPIO_PIN_PAD_DRIVER_S);
    }

  /* Set the pin function to its register */

  pin2func = (pin + 1) * 4;
  regaddr = REG_IO_MUX_BASE + pin2func;
  putreg32(func, regaddr);

  regaddr = GPIO_REG(pin);
  putreg32(cntrl, regaddr);
  return OK;
}

/****************************************************************************
 * Name: esp32s3_gpio_matrix_in
 *
 * Description:
 *   Set gpio input to a signal
 *   NOTE: one gpio can input to several signals
 *   If gpio == 0x3c, cancel input to the signal, input 0 to signal.
 *   If gpio == 0x3a, input nothing to signal.
 *   If gpio == 0x38, cancel input to the signal, input 1 to signal.
 *
 ****************************************************************************/

void esp32s3_gpio_matrix_in(uint32_t gpio, uint32_t signal_idx, bool inv)
{
  uint32_t regaddr = GPIO_FUNC0_IN_SEL_CFG_REG + (signal_idx * 4);
  uint32_t regval = (gpio << GPIO_FUNC0_IN_SEL_S);

  if (inv)
    {
      regval |= GPIO_FUNC0_IN_INV_SEL;
    }

  if (gpio != 0x3a)
    {
      regval |= GPIO_SIG0_IN_SEL;
    }

  putreg32(regval, regaddr);
}

/****************************************************************************
 * Name: esp32s3_gpio_matrix_out
 *
 * Description:
 *   Set signal output to gpio
 *   NOTE: one signal can output to several gpios
 *   If signal_idx == 0x100, cancel output put to the gpio
 *
 ****************************************************************************/

void esp32s3_gpio_matrix_out(uint32_t gpio, uint32_t signal_idx,
                             bool out_inv, bool oen_inv)
{
  uint32_t regaddr = GPIO_FUNC0_OUT_SEL_CFG_REG + (gpio * 4);
  uint32_t regval = signal_idx << GPIO_FUNC0_OUT_SEL_S;

  if (gpio >= ESP32S3_NGPIOS)
    {
      return;
    }

  putreg32(1ul << gpio, GPIO_ENABLE_W1TS_REG);

  if (out_inv)
    {
      regval |= GPIO_FUNC0_OUT_INV_SEL;
    }

  if (oen_inv)
    {
      regval |= GPIO_FUNC0_OEN_INV_SEL;
    }

  putreg32(regval, regaddr);
}

