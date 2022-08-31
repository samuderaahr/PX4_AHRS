/****************************************************************************
 * arch/arm/src/max326xx/common/max326_clrpend.c
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

#include <arch/irq.h>

#include "nvic.h"
#include "arm_arch.h"

#include "max326_irq.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: max326_clrpend
 *
 * Description:
 *   Clear a pending interrupt at the NVIC. This does not seem to be required
 *   for most interrupts.  Don't know why...
 *
 *   This function is logically a part of max326_irq.c, but I will keep it in
 *   a separate file so that it will not increase the footprint on MAX326xx
 *   platforms that do not need this function.
 *
 ****************************************************************************/

void max326_clrpend(int irq)
{
  /* Check for external interrupt */

  if (irq >= MAX326_IRQ_EXTINT)
    {
      if (irq < (MAX326_IRQ_EXTINT + 32))
        {
          putreg32(1 << (irq - MAX326_IRQ_EXTINT), NVIC_IRQ0_31_CLRPEND);
        }
      else if (irq < MAX326_IRQ_NVECTORS)
        {
          putreg32(1 << (irq - MAX326_IRQ_EXTINT - 32),
                   NVIC_IRQ32_63_CLRPEND);
        }
    }
}