//rtsp://admin:123456@xx:8554/xx
#ifndef JCRTSPSERVER_H
#define JCRTSPSERVER_H

#include <RTSPServer.hh>
#include <memory>
#include <mutex>
#include <condition_variable>
class JCRtspServer
{
public:
    //port : rtsp
    //port + 1 : rtcp
    //port +2 : rtsp over http
    //user : admin, pass: 123456
    JCRtspServer(int port);
    ~JCRtspServer();
    void Run();
    void Stop();

private:
    std::shared_ptr<TaskScheduler> mpScheduler;
    std::shared_ptr<UsageEnvironment> mpEnv;

    std::shared_ptr<UserAuthenticationDatabase> mpAuthDb;
    std::shared_ptr<RTSPServer> mpImpl;

    volatile char mExitFlag;
    std::mutex mExitMutex;
    std::condition_variable mExitCond;
    enum
    {
      EXIT_FLAG_RUN = 0,
      EXIT_FLAG_STOP,
      EXIT_FLAG_STOPPED
    };
};

#endif // JCRTSPSERVER_H
