# Mock Device Drivers
You will find here several mock device drivers.
They consist of state machine simulating the state of a device
and/or data generators that simulate how a real device may stream data.
These mock drivers are models of real devices that could be a stand in for
or be a simulation of a real device as for testing or in of support of a demonstration.

Over time, it is expected that real devices will be purchased
and real drives will be created to support physical devices.

# mock-led.js
This driver simulates a LED light that can be turned on, off, and strobed,
where you specify the number of cycles of 1 second on / 1 second off.
You can also set and query the lights intensity and red/blue/green color settings,
The intensity can also be stream an analog value.

# mock-photocell.js
This driver simulates a light sensitive photocell.
The driver streams an analog value representing the photocell's reading of light intensity.
**what about turn on and turn off**

# mock-outlet.js
This driver simulates a smart power outlet thac can be turned on and off.
Also, the drive will stream an analog value for the voltage and current for the outlet.

# mock-dcmotor.js

