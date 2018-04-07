#pragma once
#include <fstream>
#include <sstream>
#include <cstdarg> 
using namespace std;

#ifdef _WIN32
#define DllExport __declspec( dllexport )//宏定义
#else
#define DllExport
#endif


namespace z 
{
    static const int scg_iperLogMaxLen = 4096;
    static const char scg_cboxOffSignForLog = '|';
    static const string scg_slogFileName = "z";
    static const string scg_slogFileNameSuffixal = ".log";
    

    class DllExport zlog
    {
    public:
        zlog();
        zlog(const string& slogFileName);
        ~zlog();
        void init();
        void clear();
        void getMemory();
        void deleteMemory();

        void writeLog(const char * const logLevel, const string& sfileName, unsigned int iLineNo
            , const string& sfunctionName, const char *pformat, ...);
        void backupLogFile();//����־�ļ����ļ�����ʱ���׺

    private:
        stringstream m_ss;//�ݴ���־
        char* m_pperLogbuf;
        fstream m_wf;
        const string m_slogFileName;
        const string m_slogFileNameSuffixal;
    };
}

static z::zlog zlog;
#define DEBUG
#ifdef DEBUG  
#define LOG(logLevel, format, ...) zlog.writeLog(logLevel, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)  
#define PRINT(logLevel, format, ...) \
do{\
printf("%s|%s|[%s,%u]|%s", getTime().c_str(), logLevel.c_str(), __FILE__, __LINE__, __FUNCTION__);\
printf(format, ##__VA_ARGS__);\
printf("\n");\
} while (false)
#else  
#define LOG(format, ...)  
#endif  
