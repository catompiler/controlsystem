#ifndef PORTDEFS_H
#define PORTDEFS_H

#include "port.h"


#if defined(PORT_POSIX)
#define CCM_CODE
#define CCM_DATA
#define CCM_BSS
#define COMM_DATA
#define COMM_BSS
#elif defined(PORT_XMC4500)
#define CCM_CODE __attribute__((section(".ram_code"), noinline))
#define CCM_DATA __attribute__((section("PSRAM_DATA")))
#define CCM_BSS __attribute__((section("PSRAM_BSS")))
#define COMM_DATA __attribute__((section("DSRAM2_DATA")))
#define COMM_BSS __attribute__((section("DSRAM2_BSS")))
#elif defined(PORT_XMC4700)
#define CCM_CODE __attribute__((section(".ram_code"), noinline))
#define CCM_DATA __attribute__((section(".data")))
#define CCM_BSS __attribute__((section(".bss")))
#define COMM_DATA
#define COMM_BSS
#endif


#endif /* PORTDEFS_H */
