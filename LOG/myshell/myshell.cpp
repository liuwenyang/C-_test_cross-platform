#include "myshell.h"

namespace ai_matrix
{
    const int TIME_SIZE = 32;
    const int TIME_DIFF = 28800; // 8 hour
    std::mutex MyShell::mutex;
    uint32_t MyShell::shellLevel = SHELL_LEVEL_INFO;
    std::vector<std::string> MyShell::levelString{"[Debug]", "[Info ]", "[Warn ]", "[Error]", "[Fatal]"};

    MyShell::MyShell(std::string file, std::string function, int line, uint32_t level)
        : myLevel_(level), file_(file), function_(function), line_(line)
    {
    }

    MyShell::~MyShell()
    {
        if (myLevel_ >= shellLevel)
        {
            std::lock_guard<std::mutex> locker(mutex);
            // cout to screen
            std::cout << ss_.str() << std::endl;
        }
    };

    std::ostringstream &MyShell::Stream()
    {
        if (myLevel_ >= shellLevel)
        {
            struct timeval time = {0, 0};
            gettimeofday(&time, nullptr);
            time_t timep = time.tv_sec + TIME_DIFF; //加上8小时
            struct tm *ptm = gmtime(&timep);        //返回tm结构的格林尼治时间（GMT）
            char timeString[TIME_SIZE] = {0};
            //%F 年-月-日 %X 标准的时间串
            strftime(timeString, TIME_SIZE, "[%F %X:", ptm);
            long int usValue = time.tv_usec;

            date_ = timeString;
            ss_.fill('0');
            ss_ << levelString[myLevel_] << timeString << std::setw(3) << usValue / 1000 << "]";

            std::string fileName = file_.substr(file_.rfind('/') + 1);
            ss_ << "[" << fileName << " " << function_ << ":" << line_ << "] ";
        }
        return ss_;
    }

    void MyShell::ShellDebugOn()
    {
        shellLevel = SHELL_LEVEL_DEBUG;
        return;
    }
    void MyShell::ShellInfoOn()
    {
        shellLevel = SHELL_LEVEL_INFO;
        return;
    }
    void MyShell::ShellWarnOn()
    {
        shellLevel = SHELL_LEVEL_WARN;
        return;
    }
    void MyShell::ShellErrorOn()
    {
        shellLevel = SHELL_LEVEL_ERROR;
        return;
    }
    void MyShell::ShellFatalOn()
    {
        shellLevel = SHELL_LEVEL_FATAL;
        return;
    }
    void MyShell::ShellAllOn()
    {
        shellLevel = SHELL_LEVEL_DEBUG;
        return;
    }
    void MyShell::ShellAllOff()
    {
        shellLevel = SHELL_LEVEL_NONE;
        return;
    }
} // namespace matrix_common