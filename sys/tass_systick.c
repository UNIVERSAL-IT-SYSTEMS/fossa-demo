volatile unsigned int pico_ms_tick = 0u; /* Architecture dependant clock! */

void __attribute__((weak)) BSP_SysTick_Hook(void)
{
}

void __attribute__((weak)) BSP_SysTick_RTOS_Hook(void)
{
}


void SysTick_Handler(void)
{
    pico_ms_tick++;
    BSP_SysTick_Hook();
    BSP_SysTick_RTOS_Hook();
}

