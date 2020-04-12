#include "jcrtspserver.h"

#include <BasicUsageEnvironment.hh>
#include <RTSPServerSupportingHTTPStreaming.hh>
#include <H264VideoFileServerMediaSubsession.hh>

#include <iostream>
#define Debug(...)  do{std::cout << __PRETTY_FUNCTION__ << ":" << __VA_ARGS__ << std::endl;}while(0)
#define Error(...)  Debug(__VA_ARGS__)
#define Info(...)   Debug(__VA_ARGS__)

class JCRtspServerImpl : public RTSPServerSupportingHTTPStreaming
{
public:
    static JCRtspServerImpl*
    createNew(UsageEnvironment& env,
              Port ourPort,
              UserAuthenticationDatabase* authDatabase = NULL,
              unsigned reclamationTestSeconds = 65)
    {
        int ourSocket = setUpOurSocket(env, ourPort);
        if (ourSocket == -1)
        {
            Error(env.getResultMsg());
            throw std::runtime_error(env.getResultMsg());
        }

        return new JCRtspServerImpl(env,
                                    ourSocket,
                                    ourPort,
                                    authDatabase,
                                    reclamationTestSeconds);

    }

protected:
    JCRtspServerImpl(UsageEnvironment& env,
                     int ourSocket,
                     Port ourPort,
                     UserAuthenticationDatabase* authDatabase,
                     unsigned reclamationTestSeconds)
        : RTSPServerSupportingHTTPStreaming(env,
                                            ourSocket,
                                            ourPort,
                                            authDatabase,
                                            reclamationTestSeconds)
    {

    }
    virtual ~JCRtspServerImpl()
    {

    }

    virtual ServerMediaSession*
    lookupServerMediaSession(char const* streamName, Boolean isFirstLookupInSession) override
    {
        Debug("streamName:" << streamName << ",isFirstLookupInSession:" << !!isFirstLookupInSession);
        ServerMediaSession* sms = RTSPServerSupportingHTTPStreaming::lookupServerMediaSession(streamName);
        if(!sms)
        {
            UsageEnvironment& env = envir();
            sms = ServerMediaSession::createNew(env, streamName);
            std::string path = std::string("/home/jiaohhp/Downloads/") + streamName;
            sms->addSubsession(
                        H264VideoFileServerMediaSubsession::createNew(env, path.c_str(), False));
            addServerMediaSession(sms);

        }

        return sms;
    }

};

JCRtspServer::JCRtspServer(int port)
    : mpScheduler(BasicTaskScheduler::createNew())
    , mpEnv(BasicUsageEnvironment::createNew(*mpScheduler),
            [](UsageEnvironment* p){ p->reclaim(); })
    /* , mpAuthDb(new UserAuthenticationDatabase()) */
    , mpImpl(JCRtspServerImpl::createNew(*mpEnv,
                                         port,
                                         mpAuthDb.get()),
             [](RTSPServer* p){Medium::close(p);})
    , mExitFlag(EXIT_FLAG_RUN)
{
    if(mpAuthDb)
    {
        mpAuthDb->addUserRecord("admin", "123456");
    }
    mpImpl->setUpTunnelingOverHTTP(port + 2);
}

JCRtspServer::~JCRtspServer()
{

}


void JCRtspServer::Stop()
{
    std::unique_lock<std::mutex> locker(mExitMutex);
    while(mExitFlag != EXIT_FLAG_STOPPED)
    {
        Info("Wait for stop...");
        mExitFlag = EXIT_FLAG_STOP;
        mExitCond.wait(locker);
    }
}

void JCRtspServer::Run()
{
    Info("started ...");
    mpScheduler->doEventLoop(&mExitFlag);

    std::lock_guard<std::mutex> locker(mExitMutex);
    mExitFlag = EXIT_FLAG_STOPPED;
    mExitCond.notify_all();

    Info("stopped");
}
