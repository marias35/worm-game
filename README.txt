# Happy Worm 
# Authors:
Wiktoria Bortlisz
Maria Georgiana Stegaru

# Compiling instructions:
In order to compile and play the game, the joystick first needs to be connected acording to the folowing scheme;
- GPIO_0 -> UP pin on the joystick (the pin closest to the centre)
- GPIO_1 -> DOWN pin 
- GPIO_2 -> RIGHT pin
- GPIO_3 -> LEFT pin
- GND (pin 12) -> GND on the joystick

In order to play the game again the board needs to be reseted. Then the following instructions need to be executed: 
- make
- dtekv-run main.bin 
 
# Description:
Happy Worm is a game designed for one player, which moves a worm using a joystick in the following directions: up, down, right, left.
The player can collect 6 different type of objects which have special effects.
The goal is to collects as many points as possible through the objects and to avoid crushing into the walls and into the worm itself. 
The game has a maximum play time of 2 minutes, but can be stopped by collisions. 

# Game rules:
The player has 120 seconds(2 minutes) to play the game.
The play can collect objects and increase its score and nust pay attention not to crush into walls or into the worm so it does not stop the game before the timer reaches its limit;

# Hardware:
The game was developed for the DTEK-V board.
It uses the following components:
- VGA display;
- 7-segment displays;
- Timer;
- Frame buffers;
We are also using a 8-ways joystick and a VGA to HDMI adapter which is connected through a VGA to HDTV cable.

# Software:
The programming language is C;
- RISC-V for boot.S;
- GitHub;
- Visual Studio Code;


