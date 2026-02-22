#include "TextFile.h"

namespace zen::file::text {
    TextFile::TextFile(const std::string& filePath) : filePath(filePath) {}

    std::unique_ptr<std::ifstream> TextFile::createInputStream() {
        auto inStream = std::make_unique<std::ifstream>(filePath);
        if (!inStream->is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        return inStream;
    }

    std::unique_ptr<std::ofstream> TextFile::createOutputStream(bool append) {
        std::unique_ptr<std::ofstream> opStream;

        if (append) {
            opStream = std::make_unique<std::ofstream>(filePath, std::ios::app);
        } else {
            opStream = std::make_unique<std::ofstream>(filePath);
        }

        if (!opStream->is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        return opStream;
    }

    std::string TextFile::read() {
        auto stream = createInputStream();

        std::ostringstream buffer;
        buffer << stream->rdbuf();

        return buffer.str();
    }

    std::string TextFile::readFirstLine() {
        auto stream = createInputStream();
        std::string firstLine;

        std::getline(*stream, firstLine);
        return firstLine;
    }

    std::string TextFile::readLastLine() {
        auto stream = createInputStream();

        std::string line;
        while (std::getline(*stream, line)) {
        }

        return line;
    }

    std::vector<std::string> TextFile::readAllLines() {
        auto stream = createInputStream();

        std::string line;
        std::vector<std::string> lines;

        while(std::getline(*stream, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    bool TextFile::write(const std::string& content, bool append) {
        auto stream = createOutputStream(append);
        *stream << content;
        
        return true;
    }

    bool TextFile::clear() {
        auto stream = createOutputStream();
        return true;
    }

    size_t TextFile::find(const std::string& key, bool isCaseSensitive, bool findWholeWord) {
        auto stream = createInputStream();

        std::string line, newkey = key;
        size_t foundItems = 0;

        while(std::getline(*stream, line)) {
            if (!isCaseSensitive) {
                transform(newkey.begin(), newkey.end(), newkey.begin(), ::tolower);
                transform(line.begin(), line.end(), line.begin(), ::tolower);
            }

            if (findWholeWord) {
                if (line == newkey) {
                    foundItems++;
                }
            } else {
                if (line.find(newkey) != std::string::npos) {
                    foundItems++;
                }
            }
        }

        return foundItems;
    }

    size_t TextFile::count(CountItem item) {
        auto stream = createInputStream();

        std::string line;
        size_t count = 0;

        while(std::getline(*stream, line)) {
            switch(item) {
                case CountItem::Words: {
                    std::istringstream iss(line);
                    std::vector<std::string> words;

                    std::string word;
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