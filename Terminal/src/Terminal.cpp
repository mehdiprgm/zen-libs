#include "Terminal.h"

namespace zen::terminal {
    void printCharacters(char ch, int length, bool nextLine) {
        for (int i = 0; i < length; i++) {
            cout << ch;
        }

        if (nextLine) {
            cout << endl;
        }
    }

    void pressEnter(const std::string& message) {
        cout << message;
        getchar();
    }

    void pressAnyKey(const std::string& message) {
        cout << message;

        getch();
        cout << endl;
    }

    void clearScreen() {
        system("cls");
    }

    void clearScreen(size_t lines) {
        for (size_t i = 0; i < lines; i++) {
            cout << endl;
        }
    }

    void clearLine() {
        cout << "\r\r";
    }

    Answer sure(const std::string& message, bool repeat) {
        char ch;

        do {
            cout << message;
            ch = tolower(getche());
            cout << endl;

            if (ch == 'y') {
                return Answer::Yes;
            } else if (ch == 'n') {
                return Answer::No;
            }
        } while(repeat);

        return Answer::Cancel;
    }

    int ask(const std::string& message, const std::vector<std::string>& options, bool repeat) {
        std::string newMessage, answer;

        do {
            newMessage = message + " [";
            for (int i = 0; i < options.size(); i++) {
                newMessage += options[i];

                if (i +  1 < options.size()) {
                    newMessage += ",";
                }
            }

            newMessage += "]: ";

            cout << newMessage;
            getline(cin, answer);
            newMessage.clear();

            for (int i = 0; i < options.size(); i++) {
                if (options[i] == answer) {
                    return i;
                }
            }
        } while(repeat);

        return -1;
    }

    std::string read(const std::string& message, int inputLimit, bool echo, bool password) {
        std::string result;

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