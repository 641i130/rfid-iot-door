# rfid-iot-door
An Arduino ESP8266 RFID door-relay authentication system with a logging back end.

#### This is open source!
I want people to be able to contribute to this project if you have any ideas. Please feel free to fork as well!

## Features
- Google Sheets Integration with Real-Time logging using IFTTT
- Long range (Range of wifi and connection to the arduino board)
- Secure: Exponetial bruteforce mitigation, Arduino board is in-accessable from the RFID reader (about 10 feet of distance between the circuit boards)
- Cheap: Only costs around $50 for the entire build rather than hundreds of $ for a 'professional installation'

## Parts/Skills Needed : (Price)
- [Adafruit ESP8266](https://www.adafruit.com/product/2821) : $20 (+ or - $5)
- [RFID Reader](https://www.amazon.com/SunFounder-Mifare-Reader-Arduino-Raspberry/dp/B07KGBJ9VG/) : $7 or cheaper
- Soldering station / skills : (Can be used at local maker space or university; if not, buy one that isn't like $40 ($80+ range is good), it'll make your life easier)
- Cable (For distancing the card reader from the board for maximum security; Cat 5e works very well) : (You probably have it laying around and if not you could find some at a local electronics recycling center)
- [5v Relay Module](https://www.microcenter.com/product/617949/inland-single-5v-relay-module-for-arduino) : $2 - $3
- [PCB Boards](https://www.amazon.com/ELEGOO-Prototype-Soldering-Compatible-Arduino/dp/B072Z7Y19F) : $10 or less (OR you can order the pcb file with a gerber file; more details below)*
- [Spare RFID Cards / Rings](https://www.amazon.com/ETEKJOY-13-56MHz-Proximity-Electronic-Compatible/dp/B0897KHNHV) : $20 for 100 (or less)
- Time, Patience and self love and a good soldering iron vent system! You don't want solder poisoning do you?!

* This one might work if you don't live by a microcenter [Relay](https://www.amazon.com/CHENBO-Channel-Module-Shield-Arduino/dp/B07874KSLY)

### Overall Cost: ~ $60 or less (depending on the quality of parts you want)

## Build Guide:

1. First gather all the parts and make sure you have about an hour of time to assemble/solder everything.

2. 
