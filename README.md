# noise-monitoring-arduino

The noise monitoring arduino will detect the current sound level and trigger a RGB LED based on the volume reading.

Active noise monitoring settings:
- default (switches between green, yellow, and red values in relation to current volume)*
- gradientMode (switches from green to yellow to red with a gradient as volume increases)

Color testing settings (priority order):
- rainbowGradientMode (flashes through colors with a gradient; used for debugging)*
- rainbowMode (flashes through colors; used for debugging)*

General settings:
- volumeLevelOne (minimum volume level for green to be displayed)
- volumeLevelTwo (minimum volume level for yellow to be displayed)
- volumeLevelThree (minimum volume level for red to be displayed)
- minLightFlashSec (minimum amount of time in seconds light will stay on for)
- rainbowGradientModeDelaySec (time in seconds taken between colors displayed for rainbowGradientMode)*
- rainbowModeDelaySec (time in seconds taken between colors displayed for rainbowMode)*

*grove_main only
