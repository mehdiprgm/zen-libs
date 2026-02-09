#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include <algorithm>
#include <sstream>
#include <string>

#include "CountItem.h"

using namespace std;

/**
 * @namespace zen::file::text
 * @brief Text file manipulation utilities within the Zen framework.
 * 
 * This namespace provides a comprehensive set of tools for reading, writing,
 * and analyzing text files. It encapsulates file operations with proper
 * resource management and error handling.
 */
namespace zen::file::text {
    
    /**
     * @class TextFile
     * @brief Represents a text file with comprehensive read/write operations.
     * 
     * The TextFile class provides a high-level interface for text file manipulation,
     * including reading content, writing data, searching within files, and
     * statistical analysis. It implements RAII principles for automatic resource
     * management and supports both synchronous and memory-efficient operations.
     * 
     * @note This class is not thread-safe. External synchronization is required
     *       for concurrent access to the same file.
     * 
     * @example
     * @code
     * TextFile file("data.txt");
     * string content = file.read();
     * size_t lineCount = file.count(CountItem::LINES);
     * @endcode
     */
    class TextFile {
    private:
        string filePath;  ///< Absolute or relative path to the text file

        /**
         * @brief Creates an input stream for reading from the file.
         * 
         * @return unique_ptr<ifstream> Smart pointer to the input stream.
         * 
         * @exception std::runtime_error Thrown if the file cannot be opened for reading.
         * 
         * @note The caller is responsible for the stream's lifecycle. The stream
         *       will be automatically closed when the unique_ptr is destroyed.
         */
        unique_ptr<ifstream> createInputStream();
        
        /**
         * @brief Creates an output stream for writing to the file.
         * 
         * @param append If true, opens the file in append mode; otherwise truncates.
         * @return unique_ptr<ofstream> Smart pointer to the output stream.
         * 
         * @exception std::runtime_error Thrown if the file cannot be opened for writing.
         * 
         * @note In append mode, new content is added to the end of the file without
         *       affecting existing content.
         */
        unique_ptr<ofstream> createOutputStream(bool append = false);
        
    public:
        /**
         * @brief Constructs a TextFile object for the specified file.
         * 
         * @param filePath Path to the text file. Can be absolute or relative.
         * 
         * @note The file is not automatically opened during construction.
         *       Files are opened on-demand for each operation.
         * 
         * @warning The file path is stored but not validated until an I/O operation
         *          is attempted.
         */
        TextFile(const string& filePath);

        /**
         * @brief Reads the entire content of the file into a string.
         * 
         * @return string The complete content of the file.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * @exception std::bad_alloc Thrown if memory allocation fails for large files.
         * 
         * @note This method loads the entire file into memory. For very large files,
         *       consider using readAllLines() or streaming approaches.
         * 
         * @see readAllLines()
         */
        string read();
        
        /**
         * @brief Reads only the first line from the file.
         * 
         * @return string The first line of the file, or empty string if file is empty.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * 
         * @note Leading and trailing whitespace is preserved in the returned string.
         *       Empty lines are returned as empty strings.
         */
        string readFirstLine();
        
        /**
         * @brief Reads only the last line from the file.
         * 
         * @return string The last line of the file, or empty string if file is empty.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * 
         * @note This method efficiently reads the last line without loading the
         *       entire file into memory for large files.
         */
        string readLastLine();

        /**
         * @brief Reads all lines from the file into a vector.
         * 
         * @return vector<string> Vector containing all lines from the file.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * @exception std::bad_alloc Thrown if memory allocation fails for large files.
         * 
         * @note Each element in the vector represents one line from the file,
         *       with newline characters removed. Empty lines are included as
         *       empty strings in the vector.
         */
        vector<string> readAllLines();

        /**
         * @brief Writes content to the file.
         * 
         * @param content The string content to write to the file.
         * @param append If true, appends content; otherwise overwrites the file.
         * @return bool True if write operation succeeded, false otherwise.
         * 
         * @note When append is false, the entire file content is replaced.
         *       When append is true, content is added to the end of existing content.
         * 
         * @see clear()
         */
        bool write(const string& content, bool append = false);
        
        /**
         * @brief Clears all content from the file.
         * 
         * @return bool True if the file was successfully cleared, false otherwise.
         * 
         * @note This operation effectively truncates the file to zero length.
         *       The file remains open and available for subsequent operations.
         * 
         * @see write()
         */
        bool clear();

        /**
         * @brief Searches for a key within the file content.
         * 
         * @param key The string to search for.
         * @param isCaseSensitive If true, performs case-sensitive search; otherwise case-insensitive.
         * @param findWholeWord If true, matches only whole words; otherwise matches substrings.
         * @return size_t The position (byte offset) of the first occurrence, or string::npos if not found.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * 
         * @note For whole word matching, a word is defined as a sequence of characters
         *       delimited by whitespace or punctuation. The search returns the byte
         *       position in the file where the match begins.
         * 
         * @see count()
         */
        size_t find(const string& key, bool isCaseSensitive, bool findWholeWord);
        
        /**
         * @brief Counts specific items in the file based on the CountItem enumeration.
         * 
         * @param item The type of item to count (e.g., lines, words, characters).
         * @return size_t The count of the specified items in the file.
         * 
         * @exception std::runtime_error Thrown if the file cannot be read.
         * @exception std::invalid_argument Thrown if the CountItem value is not supported.
         * 
         * @note Supported CountItem values are defined in the CountItem enumeration.
         *       This method may load the entire file into memory depending on the
         *       counting operation.
         * 
         * @see CountItem
         */
        size_t count(CountItem item);
    };
}