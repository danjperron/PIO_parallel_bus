
#include <stdio.h>
#include "pico/stdlib.h"
#include <tusb.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

// Our assembled program:
#include "p_bus.pio.h"

// parallel bus cpu  simulation
// base0..7  data bus     => 8 bit data
// base8..15 address bus  => 8 bit address
// base16,17,18  CS,RD,WR
// then we need 19 pins PIO

#define FREQUENCY 125000000.0
#define P_BUS_PIO_BASE 2

PIO pio = pio0;
uint sm;


uint32_t  p_bus_write(unsigned char Address, unsigned char Data)
{
  p_bus_set(pio,sm,1,((uint32_t)Address <<8)| ((uint32_t)Data));
}

uint32_t p_bus_read(unsigned char Address)
{
  return  p_bus_set(pio,sm,0,(uint32_t)Address <<8) & 0xff;
}


int main() {
    int loop;
    stdio_init_all();

    // Choose which PIO instance to use (there are two instances)
    unsigned char byteRead,byteWritten;
    uint32_t uRead;
    uint offset=0;

    // wait until usb is ready
    while(!tud_cdc_connected()) sleep_ms(100);

    sleep_ms(1000);
    printf("__init__\n");
    sleep_ms(1000);


    // set proper GPIO
    //  PIO_BASE 0 to 7 INPUT no pull up
    //  PIO_BASE 8 to 15 and 16 to 18 OUTPUT
    for(loop =0 ;loop <8;loop++)
     {
      gpio_init(P_BUS_PIO_BASE+loop);
      gpio_disable_pulls(P_BUS_PIO_BASE+loop);
     }
    for(loop = 8; loop < 19 ; loop++)
     {
      gpio_init(P_BUS_PIO_BASE+loop);
      gpio_disable_pulls(P_BUS_PIO_BASE+loop);
      gpio_set_dir(P_BUS_PIO_BASE+loop,1);
      gpio_put(P_BUS_PIO_BASE+loop,1);
     }

    // set PIO
    // 	pio to handle data read  GPIO2..9  CS,RD,WR GPIO 20..22
    offset = pio_add_program(pio, &p_bus_program);
    sm = pio_claim_unused_sm(pio, true);
    p_bus_init(pio,sm,offset,P_BUS_PIO_BASE,FREQUENCY);

    loop = 0;
    while (true) {
        loop++;
        loop %=8;

        uRead = p_bus_read(1<<loop);
        p_bus_write(1<<loop,1<<loop);
    }
}


