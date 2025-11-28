/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Output.h
 * @brief Logging infrastructure using spdlog
 *
 * Centralized logging with console and file sinks.
 *
 * **Output Class:**
 * - outputCritical/Error/Warning/Info/Debug/Trace(): Log methods
 * - setLogLevels(): Configure console and file verbosity
 * - setConsoleSink(): Custom console output
 * - setFileSink(): Enable file logging
 *
 * **E_LogLevel (Enums.h):**
 * - Off, Critical, Error, Warning, Info, Debug, Trace
 *
 * **OutputStream Class:**
 * - std::ostream wrapper for solver output redirection
 * - Routes external solver output through SHOT logging
 * - Used by CPLEX, Gurobi, Ipopt adapters
 *
 * **Implementation:**
 * - Uses spdlog library for fast, thread-safe logging
 * - consoleSink: stdout sink
 * - fileSink: basic_file_sink for persistence
 *
 * @see Environment.h for Output access
 */
#pragma once
#include "Enums.h"
#include "Structs.h"
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace SHOT
{

class DllExport Output
{
public:
    Output();
    virtual ~Output();

    void outputCritical(std::string message);
    void outputError(std::string message);
    void outputError(std::string message, std::string errormessage);
    void outputWarning(std::string message);
    void outputInfo(std::string message);
    void outputDebug(std::string message);
    void outputTrace(std::string message);

    void setLogLevels(E_LogLevel consoleLogLevel, E_LogLevel fileLogLevel);

    void setConsoleSink(std::shared_ptr<spdlog::sinks::sink> newSink);

    void setFileSink(std::string filename);

    void flush() { logger->flush(); }

    void setPrefix(std::string prefix);

private:
    std::shared_ptr<spdlog::sinks::sink> consoleSink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_st> fileSink;

    std::shared_ptr<spdlog::logger> logger;
};

class Environment;
using EnvironmentPtr = std::shared_ptr<Environment>;

class OutputStream : public std::streambuf, public std::ostream
{
private:
    EnvironmentPtr env;
    std::stringstream ss;
    E_LogLevel logLevel;

public:
    OutputStream(EnvironmentPtr envPtr, E_LogLevel logLevel) : std::ostream(this), env(envPtr), logLevel(logLevel) { }

    int overflow(int c = std::istream::traits_type::eof());
};
}