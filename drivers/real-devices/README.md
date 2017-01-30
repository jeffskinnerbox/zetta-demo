# Zetta Device Class
This class models a device, or more specifically a device driver.
You define in this class device states and allowable transitions,
and map transitions to JavaScript functions that control the actual device state.

A device driver (commonly referred to simply as a driver)
is a computer program that operates or controls a particular type of device
that is attached to a computer directly or via a network.
A driver provides a software interface to hardware devices,
enabling other computer programs to access hardware functions
without needing to know precise details of the hardware being used.

The main purpose of a device driver is to provide abstraction
by acting as a translator between how a hardware device needs to communicate
and the software applications or operating systems that use it.
With a device driver in place,
a programmers can write the higher-level application code independently
of whatever specific hardware the end-user is using.

## j5-neopixel.js
[Johnny-Five][01] is a set of [Node.js][02]
(aka server side JavaScript) for Robotics & IoT experimentation.
It has a large user community and solid support.
Unfortunately, for many hardware platforms,
the JavaScript program is executed on a host machine running Node.js.
The program transmits basic I/O instructions to the board via USB serial.
So the solution requires tethering.
This tethering isn't required for BeagleBone, Galileo, Raspberry Pi,
and a few others, nearly all being Linux platforms.

The advantage of using Johnny-Five's family of microcontrollers is lost when you consider
the tether and how inexpensive a Linux platform is these days.
**Give this, I have mothballed my efforts to use Johnny-Five.**
**The j5-neopixel.js driver has never been tested.**



[01]:http://johnny-five.io/platform-support/
[02]:https://nodejs.org/en/
[03]:
[04]:
[05]:
[06]:
[07]:
[08]:
[09]:
[10]:
