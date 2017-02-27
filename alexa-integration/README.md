# Sonos integration with Alexa Echo

------

## Introduction

The following steps show how we integrated the Alexa Echo Dot with the Sonos (based on guidelines from the [echo-sonos](https://github.com/rgraciano/echo-sonos/blob/master/lambda/src/sonosProxy/sonosProxyFactory.js) repository by rgraciano).  

### Step 1: Get node-sonos-http-api Running on a Local Server

This step is assuming that you already got node.js and npm installed on your pc or device. 

Go to https://github.com/jishi/node-sonos-http-api. In the folder where you want run your server from do the following in the terminal (as explained by jishi):

`$ git clone https://github.com/jishi/node-sonos-http-api.git`

`$ cd node-sonos-http-api`

`$ npm install --production`

`$ npm start # or: node server.js`

Your server should now start running on http://localhost:5005.

You can try if it is working by putting the following links (which the name of the ROOM of your sonos instead of the "salon") in your browser:

 `http://localhost:5005/salon/play	`

`http://localhost:5005/salon/volume/50`

`http://localhost:5005/salon/next`

`http://localhost:5005/salon/pause`

**Tip**: in case you are running the sonos http server on a seperate device (in my case an orange pi), you can make it keep running even if you close the ssh terminal, with a npm package called [forever](https://github.com/foreverjs/forever). 

you can install it with the following command:

`$ [sudo] npm install forever -g`

Go to the folder where you installed the sonos server module

`$ cd node-sonos-http-api`

and type:

`$ forever start server.js`


### Step 2: Making Your Server Accessible for Alexa

For this step I am following the steps by Graciano in his [sonos-echo](https://github.com/rgraciano/echo-sonos) repository. 

1. I made an account on [ydsn.io](https://ydns.io/)

2. I confirmed the e-mail and [added a host](https://ydns.io/hosts/add) (the correct ip address for my internet was already there by default - great!).

3. Luckily, for FRITZ!box the steps of setting up a DynamicDSN were nicely documented on the ydsn.io website [here](https://ydns.io/knowledge-base/updating-domain-with-fritzbox). I just followed the steps.

4. Now - to set up the [Port Forwarding](https://en.avm.de/service/fritzbox/fritzbox-7390/knowledge-base/publication/show/893_Setting-up-static-port-sharing/), I went to "Portfreigaben" in the fritz.box > Internet > freigaben section and clicked `neue portfreigaben`.  And then I did the following:

   <Add screenshots here>

5. Now the sonos should be controlable even from outside the local network! I tested it by visiting the link in the browser from my phone data network (not via the wifi):

   `<THE_DOMAIN_NAME_I_JUST_MADE>/salon/next`

   If it returns `{"status"}:{"success"}` then you know you did it right!
   ​

### Step 3: Get Your Alexa Skill Running

TO DO: add steps here.















