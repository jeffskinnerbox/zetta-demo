
var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var NeoPixel = module.exports = function() {
    Device.call(this);
};
util.inherits(NeoPixel, Device);

// establishment of device state machine and initialization
NeoPixel.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name('jeffs-neopixel')
        .type('neopixal')
        .state('off')

        // define the transitions allowed by the state machine
        .when('on', { allow: ['turn-off', 'set-color'] })
        .when('off', { allow: ['turn-on'] })

        // map the state machine transitions to methods
        .map('turn-on', this.turnOn)
        .map('turn-off', this.turnOff)
        .map('set-color', this.setColor, [{text:'hex'}]);

    this.info('j5-neopixel.js initialized');
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

NeoPixel.prototype.turnOff = function(cb) {
    this.state = 'off';
    this.color = '#000000';
    this.strip.clear();              // turns entire strip off
    this.strip.show();
    cb();
};

NeoPixel.prototype.turnOn = function(cb) {
    this.state = 'on';
    this.color = '#FFFFFF';
    this.strip.color('#FFFFFF');      // turns entire strip red using a hex colour
    this.strip.show();
    cb();
};

NeoPixel.prototype.setColor = function(hex, cb) {
    this.color = hex;
    this.strip.color(hex);
    this.strip.show();
    cb();
};
