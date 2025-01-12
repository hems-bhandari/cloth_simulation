# Cloth Simulation in C++ with SFML

This project implements a cloth simulation in C++ using the SFML (Simple and Fast Multimedia Library) for rendering and window management.

## Prerequisites

To build and run this project, ensure you have the following installed:

1. **Homebrew** (for managing dependencies on macOS)
2. **SFML Library** (installed via Homebrew)

   ```bash
   brew install sfml@2
   ```

3. **g++ Compiler** with C++17 support

## Files

- `main.cpp`: The main source file containing the cloth simulation logic.
- `Makefile`: Build instructions for compiling the project.

## Building the Project

1. Clone the repository or download the source files.

   ```bash
   git clone <repository-url>
   cd <project-directory>
   ```

2. Build the project using the provided `Makefile`.

   ```bash
   make
   ```

   This will compile `main.cpp` and generate an executable named `main`.

## Running the Application

After building the project, run the executable:

```bash
./main
```

## Features

- Simulates cloth dynamics using a particle-based approach.
- Implements constraints and spring physics for realistic behavior.
- Renders the simulation using SFML for interactive visualization.

## Cleaning Up

To remove the generated files (executable and object files):

```bash
make clean
```

## SFML Library

This project links against the following SFML libraries:

- `sfml-graphics`
- `sfml-window`
- `sfml-system`

These libraries are included via Homebrew at the following paths:

- **Include Directory**: `/opt/homebrew/opt/sfml@2/include`
- **Library Directory**: `/opt/homebrew/opt/sfml@2/lib`

## Notes

- Ensure Homebrew's SFML installation paths are correctly set. If you encounter issues, confirm the paths using:

  ```bash
  brew info sfml@2
  ```

- The `Makefile` assumes the source file is named `main.cpp`. Update the `SRC` variable in the `Makefile` if additional source files are added.

## Acknowledgments

- [SFML](https://www.sfml-dev.org/) for the multimedia library
- [Homebrew](https://brew.sh/) for package management
- [Guide](https://owlree.blog/posts/simulating-a-rope.html) that I used to build this
