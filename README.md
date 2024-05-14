Title: Pacman: A Threaded Adventure with SFML (C++)

Authors:
Hammad Amer
Shayaan Khalid

Description:
This repository implements a classic Pacman game using C++, the Simple and Fast Multimedia Library (SFML), and the POSIX threads (pthread) library. It provides a fun and engaging experience with smooth animation, collision detection, and threaded ghost AI.

Features:

SFML Graphics: Leverages SFML for rendering game elements like Pacman, ghosts, pellets, and the maze.
Pthreads: Utilize pthreads for concurrent processing, potentially enhancing ghost AI behavior or other game mechanics (implementation details required).
Classic Gameplay: Offers the core Pacman experience, including pellet collection, ghost avoidance, and power-up effects.

Requirements:

C++ Compiler: A C++ compiler that supports C++11 or later (e.g., GCC, Clang).
SFML: Download and install SFML from https://www.sfml-dev.org/download.php. Follow the installation instructions for your operating system.
pthread Library: If your implementation uses pthreads, ensure the pthread library is available on your system.

Installation:

Clone this repository: git clone https://github.com/<your-username>/pacman-sfml-pthread.git
Install SFML (if not already done). Refer to the SFML documentation for specific steps.
Compile the project:
g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread -lX11

Run the compiled executable (e.g., ./main).

Basic gameplay working:
Use arrow keys or WASD to control Pacman.
Collect pellets and avoid ghosts to win!

Contribution:
We welcome contributions to improve the game mechanics, AI, or other aspects. Please create a pull request on GitHub with your changes and a clear description.


Copyright (c) 2024
All rights reserved.

This game is a Pacman clone built with SFML (Simple and Fast Multimedia Library).

All assets, including graphics, sounds, and music, are used with permission and are royalty free.

You are allowed to:

- Use the game for personal entertainment.
- Share the game with others.
- Modify the game for personal use.

You are not allowed to:

- Use the game for commercial purposes without permission.
- Distribute modified versions of the game without permission.
- Remove or modify any credits or attributions included with the game.

The game is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the game or the use or other dealings in the game.

For licensing inquiries or any questions, 
please contact at i220877@nu.edu.pk , i220863@nu.edu.pk
