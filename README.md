
<div align="center">
<img src="https://python-deprecated.readthedocs.io/en/latest/_images/logo-full.png" title="Deprecated is increasingly used as a technical term meaning 'to recommend against using something on the grounds that it is obsolete', or 'to declare some technological feature or function to be obsolescent'.  The earliest meaning of deprecate was 'to pray against, as an evil,' and soon after this first meaning it took on the additional sense 'to express disapproval of.' Meanwhile, depreciate, the closely related word with which it is often confused, means 'to lower in value.'" align="center">
</div>

----------

# Glossary
* Actuator: a type of motor that is responsible for moving or controlling a mechanism or system.
* Sensor: a device that detects events or changes in quantities and provides a corresponding output.
  Device: a actuator or sensor or the combination of the two
* Driver: the Zetta representation of a device. It includes a Scout for finding the physical device, and a driver for interacting with the device via javascript.
* Scout: responsible for searching for a physical device, and alerting Zetta to it's existence.


* [sudo npm i -g eslint](http://eslint.org/docs/user-guide/command-line-interface)
* [Self-Documented package.json](http://blainsmith.com/articles/self-documented-package.json)
* [Streamline JavaScript Development with ESLint](https://nodesource.com/blog/streamline-javascript-development-with-eslint/)


# Zetta Training Materials
The are several sources to get comfortable with Zetta.

* Documentation
    * [Zetta website](http://www.zettajs.org/)
    * [Zetta's Wiki - Introduction to Zetta](https://github.com/zettajs/zetta/wiki)
    * [Zetta API: A REST API specification for the Internet of Things](http://www.zettaapi.org/)
    * [Zetta Projects Directory](http://www.zettajs.org/projects/)
    * [Original Zetta Reference Docs](http://www.zettajs.org/reference/)
* Code Examples
    * [Zetta Tutorials](https://github.com/zettajs/zetta-tutorials)
    * [Zetta Coding Examples](https://github.com/kevinswiber?tab=repositories)
    * [Building a Zetta Security System](https://github.com/zettajs/zetta-security-system)
    * A starter Zetta phone app for [Android](https://github.com/zettaapi/zetta-starter-app-android)
and [iOS](https://github.com/zettaios/zetta)
* Slideware
    * [Zetta: An API First Platform](http://www.slideshare.net/apijp/zetta-an-api-first-platform)
    * [Zetta js Hands on IoT](http://www.slideshare.net/anilsagar/zetta-js-hands-on-iot?qid=3863ecca-1807-4cb0-95f3-692b7653d168&v=&b=&from_search=2)
    * [Designing an API for the Internet of Things](http://www.slideshare.net/kswiber/designing-an-api-for-the-internet-of-things?qid=3863ecca-1807-4cb0-95f3-692b7653d168&v=&b=&from_search=39)
* Videos
    * [Building with Zetta Series](https://github.com/zettajs/zetta/wiki/Zetta-Videos):
[Part 1](https://www.youtube.com/watch?v=zXaM7eO_EoQ),
[Part 2](https://www.youtube.com/watch?v=WYbvt8ODACY),
[Part 3](https://www.youtube.com/watch?v=CIGnQUSWjm4).

# Running the Zetta Demo
Zetta Browser - http://browser.zettajs.io   or   http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:1337
or

```bash
# change directory to run the demo
cd ~/src/zetta-demo

# start the zetta server
node index.js

# start node-red
node-red --usrDir ~/src/zetta-demo/.node-red
```

# Cloud Based Zetta Server
Located on Heroku

* URL: https://zetta-jeffskinnerbox.herokuapp.com/
* Source Code: https://github.com/zettajs/zetta-cloud-sample
* To Manage Server: https://dashboard.heroku.com/apps/zetta-jeffskinnerbox

# Query Zetta Server
Query the Zetta server for metadata

```bash
# query the root API of the zetta server
curl -sS http://localhost:1337/servers/zetta-demo | jq -C '.'

# query for device information for device type led
curl -sS http://localhost:1337/servers/zetta-demo/meta/led | jq -C '.'
```

Using POST API, change the state of the LED device

```bash
# turn on the led
curl -sS -i -X POST http://zetta-jeffskinnerbox.herokuapp.comevices/a6bdf7cc-d9e6-434a-a154-bb64e90302a1 -d 'action=turn-on'

# make the led strobe 10 cycles
curl -sS -i -X POST http://localhost:1337/servers/zetta-demo/devices/32c49e8e-211e-4299-a720-b1799da44961 -d 'action=strobe&cycles=10

# toggle the led on or off
curl -sS -i -X POST http://localhost:1337/servers/zetta-demo/devices/32c49e8e-211e-4299-a720-b1799da44961 -d 'action=toggle'
```

Print out Zetta's log data
```bash
wscat -c ws://localhost:1337/servers/zetta-demo/events?topic=logs
```

Query and stream data from the photocell

```bash
# get meta data for photocell
curl -sS http://localhost:1337/servers/zetta-demo/meta/photocell | jq -C '.'

# get photocell id
curl -sS http://localhost:1337/servers/zetta-demo?ql=where%20type%3D%22photocell%22 | jq -C '.'
curl -sS http://zetta-jeffskinnerbox.herokuapp.com/servers/zetta-demo?ql=where%20type%3D%22photocell%22 | jq -C '.'
curl -sS http://localhost:1337/servers/zetta-demo?ql=where%20type%3D%22photocell%22 | jq -C '.entities[0].properties.id'
curl -sS http://zetta-jeffskinnerbox.herokuapp.com/servers/zetta-demo?ql=where%20type%3D%22photocell%22 | jq -C '.entities[0].properties.id'

# stream photocell intensity
wscat -c ws://localhost:1337/servers/zetta-demo/events?topic=photocell%2F481edfb5-a4f1-42a0-85eb-677d42e1cf4f%2Fintensity
wscat -c ws://zetta-jeffskinnerbox.herokuapp.com/servers/zetta-demo/events?topic=photocell%2F481edfb5-a4f1-42a0-85eb-677d42e1cf4f%2Fintensity
```

# Siren API Browser
An API Browser is a web-based tool to "browse" REST APIs in a generic way,
rendering the JSON payloads nicely formated to the screen,
and turning anything that looks like a hyperlink into a hyperlink.
A Siren API Browser  does this specifically for a Siren Hypermedia API.

* Kevin Swiber's Siren Browser - https://github.com/kevinswiber/siren-api-browser
    * http://siren-api-browser.herokuapp.com/
* Applicaster's Siren Browser - https://github.com/applicaster/siren-browser
    * http://applicaster.github.io/siren-browser/#/siren-browser
* A Siren Hypermedia browser-based client - https://github.com/wurlinc/siren-browser
    * http://siren-browser.herokuapp.com/
