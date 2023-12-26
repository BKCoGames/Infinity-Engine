//
// Created by soulk on 12/26/2023.
//

#include "IOManager.h"
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <core/CoreIncludes.h>

bool IOManager::WriteBinaryFile(const std::string& FilePath, const char* Data, long long InLength, bool bIsRelative)
{
    // TODO: Check if relative path and absolute path both work and the bool param is needed
    boost::filesystem::path FilePathObj(FilePath);
    boost::filesystem::ofstream FileStream(FilePathObj, std::ios::out | std::ios::binary);
    if (!FileStream)
    {
        // Failed to open file
        IE_LOG_FMT(ELogVerbosity::Warning, "Failed to open filestream for writing binary: %1%", FilePath);
        return false;
    }

    FileStream.write(Data, InLength);
    FileStream.close();

    return true;
}

bool IOManager::ReadBinaryFile(const std::string& FilePath, std::unique_ptr<char[]>& OutData, long long& OutLength, bool bIsRelative)
{
    boost::filesystem::path FilePathObj(FilePath);
    boost::filesystem::ifstream FileStream(FilePathObj, std::ios::in | std::ios::binary);
    if (!FileStream)
    {
        // Failed to open file
        IE_LOG_FMT(ELogVerbosity::Warning, "Failed to open filestream for reading binary: %1%", FilePath);
        return false;
    }

    // Get the size of the file
    FileStream.seekg(0, std::ios::end);
    OutLength = FileStream.tellg();
    FileStream.seekg(0, std::ios::beg);

    // Allocate memory for the buffer
    OutData.reset(new char[OutLength]);

    // Read the file data
    if (!FileStream.read(OutData.get(), OutLength)) {
        // Failed to read file
        IE_LOG_FMT(ELogVerbosity::Warning, "Failed to read the binary file: %1%", FilePath);
        return false;
    }

    return true;
}

IOManager* IOManager::Initialize()
{
    IE_ASSERT_MSG(IOManagerInstance == nullptr, "Multiple IOManager::Initialize() calls detected! IOManager is already initialized!"); // Does not trigger in release build
    if (IOManagerInstance != nullptr)
    {
        IE_LOG_FMT(ELogVerbosity::Warning, "Multiple IOManager::Initialize() calls detected! IOManager is already initialized!");
        return IOManagerInstance;
    }
    IOManagerInstance = new IOManager();

    return IOManagerInstance;
}
