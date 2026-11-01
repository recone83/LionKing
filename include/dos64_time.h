#ifndef DOS64_TIME_H
#define DOS64_TIME_H

/* System and precise time for DOS64 programs. Header-only wrappers over DOS64_API.Time.
 * Call time_init(Api) first. Sleeping (millisecond, polls input) is Api->Sleep. */

#include "dos64_api.h"

static const DOS64_API *Dos64Time;

static inline void time_init(const DOS64_API *Api)
{
    Dos64Time = Api;
}

static inline unsigned long long time_ticks(void) { return Dos64Time->Time.Ticks(); }
static inline unsigned long long time_ticks_per_second(void) { return Dos64Time->Time.TicksPerSecond; }
static inline unsigned long long time_ns(void) { return Dos64Time->Time.Nanoseconds(); }
static inline unsigned long long time_us(void) { return Dos64Time->Time.Nanoseconds() / 1000ULL; }
static inline unsigned long long time_ms(void) { return Dos64Time->Time.Nanoseconds() / 1000000ULL; }
static inline void time_delay_ns(unsigned long long Ns) { Dos64Time->Time.DelayNanoseconds(Ns); }
static inline void time_delay_us(unsigned long long Us) { Dos64Time->Time.DelayNanoseconds(Us * 1000ULL); }
/* Real-time clock; returns 0 on success. */
static inline int time_now(DOS64_DATETIME *Time) { return Dos64Time->Time.Now(Time); }
/* Wall clock since 1970-01-01 UTC, nanosecond resolution (0 when there is no clock). */
static inline unsigned long long time_unix_ns(void) { return Dos64Time->Time.UnixNanoseconds(); }
static inline unsigned long long time_unix(void) { return Dos64Time->Time.UnixNanoseconds() / 1000000000ULL; }

#endif
