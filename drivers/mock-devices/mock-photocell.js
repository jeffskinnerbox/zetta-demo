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
    var name = this.opts.name || 'Mock Photocell Device: ' + 'MAC 123.ABC.483';

    config
        .name(name)
        .type('photocell')
        .monitor('intensity');

    // used to simulate photocell intensity data
    var self = this;
    var counter = 0;
    setInterval(function() {
//        self.intensity = 3 * ( Math.sin(degToRad(counter)) + 1.0 );
        self.intensity = 3 * (Math.sin(counter*(Math.PI/180))+1.0);
        counter += 15;
    }, 100);
};

//----------------- Supporting Functions -----------------

