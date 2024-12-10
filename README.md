# Snake Game in C

This project is a classic implementation of the Snake game written in C using the SDL3 library for graphics rendering. The snake grows as it consumes food, and the game ends if the snake collides with itself or the boundaries of the window.

## Features

- **Snake Movement:** The snake moves in four directions (up, down, left, right) and follows the classic snake behavior.
- **Food Generation:** Food appears randomly on the grid for the snake to consume.
- **Growth Mechanism:** The snake grows longer as it eats food.
- **Collision Detection:** The game ends when the snake collides with itself or the game window's borders.
- **Smooth Rendering:** The game uses SDL3 for rendering the grid, snake, and food.

---

## Getting Started

### Prerequisites

Make sure you have the following installed on your system:
- GCC or Clang compiler
- SDL3 library (`libsdl3` or equivalent package)

### Installation

1. Clone this repository:
    ```bash
    git clone https://github.com/your-username/snake-game.git
    cd snake-game
    ```

2. Install SDL3 library (if not already installed):
    - **On Debian/Ubuntu:**
      ```bash
      sudo apt install libsdl3-dev
      ```

3. Compile the program:
    ```bash
    gcc -o snake_game snake_game.c -lSDL3
    ```

4. Run the game:
    ```bash
    ./snake_game
    ```

---

## Controls

- **Arrow Keys:** Change the direction of the snake.
- **Q:** Quit the game.

---

## Code Overview

### Main Components
1. **Event Loop:** Manages user input, game logic, and rendering.
2. **Snake Representation:**
   - A **doubly linked list** is used to represent the snake, where each node contains the coordinates and dimensions of a body segment.
3. **Game Mechanics:**
   - Food is generated randomly.
   - The snake grows when it eats food, and the game ends on collision with itself or the boundaries.

### Key Functions
- `EventLoop`: Handles game events and main logic.
- `DrawSnake`: Renders the snake on the screen.
- `GrowSnake`: Adds a new segment to the snake's body.
- `MakeSnack`: Generates food on the grid.
- `CheckCollision`: Detects collisions with the window boundaries or the snake itself.

---

## Known Issues

- **Timing Sensitivity:** The program relies on `SDL_GetTicks()` for smooth gameplay. Excessive CPU load may affect rendering consistency.
- **No Pause Functionality:** There is currently no way to pause the game.

---

## Possible Improvements

- Add a score display to show the player's progress.
- Implement difficulty levels by increasing the snake's speed over time.
- Add a pause functionality.
- Improve collision detection to handle edge cases.
- Add multiplayer so two Snakes can compete against each other

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

## Acknowledgments

- This project uses the [SDL3 library](https://libsdl.org/) for rendering and event handling.
