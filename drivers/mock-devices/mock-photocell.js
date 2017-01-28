// ADAPTED FROM: https://github.com/zettajs/zetta-photocell-mock-driver

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var Dev = module.exports = function(opts) {
    Device.call(this);
    this.opts = opts || {};
    this.intensity = 0;
};
util.inherits(Dev, Device);

// establishment of device state machine and initialization
Dev.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name('Mock Photocell Device')
        .type('photocell')

        // define parameters that can be monitored in real-time
        .monitor('intensity');

    // used to simulate photocell intensity data
    var self = this;
    var counter = 0;
    setInterval(function() {
        self.intensity = 3 * (Math.sin(counter*(Math.PI/180))+1.0);
        counter += 15;
    }, 100);

    this.info('mock-photocell.js initialized');
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

