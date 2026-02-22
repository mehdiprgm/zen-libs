#pragma once

#include <termios.h>
#include <stdio.h>

static struct termios old, current;

namespace zen::terminal {
/**
     * @brief Initializes terminal settings for custom input handling
     * 
     * Configures the terminal to enable or disable echo mode. This is a low-level
     * function that modifies terminal attributes to allow character-by-character
     * input processing without buffering.
     * 
     * @param echo Controls whether input characters are displayed:
     *            - 1: Enable echo (typed characters are visible)
     *            - 0: Disable echo (typed characters are not visible)
     * 
     * @note This function modifies global terminal settings and should be paired
     *       with resetTermios() to restore normal terminal behavior.
     * @warning Improper use can leave the terminal in an unusable state. Always
     *          ensure resetTermios() is called before program exit.
     * 
     * @see resetTermios()
     */
    void initTermios(int echo);

    /**
     * @brief Restores original terminal settings
     * 
     * Resets the terminal to its default configuration that was active before
     * initTermios() was called. This function must be called to restore normal
     * terminal behavior after custom input handling.
     * 
     * @note Always call this function before program exit to ensure the terminal
     *       is left in a usable state.
     * 
     * @see initTermios()
     */
    void resetTermios();

    /**
     * @brief Internal function for character input with configurable echo
     * 
     * Reads a single character from standard input with optional echo control.
     * This is a low-level function that requires proper terminal initialization.
     * 
     * @param echo Controls whether the input character is displayed:
     *            - 1: Character is displayed as typed (echo on)
     *            - 0: Character is not displayed (echo off)
     * @return char The character read from input
     * 
     * @note This function does not initialize terminal settings. Call initTermios()
     *       before using this function.
     * @warning Ensure resetTermios() is called after finishing raw input operations.
     * 
     * @see initTermios()
     * @see resetTermios()
     * @see getch()
     * @see getche()
     */
    char getch_(int echo);

    /**
     * @brief Reads a single character without echoing (no Enter key required)
     * 
     * Captures a single keystroke immediately without waiting for the Enter key
     * and without displaying the character on screen. This is ideal for password
     * input, menu navigation, and game controls.
     * 
     * @return char The character read from input
     * 
     * Example usage:
     * @code
     * #include <iostream>
     * #include "zen/terminal/Terminal.hpp"
     * 
     * int main() {
     *     std::cout << "Press any key to continue (character won't be shown)...";
     *     char key = zen::terminal::getch();
     *     std::cout << "\nYou pressed: " << key << std::endl;
     *     return 0;
     * }
     * @endcode
     * 
     * Password input example:
     * @code
     * std::string password;
     * std::cout << "Enter password: ";
     * char ch;
     * while ((ch = zen::terminal::getch()) != '\n') {
     *     if (ch == '\b') {  // Handle backspace
     *         if (!password.empty()) {
     *             password.pop_back();
     *             std::cout << "\b \b";  // Erase character on screen
     *         }
     *     } else {
     *         password += ch;
     *         std::cout << '*';  // Display asterisk instead of character
     *     }
     * }
     * @endcode
     * 
     * @note This function automatically handles terminal initialization and cleanup.
     * @see getche() For version that echoes the character
     */
    char getch(void);

    /**
     * @brief Reads a single character with echoing (no Enter key required)
     * 
     * Captures a single keystroke immediately without waiting for the Enter key
     * and displays the typed character on screen. Useful for interactive prompts
     * where immediate feedback is desired.
     * 
     * @return char The character read from input
     * 
     * Example usage:
     * @code
     * #include <iostream>
     * #include "zen/terminal/Terminal.hpp"
     * 
     * int main() {
     *     std::cout << "Choose an option (A/B/C): ";
     *     char choice = zen::terminal::getche();
     *     std::cout << "\nYou chose: " << choice << std::endl;
     *     return 0;
     * }
     * @endcode
     * 
     * Interactive menu example:
     * @code
     * char option;
     * do {
     *     std::cout << "\nMenu:\n";
     *     std::cout << "1. New Game\n";
     *     std::cout << "2. Load Game\n";
     *     std::cout << "3. Settings\n";
     *     std::cout << "4. Exit\n";
     *     std::cout << "Select option: ";
     *     
     *     option = zen::terminal::getche();
     *     std::cout << std::endl;
     *     
     *     switch(option) {
     *         case '1': startNewGame(); break;
     *         case '2': loadGame(); break;
     *         case '3': showSettings(); break;
     *     }
     * } while (option != '4');
     * @endcode
     * 
     * @note This function automatically handles terminal initialization and cleanup.
     * @see getch() For version that doesn't echo the character
     */
    char getche(void);
}

