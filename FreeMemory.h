#ifndef FREE_MEMORY_H
#define FREE_MEMORY_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

/** Return the number of bytes currently free in RAM. */
int FreeRam(void);

#endif
