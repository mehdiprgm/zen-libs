#include "System.h"

namespace zen::sys {

    SystemInfo readSystemInfo() {
        struct utsname sysInfo;
        struct passwd *passwd;

        SystemInfo systemInfo;

        uname(&sysInfo);
        passwd = getpwuid(getuid());

        systemInfo.name = string(sysInfo.sysname);
        systemInfo.kernelModel = string(sysInfo.release);
        systemInfo.architecture = string(sysInfo.machine);

        if (passwd) {
            systemInfo.username = passwd->pw_name;
            systemInfo.homeDirectory = passwd->pw_dir;
        } else {
            char* username = getenv("USER");
            char* home = getenv("HOME");
            char cwd[1024];

            systemInfo.username = username ? username : "ERROR";
            systemInfo.homeDirectory = home ? home : "ERROR";

            getcwd(cwd, sizeof(cwd));
            systemInfo.executePath = string(cwd);
        }

        systemInfo.hostName = sysInfo.nodename;
        return systemInfo;
    }

    CPUInfo readCpuInfo() {
        CPUInfo cpuInfo;

        ifstream file("/proc/cpuinfo");
        if (!file.is_open()) {
            throw runtime_error("Can't read cpu file from /proc/cpuinfo");
        }

        string line;
        int virtualCores = 0;

        while (getline(file, line)) {
            size_t pos = line.find(":");

            if (line.find("model name") != string::npos) {
                cpuInfo.modelName = line.substr(pos + 2);
            }

            if (line.find("model") != string::npos) {
                cpuInfo.model = stoi(line.substr(pos + 2));
            }

            if (line.find("stepping") != string::npos) {
                cpuInfo.stepping = stoi(line.substr(pos + 2));
            }

            if (line.find("cpu cores") != string::npos) {
                cpuInfo.physicalCores = stoi(line.substr(pos + 2));
            }

            if (line.find("microcode") != string::npos) {
                cpuInfo.microcode = line.substr(pos + 2);
            }
            
            if (line.find("processor") != string::npos) {
                virtualCores++;
            }

            if (line.find("vendor_id") != string::npos) {
                cpuInfo.vendorId = line.substr(pos + 2);
            }
        }

        cpuInfo.virtualCores = virtualCores;
        return cpuInfo;
    }

    MemoryInfo readMemoryInfo() {
        MemoryInfo memoryInfo;

        ifstream file("/proc/meminfo");
        if (!file.is_open()) {
            throw runtime_error("Can't read memory file from /proc/meminfo");
        }

        string line;

        while (getline(file, line)) {
            size_t pos = line.find(":");

            if (line.find("MemTotal") != string::npos) {
                memoryInfo.totalSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("MemFree") != string::npos) {
                memoryInfo.freeSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("Buffers") != string::npos) {
                memoryInfo.buffers = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("Cached") != string::npos) {
                memoryInfo.cahced = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapTotal") != string::npos) {
                memoryInfo.swapTotalSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapFree") != string::npos) {
                memoryInfo.swapFreeSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapCached") != string::npos) {
                memoryInfo.swapCached = stol(line.substr(pos + 2)) * 1024;
            }
        }

        return memoryInfo;
    }

    void copyText(const string& text) {
        string command = "echo \"" + text + "\" | xclip -selection clipboard";
        system(command.c_str());
    }

    string getTimeDate(SystemTime sysTime) {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        char buffer[21];

        switch(sysTime) {
            case SystemTime::Time:
                strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
                break;

            case SystemTime::Date:
                strftime(buffer, sizeof(buffer), "%Y/%m/%d", localTime);
                break;

            case SystemTime::Both:
                strftime(buffer, sizeof(buffer), "%H:%M:%S %Y/%m/%d", localTime);
                break;
        }

        return buffer;
    }

    string pasteFromClipboard() {
        const char* command = "xclip -selection clipboard -o 2>/dev/null";
        FILE *fp = popen(command, "r");

        if (!fp) {
            throw runtime_error("Failed to open pipe to xclip\n");
        }
    
        array<char, 4096> buffer{};
        string result;
    
        while (fgets(buffer.data(), buffer.size(), fp)) {
            result += buffer.data();
        }
    
        if (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }
    
        pclose(fp);
        return result;
    }

    bool openFile(const string& path) {
        string command = "xdg-open \"" + path + "\"";
        return system(command.c_str()) == 0;
    }
}