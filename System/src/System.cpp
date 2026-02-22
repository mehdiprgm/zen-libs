#include "System.h"

namespace zen::sys {

    SystemInfo readSystemInfo() {
        struct utsname sysInfo;
        struct passwd *passwd;

        SystemInfo systemInfo;

        uname(&sysInfo);
        passwd = getpwuid(getuid());

        systemInfo.name = std::string(sysInfo.sysname);
        systemInfo.kernelModel = std::string(sysInfo.release);
        systemInfo.architecture = std::string(sysInfo.machine);

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
            systemInfo.executePath = std::string(cwd);
        }

        systemInfo.hostName = sysInfo.nodename;
        return systemInfo;
    }

    CPUInfo readCpuInfo() {
        CPUInfo cpuInfo;

        std::ifstream file("/proc/cpuinfo");
        if (!file.is_open()) {
            throw std::runtime_error("Can't read cpu file from /proc/cpuinfo");
        }

        std::string line;
        int virtualCores = 0;

        while (getline(file, line)) {
            size_t pos = line.find(":");

            if (line.find("model name") != std::string::npos) {
                cpuInfo.modelName = line.substr(pos + 2);
            }

            if (line.find("model") != std::string::npos) {
                cpuInfo.model = stoi(line.substr(pos + 2));
            }

            if (line.find("stepping") != std::string::npos) {
                cpuInfo.stepping = stoi(line.substr(pos + 2));
            }

            if (line.find("cpu cores") != std::string::npos) {
                cpuInfo.physicalCores = stoi(line.substr(pos + 2));
            }

            if (line.find("microcode") != std::string::npos) {
                cpuInfo.microcode = line.substr(pos + 2);
            }
            
            if (line.find("processor") != std::string::npos) {
                virtualCores++;
            }

            if (line.find("vendor_id") != std::string::npos) {
                cpuInfo.vendorId = line.substr(pos + 2);
            }
        }

        cpuInfo.virtualCores = virtualCores;
        return cpuInfo;
    }

    MemoryInfo readMemoryInfo() {
        MemoryInfo memoryInfo;

        std::ifstream file("/proc/meminfo");
        if (!file.is_open()) {
            throw std::runtime_error("Can't read memory file from /proc/meminfo");
        }

        std::string line;

        while (getline(file, line)) {
            size_t pos = line.find(":");

            if (line.find("MemTotal") != std::string::npos) {
                memoryInfo.totalSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("MemFree") != std::string::npos) {
                memoryInfo.freeSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("Buffers") != std::string::npos) {
                memoryInfo.buffers = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("Cached") != std::string::npos) {
                memoryInfo.cached = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapTotal") != std::string::npos) {
                memoryInfo.swapTotalSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapFree") != std::string::npos) {
                memoryInfo.swapFreeSpace = stol(line.substr(pos + 2)) * 1024;
            }

            if (line.find("SwapCached") != std::string::npos) {
                memoryInfo.swapCached = stol(line.substr(pos + 2)) * 1024;
            }
        }

        return memoryInfo;
    }

    void copyText(const std::string& text) {
        std::string command = "echo \"" + text + "\" | xclip -selection clipboard";
        system(command.c_str());
    }

    std::string getTimeDate(TimeFormat timeFormat) {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        char buffer[21];

        switch(timeFormat) {
            case TimeFormat::Time:
                strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
                break;

            case TimeFormat::Date:
                strftime(buffer, sizeof(buffer), "%Y/%m/%d", localTime);
                break;

            case TimeFormat::Both:
                strftime(buffer, sizeof(buffer), "%H:%M:%S %Y/%m/%d", localTime);
                break;
        }

        return buffer;
    }

    std::string pasteFromClipboard() {
        const char* command = "xclip -selection clipboard -o 2>/dev/null";
        FILE *fp = popen(command, "r");

        if (!fp) {
            throw std::runtime_error("Failed to open pipe to xclip\n");
        }
    
        std::array<char, 4096> buffer{};
        std::string result;
    
        while (fgets(buffer.data(), buffer.size(), fp)) {
            result += buffer.data();
        }
    
        if (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }
    
        pclose(fp);
        return result;
    }

    bool openFile(const std::string& path) {
        std::string command = "xdg-open \"" + path + "\"";
        return system(command.c_str()) == 0;
    }
}