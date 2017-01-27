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

## led.js
