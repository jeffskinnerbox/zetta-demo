
// make global the working directory and port used by zetta server
global.port = require('./package.json').config.port;
global.dir = require('./package.json').config.dir;

// create zetta server object
var zetta = require('zetta');

// create device driver objects
var led_mock = require(global.dir + '/scouts/scout-mock-led.js');
var outlet_mock = require(global.dir + '/drivers/mock-devices/mock-outlet.js');
var dcmotor_mock = require(global.dir +'/drivers/mock-devices/mock-dcmotor.js');
var photocell_mock = require(global.dir +'/drivers/mock-devices/mock-photocell.js');
var screen_mock = require(global.dir +'/drivers/mock-devices/mock-screen.js');
var app = require(global.dir + '/apps/sync-mock-led.js');

zetta()
    .name('zetta-demo')
//    .link('http://external-server')
    .use(app)
    .use(led_mock)
    .use(screen_mock)
    .use(outlet_mock)
    .use(dcmotor_mock)
    .use(photocell_mock)
   .listen(global.port, function(){
        console.log('Your working directory is ' + global.dir);
        console.log('Zetta Server is running at http://127.0.0.1:' + global.port);
        console.log('Zetta Browser at http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:' + global.port);
        console.log('Start Node-RED with "node-red --port 1880 --usrDir ' + global.dir + '/.node-red"');
        console.log('Node-RED Browser is at http://127.0.0.1:1880');
    })
