# Deploying the Project in an Orange Pi One

## Introduction

The [Orange Pi One](http://www.orangepi.org/orangepione/) is an affordable open-source single-board computer based on the AllWinner H3 SoC (System on Chip), that counts with a 512MB DDR3 SDRAM. Since it's [one of the cheapest](https://www.aliexpress.com/store/product/Orange-Pi-One-ubuntu-linux-and-android-mini-PC-Beyond-and-Compatible-with-Raspberry-Pi-2/1553371_32603308880.html) *devkits* out there, it's a great option for DIY projects.

This document explains how to deploy this project, i.e. the [Sonos HTTP API](https://github.com/jishi/node-sonos-http-api) server, as well as the [Node.js scripts](./nodejs-scripts) to fire requests and control your Sonos speakers using sensor data or other events.

In this tutorial, we will be using **Armbian version 5.25**, a flavor based on Debian Jessie 3.4.113, specifically built for the Orange Pi One. Please note that this document applies to the **server version**, so **no graphical interface** will be available by default.

## Requirements

The following hardware is required:

* [Orange Pi One](https://www.aliexpress.com/store/product/Orange-Pi-One-ubuntu-linux-and-android-mini-PC-Beyond-and-Compatible-with-Raspberry-Pi-2/1553371_32603308880.html)
* 4GB SD Card (8GB is strongly recommended)
* A decent 5V/2A USB power supply
* A USB to 4.0x1.7mm DC jack cable (like [this one](http://tinkersphere.com/power/1746-orange-pi-power-cable-usb.html))

Please note that other power supplies may work, but your board could find issues booting or experience several instabilities. Also, note the USB to jack converter, which is mandatory and not easy to source.

## Installation & Configuration

### Burn Armbian in an SD Card

1. Download Armbian from the [official project source](https://www.armbian.com/orange-pi-one/). Click on the `Server` tab, and then on `Debian Jessie` to start the download.
2. Once ready, unzip the downloaded file with your program of choice (e.g. [7-Zip](http://www.7-zip.org) on Linux and Windows, or [The Unarchiver](https://itunes.apple.com/us/app/the-unarchiver/id425424353?mt=12) on OS X). For additional explanations, refer to the [official guide](https://www.armbian.com/orange-pi-one/), under the tab `Quick Start`.
3. Insert the SD card in your computer and format it with [SD Formatter](https://www.sdcard.org/downloads/formatter_4/). Make sure that you run an **Overwrite Format**, and not a Quick Format. This is a slow process and may take a few minutes.
4. Burn the image with Etcher. Simply select the file with the extension `.img` in the folder where you unzipped the contents of the downloaded package, and follow the on-screen instructions.

### Install Node.js and NPM

We've experienced issues with Node.js v7, so this tutorial will cover the installation of Node.js and NPM (Node Package Manager) v6. These instructions are based on the official Node.js documentation, that can be found [here](https://nodejs.org/en/download/package-manager/#debian-and-ubuntu-based-linux-distributions).

On the terminal login and run the following command to download the package:
`curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -`

To proceed with the installation, simply run:
`sudo apt-get install -y nodejs`

Once ready, to make sure that Node.js has been properly installed, you can check the version with the command `node -v`. Same happens with NPM; find out the current version running `npm -v`.

## Network

*Hotplug* Ethernet and DHCP will work by default, so hook the board up to one of the ports of your router, and it will get an IP address automatically.

Please note that running `ifconfig` will not work, as it does not come by default, so you will need to install it if you need it. However, if you only need basic information, like finding out the **IP address of your Orange Pi**, use the command `ip addr`.

## Shutting Down the System

If you want to turn off your Orange Pi, **do not disconnect the Orange from the power supply**, as this may corrupt the file system. Instead, to halt the board immediately, while *ssh'ing* it, run the following command:
`sudo shutdown -h now`

## To Do

* How to SSH'ing