# Sensational Sonos Sensor Synchronization

## Introduction

Wouldn't it be nice to come home and have your music on automatically? And what if you could control the speaker easily, just using your voice?

With such title, you probably have big expectations! It's a relatively simple project though, and the idea was to provide good documentation so anyone with the required hardware could replicate it at home

Well, it's still a work in progress!  
But meanwhile you can see this video (*recorded after some Spanish wines*), in which we explain briefly how it works:

[![ScreenShot](http://img.youtube.com/vi/bAIFPeIl3MI/0.jpg)](https://www.youtube.com/watch?v=bAIFPeIl3MI)

This project is mainly divided in two parts:

* **The first one** consists on running a local API on a Linux-based single-board computer, and fire HTTP requests to the Sonos local API depending on the readings comming from different sensors. The speaker can then play music (or shuffle songs, or change the volume, etc.) based on these events.

* **The second** makes it possible to control the speaker using voice commands from an Amazon Echo device.

## Requirements

### First Part

To trigger actions in your Sonos speaker using data from sensors you will need:

* [Sonos](http://www.sonos.com) speaker (see the "Notes About the Requirements" below).
* A WiFi development kit (see the "Notes About the Requirements" below).
* Grove PIR sensor.
* Magnetic switch (optional).
* Orange Pi set, consisting on:
	* [Orange Pi One](http://www.orangepi.org/orangepione) single-board computer
	* 4GB SD Card (8GB is strongly recommended)
	* A decent 5V/2A USB power supply (like [this one](https://www.amazon.de/dp/B00JWXT6BK/ref=cm_sw_em_r_mt_dp_TIjTyb0T3E30H))
	* A USB to 4.0x1.7mm DC jack cable (like [this one](http://tinkersphere.com/power/1746-orange-pi-power-cable-usb.html))

A [developer account on the relayr cloud platform (free)](https://dev.relayr.io) is required to onboard the WiFi sensor node.

### Second Part

To control the Sonos speaker using your voice, you will need:

* An [Amazon Echo](http://a.co/9imYj0b) (or an [Echo Dot](http://a.co/4MYRdzt))

To create and deploy the Alexa skill, a [developer account on Amazon (free)](https://developer.amazon.com) and an [account in AWS (free but requires confirmation via credit card)](https://aws.amazon.com) are needed.

### Notes About the Requirements

This project will work great with any Sonos PLAY:1, PLAY:3 or PLAY:5. It has not been tested in other Sonos devices, but it will likely work well.

As for the single-board computer, the first version of this project has been deployed in an Orange Pi One, but it may work in other Armbian-based boards. More boards will be added soon, including the Raspberry Pi.

Regarding the WiFi development kit, almost any ESP8266-based board will do. In the first version of this project, a [WeMos D1 mini](https://www.aliexpress.com/store/product/D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/1331105_32529101036.html?spm=2114.12010108.0.0.yP8NGa) has been used due to its low price tag. The codes for the [Particle Photon](https://www.particle.io/products/hardware/photon-wifi-dev-kit) will be added in the future as well.

## Installation & Configuration

### Single-board Computer

As said, in this project we will be using a Sonos HTTP API (more info on the specific tutorials below), as well as a script to read data from the sensors.

**Select your board from the list below**, and follow the corresponding tutorial:

* [Orange Pi One](./orange-pi-setup/README.md) (it will probably work with most Armbian-based systems as well)
* [Raspberry Pi]() (**NOT AVAILABLE YET** - it will probably work with most Raspbian-based systems as well)

### Sensor Node

The next part consists on configuring the sensor node, i.e. a WiFi development kit connected to a set of sensors. In this case, we will use two: A PIR sensor, which detects presence, and a magnetic switch, which will be triggered when the door opens. This node will send the readings to the cloud, so the script running on the single-board computer can retrieve them remotely an fire HTTP requests to the Sonos speaker.

**Select your WiFi _devkit_ from the list below**, and follow the instructions:

* [WeMos D1 mini]() (**WORK IN PROGRESS**)
* [Particle Photon]() (**WORK IN PROGRESS**)

### Amazon Echo / Alexa Integration

-----WORK IN PROGRESS-----

## To Do

* Add WeMos D1 mini tutorial on the "sensor node" section.
* Add Particle Photon tutorial on the "sensor node" section.
* Add Raspberry Pi tutorial on the "single-board computer" section.
* Add Amazon Echo / Alexa integration tutorial.
* OPTIONAL: Create the project structure.
* OPTIONAL: Create the solution architecture.

## License

Copyright (C) 2017 Emelie Hofland <emelie_hofland@hotmail.com>, Jaime González-Arintero <a.lie.called.life@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

Except as contained in this notice, the name(s) of the above copyright holders shall not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization.

THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.