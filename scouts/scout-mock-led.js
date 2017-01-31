
var util = require('util');
var Scout = require('zetta-scout');
//var Scout = require('zetta').Scout;

// read the port, directory, etc. to be used from the environment
var DIR = process.env.DIR || '/home/jeff/src/zetta-demo';

// create device objects
var led_mock = require(DIR + '/drivers/mock-devices/mock-led.js');

// create scout object
LEDScout = module.exports = function() {
    Scout.call(this);
};
util.inherits(LEDScout, Scout);

// initialization of the scout
LEDScout.prototype.init = function(next) {
    var self = this;
    var counter = 0;
    var counterstop = 5;

    // create the multiple leds
    setInterval(function() {
        while (counter < counterstop) {
            self.discover(led_mock, 'Mock LED ' + counter);
            counter++;
        }
    }, 1000);

    this.server.info('scout-mock-led initialized');
    next();
};
