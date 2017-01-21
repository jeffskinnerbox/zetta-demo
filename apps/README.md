# Zetta Apps Module
Zetta can make devices locally interact with each other using simple javascript.
An app in Zetta is just a local orchestration between devices based on state or sensor readings.
It does this interaction using custom JavaScript code that you implement to query for devices
and wire up interactions between them.
Apps are stateless and run in the context of the Zetta server.
Unlike Scouts and Devices, which are JavaScript objects,
apps are basic Node.js modules.

# References
* [Zetta Wiki: Apps](https://github.com/zettajs/zetta/wiki/Apps)
