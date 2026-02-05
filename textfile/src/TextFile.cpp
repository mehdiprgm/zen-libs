#include "TextFile.h"

namespace zen::file::text {
    TextFile::TextFile(const string& filePath) : filePath(filePath) {}

    unique_ptr<ifstream> TextFile::createInputStream() {
        auto inStream = make_unique<ifstream>(filePath);
        if (!inStream->is_open()) {
            throw runtime_error("Failed to open file: " + filePath);
        }

        return inStream;
    }

    unique_ptr<ofstream> TextFile::createOutputStream(bool append) {
        unique_ptr<ofstream> opStream;

        if (append) {
            opStream = make_unique<ofstream>(filePath, ios::app);
        } else {
            opStream = make_unique<ofstream>(filePath);
        }

        if (!opStream->is_open()) {
            throw runtime_error("Failed to open file: " + filePath);
        }

        return opStream;
    }

    string TextFile::read() {
        auto stream = createInputStream();

        ostringstream buffer;
        buffer << stream->rdbuf();

        return buffer.str();
    }

    string TextFile::readFirstLine() {
        auto stream = createInputStream();
        string firstLine;

        getline(*stream, firstLine);
        return firstLine;
    }

    string TextFile::readLastLine() {
        auto stream = createInputStream();

        string line;
        while (getline(*stream, line)) {
        }

        return line;
    }

    vector<string> TextFile::readAllLines() {
        auto stream = createInputStream();

        string line;
        vector<string> lines;

        while(getline(*stream, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    bool TextFile::write(const string& content, bool append) {
        auto stream = createOutputStream(append);
        *stream << content;
        
        return true;
    }

    bool TextFile::clear() {
        auto stream = createOutputStream();
        return true;
    }

    size_t TextFile::find(const string& key, bool isCaseSensitive, bool findWholeWord) {
        auto stream = createInputStream();

        string line, newkey = key;
        size_t foundItems = 0;

        while(getline(*stream, line)) {
            if (!isCaseSensitive) {
                transform(newkey.begin(), newkey.end(), newkey.begin(), ::tolower);
                transform(line.begin(), line.end(), line.begin(), ::tolower);
            }

            if (findWholeWord) {
                if (line == newkey) {
                    foundItems++;
                }
            } else {
                if (line.find(newkey) != string::npos) {
                    foundItems++;
                }
            }
        }

        return foundItems;
    }

    size_t TextFile::count(CountItem item) {
        auto stream = createInputStream();

        string line;
        size_t count = 0;

        while(getline(*stream, line)) {
            switch(item) {
                case CountItem::Words: {
                    istringstream iss(line);
                    vector<string> words;

                    string word;
                    while (iss >> word) {
                        words.push_back(word);
                    }

                    count += words.size();
                    break;
                }

                case CountItem::Characters:
                    count += line.length();
                    break;

                case CountItem::Lines:
                    count += 1;
                    break;

                case CountItem::EmptyLines:
                    if (line == "") {
                        count += 1;
                    }

                    break;
            }
        }

        return count;
    }
}