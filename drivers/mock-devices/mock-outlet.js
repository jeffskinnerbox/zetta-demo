
var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var Dev = module.exports = function() {
    Device.call(this);
    this.voltage = 0;
    this.current = 0;
};
util.inherits(Dev, Device);

// establishment of device state machine and initialization
Dev.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name('Mock Smart Outlet Device')
        .type('outlet')
        .state('on')

        // define parameters that can be monitored in real-time
        .monitor('voltage')
        .monitor('current')

        // define the transitions allowed by the state machine
        .when('on', { allow: ['turn-off'] })
        .when('off', { allow: ['turn-on'] })

        // map the state machine transitions to methods
        .map('turn-on', this.turnOn)
        .map('turn-off', this.turnOff);

    // used to simulate voltage and current data
    var self = this;
    var counterV = 0;
    var counterI = 0;
    setInterval(function() {
        self.voltage = 120 + 2.5 * Math.sin(counterV*(Math.PI/180));
        counterV += 15;
    }, 100);
    setInterval(function() {
        if (self.state ==='on') {
            if (Math.random() > 0.65) {
                self.current = 3.5 + Math.sin(counterI*(Math.PI/180));
            } else {
                self.current = 0;
                counterI += 15;
            }
            counterI += 15;
        } else {
            self.current = 0;
        }
    }, 1000);

    this.info('mock-outlet.js initialized');
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

Dev.prototype.turnOff = function(cb) {
    this.state = 'off';
    cb();
};

Dev.prototype.turnOn = function(cb) {
    this.state = 'on';
    cb();
};

