
// make global the working directory and port used by zetta server
global.port = require('./package.json').config.port;
global.dir = require('./package.json').config.dir;

// read the port and directory to be used from the environment or package.json
const HOSTNAME = require('./package.json').config.hostname || '127.0.0.1';
const PORT = process.env.PORT || global.port;
const DIR = process.env.DIR || global.dir;

// create zetta server object
var zetta = require('zetta');

// create mock device driver objects
var led_mock = require(DIR + '/scouts/scout-mock-led.js');
//var neopixel_mock = require(DIR + '/drivers/mock-devices/mock-neopixel.js');
var outlet_mock = require(DIR + '/drivers/mock-devices/mock-outlet.js');
var dcmotor_mock = require(DIR +'/drivers/mock-devices/mock-dcmotor.js');
var photocell_mock = require(DIR +'/drivers/mock-devices/mock-photocell.js');
var screen_mock = require(DIR +'/drivers/mock-devices/mock-screen.js');

// create device driver objects
//var neopixel = require(DIR + '/scouts/scout-j5-neopixel.js');

// apps to support device interaction
var app = require(DIR + '/apps/sync-mock-led.js');

zetta()
    .name('zetta-demo')                         // start zetta server and give it human readable name
//    .silent()                                   // suppress all logging messages
//    .logger()                                   // customer logger
    .link('http://hello-zetta.herokuapp.com/')  // link to Apigee's zetta server in cloud
    .use(app)                                   // loads zetta app modules for interactions between devices
    .use(led_mock)
//    .use(neopixel_mock)
//    .use(neopixel)
    .use(screen_mock)
    .use(outlet_mock)
    .use(dcmotor_mock)
    .use(photocell_mock)
   .listen(PORT, function(err) {
        console.log('Your working directory is ' + DIR);
        console.log('Zetta Server is running at http://' + HOSTNAME + ':' + PORT);
        console.log('Browser for Local Zetta server at http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:' + PORT);
        console.log('Zetta Cloud Server is running at http://hello-zetta.herokuapp.com/servers/zetta-demo');
        console.log('Browser for cloud Zetta server at http://browser.zettajs.io/#/overview?url=http:%2F%2Fhello-zetta.herokuapp.com');
        console.log('Start Node-RED with "node-red --port 1880 --usrDir ' + DIR + '/.node-red"');
        console.log('Node-RED Browser is at http://127.0.0.1:1880');
        if(err) {
            console.error(err);
            process.exit(1);
        }
    });
