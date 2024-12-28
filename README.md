# Overview

This project is a GPU-based implementation of the paper Particle-Based Viscoelastic Fluid Simulation. It harnesses modern GPU computing capabilities to efficiently simulate large numbers of fluid particles with viscoelastic properties in real time.
# Dependencies
- ImGui
- GLFW
- glew
- glm
These libraries handle the user interface, windowing, OpenGL extensions, and math operations needed for the simulation.

# How it works
1. Initialization <br> Each particle is assigned an initial velocity, then gravity is applied as a global force. 
2. Predicted Position <br> The particles are moved to a predicted position based on the current velocity and forces.
3. Forces and Interactions <br> Particle interactions (including viscoelastic behavior) are computed on the GPU, leveraging parallel kernel dispatches.
4. Collision Resolution <br> Collisions with boundaries or other obstacles are detected and resolved accordingly.

# Performance and Optimization 
A uniform grid is used to minimize unnecessary pairwise computations. Each particle only checks for interactions with neighboring particles located in its own cell or in adjacent cells, significantly improving the performance.

# Demo

https://github.com/user-attachments/assets/c07ef396-1b01-4bfb-9cb5-778657b990ec

The video showcases 65,536 particles running at a stable 100 FPS on a GTX 1080 GPU, demonstrating the efficiency of the grid-based parallel approach and the kernel dispatch strategy.
