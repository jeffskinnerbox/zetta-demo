// ADAPTED FROM: https://community.apigee.com/questions/18344/how-to-create-a-mock-zettajs-driver.html

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

// create device driver object
var DCMotor = module.exports = function(DCMotor) {
    this.DCMotor = DCMotor;
    this.speed = 0;
    Device.call(this);
};
util.inherits(DCMotor, Device);

// establishment of device state machine and initialization
DCMotor.prototype.init = function(config) {
    config
        // setup the device's initial state
        .name('Mock DC Motor Device')
        .type('dcmotor')
        .state('stopped')

        // define parameters that can be monitored in real-time
        .monitor('speed')

        // define the transitions allowed by the state machine
        .when('stopped', { allow: ['rotateforward'] })
        .when('rotatingforward', { allow: ['speedingup', 'stop'] })
        .when('speedingup', { allow: ['speedingdown', 'stop', 'speedingup'] })
        .when('speedingdown', { allow: ['speedingup', 'stop', 'speedingdown'] })

        // map the state machine transitions to methods
        .map('rotateforward', this.RotateForwardinRPM)
        .map('speedingup', this.SpeedUpinRPM)
        .map('speedingdown', this.SpeedDowninRPM)
        .map('stop', this.Stop);
};

//----------------- Supporting Functions -----------------
//----------------- Device Interface Code -----------------

DCMotor.prototype.Stop = function(cb) {
    this.state = 'stopped';
    var selfd = this;
    var speedvar;
    speedvar = setInterval(function() {
        if (selfd.speed == 0) {
            clearInterval(speedvar);
        } else {
            selfd.speed = selfd.speed - 2;
        }
    }, 500);
    cb();
};

DCMotor.prototype.RotateForwardinRPM = function(cb) {
    this.state = 'rotatingforward';
    var self = this;
    var speedvar;
    speedvar = setInterval(function() {
        if (self.speed == 2) {
            clearInterval(speedvar);
        } else {
            self.speed = self.speed + 2;
            clearInterval(speedvar);
        }
    }, 500);
    cb();
};

DCMotor.prototype.SpeedUpinRPM = function(cb) {
    this.state = 'speedingup';
    var self = this;
    var speedvar;
    speedvar = setInterval(function() {
        if (self.speed <= 20) {
            self.speed = self.speed + 2;
            clearInterval(speedvar);
        }
    }, 500);
    cb();
};

DCMotor.prototype.SpeedDowninRPM = function(cb) {
    this.state = 'speedingdown';
    var selfd = this;
    var speedvar;
    speedvar = setInterval(function() {
        if (selfd.speed == 0) {
            this.state = 'stopped';
        } else {
            selfd.speed = selfd.speed - 2;
            clearInterval(speedvar);
        }
    }, 500);
    cb();
};

