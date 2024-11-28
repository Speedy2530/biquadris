# Biquadris Game

Welcome to **Biquadris**, a two-player Tetris-inspired game developed in C++ with both graphical and text-based interfaces. This game was created as a project for CS246 Fall 2024 and demonstrates object-oriented programming concepts, design patterns, and software engineering principles.

## Table of Contents

- [Introduction](#introduction)
- [Game Rules](#game-rules)
- [Features](#features)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Steps](#steps)
- [Usage](#usage)
  - [Example](#example)
- [Command-Line Options](#command-line-options)
- [Gameplay Commands](#gameplay-commands)
  - [Command Multipliers](#command-multipliers)
- [Scoring System](#scoring-system)
- [Levels and Difficulty](#levels-and-difficulty)
  - [Level 0](#level-0)
  - [Level 1](#level-1)
  - [Level 2](#level-2)
  - [Level 3](#level-3)
  - [Level 4](#level-4)
- [Special Actions](#special-actions)
- [Design Overview](#design-overview)
  - [Extensibility and Maintainability](#extensibility-and-maintainability)
- [Contributors](#contributors)

## Introduction

**Biquadris** is a turn-based, two-player game where players compete by strategically placing blocks on their respective boards. The objective is to clear lines and hinder the opponent through special actions triggered by clearing multiple lines simultaneously.

The game supports both text-based and graphical displays, allowing flexibility in how you choose to play. It also features multiple difficulty levels, each altering the gameplay dynamics for added challenge.

## Game Rules

- Each player has a separate 11x15 board.
- Blocks of various shapes (tetrominoes) appear at the top of each board.
- Players take turns to move, rotate, and drop blocks.
- When a row is completely filled, it disappears, and blocks above it shift down.
- The game ends when a new block cannot be placed at the top of the board.

## Features

- **Two-player Turn-Based Gameplay**: Compete against another player in a strategic battle.
- **Text and Graphical Interfaces**: Play in the terminal or with a graphical window.
- **Multiple Difficulty Levels**: Levels 0 to 4, each with unique block generation rules.
- **Special Actions**: Trigger special effects on your opponent by clearing multiple lines.
- **Command-Line Options**: Customize your gameplay experience through various options.
- **Scoring System**: Keep track of scores with a high score feature.

## Installation

### Prerequisites

- C++20 compatible compiler (e.g., g++)
- X11 development libraries (for graphical display)
- Make utility

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/biquadris.git
   cd biquadris
   ```

2. **Compile the Game**
   
   ```bash
   make
   ```
   This will generate the `biquadris` executable.

## Usage

   Run the game using the following command:
   ```bash
   ./biquadris [options]
   ```

### Example

   ```bash
   ./biquadris -startlevel 1 -text
   ```
   This command starts the game at level 1 in text-only mode.

# Command-Line Options
   
   - `text`: Runs the game in text-only mode. If omitted, both text and graphical displays are shown.
   - `-seed [number]`: Sets the seed for the random number generator.
   - `-scriptfile1 [filename]`: Uses a custom script file for player 1 in level 0.
   - `-scriptfile2 [filename]`: Uses a custom script file for player 2 in level 0.
   - `-startlevel [number]`: Starts the game at the specified level (0 to 4).

## Gameplay Commands

   During the game, players can enter the following commands:
   - `left`: Move the current block one cell to the left.
   - `right`: Move the current block one cell to the right.
   - `down`: Move the current block one cell downward.
   - `clockwise`: Rotate the block 90 degrees clockwise.
   - `counterclockwise`: Rotate the block 90 degrees counterclockwise.
   - `drop`: Drop the current block to the lowest possible position.
   - `levelup`: Increase the difficulty level by one.
   - `leveldown`: Decrease the difficulty level by one.
   - `norandom [filename]`: Use a sequence file for block generation in levels 3 and 4.
   - `random`: Restore random block generation in levels 3 and 4.
   - `[block type]`: Replace the current block with a specified block type (e.g., `I`, `J`, `L`).
   - `sequence [filename]`: Execute a sequence of commands from a file.
   - `restart`: Restart the game.

### Command Multipliers
   
   You can prefix commands with a number to execute them multiple times. For example:
   - `3left`: Move left three times.
   - `2drop`: Drop two blocks consecutively.

## Scoring System

   - **Line Clear Points**: `(Level + Number of Lines Cleared)²`
   - **Block Removal Points**: `(Level at Block Generation + 1)²` when a block is completely removed from the board.
   - **High Score Tracking**: The game keeps track of the highest score achieved during the session.

## Levels and Difficulty

### Level 0

   - Blocks are taken in sequence from a file (e.g., `sequence1.txt`).
   - Ideal for testing and predictable gameplay.

### Level 1

   - Blocks are randomly generated.
   - S and Z blocks have a probability of 1/12 each.
   - Other blocks have a probability of 1/6 each.

### Level 2

   - All blocks are selected with equal probability.

### Level 3
   
   - S and Z blocks have a probability of 2/9 each.
   - Other blocks have a probability of 1/9 each.
   - Blocks are "heavy" and automatically move down one row after each move or rotation.

### Level 4
   
   - Inherits all rules from Level 3.
   - Introduces a 1x1 block (`*`) dropped in the center column every 5 blocks if no lines are cleared.

## Special Actions

   When a player clears two or more lines simultaneously, they can trigger a special action against their opponent:
   - **Blind**: Covers a portion of the opponent's board with question marks until they drop their next block.
   - **Heavy**: Makes the opponent's blocks automatically drop by two rows after each left or right move.
   - **Force [block type]**: Changes the opponent's current block to a specified type.

## Design Overview

   The game is designed using object-oriented principles, ensuring high cohesion and low coupling among classes. Key design patterns and strategies include:
   - **Modular Design**: Separate classes for blocks, boards, levels, and display interfaces.
   - **Factory Pattern**: Used for block and level creation, facilitating easy addition of new types.
   - **Strategy Pattern**: Implements different level behaviors and block generation strategies.
   - **Observer Pattern**: Keeps the display in sync with the game state.
   - **Command Pattern**: Simplifies the addition of new commands and parsing of user input.

### Extensibility and Maintainability
   
   - **Adding New Levels**: The level system is designed to accommodate new levels with minimal changes.
   - **Custom Commands**: The command interpreter can be extended to support new commands or macros.
   - **Special Blocks**: The block system allows for easy integration of new block types with unique behaviors.

## Contributors
   
   - **Amitpal Badhan** - as3badha@uwaterloo.ca
   - **Shrey Varma** - s3varma@uwaterloo.ca
   - **Saihej Singh** - s268sing@uwaterloo.ca

---

Thank you for choosing Biquadris! We hope you enjoy the game. If you have any questions or feedback, please reach out to the contributors listed above.
