#include "pico_device.h"
#include "pico_dev_tap.h"

struct pico_device *pico_eth_create(const char *name, const uint8_t *mac)
{
    (void)mac;
    (void)name;
    return (struct pico_device *)pico_tap_create("tap0");
}

void pico_eth_destroy(struct pico_device *dev)
{
    pico_tap_destroy(dev);
}

