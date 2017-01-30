
// make global the working directory and port used by zetta server
global.port = require('./package.json').config.port;
global.dir = require('./package.json').config.dir;

// read the port and directory to be used from the environment or package.json
var HOSTNAME = require('./package.json').config.hostname || '127.0.0.1';
var PORT = process.env.PORT || global.port;
var DIR = process.env.DIR || global.dir;
var CLOUD = process.env.cloud || 'zetta-jeffskinnerbox.herokuapp.com';

// create zetta server object
var zetta = require('zetta');

// create mock device driver objects
var led_mock = require(DIR + '/scouts/scout-mock-led.js');
//var neopixel_mock = require(DIR + '/drivers/mock-devices/mock-neopixel.js');
var outlet_mock = require(DIR + '/drivers/mock-devices/mock-outlet.js');
var dcmotor_mock = require(DIR +'/drivers/mock-devices/mock-dcmotor.js');
var photocell_mock = require(DIR +'/drivers/mock-devices/mock-photocell.js');
var screen_mock = require(DIR +'/drivers/mock-devices/mock-screen.js');
var camera_mock = require(DIR +'/drivers/mock-devices/mock-camera.js');

// create device driver objects
//var neopixel = require(DIR + '/scouts/scout-j5-neopixel.js');

// apps to support device interaction
var app = require(DIR + '/apps/sync-mock-led.js');

zetta()
    .name('zetta-demo')                         // start zetta server and give it human readable name
//    .silent()                                   // suppress all logging messages
    .link('http://' + CLOUD)                    // link to zetta server in cloud
    .use(app)                                   // loads zetta app modules for interactions between devices
    .use(led_mock)
//    .use(neopixel_mock)
//    .use(neopixel)
    .use(camera_mock, 'http://www.zettaapi.org/public/demo/detroit.jpg')
    .use(screen_mock)
    .use(outlet_mock)
    .use(dcmotor_mock)
    .use(photocell_mock)
    .listen(PORT, function(err) {
        console.log('Your working directory is ' + DIR);
        console.log('Zetta Server is running at http://' + HOSTNAME + ':' + PORT);
        console.log('Use Zetta Browser http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:' + PORT);
        console.log('Zetta Cloud Server is running at http://hello-zetta.herokuapp.com/servers/zetta-demo');
        console.log('Use Zetta Browser http://browser.zettajs.io/#/overview?url=http:%2F%2F' + CLOUD);
        console.log('You can view camera at ????');
        console.log('Start Node-RED with "node-red --port 1880 --usrDir ' + DIR + '/.node-red"');
        console.log('Node-RED Browser is at http://127.0.0.1:1880');
        if (err) {
            console.error(err);
            process.exit(1);
        }
    });
