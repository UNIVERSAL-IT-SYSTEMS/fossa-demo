# fossa-demo
RESTful server demo using Fossa library + picoTCP + picotcp-bsd

To build:
```
$ git clone git@github.com:tass-belgium/fossa-demo.git
$ cd fossa-demo
$ git submodule init
$ git submodule update
$ make
```

To run:
```
$ sudo ./out/image.elf
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
