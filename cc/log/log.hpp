#ifndef _LOG_H_
#define _LOG_H_
#include <iostream>
#include <chrono>
#include <sstream>
#include <thread>
#include <sstream>
#include <fstream>


enum class LogMode:int8_t {
    kOff  = 1,
    kConsole = 2,
    kFile = 3
};

enum class LogLevel:int8_t {
    kDebug = 1,
    kInfo = 2,
    kWarn = 3,
    kError = 4
};

static std::string g_log_file = "";
static LogMode g_log_mode = LogMode::kOff;
static int g_size = 0;




class LogStream {
    public:
    LogStream(){}
    std::stringstream& operator()(LogLevel level) {
        level_ = level;
        return ss_;
    }
    const std::string GetCurrentSystemTime()
    {
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm* ptm = localtime(&t);
        char date[60] = { 0 };
        sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
            (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
            (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
        //std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") <<std::endl;
        return move(std::string(date));
    }
    
    ~LogStream(){
        if(g_log_mode == LogMode::kFile) {
            std::streambuf * coutbuf = std::cout.rdbuf();
            std::ofstream log(g_log_file);
            if(log.is_open()) {
                std::streambuf * filebuf = log.rdbuf();
                std::cout.rdbuf(filebuf); //cout >> file
            }
        }
        switch (level_)
        {
        case LogLevel::kDebug:
            std::cout<<"[Debug]"<<"["<<std::this_thread::get_id()<<"]["<<GetCurrentSystemTime()<<"]"<<ss_.str()<<std::endl;
            break;
        case LogLevel::kInfo:
            std::cout<<"[Info]"<<"["<<std::this_thread::get_id()<<"]["<<GetCurrentSystemTime()<<"]"<<ss_.str()<<std::endl;
            break;
        case LogLevel::kWarn:
            std::cout<<"[Warn]"<<"["<<std::this_thread::get_id()<<"]["<<GetCurrentSystemTime()<<"]"<<ss_.str()<<std::endl;
            break;
        case LogLevel::kError:
            std::cout<<"[Error]"<<"["<<std::this_thread::get_id()<<"]["<<GetCurrentSystemTime()<<"]"<<ss_.str()<<std::endl;
            break;
        default:
            break;
        }
    }

    private:
    LogLevel level_;
    std::stringstream ss_;
};


class Logger {
    public:
    explicit Logger(const std::string &log_file) {

    }
    Logger() {
    }

    LogStream & operator()() {
        return log_stream_;
    }

    void Debug(std::string str){
        //std::cout<<"[Debug] "<<std::endl;
        log_stream_(LogLevel::kDebug)<<str;
    }
    void Info(std::string str){
        //std::cout<<"[Debug] "<<std::endl;
        log_stream_(LogLevel::kInfo)<<str;
    }
    void Warn(std::string str){
        //std::cout<<"[Debug] "<<std::endl;
        log_stream_(LogLevel::kWarn)<<str;
    }
    void Error(std::string str){
        //std::cout<<"[Debug] "<<std::endl;
        log_stream_(LogLevel::kError)<<str;
    }
    ~Logger(){

    }
    private:
    LogStream log_stream_;
    std::string log_file_;
};

#define LogDebug \
    []() -> std::unique_ptr<Logger> { \
        return std::move(std::unique_ptr<Logger>(new Logger())); \
    }()->operator()()(LogLevel::kDebug) \
    
#define LogInfo \
    []() -> std::unique_ptr<Logger> { \
        return std::move(std::unique_ptr<Logger>(new Logger())); \
    }()->operator()()(LogLevel::kInfo) \

#define LogWarn \
    []() -> std::unique_ptr<Logger> { \
        return std::move(std::unique_ptr<Logger>(new Logger())); \
    }()->operator()()(LogLevel::kWarn) \

#define LogError \
    []() -> std::unique_ptr<Logger> { \
        return std::move(std::unique_ptr<Logger>(new Logger())); \
    }()->operator()()(LogLevel::kError) \


inline bool InitLog(const std::string & file,LogMode log_model) {
    if (file.length() > 0) {
        g_log_file = file;
    }
    g_log_mode = log_model;
    g_size = 111;


    std::cout<<"model:"<<(int)g_log_mode<<std::endl;
    std::cout<<"size:"<<g_size<<std::endl;
    std::cout<<"log_file:"<<g_log_file<<std::endl;
}



#endif // _LOG_H_