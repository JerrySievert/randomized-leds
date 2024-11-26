# Randomized LEDs

A very simple Arduino project for setting and changing LED light strings for a specific pallet. Hardware
used was a WS2811 LED strip, RP2040 micro-controller, and a connector cable.

I built this for [Level Beer](https://www.levelbeer.com) to match their brewery colors in use for their
large light-up signage.

I used some parts I had sitting around, but if you want to create your own (links provided as an example):

- [WS2811 LED strip](https://www.amazon.com/ALITOVE-Addressable-Digital-Diffused-Waterproof/dp/B06XD72LYM/)
- [Seeed Xiao RP2040](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html)
- [3-pin JST connector](https://www.amazon.com/dp/B071H5XCN5)

The Seeed Xiao has a pretty decent DC-DC converter, so I was able to pull power from the 5v pin to power
the LED strip, and power the whole thing via the Seeed's USB-C adapter.

The heavy lifting for the LEDs was done using [FastLED](http://fastled.io).
