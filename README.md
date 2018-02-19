# ESP8266 WiFi Setup configuration portal library

This library allows you to create a captive portal to configure ESP8266 chip with WiFi credentials to connect to the WiFi in station mode.

- Library starts a WiFi in AP mode and setup a webserver and a DNS server.
- This lib allows you to pass an image which is shown in the header of the config portal webpages.
- The lib tries to connect to a preconfigured WiFi on initializtion if WiFi creadetials were configured earlier on same chip.
