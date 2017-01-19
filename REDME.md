# Zetta Training Materials

* Documentation
    * [Zetta website](http://www.zettajs.org/)
    * [Zetta's Wiki - Introduction to Zetta](https://github.com/zettajs/zetta/wiki)
    * [Zetta Projects Directory](http://www.zettajs.org/projects/)
* Code Examples
    * [Zetta Tutorials](https://github.com/zettajs/zetta-tutorials)
    * [Zetta Coding Examples](https://github.com/kevinswiber?tab=repositories)
    * [Building a Zetta Security System](https://github.com/zettajs/zetta-security-system)
* Slideware
    * [Zetta: An API First Platform](http://www.slideshare.net/apijp/zetta-an-api-first-platform)
    * [Zetta js Hands on IoT](http://www.slideshare.net/anilsagar/zetta-js-hands-on-iot?qid=3863ecca-1807-4cb0-95f3-692b7653d168&v=&b=&from_search=2)
    * [Designing an API for the Internet of Things](http://www.slideshare.net/kswiber/designing-an-api-for-the-internet-of-things?qid=3863ecca-1807-4cb0-95f3-692b7653d168&v=&b=&from_search=39)
* Videos
    * Zetta training by Matthew Dobson (Software Engineer at Apigee)
"JavaScript with featured guest Zetta:
[Part 1](https://www.youtube.com/watch?v=zXaM7eO_EoQ),
[Part 2](https://www.youtube.com/watch?v=WYbvt8ODACY),
[Part 3](https://www.youtube.com/watch?v=CIGnQUSWjm4)".

# Running the Zetta Demo
Zetta Browser - http://browser.zettajs.io   or   http://browser.zettajs.io/#/overview?url=http:%2F%2F127.0.0.1:1337

```bash
# change directory to run the demo
cd ~/src/zetta-demo

# start the zetta server
node index.js

# start node-red
node-red --usrDir ~/src/zetta-demo/.node-red
```

# Query Zetta Server
```bash
# query for server information
curl -sS http://localhost:1337/servers/zetta-server | jq -C '.'

# query for device information for the LED
curl -sS http://localhost:1337/servers/zetta-server | jq -C '.'
```

```bash
curl -sS -i -X POST http://localhost:1337/servers/zetta-server/devices/32c49e8e-211e-4299-a720-b1799da44961 -d 'action=turn-on'
curl -sS -i -X POST http://localhost:1337/servers/zetta-server/devices/32c49e8e-211e-4299-a720-b1799da44961 -d 'action=strobe&cycles=10
curl -sS -i -X POST http://localhost:1337/servers/zetta-server/devices/32c49e8e-211e-4299-a720-b1799da44961 -d 'action=toggle'
```

```bash
wscat -c ws://localhost:1337/servers/zetta-server/events?topic=logs
```
