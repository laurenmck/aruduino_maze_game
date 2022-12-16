# Introduction 

For the project, we will be creating a maze game! The goal of this game is for the users to move the ball from start to finish through the maze. The maze will be controlled by a joystick and will have the ability to move left, right, up, and down at the user's discretion. 

# Project Information 

Group Members: @laurenmck, @jessieyli, James Cai and Brennan Nugent. 
Project Durration: November 2022 - December 2022
Project Type: Group Project for Real Time and Embedded Software (cs1600)

# Project Demo!

https://user-images.githubusercontent.com/28674640/208175935-69cc6729-44d5-43bd-a8c1-16b55f44f214.mp4

![IMG_1602-min](https://user-images.githubusercontent.com/28674640/208176930-211b0bd8-0ee6-4207-8dde-eefedb3ac37c.png)

# Project Requirements 

For this project, our solution was required to use PWM, ADC, or DAC, have an interrupt service routine and a watchdog timer and use one of serial communication, WiFi or a Timer/Counter. Our design choices are explained below. 
 
**ADC**: The joystick functions like two potentiometers and indicates its position using analog voltages, which are then converted using an ADC into digital values ranging from 0 to 1023 that we can then read.  

**Watchdog Timer**: The watchdog timer will ensure that there is a constant connection between the LCD screen and the game components. If the connection is lost, the user cannot be informed about the game status, and the timer ensures that the display properly reflects the current game status. Thus, the watchdog is pet every time a message is received, and if the receiver goes 2 seconds without receiving a message, the early warning ‘connection is lost!’ message will be shown and the system will be reset.
Interrupt: The interrupt is triggered when the joystick is clicked by the user (and its signal changes from 1 to 0). This will restart the game, starting the countdown to begin a new game. 

**Serial Communication**: we are using the Arduino LCD screen to communicate game updates to the user. Based on the game state, our main Arduino will send messages to the LCD screen Arduino and the corresponding message will be shown to the user. 

Displayed messages: 
“You Won!”
“Game in Progress” 
Pre-game countdown from “3” to “1”
Watchdog timer’s warning “Communication Lost” 

More specific messaging specs:
3, 2, 1 → these will notify the receiver that the countdown is in progress, and the corresponding number will be displayed on the screen. 
4 → the number 4 will represent that the game is in progress, when this is received, “game in progress” will be displayed on the screen.  
5 → the number 5 will be sent to indicate to the receiver that the game is over, when this message is received, the “You Won!” will be displayed. 

# Learn More 
More information about our project, including out state machine, architecture diagram and testing procedure can be found in our project write up: https://docs.google.com/document/d/1gAKFA8TQqzthJVI9mLayMgBqKDwhxPAjZJZoRz2uU3A/edit
