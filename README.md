# PIO_parallel_bus
using PIO from raspberry pi Pico to read i.c. using address and data bus 

BASE GPIO 0..7  are data bus
BASE GPIO 8..15 are address bus
BASE GPIO 16  is CS chip select
BASE GPIO 17  is RW write 
BASE GPIO 18. is RD read

CS,RW and RD are enable low.


Two functions

unsigned char p_bus_read( unsigned char Address) -> It will return the data bye <br>
void p_bus_write(unsigned char Address, unsigned char Data) -> it will write data at the specific address


You need the pico c-sdk

To compile.

cd PIO_parallel_bus
mkdir build
cd build
cmake ..
make

just copy the p_bus.uf2 to the pico in load mode  or use the opencd method.
