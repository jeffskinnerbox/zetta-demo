
var zetta = require('zetta');

var led_mock = require("./drivers/mock-devices/mock-led.js");
var outlet_mock = require("./drivers/mock-devices/mock-outlet.js");
var dcmotor_mock = require('./drivers/mock-devices/mock-dcmotor.js');
var photocell_mock = require('./drivers/mock-devices/mock-photocell.js');

zetta()
    .name('zetta-server')
    .use(led_mock)
    .use(outlet_mock)
    .use(dcmotor_mock)
    .use(photocell_mock)
    .listen(1337, function(){
        console.log('Zetta Server is running at http://127.0.0.1:1337');
        console.log('Zetta Browser at http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:1337');
        console.log('Start Node-RED with "node-red --usrDir ~/src/zetta-demo/.node-red"');
        console.log('Node-RED Browser at http://127.0.0.1:1880');
    }
);
