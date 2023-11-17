# Tally System for ATEM Switcher using ESP-Now

Commercial tally systems that signal whether a camera is currently live or in preview are quite expensive. This project enables you to create such a system for a fraction of the cost.

We use a WT32-ETH01 module as a Controller and ESP8266 Mini D1 modules as Clients. The Controller is connected via LAN and grabs the ATEM updates from the network. Updates are then sent to the client over ESP-Now which is a low-power wireless network protocol by espressif.

## Get started
The code is written for [platformio](https://platformio.org/). The easiest way is to use VS Code and install the platformio extension. Then you can simply open the project folder and compile and upload the code to the devices.

### Hardware
All you need to do is solder the three LEDs and the button to the ESP8266 Mini D1 like this:

<div style="display: flex; gap: 15px">
    <img src="./assets/tally_receiver_pinout.png" alt="Image Description" style="width: 50%;">
    <img src="./assets/tally_server_pinout.png" alt="Second Image" style="width: 50%;">
</div>


For the Controller you need to add a USB to serial converter to the WT32-ETH01 module. This is needed to flash and power the module. You can use a CP2102 or a CH340G converter. The pinout is as follows:

TODO: Add image

### Configuration
The Controller can be connected to your network via LAN. It will automatically acquire an IP address via DHCP. You can either reach the control interface via the IP address or by using the DNS name [WT32-ETH01.local](http://WT32-ETH01.local). On the control interface, you can configure the IP addresses of the ATEM switcher. If the Controller is successfully connected to the ATEM switcher the red LED will turn off.

The Clients need to be configured with the IP address of the Controller. You can do this by pressing the button on the Client while you plug in the power cable and wait until the blue LED stops blinking. You can then release the button and connect to the Wifi of the Client. A website should open where you can change the ID of the client.

## Used libraries
Many thanks to the authors of the following libraries:
- [ESPAsyncWebServer](https://github.com/khoih-prog/WebServer_WT32_ETH01)
- [ATEMbase, ATEMstd, SkaarhojPgmspace](https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering/tree/master) (adjusted to work with ESP32-ETH01)