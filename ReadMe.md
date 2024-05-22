# Simulator - Main Program

This C program serves as a simulator for managing books, plates, and shopping queues. It generates and consumes events, such as adding books to a sorted list, managing plates in stacks, and simulating robots going for shopping.

## Description

The program consists of several modules to handle different tasks:

### Books Module

- **GenerateBook**: Generates a random book with a predefined set of authors, titles, and publication years.
- **SortingBooks**: Simulates sorting books based on the author's name and adds them to a sorted linked list.
- **PrintBooks**: Prints the list of sorted books.
- **RemoveSortingBooks**: Removes all books from the sorted list.

### Plates Module

- **GeneratePlate**: Generates a random plate with a predefined set of types and colors.
- **InitStacks**: Initializes stacks for different types of plates.
- **PrintPlates**: Prints the number of plates in each stack.
- **SimulateManagingPlate**: Simulates managing plates by adding them to corresponding stacks.
- **RemoveStack**: Removes a stack of plates when it reaches its maximum capacity.
- **CleanPlateStacks**: Removes all plates from the stacks.

### Shopping Module

- **GenerateShopping**: Generates a shopping task for a robot with a random number of items to buy.
- **AddToQueue**: Adds a robot to a shopping queue.
- **Dequeue**: Removes a robot from the queue and serves it.
- **UpdateShopping**: Simulates the time spent by robots in the queue.
- **SimulateGoForShopping**: Simulates a robot going for shopping and adds it to the queue.
- **CleanShoppingQueue**: Removes all robots from the shopping queue.

### Main Module

- **SimulationLoop**: The main loop of the program, which generates and consumes events for a specified number of iterations.
- **CheckArguments**: Validates the command-line arguments passed to the program.
- **main**: The entry point of the program, which initializes the simulation loop and executes it.

## Usage

1. Compile the program.
2. Run the compiled executable with the number of simulation events as a command-line argument.
3. The program will simulate the specified number of events, such as managing books, plates, and shopping queues.
4. After completing the simulation, it will print the statistics and clean up resources.

## Contributors

- **Martina Carretta** - [1673930]
- **Meritxell Carvajal** - [1671647]

## Degree and Subject

- **Degree**: Artificial Intelligence
- **Subject**: Fundamentals of Programming 2
- **Practical Project**: 1