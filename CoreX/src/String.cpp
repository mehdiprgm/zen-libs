#include "String.h"

namespace zen::corex {

    void String::initialize(const std::string& input) {
        if (input.empty()) {
            size = 0;
            capacity = DEFAULT_CAPACITY;

            data = new char[DEFAULT_CAPACITY];
        } else {
            size = input.length();

            /* Add 1 for null terminator character */
            size_t needed_capacity = size + 1;
        
            /* Round up to next multiple of 32 */
            capacity = ((needed_capacity + 31) / 32) * 32;
            data = new char[capacity];
        
            std::copy(input.begin(), input.end(), data);
            data[size] = '\0';
        }
    }

    String::String() {
        initialize("");
    }

    String::String(const String& input) {
        initialize(input.toString());
    }

    String::String(const std::string& input) {
        initialize(input);
    }

    String::String(const char* input) {
        initialize(std::string(input));
    }

    String::~String() {
        delete data;
    }

    String& String::operator=(const String& input) {
        if (this == &input || input.isEmpty() == 0) {
            return *this;
        }

        initialize(input.toString());
        return *this;
    }

    String& String::operator=(const std::string& input) {
        if (input.empty()) {
            return *this;
        }

        initialize(input);
        return *this;
    }

    String& String::operator=(const char* input) {
        if (!input) {
            return *this;
        }

        initialize(std::string(input));
        return *this;
    }

    String& String::operator+=(const String& input) {
        if (this == &input || input.getSize() == 0) {
            return *this;
        }

        this->append(input);
        return *this;
    }

    String& String::operator+=(const std::string& input) {
        this->append(String(input));
        return *this;
    }

    String& String::operator+=(const char* input) {
        this->append(String(input));
        return *this;
    }

    String& String::operator-=(const String& input) {
        if (this == &input || input.getSize() == 0) {
            return *this;
        }

        this->remove(input);
        return *this;
    }

    String& String::operator-=(const std::string& input) {
        this->remove(String(input));
        return *this;
    }

    String& String::operator-=(const char* input) {
        this->remove(String(input));
        return *this;
    }

    bool String::operator==(const String& input) const {
        if (!data || !input.data) {
            return data == input.data;
        }
    
        if (size != input.size) {
            return false;
        }
    
        return strcmp(data, input.data) == 0;
    }

    bool String::operator==(const std::string& input) const {
        if (!data) {
            return input.empty();
        }
    
        return input == data; 
    }

    bool String::operator==(const char* input) const {
        if (!data || !input) {
            return data == input;
        }
    
        return strcmp(data, input) == 0;
    }

    bool String::operator!=(const String& input) const {
        return !(*this == input);
    }

    bool String::operator!=(const std::string& input) const {
        return !(*this == input);
    }

    bool String::operator!=(const char* input) const {
        return !(*this == input);
    }

    char& String::operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        return data[index];
    }

    const char& String::operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    std::ostream& operator<<(std::ostream& os, const String& input) {
        if (input.data && input.size > 0) {
            os.write(input.data, input.size);
        }

        return os;
    }

    String String::copy() {
        return String(*this);
    }

    void String::append(const String& input) {
        int currentDataSize = strlen(data), maxLength = 0;
        std::string tmpString = input.toString();

        if (input.isEmpty()) {
            return;
        }

        /* The last one is for null termination character + 1*/
        maxLength = currentDataSize + input.getSize() + 1;

        char* newData = new char[maxLength];
        strcpy(newData, data);

        for (size_t i = 0; i < input.getSize(); i++) {
            newData[currentDataSize + i] = tmpString[i];
        }

        newData[currentDataSize + input.getSize()] = '\0';
        delete [] data;

        initialize(std::string(newData));
        delete [] newData;
    }

    void String::remove(const String& input) {
        if (input.isEmpty() || input.size > size) {
            return;
        }

        char* pos = strstr(data, input.toCharArray());
        if (!pos) {
            return;
        }

        size_t index = pos - data;
        int newSize = size - input.size + 1;

        char *newData = new char[newSize];
        strncpy(newData, data, index);

        size_t afterIndex = index + input.size;
        size_t remainingLength = size - afterIndex;

        for (int i = 0; i < remainingLength; i++) {
            newData[index + i] = data[afterIndex + i];
        }

        newData[newSize - 1] = '\0';
        initialize(std::string(newData));
    }

    void String::toLowerCase() {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<char>(tolower(static_cast<char>(data[i])));
        }
    }

    void String::toUpperCase() {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<char>(toupper(static_cast<char>(data[i])));
        }
    }

    void String::replace(const String& oldStr, const String& newStr) {
        if (oldStr.isEmpty()) {
            return;
        }

        char* pos = strstr(data, oldStr.toCharArray());
        if (!pos) {
            return;
        }

        size_t oldStringIndex = pos - data;
        int newSize = size - oldStr.size + newStr.size + 1;

        char *newData = new char[newSize];

        strncpy(newData, data, oldStringIndex);
        newData[oldStringIndex] = '\0';

        strcat(newData, newStr.toCharArray());
        strcat(newData, data + oldStringIndex + oldStr.size);

        delete [] data;
        initialize(std::string(newData));
        delete [] newData;
    }

    void String::clear() {
        initialize("");
    }

    void String::reverse() {
        std::string str;

        for (int i = size; i >= 0; i--) {
            str += data[i];
        }

        initialize(str);
    }

    int String::contains(const String& input) {
        if (input.isEmpty()) {
            return -1;
        }

        size_t inputSize = input.size;
        if (inputSize > size) {
            return -1;
        }

        for (int i = 0; i <= size - inputSize; i++) {
            bool found = true;
        
            for (int j = 0; j < inputSize; j++) {
                /* Check if current character equals to the input character */
                if (data[i + j] != input[j]) {
                    found = false;
                    break;
                }
            }

            if (found) {
                return i;
            }
        }

        return -1;
    }

    bool String::isEmpty() const {
        return size == 0;
    }

    bool String::isBlank() const {
        for (int i = 0; i < size; i++) {
            if (!isspace(data[i])) {
                return false;
            }
        }

        return true;
    }

    bool String::isNumber() const {
        for (int i = 0; i < size; i++) {
            if (!isdigit(data[i])) {
                return false;
            }
        }

        return true;
    }

    bool String::isText() const {
        for (int i = 0; i < size; i++) {
            if (isdigit(data[i])) {
                return false;
            }
        }

        return true;
    }

    short String::toShort() {
        short number;
        if (sscanf(data, "%hd", &number) != 1) {
            throw std::invalid_argument("number convertion failed");
        }

        return number;
    }

    int String::toInt() {
        int number;
        if (sscanf(data, "%d", &number) != 1) {
            throw std::invalid_argument("number convertion failed");
        }

        return number;
    }

    long String::toLong() {
        long number;
        if (sscanf(data, "%ld", &number) != 1) {
            throw std::invalid_argument("number convertion failed");
        }

        return number;
    }

    float String::toFloat() {
        float number;
        if (sscanf(data, "%f", &number) != 1) {
            throw std::invalid_argument("number convertion failed");
        }

        return number;
    }

    double String::toDouble() {
        double number;
        if (sscanf(data, "%lf", &number) != 1) {
            throw std::invalid_argument("number convertion failed");
        }

        return number;
    }

    size_t String::getSize() const {
        return size;
    }

    size_t String::getCapacity() const {
        return capacity;
    }

    std::string String::toString() const {
        std::string result;

        for (int i = 0; i < size; i++) {
            result += data[i];
        }

        return result;
    }

    char* String::toCharArray() const {
        return data;
    }
}