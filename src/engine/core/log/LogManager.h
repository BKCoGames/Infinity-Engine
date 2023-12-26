//
// Created by KiiroiSenko on 12/26/2023.
//

#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <string>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/variadic/size.hpp>

enum class ELogVerbosity
{
    Log,
    Warning,
    Error,
    Critical,
};

class LogManager
{
public:

    /**
     * @brief Writes a log to the console
     * @param verbosity The verbosity of the log
     * @param Format The format of the log. Accepts std::string only. Should be formatted like this: "Hello %1% %2% %3%" (uses boost::format atm)
     * @param Arguments The arguments to the format
     */
    template<typename T, typename... Args, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::string>>>
    static void WriteLog(ELogVerbosity verbosity, T&& Format, Args... Arguments)
    {
        std::cout << (boost::format(std::forward<T>(Format)) % ... % std::forward<Args>(Arguments)).str() << IE_LB;
    }

    /**
     * @brief Writes a log to the console. No formatting arg version
     * @param verbosity The verbosity of the log
     * @param Format The format of the log. Accepts std::string only. Should be formatted like this: "Hello %1% %2% %3%" (uses boost::format atm)
     * @param Arguments The arguments to the format
     */
    template<typename T, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::string>>>
    static void WriteLog(ELogVerbosity verbosity, T&& Format)
    {
        std::cout << std::forward<T>(Format) << std::endl;
    }
};

#define IE_LOG_FMT(Verbosity, Format, ...) \
    LogManager::WriteLog(Verbosity, Format __VA_OPT__(,) __VA_ARGS__)
