// ADOPTED FROM: https://github.com/ajfisher/node-pixel/blob/master/docs/johnnyfive.md
//               https://www.youtube.com/watch?v=CIGnQUSWjm4
//
//Prototyping a Smart Device w/ Arduino & Node.js using Johnny-Five
//   https://www.pubnub.com/blog/2016-05-25-howcreate-a-smart-device-with-arduino-and-node-js-using-johnny-five/

// read the directory to be used from the environment or package.json
const DIR = process.env.DIR || global.dir;

var util = require('util');
var Scout = require('zetta-scout');
//var Scout = require('zetta').Scout;
var five = require('johnny-five');
var Drive = require(DIR + '/drivers/real-devices/j5-neopixel.js');
var Board = five.Board();
var pixel = require('node-pixel');

var opts = {
    repl: false,
    debug: false
};

// create scout object
JohnnyFiveBoardScout = module.exports = function(strip) {
    Scout.call(this);
    this.strip = strip;
};
util.inherits(JohnnyFiveBoardScout, Scout);
this.server.info('scout-neopixel.js constructed');

// initialization of the scout
JohnnyFiveBoardScout.prototype.init = function(next) {
    var self = this;
    //var this.board = new five.Board(opts);
    var board = new Board(opts);
    var strip = null;

    //this.board.on('ready', function() {
    board.on('ready', function() {
        self.strip = new pixel.Strip({
            board: this,
            controller: 'FIRMATA',
            data: 6,
            lenght: 8,
            color_order: pixel.COLOR_ORDER.RGB,
        });

        //this.strip.on('ready', function() {
        strip.on('ready', function() {
            self.discover(Driver, strip);
            console.log("Strip ready, let's go");
        });

    this.server.info('scout-neopixel initialized');
    next();
    });
};

