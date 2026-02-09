#pragma once

#include <iostream>
#include <vector>

#include "Conio.h"

#define FR_RED_BOLD         "\u001b[1;31m"
#define FR_GREEN_BOLD       "\u001b[1;32m"
#define FR_BLUE_BOLD        "\u001b[1;34m"
#define FR_YELLOW_BOLD      "\u001b[1;33m"
#define FR_RESET            "\u001b[0m"

using namespace std;

/**
 * @namespace zen::terminal
 * @brief Utilities for terminal-based user interaction.
 *
 * This namespace provides helper functions for printing colored messages,
 * handling user input, clearing the screen, and asking interactive questions
 * in console applications.
 */
namespace zen::terminal {

    /**
     * @enum MessageType
     * @brief Defines message severity for colored terminal output.
     */
    enum class MessageType {
        Warning,        /**< Warning message (yellow) */
        Error,          /**< Error message (red) */
        Success,        /**< Success message (green) */
        Information,    /**< Informational message (blue) */
        Normal          /**< Default terminal output */
    };

    /**
     * @enum Answer
     * @brief Represents user response in confirmation dialogs.
     */
    enum class Answer {
        Yes,     /**< User answered yes */
        No,      /**< User answered no */
        Cancel  /**< User cancelled the operation */
    };

    /**
     * @brief Prints a character repeatedly to the terminal.
     *
     * @param ch Character to be printed
     * @param length Number of times the character is printed
     * @param nextLine If true, moves cursor to the next line after printing
     */
    void printCharacters(char ch, int length, bool nextLine);

    /**
     * @brief Prompts the user to press Enter to continue.
     *
     * @param message Message displayed to the user
     */
    void pressEnter(const string& message = "Press enter to continue!... ");

    /**
     * @brief Prompts the user to press any key to continue.
     *
     * @param message Message displayed to the user
     */
    void pressAnyKey(const string& message = "Press any key to continue!... ");

    /**
     * @brief Clears the entire terminal screen.
     */
    void clearScreen();

    /**
     * @brief Clears a specific number of lines from the terminal.
     *
     * @param lines Number of lines to clear
     */
    void clearScreen(size_t lines);

    /**
     * @brief Clears the current line in the terminal.
     */
    void clearLine();

    /**
     * @brief Displays a confirmation prompt to the user.
     *
     * @param message Question displayed to the user
     * @param repeat If true, repeats the prompt until a valid answer is given
     * @return User's selected answer
     */
    Answer sure(const string& message, bool repeat = false);

    /**
     * @brief Displays a multiple-choice question and gets user's selection.
     *
     * @param message Question displayed to the user
     * @param options List of selectable options
     * @param repeat If true, repeats the prompt until a valid option is chosen
     * @return Index of the selected option
     */
    int ask(const string& message, const vector<string>& options, bool repeat);

    /**
     * @brief Prints a value to the terminal with optional colored formatting.
     *
     * @tparam T Type of the value to print
     * @param input Value to be printed
     * @param messageType Type of message determining text color
     */
    template <typename T>
    void print(T input, MessageType messageType = MessageType::Normal) {
        switch(messageType) {
            case MessageType::Normal:
                cout << input;
                break;

            case MessageType::Error:
                cout << FR_RED_BOLD << input;
                break;

            case MessageType::Warning:
                cout << FR_YELLOW_BOLD << input;
                break;

            case MessageType::Success:
                cout << FR_GREEN_BOLD << input;
                break;

            case MessageType::Information:
                cout << FR_BLUE_BOLD << input;
                break;
        }

        cout << FR_RESET;
    }

    /**
     * @brief Prints a value followed by a newline with optional colored formatting.
     *
     * @tparam T Type of the value to print
     * @param input Value to be printed
     * @param messageType Type of message determining text color
     */
    template <typename T>
    void println(T input, MessageType messageType = MessageType::Normal) {
        print(input, messageType);
        cout << endl;
    }
}