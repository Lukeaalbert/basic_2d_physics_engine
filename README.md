# Basic 2D Physics Engine

This repository contains a simple yet powerful 2D physics engine built from scratch, simulating gravity and particle collisions. It utilizes **SFML** for rendering, providing a visual representation of the physics in action.

## Features

- **Particle-Based Physics**: Simulates dynamic particle interactions with realistic collision responses.
- **Gravity Simulation**: Objects experience acceleration due to gravity, creating natural movement.
- **Verlet Integration**: A stable numerical method for motion calculation, improving realism.
- **Collision Handling**: Resolves object collisions using normal and tangent vectors for accurate responses.
- **SFML-Based Rendering**: Provides real-time visualization of the physics simulation.
- **Interactive Demonstration**: The included `main.cpp` launches a sample scene where balls are "shot" into a container.

## Visualization

The physics engine supports rendering visual elements to observe real-time interactions. The demo video showcases objects interacting within a bounded space.

[![Demo Video](https://github.com/user-attachments/assets/30e4f1b4-9938-4f80-9dd9-ddedeb2e7ba5)](https://github.com/user-attachments/assets/30e4f1b4-9938-4f80-9dd9-ddedeb2e7ba5)

## Installation & Usage

1. Clone the repository:
   ```sh
   git clone https://github.com/your-repo-link.git
   cd your-repo-name
   ```
2. Install SFML if not already installed.
3. Compile the project:
   ```sh
   g++ main.cpp -o physics_engine -lsfml-graphics -lsfml-window -lsfml-system
   ```
4. Run the program:
   ```sh
   ./physics_engine
   ```
