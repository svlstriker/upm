/*
 * Authors:
 *          Jon Trulson <jtrulson@ics.com>
 * Contributions: Rex Tsai <rex.cc.tsai@gmail.com>
 *                Abhishek Malik <abhishek.malik@intel.com>
 * Copyright (c) 2017 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef UPM_UTILITIES_H_
#define UPM_UTILITIES_H_

#include <upm_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(UPM_PLATFORM_LINUX)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timespec upm_clock_t;
#endif /* UPM_PLATFORM_LINUX */

#if defined(UPM_PLATFORM_ZEPHYR)
#include <zephyr.h>
#include <device.h>
#include <sys_clock.h>
#include <version.h>
#include <kernel_version.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

typedef uint64_t upm_clock_t;

#endif /* UPM_PLATFORM_ZEPHYR */

/**
 * Delay for a number of seconds (s)
 *
 * @param time The number of seconds to delay for
 */
void upm_delay(uint32_t time);

/**
 * Delay for a number of milliseconds (ms)
 *
 * @param time The number of milliseconds to delay for
 */
void upm_delay_ms(uint32_t time);

/**
 * Delay for a number of microseconds (us)
 *
 * @param time The number of microseconds to delay for
 */
void upm_delay_us(uint32_t time);

/**
 * Delay for a number of nanoseconds (ns)
 *
 * Note, sub-microsecond accurate time on *nix is generally not available OOB
 * and high resolution times are also not supported on all HW architectures.
 *
 * @param time The number of nanoseconds to delay for
 */
void upm_delay_ns(uint64_t time);

/**
 * Initialize a clock.  This can be used with upm_elapsed_ms() and
 * upm_elapsed_us() for measuring a duration.
 *
 * For *nix operating systems, this initializes a MONOTONIC clock.
 *
 * Example:
 *      upm_clock_t start = upm_clock_init();
 *          ... do stuff ...
 *      uint64_t delta_ns = upm_elapsed_us(&start);
 *
 * @return The upm_clock_t initialized to the current time
 */
upm_clock_t upm_clock_init(void);

/**
 * Return the elapsed time in milliseconds since upm_init_clock() was
 * last called.
 *
 * @param clock A upm_clock_t initialized by upm_init_clock()
 * @return the number of milliseconds elapsed since upm_init_clock()
 * was called on the clock parameter.
 */
uint64_t upm_elapsed_ms(const upm_clock_t *clock);

/**
 * Return the elapsed time in microseconds since upm_init_clock() was
 * last called.
 *
 * @param clock A upm_clock_t initialized by upm_init_clock()
 * @return the number of microseconds elapsed since upm_init_clock()
 * was called on the clock parameter.
 */
uint64_t upm_elapsed_us(const upm_clock_t *clock);

/**
 * Return the elapsed time in nanoseconds since upm_init_clock() was
 * last called.
 *
 * Note, sub-microsecond accurate time on *nix is generally not available OOB
 * and high resolution times are also not supported on all HW architectures.
 *
 * @param clock A upm_clock_t initialized by upm_init_clock()
 * @return the number of nanoseconds elapsed since upm_init_clock()
 * was called on the clock parameter.
 */
uint64_t upm_elapsed_ns(const upm_clock_t *clock);

/**
 * Return the AQI (based on EPA standards) using the ugm3 value
 * calculated by the sensor module.
 *
 * @param ugm3 micrograms per cubic meter
 * @return calculated AQI
 */
int upm_ugm3_to_aqi (double ugm3);

#ifdef __cplusplus
}
#endif

#endif /* UPM_UTILITIES_H_ */