#if !defined(CUSTOM_H)
#define CUSTOM_H
#include <stdlib.h>
#include <string>
#include <ctype.h>
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
#include "USTPFtdcUserApiDataType.h"
extern void * OrderFunc(void *pParam);
extern int g_choose;
extern TUstpFtdcDirectionType g_direction;
extern TUstpFtdcOffsetFlagType g_offsetflag;
extern TUstpFtdcOrderPriceTypeType g_pricetype;
extern TUstpFtdcHedgeFlagType g_hedgeflag;
extern TUstpFtdcTimeConditionType g_timecondition;
extern TUstpFtdcPriceType g_limitprice;
extern TUstpFtdcVolumeType g_volume;
extern TUstpFtdcVolumeConditionType g_volume_condition;
extern bool ordered;
extern TUstpFtdcOrderSysIDType g_drop_OrderSysID;
extern TUstpFtdcInstrumentIDType g_instrumentID;
typedef struct{
    float ask[45000];
    float bid[45000];
    int idx;
}price_data;
enum TradeType{
    BUY=1,
    SALE,
    EVEN,
};
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double ask READ ask WRITE setask NOTIFY askvalueChanged)
    Q_PROPERTY(double bid READ bid WRITE setbid NOTIFY bidvalueChanged)
    Q_PROPERTY(double curr READ curr WRITE setcurr NOTIFY currvalueChanged)
    Q_PROPERTY(int data_count_1 READ data_count_1 WRITE setdata_count_1 NOTIFY data_countvalueChanged_1)
public:
    char current_show[31];
    double data[4];
//    price_data IF1509;
 //   price_data IF1512;
    int data_idx;
    MyClass()
    {
        setask(10);
        setbid(10);
        strcpy(current_show,"\n");
 //       printf("pshow:%s\n",current_show);
        data_idx=0;
    }
    QObject *object;
    int TType;
/*
    Q_INVOKABLE float nextAsk(int idx)
    {
        return IF1509.ask[idx];
    }
    Q_INVOKABLE float nextBid(int idx)
    {
        return IF1509.bid[idx];
    }
    */
    Q_INVOKABLE bool set_limitprice(QString limitprice)
    {
        g_limitprice=limitprice.toDouble();
 //       qDebug()<<g_limitprice;
    }
    Q_INVOKABLE void getSelect(const QString &msg)
    {
        memcpy(current_show,msg.toStdString().c_str(),7);
        memcpy(g_instrumentID,current_show,31);
    }

    Q_INVOKABLE void getTType(int t) {
        TType=t;
        char* msg;
        if(t==1)
        {msg="buy";}
        else if(t==2)
        {
           msg="sale";
        }
        else if(t==3)
        {
           msg="even";
        }
        qDebug()<<"Trade Type:"<<msg<<" "<<TType;
    }

    Q_INVOKABLE bool set_g_choose(int idx)
    {
        g_choose=idx;
    }
    Q_INVOKABLE bool set_volume(QString volume)
    {
        g_volume=volume.toDouble();
    }
    Q_INVOKABLE bool set_volume_condition(int volume_condition)
    {
        g_volume_condition='3';
        if(volume_condition==1)
        {
        g_volume_condition='1';
        }
        else if(volume_condition==2)
        {
            g_volume_condition='2';
        }
    }
    Q_INVOKABLE bool set_offset(int offset)
    {
        g_offsetflag='1';
        if(offset==0)
        {
        g_offsetflag='0';
        }
    }
    Q_INVOKABLE bool set_direction(int direction)
    {
        g_direction='1';
        if(direction==0)
        {
        g_direction='0';
        }
    }
    Q_INVOKABLE bool set_drop_num(QString num)
    {
        strcpy(g_drop_OrderSysID,num.toStdString().c_str());
    }
    Q_INVOKABLE bool set_pricetype(int type)
    {
        g_pricetype='1';
        if(type==2)
        {
        g_pricetype='2';
        }
    }
    Q_INVOKABLE bool set_hedge(int type)
    {
        g_hedgeflag='3';
        if(type==1)
        {
        g_hedgeflag='1';
        }
        else if(type==2)
        {
            g_hedgeflag='2';
        }
    }
    Q_INVOKABLE bool set_timeCon(int type)
    {
        g_timecondition='3';
        if(type==1)
        {
        g_timecondition='1';
        }
        else if(type==2)
        {
            g_timecondition='2';
        }
    }
    double ask(){return current_ask;}
    /*!
     * Sets the value.
     */
    void setask(double i)
    {
            current_ask=i;
            emit askvalueChanged(i);
    }
    void setcurr(double i)
    {
            current_data=i;
            emit currvalueChanged(i);
    }
    double curr(){return current_data;}
    double bid(){return current_bid;}
    int data_count_1(){return current_data_count_1;}
    /*!
     * Sets the value.
     */
    void setbid(double i)
    {
            current_bid=i;
            emit bidvalueChanged(i);
    }
    void setdata_count_1(int i)
    {
            current_data_count_1=i;
            emit data_countvalueChanged_1(i);
    }
signals:
    /*!
     * Emitted when the value changes.
     */
    void askvalueChanged(double);
    void bidvalueChanged(double);
    void currvalueChanged(double);
    void data_countvalueChanged_1(int);
public slots:
    void cppSlot(int number) {
        std::cout << "Called the C++ slot with" << number;
    }
private:

double current_ask;
double current_bid;
double current_data;
double current_data_count_1;
};

#endif
