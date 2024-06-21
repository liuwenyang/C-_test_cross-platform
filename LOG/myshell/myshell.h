#ifndef MYSHELL_H
#define MYSHELL_H

#include <mutex>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/time.h>
#include <vector>

namespace ai_matrix
{
    // shell level
    enum ShellLevels
    {
        SHELL_LEVEL_DEBUG = 0,
        SHELL_LEVEL_INFO = 1,
        SHELL_LEVEL_WARN = 2,
        SHELL_LEVEL_ERROR = 3,
        SHELL_LEVEL_FATAL = 4,
        SHELL_LEVEL_NONE
    };

    class MyShell final
    {
    public:
        MyShell(std::string file, std::string function, int line, uint32_t level);
        ~MyShell();
        std::ostringstream &Stream();

        static void ShellDebugOn();
        static void ShellInfoOn();
        static void ShellWarnOn();
        static void ShellErrorOn();
        static void ShellFatalOn();
        static void ShellAllOn();
        static void ShellAllOff();

    private:
        std::ostringstream ss_;
        uint32_t myLevel_;
        std::string date_;
        std::string file_;
        std::string function_;
        int line_;

        static uint32_t shellLevel;
        static std::vector<std::string> levelString;
        static std::mutex mutex;
    };
} // namespace ai_matrix

#define MyShellDebug ai_matrix::MyShell(__FILE__, __FUNCTION__, __LINE__, ai_matrix::SHELL_LEVEL_DEBUG).Stream()
#define MyShellInfo ai_matrix::MyShell(__FILE__, __FUNCTION__, __LINE__, ai_matrix::SHELL_LEVEL_INFO).Stream()
#define MyShellWarn ai_matrix::MyShell(__FILE__, __FUNCTION__, __LINE__, ai_matrix::SHELL_LEVEL_WARN).Stream()
#define MyShellError ai_matrix::MyShell(__FILE__, __FUNCTION__, __LINE__, ai_matrix::SHELL_LEVEL_ERROR).Stream()
#define MyShellFatal ai_matrix::MyShell(__FILE__, __FUNCTION__, __LINE__, ai_matrix::SHELL_LEVEL_FATAL).Stream()

#endif