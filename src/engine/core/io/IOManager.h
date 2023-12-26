//
// Created by KiiroiSenko on 12/26/2023.
//

#pragma once

#include <string>
#include <memory>

class IOManager final
{

public:
    static IOManager* Initialize();

    static bool ReadBinaryFile(const std::string& FilePath, std::unique_ptr<char[]>& OutData, long long& OutLength, bool bIsRelative);

    static bool WriteBinaryFile(const std::string& FilePath, const char* Data, long long InLength, bool bIsRelative);


private:
    inline static IOManager* IOManagerInstance = nullptr;

    IOManager()  = default;
    ~IOManager() = default;
};
