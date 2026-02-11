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

#include "SystemTime.h"

using namespace std;

namespace zen::sys {
    struct SystemInfo {
        string name;
        string kernelModel;
        string architecture;

        string username;
        string hostName;

        string homeDirectory;
        string executePath;
    };

    struct CPUInfo {
        string vendorId;
        string modelName;
        string microcode;

        int virtualCores;
        int physicalCores;
        int model;
        int stepping;
    };

    struct MemoryInfo {
        size_t totalSpace;
        size_t freeSpace;

        size_t buffers;
        size_t cahced;

        size_t swapTotalSpace;
        size_t swapFreeSpace;
        size_t swapCached;
    };

    SystemInfo readSystemInfo();
    CPUInfo readCpuInfo();
    MemoryInfo readMemoryInfo();

    void copyText(const string& text);

    string getTimeDate(SystemTime sysTime);
    string pasteFromClipboard();

    bool openFile(const string& path);
}