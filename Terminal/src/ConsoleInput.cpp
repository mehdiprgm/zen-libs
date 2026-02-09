#include "ConsoleInput.h"

namespace zen::terminal {
    ConsoleInput::ConsoleInput() : password(false), echo(true), inputLimit(100) {}

    bool ConsoleInput::getPassword() const {
        return password;
    }
    
    bool ConsoleInput::getEcho() const {
        return echo;
    }
    
    size_t ConsoleInput::getInputLimit() const {
        return inputLimit;
    }
    
    void ConsoleInput::setPassword(bool password) {
        this->password = password;
    }
    
    void ConsoleInput::setEcho(bool echo) {
        this->echo = echo;
    }
    
    void ConsoleInput::setInputLimit(size_t inputLimit) {
        this->inputLimit = inputLimit;
    }

    string ConsoleInput::read(const string& message) {
        string result;

        char ch;
        int i = 0;

        cout << message;

        do {
            if (i == inputLimit) {
                result[i] = '\0';
                break;
            }

            ch = getch();

            if (ch == ENTER || ch == TAB) {
                result[i] = '\0';
                break;
            } else if (ch == BKSP) {
                if (i > 0) {
                    if (echo) {
                        cout << "\b \b";
                    }

                    i--;
                }
            } else {
                if (echo) {
                    if (password) {
                        cout << "*";
                    } else {
                        cout << ch;
                    }
                }

                result[i++] = ch;
            }
        } while(true);

        cout << endl;
        return result.c_str();
    }
}