#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include "StringOperation.h"

using std::cout, std::cin, std::endl;

namespace zen::corex {
    /**
     * @brief A dynamic string class with automatic memory management
     * 
     * The String class provides a flexible and efficient string container that
     * dynamically manages memory and offers a wide range of string manipulation
     * operations. It features:
     * - Dynamic memory management with automatic resizing
     * - Construction from various string types (String, std::string, C-string)
     * - Comprehensive operator overloads for intuitive usage
     * - Case conversion utilities
     * - Search and replacement operations
     * - Type conversion utilities (numeric conversions)
     * - Validation methods (blank, number, text checks)
     * 
     * Example usage:
     * @code
     * zen::corex::String str1("Hello");
     * zen::corex::String str2(" World");
     * str1 += str2;                    // str1 = "Hello World"
     * str1.toUpperCase();               // str1 = "HELLO WORLD"
     * int len = str1.getSize();         // len = 11
     * bool isNum = str1.isNumber();     // false
     * @endcode
     */
    class String {
        private:
            /** @brief Default capacity for new strings (32 characters) */
            const size_t DEFAULT_CAPACITY = 32;
            
            /** @brief Pointer to dynamically allocated character array */
            char* data;
            
            /** @brief Current length of the string (excluding null terminator) */
            size_t size;
            
            /** @brief Current allocated capacity (including space for null terminator) */
            size_t capacity;

            /**
             * @brief Internal helper method to initialize string from std::string
             * @param input Source string to initialize from
             */
            void initialize(const std::string& input);

        public:
            /**
             * @brief Constructs an empty string
             * 
             * Creates an empty string with default capacity.
             * @post size == 0 && capacity == DEFAULT_CAPACITY
             */
            String();

            /**
             * @brief Copy constructor
             * @param input Source string to copy from
             * 
             * Creates a deep copy of the source string.
             * @complexity O(n) where n is the length of the input string
             */
            String(const String& input);

            /**
             * @brief Constructs a string from std::string
             * @param input Source std::string to copy from
             * 
             * Creates a deep copy of the source std::string.
             * @complexity O(n) where n is the length of the input string
             */
            String(const std::string& input);

            /**
             * @brief Constructs a string from a C-style string
             * @param input Source C-string to copy from (null-terminated)
             * 
             * Creates a deep copy of the source C-string.
             * @complexity O(n) where n is the length of the input string
             */
            String(const char* input);

            /**
             * @brief Destructor
             * 
             * Releases dynamically allocated memory.
             */
            ~String();

            /**
             * @brief Copy assignment from String
             * @param input Source string to copy from
             * @return String& Reference to this string after assignment
             * 
             * Performs a deep copy of the source string.
             * @complexity O(n) where n is the length of the input string
             */
            String& operator=(const String& input);

            /**
             * @brief Copy assignment from std::string
             * @param input Source std::string to copy from
             * @return String& Reference to this string after assignment
             * 
             * Performs a deep copy of the source std::string.
             * @complexity O(n) where n is the length of the input string
             */
            String& operator=(const std::string& input);

            /**
             * @brief Copy assignment from C-string
             * @param input Source C-string to copy from (null-terminated)
             * @return String& Reference to this string after assignment
             * 
             * Performs a deep copy of the source C-string.
             * @complexity O(n) where n is the length of the input string
             */
            String& operator=(const char* input);

            /**
             * @brief In-place concatenation with String
             * @param input String to append
             * @return String& Reference to this string after concatenation
             * 
             * Appends the content of another String to the end of this string.
             * Automatically resizes if necessary.
             * @complexity O(n + m) where n and m are the lengths of the strings
             */
            String& operator+=(const String& input);

            /**
             * @brief In-place concatenation with std::string
             * @param input std::string to append
             * @return String& Reference to this string after concatenation
             * 
             * Appends the content of a std::string to the end of this string.
             * Automatically resizes if necessary.
             * @complexity O(n + m) where n and m are the lengths of the strings
             */
            String& operator+=(const std::string& input);

