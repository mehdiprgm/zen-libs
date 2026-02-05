#include "terminal.h"

namespace zen::terminal {
    void printCharacters(char ch, int length, bool nextLine) {
        for (int i = 0; i < length; i++) {
            cout << ch;
        }

        if (nextLine) {
            cout << endl;
        }
    }

    void pressEnter(const string& message) {
        cout << message;
        getchar();
    }

    void pressAnyKey(const string& message) {
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

    Answer sure(const string& message, bool repeat) {
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

    int ask(const string& message, const vector<string>& options, bool repeat) {
        string newMessage, answer;

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
}