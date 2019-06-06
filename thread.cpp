#include "thread.h"
#include "app.h"

Thread::Thread()
{
    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//ȡ��ԭ������
    tcpClient->connectToHost("127.0.0.1",60000);
    //if (tcpClient->waitForConnected(1000));
stopped=false;
}

Thread::~Thread()
{

}

void Thread::stop()
{
    stopped=true;
}

void Thread::run()
{
    while(!stopped){
        mutex.lock();
        if (App::list.count()>0){            
            QString txt=App::list.takeFirst();
            emit readOne(txt);
        }
//        tcpClient=new QTcpSocket(this);
//        tcpClient->abort();//ȡ��ԭ������
//        tcpClient->connectToHost("127.0.0.1",60000);
        QString data="11111111";
        tcpClient->write(data.toLatin1().data());
        mutex.unlock();
        msleep(1);//�������CPUռ���ʸߴ�50%
    }
    stopped=false;
}

