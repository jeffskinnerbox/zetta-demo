// ADAPTED FROM: https://github.com/zettajs/zetta-mock-led

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var Dev = module.exports = function(n) {
    Device.call(this);
    this.asignedname = n;
}
util.inherits(Dev, Device);

// establishment of device state machine and initialization
Dev.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name(this.asignedname)
        .type('led')
        .state('off')

        // define the transitions allowed by the state machine
        .when('on', { allow: ['turn-off', 'strobe', 'toggle'] })
        .when('off', { allow: ['turn-on', 'strobe', 'toggle'] })
        .when('strobe', { allow: ['turn-on', 'turn-off'] })

        // map the state machine transitions to methods
        .map('turn-on', this.turnOn)
        .map('turn-off', this.turnOff)
        .map('strobe', this.strobe, [{name:'cycles', type:'number'}])
        .map('toggle', this.toggle);

        // stream data out of Zetta server, not the devices
        //.stream('stream-numbers', this.streamNumbers);
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

Dev.prototype.turnOff = function(cb) {
    this.state = 'off';
    cb();
}

Dev.prototype.turnOn = function(cb) {
    this.state = 'on';
    cb();
}

Dev.prototype.toggle = function(cb) {
    if (this.state === 'on') {
        this.call('turn-off', cb);
    } else {
        this.call('turn-on', cb);
    }
}

// ************ not working right ********************
Dev.prototype.strobe = function(cycles, cb) {
    var self = this;
    var counter = 0;
    var orginal = this.state;
    setInterval(function() {
        if (counter < cycles) {
            if (self.state === 'off') {
//                self.state = 'on';
                self.call('turn-off', cb);
            } else {
//                self.state = 'off';
                self.call('turn-off', cb);
            }
        }
        counter += 1;
    }, 1000);
//    this.state = orginal;
    if (orginal === 'off') {
        self.call('turn-off', cb);
    } else {
        self.call('turn-on', cb);
    }
    cb();
}

//Dev.prototype.streamNumbers = function(stream, cb) {
//  setInterval(function(){
//    stream.write(Math.random());
//  }, 3000);
//  cb();
//}