            /**
             * @brief In-place concatenation with C-string
             * @param input C-string to append (null-terminated)
             * @return String& Reference to this string after concatenation
             * 
             * Appends the content of a C-string to the end of this string.
             * Automatically resizes if necessary.
             * @complexity O(n + m) where n and m are the lengths of the strings
             */
            String& operator+=(const char* input);

            /**
             * @brief Removes all occurrences of a substring (in-place)
             * @param input Substring to remove
             * @return String& Reference to this string after removal
             * 
             * Removes all occurrences of the specified substring from this string.
             * @complexity O(n * m) where n is string length and m is substring length
             */
            String& operator-=(const String& input);

            /**
             * @brief Removes all occurrences of a std::string substring (in-place)
             * @param input Substring to remove (as std::string)
             * @return String& Reference to this string after removal
             * 
             * Removes all occurrences of the specified substring from this string.
             * @complexity O(n * m) where n is string length and m is substring length
             */
            String& operator-=(const std::string& input);

            /**
             * @brief Removes all occurrences of a C-string substring (in-place)
             * @param input Substring to remove (as C-string)
             * @return String& Reference to this string after removal
             * 
             * Removes all occurrences of the specified substring from this string.
             * @complexity O(n * m) where n is string length and m is substring length
             */
            String& operator-=(const char* input);

            /**
             * @brief Equality comparison with String
             * @param input String to compare with
             * @return true If strings are identical
             * @return false Otherwise
             * @complexity O(n) where n is the length of the strings
             */
            bool operator==(const String& input) const;

            /**
             * @brief Equality comparison with std::string
             * @param input std::string to compare with
             * @return true If strings are identical
             * @return false Otherwise
             * @complexity O(n) where n is the length of the strings
             */
            bool operator==(const std::string& input) const;

            /**
             * @brief Equality comparison with C-string
             * @param input C-string to compare with (null-terminated)
             * @return true If strings are identical
             * @return false Otherwise
             * @complexity O(n) where n is the length of the strings
             */
            bool operator==(const char* input) const;

            /**
             * @brief Inequality comparison with String
             * @param input String to compare with
             * @return true If strings are different
             * @return false If strings are identical
             * @complexity O(n) where n is the length of the strings
             */
            bool operator!=(const String& input) const;

            /**
             * @brief Inequality comparison with std::string
             * @param input std::string to compare with
             * @return true If strings are different
             * @return false If strings are identical
             * @complexity O(n) where n is the length of the strings
             */
            bool operator!=(const std::string& input) const;

            /**
             * @brief Inequality comparison with C-string
             * @param input C-string to compare with (null-terminated)
             * @return true If strings are different
             * @return false If strings are identical
             * @complexity O(n) where n is the length of the strings
             */
            bool operator!=(const char* input) const;

            /**
             * @brief Accesses character at specified index (non-const)
             * @param index Position of the character to access (0-based)
             * @return char& Reference to the character at the specified index
             * @throws std::out_of_range if index is greater than or equal to size
             * @complexity O(1)
             */
            char& operator[](size_t index);

            /**
             * @brief Accesses character at specified index (const)
             * @param index Position of the character to access (0-based)
             * @return const char& Const reference to the character at the specified index
             * @throws std::out_of_range if index is greater than or equal to size
             * @complexity O(1)
             */
            const char& operator[](size_t index) const;

            /**
             * @brief Stream insertion operator
             * @param os Output stream
             * @param input String to output
             * @return std::ostream& Reference to the output stream
             * 
             * Allows direct output of String objects to streams.
             */
            friend std::ostream& operator<<(std::ostream& os, const String& input);

            /**
             * @brief Creates a deep copy of the string
             * @return String New string containing a copy of this string
             * @complexity O(n) where n is the length of the string
             */
            String copy();

            /**
             * @brief Appends another string to this string
             * @param input String to append
             * 
             * Appends the content of another String to the end of this string.
             * @complexity O(n + m) where n and m are the lengths of the strings
             */
            void append(const String& input);

