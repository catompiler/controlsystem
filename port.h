#ifndef PORT_H
#define PORT_H

#if defined(PORT_DESKTOP)
#define PORT_POSIX
#elif defined(PORT_KIT_XMC45_RELAX_LITE_V1)
#define PORT_XMC4500
#elif defined(PORT_TVU_V2_0)
#define PORT_XMC4700
#else
#error Unknown port!
#endif

#endif /* PORT_H */
