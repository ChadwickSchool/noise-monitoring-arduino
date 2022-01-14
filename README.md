# noise-monitoring-arduino

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

## Configuring the Project 

#### Configuring the ip
Anytime setting up the system you should double check that the ip your sending to is correct because it can change.

1. Find the ip of the sever you are sending to by running source `run.sh` in the command line. 

2. Check if the ip of the sever is the same ip as the Arduino code located at `sketch_nov09a/sketch_nov09a.ino`

3. If they are the same run the Arduino. If not change the ip to the one in step 1. then upload sketch to Arduino.

#### Configuring Google API

This project uses Google's Spreadsheets API. 




## Running the Project

The noise monitoring arduino will detect the current sound level and send the data to a google spreadsheet. 

Anytime starting up the flask sever make sure to be in a the virtual enviroment.

1. in the command line run source `run.sh`
  * This will start and run the flask sever.

2. Turn on Arduino 
   * Make sure to configure the ip of the sever and the ip the Arduino sends to. 


