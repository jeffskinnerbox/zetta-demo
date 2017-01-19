// ADAPTED FROM: https://community.apigee.com/questions/18344/how-to-create-a-mock-zettajs-driver.html

var util = require('util');
var Device = require('zetta-device');
//var Device = require('zetta').Device;

var DCMotor = module.exports = function(DCMotor) {
    this.DCMotor = DCMotor;
    this.speed = 0;
    Device.call(this);
};
util.inherits(DCMotor, Device);

DCMotor.prototype.init = function(config) {
    config
        .type('DCMotor')
        .monitor('speed')
        .state('STOPPED')
        .name(this.DCMotor)
        .when('STOPPED', {
            allow: ['RotateForwardinRPM']
        })
        .when('RotatingForward', {
            allow: ['SpeedUpinRPM', 'Stop']
        })
        .when('SpeedingUp', {
            allow: ['SpeedDowninRPM', 'Stop', 'SpeedUpinRPM']
        })
        .when('SpeedingDown', {
            allow: ['SpeedUpinRPM', 'Stop', 'SpeedDowninRPM']
        })
        .map('RotateForwardinRPM', this.RotateForwardinRPM)
        .map('SpeedUpinRPM', this.SpeedUpinRPM)
        .map('SpeedDowninRPM', this.SpeedDowninRPM)
        .map('Stop', this.Stop);
};

//----------------- Supporting Functions -----------------

DCMotor.prototype.Stop = function(cb) {
    this.state = 'STOPPED';
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
    this.state = 'RotatingForward';
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
    this.state = 'SpeedingUp';
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
    this.state = 'SpeedingDown';
    var selfd = this;
    var speedvar;
    speedvar = setInterval(function() {
        if (selfd.speed == 0) {
            this.state = 'STOPPED';
        } else {
            selfd.speed = selfd.speed - 2;
            clearInterval(speedvar);
        }
    }, 500);
    cb();
};

