#ifndef BSP_INCLUDED_H
#define BSP_INCLUDED_H

#include <stdint.h>

extern volatile unsigned int pico_ms_tick;

void BSP_Init(void);
void BSP_SysTick_Hook(void);
void BSP_SysTick_RTOS_Hook(void);
void BSP_Reset(void);

#endif /* BSP_INCLUDED_H */
