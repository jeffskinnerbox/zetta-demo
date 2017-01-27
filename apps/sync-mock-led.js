// This is a Zatta app
//
// REFERENCES
//    https://github.com/zettajs/zetta/wiki/Apps

module.exports = function(server) {
    var LED0Query = server.where({type: 'led', name: 'led0'});
    var LED1Query = server.where({type: 'led', name: 'led1'});
    var LED2Query = server.where({type: 'led', name: 'led2'});

    server.observe([LED0Query, LED1Query, LED2Query], function(led0, led1, led2) {
        console.log('sync-mock-led.js app waiting for event');
        led0.on('turn-off', function() {
            led1.call('turn-off');
            led2.call('turn-off');
        });
        led0.on('turn-on', function() {
            led1.call('turn-on');
            led2.call('turn-on');
        });
    });
};