            /**
             * @brief Removes all occurrences of a substring
             * @param input Substring to remove
             * 
             * Removes all occurrences of the specified substring from this string.
             * @complexity O(n * m) where n is string length and m is substring length
             */
            void remove(const String& input);

            /**
             * @brief Converts all characters to lowercase
             * 
             * Transforms all uppercase letters in the string to lowercase.
             * Non-alphabetic characters remain unchanged.
             * @complexity O(n)
             */
            void toLowerCase();

            /**
             * @brief Converts all characters to uppercase
             * 
             * Transforms all lowercase letters in the string to uppercase.
             * Non-alphabetic characters remain unchanged.
             * @complexity O(n)
             */
            void toUpperCase();

            /**
             * @brief Replaces all occurrences of a substring with another
             * @param oldStr Substring to be replaced
             * @param newStr Replacement substring
             * 
             * Replaces every occurrence of oldStr with newStr in the string.
             * @complexity O(n * m) where n is string length and m is pattern length
             */
            void replace(const String& oldStr, const String& newStr);

            /**
             * @brief Clears the string content
             * 
             * Resets the string to empty state.
             * @post size == 0
             */
            void clear();

            /**
             * @brief Reverses the string
             * 
             * Reverses the order of characters in the string.
             * @complexity O(n)
             */
            void reverse();

            /**
             * @brief Searches for a substring
             * @param input Substring to search for
             * @return int Index of first occurrence, or -1 if not found
             * @complexity O(n * m) where n is string length and m is substring length
             */
            int contains(const String& input);

            /**
             * @brief Checks if the string is empty
             * @return true If string has no characters (size == 0)
             * @return false If string contains at least one character
             * @complexity O(1)
             */
            bool isEmpty() const;

            /**
             * @brief Checks if the string is blank
             * @return true If string is empty or contains only whitespace
             * @return false If string contains non-whitespace characters
             * @complexity O(n)
             */
            bool isBlank() const;

            /**
             * @brief Checks if the string represents a valid number
             * @return true If string can be parsed as a number
             * @return false Otherwise
             * @complexity O(n)
             */
            bool isNumber() const;

            /**
             * @brief Checks if the string contains only text characters
             * @return true If string contains only alphabetic characters
             * @return false If string contains non-alphabetic characters
             * @complexity O(n)
             */
            bool isText() const;

            /**
             * @brief Converts string to short integer
             * @return short Numeric value
             * @throws std::invalid_argument if conversion fails
             * @complexity O(n)
             */
            short toShort();

            /**
             * @brief Converts string to integer
             * @return int Numeric value
             * @throws std::invalid_argument if conversion fails
             * @complexity O(n)
             */
            int toInt();

            /**
             * @brief Converts string to long integer
             * @return long Numeric value
             * @throws std::invalid_argument if conversion fails
             * @complexity O(n)
             */
            long toLong();

            /**
             * @brief Converts string to float
             * @return float Numeric value
             * @throws std::invalid_argument if conversion fails
             * @complexity O(n)
             */
            float toFloat();

            /**
             * @brief Converts string to double
             * @return double Numeric value
             * @throws std::invalid_argument if conversion fails
             * @complexity O(n)
             */
            double toDouble();

            /**
             * @brief Returns the current length of the string
             * @return size_t Number of characters in the string
             * @complexity O(1)
             */
            size_t getSize() const;

            /**
             * @brief Returns the current capacity of the string
             * @return size_t Total allocated capacity (including null terminator)
             * @complexity O(1)
             */
            size_t getCapacity() const;

            /**
             * @brief Converts to std::string
             * @return std::string Copy of the string content
             * @complexity O(n)
             */
            std::string toString() const;

            /**
             * @brief Converts to C-style string
             * @return char* Dynamically allocated copy of the string content
             * @note Caller is responsible for deleting the returned array
             * @complexity O(n)
             */
            char* toCharArray() const;
    };
}