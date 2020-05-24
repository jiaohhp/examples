#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>
#include <Poco/ThreadPool.h>
#include <Poco/RunnableAdapter.h>
#include <iostream>
class JCProducer
{
public:
    Poco::BasicEvent<void> dataChanged;
    JCProducer()
    {

    }
    ~JCProducer()
    {

    }
    void SetData()
    {
        std::cout << "Producer sleep 5@" << Poco::Thread::current()->getName() << std::endl;
        Poco::Thread::sleep(5000);
        std::cout << "Producer start @" << Poco::Thread::current()->getName() << std::endl;
        dataChanged(this);
        std::cout << "Producer sleep 10" << std::endl;
        Poco::Thread::sleep(10000);
        std::cout << "Producer end" << std::endl;
    }
};

class JCConsumer
{
public:
    JCConsumer()
    {

    }
    ~JCConsumer()
    {

    }
    void OnDataChanged(const void* pSender)
    {
        std::cout << "Consumer sleep 5@" << Poco::Thread::current()->getName() << std::endl;
        Poco::Thread::sleep(5000);
        std::cout << "Consumer end" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    JCProducer producer;
    JCConsumer consumer;
    producer.dataChanged += Poco::delegate(&consumer, &JCConsumer::OnDataChanged);

    Poco::RunnableAdapter<JCProducer> producerThread(producer, &JCProducer::SetData);
    Poco::Thread t("producerThread");
    t.start(producerThread);

    std::cin.get();
    return 0;
}
