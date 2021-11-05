s# noise-monitoring-arduino

## Setting up Virtual Environment

This project requires python 3.10. Assume you have `virtualenv` installed. (If not run `pip install virtualenv`).

1. Setup virtual environment at root of project. Run `virtualenv -p python3.10 venv`
    * This will create a directory `venv` in your root directory. This directory is in the .gitignore and should not be committed

## Setting up the project

Anytime you work on this project, you should activate the virtual environment.

1. source `venv/bin/activate`.
  * You should see `(venv)` at the beginning of your console prompt. This means you're in the environment.

2. Run `pip install -r requirements.txt`
  * This will install all of the projects dependencies inside the virtual environment.

## Running the Project



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


