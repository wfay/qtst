///@system	 飞马行情接受系统
///@company  上海金融期货信息技术有限公司
///@file	 CUstpMs
///@brief	 接受飞马系统的行情
///@history 
///20130502: 徐忠华 创建
//////////////////////////////////////////////////////////////////////

#include "USTPMDClient.h"
#include <signal.h>
#include "custom.hpp"
#include <unistd.h>
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQmlContext>
#include <QQuickView>
#include <QObject>
#include <QQuickWindow>
#include <QDebug>
/*
void on_exit(int signum)
{
    CUstpMs::ExitInstance();
}
*/
extern QObject *object;
bool CUstpMs::InitInstance(char *  number,char * inifile,MyClass* p)
{
	char tmp[200];
	const char * tradingDay="abc";
//	signal(SIGINT, on_exit);

	strcpy(m_number,number);
//	CConfig *pConfig = 	new CConfig(INI_FILE_NAME);	
    TIniFile tf;
    if (!tf.Open(inifile))
    {
        printf("init file not found,exit\n");
        exit(-1000);
    }


	pUserApi = CUstpFtdcMduserApi::CreateFtdcMduserApi();

    sh = new CUSTPMDHandler(pUserApi,m_number,p);

	pUserApi->RegisterSpi(sh);


    int topicid = tf.ReadInt(m_number,"Topic",100);
    int tert = tf.ReadInt(m_number,"TERT",0);
    QMetaObject::invokeMethod(object, "insertoUndealed");
    switch(tert)
    {
    case 0:
        {
            pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_RESTART);
            break;
        }
    case 1:
        {
			pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_RESUME);
            break;
        }
    case 2:
        {
            pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_QUICK);
            break;
        }
    default:
        {
            printf("%s,%d,%s exit! \n",__FILE__,__LINE__,__FUNCTION__);
            exit(-1);
        }
    }

    tf.ReadString(m_number,"MDFrontAdd","",tmp,sizeof(tmp)-1);
    mytrim(tmp);
    printf("%s\n",tmp);
    pUserApi->RegisterFront(tmp);

	int a=0;
	int b=0;
    printf("%s\n",pUserApi->GetVersion(a,b));
	pUserApi->SetHeartbeatTimeout(300);
    printf("\nFinish Init,Start Joing\n");
	pUserApi->Init();

    tradingDay=pUserApi->GetTradingDay();

    pUserApi->Join();
//	printf("\nTrading Day:%s\n",tradingDay);
    // 释放useapi实例
    pUserApi->Release();

	return true;
}

void CUstpMs::ExitInstance()
{
    printf("Delete api instance\n");
	pUserApi->Release();
	delete sh;
}
