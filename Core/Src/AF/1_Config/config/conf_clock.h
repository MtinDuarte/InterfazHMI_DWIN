/**
 * \file
 *
 * \brief Chip-specific system clock manager configuration
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

/* ===== System Clock Source Options */
#define SYSCLK_SRC_RC16MHZ    0
#define SYSCLK_SRC_RC128KHZ   1
#define SYSCLK_SRC_TRS16MHZ   2
#define SYSCLK_SRC_RC32KHZ    3
#define SYSCLK_SRC_XOC16MHZ   4
#define SYSCLK_SRC_EXTERNAL   5

#define CONFIG_SYSCLK_PSDIV         SYSCLK_PSDIV_1

/* =====  Select connected clock source */
#define  SYSCLK_SOURCE         SYSCLK_SRC_RC16MHZ
//#define SYSCLK_SOURCE        SYSCLK_SRC_RC128KHZ
//#define SYSCLK_SOURCE        SYSCLK_SRC_TRS16MHZ
//#define SYSCLK_SOURCE        SYSCLK_SRC_XOC16MHZ

/* ===== System Clock Bus Division Options */
#define SYSCLK_PSDIV_1      0   /* !< Do not prescale */
//#define SYSCLK_PSDIV_2      1   /* !< Prescale CLKper4 by 2 */
//#define SYSCLK_PSDIV_4      2   /* !< Prescale CLKper4 by 4 */
//#define SYSCLK_PSDIV_8      3   /* !< Prescale CLKper4 by 8 */
//#define SYSCLK_PSDIV_16     4   /* !< Prescale CLKper4 by 16 */
//#define SYSCLK_PSDIV_32     5   /* !< Prescale CLKper4 by 32 */
//#define SYSCLK_PSDIV_64     6   /* !< Prescale CLKper4 by 64 */
//#define SYSCLK_PSDIV_128    7   /* !< Prescale CLKper4 by 128 */
//#define SYSCLK_PSDIV_256    8   /* !< Prescale CLKper4 by 256 */

#endif /* CONF_CLOCK_H_INCLUDED */
