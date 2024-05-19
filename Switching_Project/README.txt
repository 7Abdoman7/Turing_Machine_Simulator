Turing Machine Simulator
Overview

This is a simple Turing Machine simulator implemented in C. It allows users to define a transition table representing the behavior of a Turing Machine and simulate its operation on a given input tape.
Features

    Define transition rules for the Turing Machine.
    Simulate the Turing Machine's operation on an input tape.
    Print the encrypted representation of the Turing Machine.

Usage

    Compilation: Compile the program using a C compiler. For example: gcc Project.c -o Project

Execution: Run the compiled program: ./Project

    Input: Follow the instructions to input the transition table in the specified format. Then input the tape contents and the initial state.
    Output: The program will simulate the operation of the Turing Machine and print the final state of the tape.

Transition Table Format

The transition table should be entered in the following format:


(state, input, newState, output, action)

    state: The current state of the Turing Machine.
    input: The symbol read from the tape.
    newState: The new state of the Turing Machine.
    output: The symbol to write to the tape.
    action: The action to perform (R = Right, L = Left, Y = Yes, N = No).

Examples:

Examples of transition tables and input tapes are provided at the end of the code file. You can copy and paste them into the program for testing.
Encryption

The program also provides an option to print the encrypted representation of the Turing Machine. This can be useful for sharing or storing the Turing Machine configuration securely.
License

This project is licensed under the MIT License - see the LICENSE file for details.
Acknowledgments

This project was inspired by the concepts of Turing Machines and the desire to create a simple simulator for educational purposes.




feel free to contact me:
@Auther: Abdelrahman Elsayed Ahmed
@E-Mail: abdo.elsayd102@gmail.com