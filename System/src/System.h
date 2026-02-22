#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <locale.h>
#include <array>
#include <span>
#include <format>

#include "TimeFormat.h"

using std::cout, std::cin, std::endl;

namespace zen::sys {

    /**
     * @brief Operating system and environment information
     * 
     * Contains details about the operating system, kernel, user environment,
     * and execution context.
     */
    struct SystemInfo {
        /** @brief Operating system name (e.g., "Linux", "Windows", "macOS") */
        std::string name;
        
        /** @brief Kernel version or model (e.g., "6.1.0-15-amd64") */
        std::string kernelModel;
        
        /** @brief System architecture (e.g., "x86_64", "arm64", "i386") */
        std::string architecture;

        /** @brief Current username of the logged-in user */
        std::string username;
        
        /** @brief Network hostname of the system */
        std::string hostName;

        /** @brief Path to the user's home directory */
        std::string homeDirectory;
        
        /** @brief Path to the currently executing program */
        std::string executePath;
    };

    /**
     * @brief Central Processing Unit (CPU) information
     * 
     * Contains detailed information about the system's processor(s),
     * including vendor, model, core counts, and revision data.
     */
    struct CPUInfo {
        /** @brief CPU vendor identifier (e.g., "GenuineIntel", "AuthenticAMD") */
        std::string vendorId;
        
        /** @brief Full model name of the CPU (e.g., "Intel Core i7-10750H") */
        std::string modelName;
        
        /** @brief Microcode version/identifier */
        std::string microcode;

        /** @brief Number of logical/virtual cores (including hyper-threading) */
        int virtualCores;
        
        /** @brief Number of physical cores (actual hardware cores) */
        int physicalCores;
        
        /** @brief CPU model number (typically from CPUID) */
        int model;
        
        /** @brief CPU stepping/revision number */
        int stepping;
    };

    /**
     * @brief System memory (RAM) and swap information
     * 
     * Contains details about physical memory usage, buffers,
     * cache, and swap space utilization.
     * 
     * @note All sizes are in bytes
     */
    struct MemoryInfo {
        /** @brief Total physical RAM installed in the system */
        size_t totalSpace;
        
        /** @brief Currently free/unused physical RAM */
        size_t freeSpace;

        /** @brief Memory used for file buffers */
        size_t buffers;
        
        /** @brief Memory used for cached files */
        size_t cached;

        /** @brief Total swap space available */
        size_t swapTotalSpace;
        
        /** @brief Currently free/unused swap space */
        size_t swapFreeSpace;
        
        /** @brief Memory that has been swapped out and cached */
        size_t swapCached;
    };

    /**
     * @brief Copies text to the system clipboard
     * 
     * Places the specified text into the system's clipboard buffer,
     * making it available for paste operations in other applications.
     * 
     * @param text The text content to copy to clipboard
     * 
     * Example usage:
     * @code
     * zen::sys::copyText("Hello, World!");
     * // User can now paste "Hello, World!" in other applications
     * @endcode
     */
    void copyText(const std::string& text);

    /**
     * @brief Opens a file with the system's default application
     * 
     * Attempts to open the specified file using the operating system's
     * default associated application for that file type.
     * 
     * @param path Path to the file to open (absolute or relative)
     * @return true if the file was successfully opened
     * @return false if the file could not be opened (file doesn't exist, no default application, etc.)
     * 
     * Example usage:
     * @code
     * if (zen::sys::openFile("document.pdf")) {
     *     std::cout << "PDF opened successfully" << std::endl;
     * }
     * @endcode
     */
    bool openFile(const std::string& path);

    /**
     * @brief Retrieves comprehensive system information
     * 
     * Gathers information about the operating system, kernel,
     * user environment, and execution context.
     * 
     * @return SystemInfo Structure containing system details
     * 
     * Example usage:
     * @code
     * auto sysInfo = zen::sys::readSystemInfo();
     * std::cout << "Running on: " << sysInfo.name << std::endl;
     * std::cout << "User: " << sysInfo.username << "@" << sysInfo.hostName << std::endl;
     * @endcode
     */
    SystemInfo readSystemInfo();

    /**
     * @brief Retrieves detailed CPU information
     * 
     * Gathers information about the system's processor(s),
     * including vendor, model, core counts, and revision data.
     * 
     * @return CPUInfo Structure containing CPU details
     * 
     * Example usage:
     * @code
     * auto cpuInfo = zen::sys::readCpuInfo();
     * std::cout << "CPU: " << cpuInfo.modelName << std::endl;
     * std::cout << "Cores: " << cpuInfo.physicalCores << " physical, "
     *           << cpuInfo.virtualCores << " virtual" << std::endl;
     * @endcode
     */
    CPUInfo readCpuInfo();

    /**
     * @brief Retrieves system memory information
     * 
     * Gathers current statistics about RAM usage, buffers,
     * cache, and swap space utilization.
     * 
     * @return MemoryInfo Structure containing memory details (sizes in bytes)
     * 
     * Example usage:
     * @code
     * auto memInfo = zen::sys::readMemoryInfo();
     * double usedPercent = 100.0 * (memInfo.totalSpace - memInfo.freeSpace) / memInfo.totalSpace;
     * std::cout << "Memory usage: " << usedPercent << "%" << std::endl;
     * @endcode
     */
    MemoryInfo readMemoryInfo();

    /**
     * @brief Retrieves current system time and date
     * 
     * Returns the current system time and date in the specified format.
     * 
     * @param timeFormat The desired format for the date/time string
     * @return std::string Formatted date and time string
     * 
     * Available formats:
     * - TimeFormat::Date: "2023-12-25"
     * - TimeFormat::Time: "14:30:45"
     * - TimeFormat::Both: "2023-12-25 14:30:45"
     * 
     * Example usage:
     * @code
     * std::string timestamp = zen::sys::getTimeDate(TimeFormat::Both);
     * std::string filename = "backup_" + timestamp + ".zip";
     * @endcode
     */
    std::string getTimeDate(TimeFormat timeFormat);

    /**
     * @brief Retrieves text from the system clipboard
     * 
     * Reads the current contents of the system clipboard and returns it
     * as a string. If the clipboard is empty or contains non-text data,
     * returns an empty string.
     * 
     * @return std::string The text content currently in the clipboard
     * 
     * Example usage:
     * @code
     * std::string clipboardContent = zen::sys::pasteFromClipboard();
     * if (!clipboardContent.empty()) {
     *     std::cout << "Clipboard contains: " << clipboardContent << std::endl;
     * }
     * @endcode
     */
    std::string pasteFromClipboard();
}