#include "util.hpp"
#include "level.hpp"
#include "format.hpp"
#include "message.hpp"
#include "sink.hpp"
#include "logger.hpp"
#include"buffer.hpp"
#include"log.hpp"
#include <unistd.h>
#include<vector>

using namespace std;
using namespace log;
using namespace util;


void test()
{
    Logger::ptr slogger = getLogger("async-logger");
    slogger->debug( "%s", "测试日志");
    slogger->info( "%s", "测试日志");
    slogger->warn( "%s", "测试日志");
    slogger->error("%s", "测试日志");
    slogger->fatal("%s", "测试日志");

    size_t count = 0;
    while (count < 300000)
    {
        slogger->fatal("测试日志-%d", count++);
    }


//     DEBUG("%s", "测试日志");
//     INFO("%s", "测试日志");
//     WARN("%s", "测试日志");
//     ERROR("%s", "测试日志");
//     FATAL("%s", "测试日志");

//     size_t count = 0;
//     while (count < 300000)
//     {
//         FATAL("测试日志-%d", count++);
//     }


}

int main()
{

    // 日志器管理器测试

    std::unique_ptr<LoggerBuilder> lb(new GlobalLoggerBuilder());
    lb->buildLoggerName("async-logger");
    lb->buildLoggerType(LoggerType::ASyncLogger);
    lb->buildLoggerLevel(LogLevel::value::DEBUG);
    lb->buildEnableUnsafe();
    lb->buildFormatter("[%f][%l]%d{%H:%M:%S}%T%m%n");
    lb->buildSink<StdOutSink>();
    lb->buildSink<FileSink>("./logfile/async-test.log");
    lb->build();

    test();



    // 异步日志器测试

    // std::unique_ptr<LoggerBuilder> lb(new LocalLoggerBuilder());
    // lb->buildLoggerName("async-logger");
    // lb->buildLoggerType(LoggerType::ASyncLogger);
    // lb->buildLoggerLevel(LogLevel::value::DEBUG);
    // lb->buildEnableUnsafe();
    // lb->buildFormatter("%d{%H:%M:%S}%T%m%n");
    // lb->buildSink<StdOutSink>();
    // lb->buildSink<FileSink>("./logfile/async-test.log");
    // Logger::ptr slogger=lb->build();

    // slogger->debug(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->info(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->warn(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->error(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->fatal(__FILE__, __LINE__, "%s", "测试日志");

    // size_t count=0;
    // while(count<300000)
    // {
    //     slogger->fatal(__FILE__,__LINE__,"测试日志-%d",count++);
    // }




    // 缓冲区测试
    // std::ifstream ifs("./logfile/test.log",std::ios::binary);
    // if(!ifs.good()) cout<<"open file error"<<endl;
    // string tmp;
    // ifs.seekg(0,std::ios::end);
    // size_t tsize=ifs.tellg();
    // ifs.seekg(0,std::ios::beg);
    // tmp.resize(tsize);
    // ifs.read(&tmp[0],tsize);
    // if(ifs.good() == false) cout<<"read error"<<endl;
    // ifs.close();

    // Buffer buffer;
    // for(int i=0;i<tsize;i++)
    // {
    //     buffer.push(&tmp[i],1);
    // }


    // std::ofstream ofs("./logfile/tmp.log",std::ios::binary);
    // size_t size=buffer.readAbleSize();
    // cout<<size<<endl;
    // for(int i=0;i<size;i++)
    // {
    //     ofs.write(buffer.begin(),1);
    //     buffer.moveReader(1);
    // }
    // ofs.close();




    //  logger 的测试
    // string name("test-logger");
    // LogLevel::value level = LogLevel::value::WARN;
    // Formatter::ptr fmt(new Formatter());
    // LogSink::ptr outlpt= SinkFactory::create<StdOutSink>();
    // LogSink::ptr filelpt = SinkFactory::create<FileSink>("./logfile/filelpt.log");
    // LogSink::ptr rolllpt = SinkFactory::create<RollSinkBySize>("./logfile/roll-", 1024 * 1024);
    // vector<LogSink::ptr> ptrs= {outlpt,filelpt,rolllpt};
    // SyncLogger::ptr  slogger(new SyncLogger(name,level,fmt,ptrs));

    // 建造者测试
    // std::unique_ptr<LoggerBuilder> lb(new LocalLoggerBuilder());
    // lb->buildLoggerName("sync-logger");
    // lb->buildLoggerType(LoggerType::SyncLogger);
    // lb->buildLoggerLevel(LogLevel::value::DEBUG);
    // lb->buildFormatter("%d{%H:%M:%S}%T%m%n");
    // //lb->buildSink<StdOutSink>();
    // lb->buildSink<FileSink>("./logfile/test.log");
    // Logger::ptr slogger=lb->build();

    // slogger->debug(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->info(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->warn(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->error(__FILE__, __LINE__, "%s", "测试日志");
    // slogger->fatal(__FILE__, __LINE__, "%s", "测试日志");

    // size_t cursize=0,count=0;
    // while(cursize<10*1024*1024)
    // {
    //     slogger->fatal(__FILE__,__LINE__,"测试日志-%d",count++);
    //     cursize+=20;
    // }



    // LogMsg ms(LogLevel::value::DEBUG,111,"test.cpp","root","测试格式化字符串.....");
    // Formatter fm;
    // string s=fm.format(ms);
    // cout<<s<<endl;

    // LogSink::ptr outlpt= SinkFactory::create<StdOutSink>();
    // LogSink::ptr filelpt = SinkFactory::create<FileSink>("./logfile/filelpt.log");
    // LogSink::ptr rolllpt = SinkFactory::create<RollSinkBySize>("./logfile/roll-", 1024 * 1024);
    // outlpt->log(s.c_str(),s.size());
    // filelpt->log(s.c_str(),s.size());

    // size_t cursize=0;
    // size_t count=0;
    // while(cursize<10*1024*1024)
    // {
    //     string tmp=s + to_string(count++);
    //     rolllpt->log(tmp.c_str(),tmp.size());
    //     cursize+=tmp.size();
    // }

    // LogSink::ptr timelpt = SinkFactory::create<RollSinkByTime>("./logfile/time-", GapType::GAP_SECOND);
    // time_t cur=Date::getTime();
    // while (Date::getTime() < cur+5)
    // {
    //     timelpt->log(s.c_str(),s.size());
    //     usleep(100);
    // }

    // string pathname("./abc/bcd/test.txt");
    // cout<<Date::getTime()<<endl;
    // cout<<File::path(pathname)<<endl;
    // cout<<File::exists(pathname)<<endl;
    // File::createDirectory(pathname);
    // cout<<File::exists(pathname)<<endl;

    // cout<<log::LogLevel::toString(log::LogLevel::value::DEBUG)<<endl;
    // cout<<log::LogLevel::toString(log::LogLevel::value::INFO)<<endl;
    // cout<<log::LogLevel::toString(log::LogLevel::value::OFF)<<endl;
    // cout << log::LogLevel::toString(log::LogLevel::value::FATAL) << endl;
    return 0;
}