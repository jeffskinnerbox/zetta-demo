
var util = require('util');
var Scout = require('zetta-scout');
//var Scout = require('zetta').Scout;

// create device objects
var led_mock = require(global.dir + '/drivers/mock-devices/mock-led.js');

// create scout object
LEDScout = module.exports = function() {
    Scout.call(this);
}
util.inherits(LEDScout, Scout);

// initialization of the scout
LEDScout.prototype.init = function(cb) {
    var self = this;
    var counter = 0;
    var counterstop = 5;

    // create the multiple leds
    setInterval(function() {
        while (counter < counterstop) {
            self.discover(led_mock, 'led' + counter);
            counter++;
        }
    }, 1000);

    cb();
}
