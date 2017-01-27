// for accepting input from a user

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var Screen = module.exports = function(n) {
    Device.call(this);
};
util.inherits(Screen, Device);

// establishment of device state machine and initialization
Screen.prototype.init = function(config) {
    this.written = '';
    config
        // setup the device's initial state
        .name('my screen')
        .type('screen')
        .state('ready')

        // define the transitions allowed by the state machine
        .when('ready', { allow: ['write'] })

        // map the state machine transitions to methods
        .map('write', this.write, [{type:'text', name:'texttowrite'}])

        // define parameters that can be monitored in real-time
        .monitor('written');
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

Screen.prototype.write = function(texttowrite, cb) {
    this.written = texttowrite;
    cb();
};

