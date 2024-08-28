# Jigsaw Puzzle & Puzzle Piece Generator in C

## Overview
This project is a C-based jigsaw puzzle solver. It aims to create and manipulate puzzle pieces, attempting to solve a jigsaw puzzle by matching pieces based on their shapes.

## Features
- Create and manage puzzle pieces.
- Attempt to solve the puzzle using a matching algorithm.
- Display the final puzzle board upon successful completion.

## Requirements
- CMake (version 3.28 or higher)
- A C compiler (e.g., GCC, Clang)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/jigsaw.git
   cd jigsaw
   ```

2. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   make
   ```

## Usage
After building the project, you can run the executable:
```bash
./jigsaw
```

The program will create some pieces for testing and attempt to solve the puzzle, displaying the result in the console.
