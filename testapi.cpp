// TestApi.cpp : Defines the entry point for the console application.
//
#include "PublicFuncs.h"
#include "TraderSpi.h"
#include "USTPFtdcTraderApi.h"
#include <iostream>
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQmlContext>
#include <QQuickView>
#include <QObject>
#include <QQuickWindow>
#include <QDebug>
int g_nSwitch=0;

extern int g_nOrdSpeed;
extern QObject *object;
void usage(char* pName)
{
	printf("usage:%s FrontAddress (tcp://172.31.112.133:15555)\n",pName);
	return;
}

void* trade_main(void*)
{

	//init
    printf("entering trade main\n");
/*
    QVariant returnedValue;
    QVariant msg = "Hello from C++";
    QMetaObject::invokeMethod(object, "myQmlFunction",
    Q_ARG(QVariant, msg));
    qDebug() << "QML function returned:" << returnedValue.toString();
*/

    memset(g_frontaddr,0,BUFLEN);
    strcpy(g_frontaddr,"tcp://117.185.125.4:17198");
    strcpy(g_BrokerID,"1004");
    strcpy(g_UserID,"0193764301");
    strcpy(g_Password,"71de26b5ad29d562cfe07814e8c80974");
	printf("Input g_BrokerID=[%s]g_UserID=[%s]g_Password=[%s]\n",g_BrokerID,g_UserID,g_Password);
 //   getchar();
	CUstpFtdcTraderApi *pTrader = CUstpFtdcTraderApi::CreateFtdcTraderApi("");	
	g_puserapi=pTrader;

 	CTraderSpi spi(pTrader);
 	pTrader->RegisterFront(g_frontaddr);	
    pTrader->SubscribePrivateTopic(USTP_TERT_RESUME);
    pTrader->SubscribePublicTopic(USTP_TERT_RESUME);
	pTrader->RegisterSpi(&spi);
    pTrader->Init();

    pTrader->Join();
    pTrader->Release();


	return 0;
}
