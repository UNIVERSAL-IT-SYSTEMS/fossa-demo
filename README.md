# fossa-demo
RESTful server demo using Fossa library + picoTCP + picotcp-bsd

NOTE: This demo runs picoTCP and the complete application as a "Sandbox" ELF application inside a Linux application.
It will use the TAP device driver to create a virtual networking device, which you should assign an IP address.
this was done because demonstrating the code this way is very easy, and allows anyone to evaluate it, without any specific hardware.
This code can very well run on an actual embedded target, using the exact same code as demonstrated here.
This very code has been run on NXP LPC, ST Micro STM32Fxxx, and TI Stellaris microcontrollers already.


To build:
```
$ git clone git@github.com:tass-belgium/fossa-demo.git
$ cd fossa-demo
$ git submodule init
$ git submodule update
$ make
```

To run the sandbox application:
```
$ sudo ./out/image.elf
```
This needs to run as root, because it will create a TAP device.
It will be configured with the 192.168.2.150/24 IP.
The other end of the TAP (Linux side) will have to be configured in the same subnet.
One way to do this is:
```
$ sudo ifconfig tap0 192.168.2.1/24
```

Now you can check the uptime here:
```
http://192.168.2.150/api/v1/uptime
```
or try the "sum" api that will return the result in JSON:
```
http://192.168.2.150/api/v1/sum?n1=5&n2=10
```
