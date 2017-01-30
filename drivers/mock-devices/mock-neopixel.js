// ADAPTED FROM: https://github.com/zettajs/zetta-mock-led

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var Dev = module.exports = function(n) {
    Device.call(this);
    this.asignedname = n;
};
util.inherits(Dev, Device);

// establishment of device state machine and initialization
Dev.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name('Mock Neopixel')
        .type('neopixel')
        .state('off')

        // define the transitions allowed by the state machine
        .when('on', { allow: ['turn-off', 'toggle'] })
        .when('off', { allow: ['turn-on', 'toggle'] })

        // map the state machine transitions to methods
        .map('turn-on', this.turnOn)
        .map('turn-off', this.turnOff)
        .map('toggle', this.toggle)
        .map('set-color', this.setColor, [{ text: 'hex' }]);

    this.info('mock-neopixel.js initialized');

        // stream data out of Zetta server, not the devices
        //.stream('stream-numbers', this.streamNumbers);
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

Dev.prototype.toggle = function(cb) {
    if (this.state === 'on') {
        this.call('turn-off', cb);
    } else {
        this.call('turn-on', cb);
    }
};

Dev.prototype.setColor = function(hex, cb) {
    this.color = hex;
    cb();
};

