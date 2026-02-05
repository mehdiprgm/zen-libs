#pragma once

#include <iostream>
#include <conio.h>

#define ENTER 13
#define TAB 9
#define BKSP 8

using namespace std;

/**
 * @namespace zen::terminal
 * @brief Terminal utilities for console-based user interaction.
 *
 * This namespace contains classes and functions designed to simplify
 * console input/output handling, including interactive and secure input.
 */
namespace zen::terminal {

    /**
     * @class ConsoleInput
     * @brief Handles interactive console input with optional masking and limits.
     *
     * This class provides a configurable interface for reading user input
     * from the console. It supports password-style input, echo control,
     * and maximum input length constraints.
     */
    class ConsoleInput {
        private:
            string message;      /**< Prompt message shown to the user */
            bool password;       /**< Enables password (masked) input */
            bool echo;           /**< Enables or disables character echo */
            size_t inputLimit;   /**< Maximum allowed input length */

        public:
            /**
             * @brief Constructs a ConsoleInput object with default settings.
             */
            ConsoleInput();

            /**
             * @brief Returns the prompt message.
             * @return Current input message
             */
            string getMessage() const;
    
            /**
             * @brief Checks whether password mode is enabled.
             * @return True if password input is enabled
             */
            bool getPassword() const;

            /**
             * @brief Checks whether input echo is enabled.
             * @return True if echo is enabled
             */
            bool getEcho() const;
    
            /**
             * @brief Returns the maximum allowed input length.
             * @return Input character limit
             */
            size_t getInputLimit() const;
    
            /**
             * @brief Sets the prompt message displayed to the user.
             * @param msg Message text
             */
            void setMessage(const string& msg);

            /**
             * @brief Enables or disables password input mode.
             *
             * When enabled, user input is masked (e.g., with '*').
             *
             * @param pwd True to enable password mode
             */
            void setPassword(bool pwd);

            /**
             * @brief Enables or disables character echo.
             *
             * @param e True to enable echo, false to disable it
             */
            void setEcho(bool e);

            /**
             * @brief Sets the maximum allowed input length.
             *
             * @param limit Maximum number of input characters
             */
            void setInputLimit(size_t limit);

            /**
             * @brief Reads input from the console according to current settings.
             *
             * This function processes keyboard input, applies echo and password
             * rules, and respects the defined input length limit.
             *
             * @return User input as a string
             */
            string read();
    };
}