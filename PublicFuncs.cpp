// PublicFuncs.cpp: implementation of the PublicFuncs class.
//
//////////////////////////////////////////////////////////////////////

#include "PublicFuncs.h"
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
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern QObject *object;
PublicFuncs::~PublicFuncs()
{

}

typedef struct 
{
	int nordspeed;
	int nordloop;
} stordspeed;

/*---------------ȫ�ֱ�����---------------*/

const char* TEST_API_INI_NAME="./config/TestApi.ini";
char* g_pFlowPath="./flow/";
char* g_pProductInfo="��ʾ���Թ���V1.0";
char* g_pProgramName="TestApi";
int g_choose;
TUstpFtdcInstrumentIDType g_instrumentID="IF1509";
TUstpFtdcOrderPriceTypeType g_pricetype;//[1:�м� 2:�޼�]
TUstpFtdcDirectionType g_direction;//[0:�� 1:��]
TUstpFtdcOffsetFlagType g_offsetflag;//[0:���� 1:ƽ��]
TUstpFtdcHedgeFlagType g_hedgeflag;//[1:Ͷ�� 2:�ױ� 3:����]
TUstpFtdcPriceType g_limitprice;
TUstpFtdcVolumeType g_volume;
TUstpFtdcVolumeConditionType g_volume_condition;
TUstpFtdcOrderSysIDType g_OrderSysID;
TUstpFtdcOrderSysIDType g_drop_OrderSysID;
//�κ�����
// #define USTP_FTDC_VC_AV '1'
//��С����
//#define USTP_FTDC_VC_MV '2'
//ȫ������
//#define USTP_FTDC_VC_CV '3'
TUstpFtdcTimeConditionType g_timecondition;//[1:IOC  2:������Ч 3:������Ч]
extern int g_nSwitch;
extern FILE * g_fpSend;
bool ordered=false;
//1.��¼��Ϣ
///���͹�˾����
TUstpFtdcBrokerIDType g_BrokerID;
///�����û�����
TUstpFtdcUserIDType	g_UserID;
///����
TUstpFtdcPasswordType	g_Password;

//2.��ַ��Ϣ
char g_frontaddr[BUFLEN];

//3.������Ϣ
int g_nOrdLocalID=0;
CUstpFtdcTraderApi * g_puserapi=NULL;

/*---------------ȫ�ֺ�����---------------*/
void ShowManu()
{
	printf("**********************\n"
	       "ѡ����Ҫִ�еĲ���\n"
	       "1-�����걨\n"
	       "2-��������\n"
	       "3-������ѯ\n"
	       "4-�ɽ���ѯ\n"
	       "5-Ͷ�����˻���ѯ\n"
	       "6-���ױ����ѯ\n"
	       "7-��������ѯ\n"
	       "8-��Լ��Ϣ��ѯ\n"
	       "9-����Ͷ���߲�ѯ\n"
	       "10-�ͻ��ֲֲ�ѯ\n"
	       "11-�޸��û�����\n"
		   "12-Ͷ�����������ʲ�ѯ\n"
		   "13-Ͷ���߱�֤���ʲ�ѯ\n"
		   "14-�Ϲ������ѯ\n"
		   "15-����¼��\n"
		   "16-���۲���\n"
		   "17-ѯ������\n"
	       "0-�˳�\n"
	       "**********************\n"
	       "��ѡ��"
	);
}
void printOrderInfo(void)
{
    printf("--------������Ϣ--------\n");
    if(g_pricetype=='1')
    {printf("�м�\n");}
    else if(g_pricetype=='2')
    {printf("�޼�\n");}

    if(g_direction=='0')
    {printf("��\n");}
    else if(g_direction=='1')
    {printf("��\n");}

    if(g_offsetflag=='0')
    {printf("����\n");}
    else if(g_offsetflag=='1')
    {printf("ƽ��\n");}

    if(g_hedgeflag=='1')
    {printf("Ͷ��\n");}
    else if(g_hedgeflag=='2')
    {printf("�ױ�\n");}
    else if(g_hedgeflag=='3')
    {printf("����\n");}

    printf("�޼�:%f\n",g_limitprice);

    printf("����:%d\n",g_volume);

    if(g_timecondition=='1')
    {printf("IOC\n");}
    else if(g_timecondition=='2')
    {printf("������Ч\n");}
    else if(g_timecondition=='3')
    {printf("������Ч\n");}

    if(g_volume_condition=='1')
    {printf("FAK\n");}
    else if(g_volume_condition=='2')
    {printf("ANY\n");}
    else if(g_volume_condition=='3')
    {printf("FOK\n");}
 //   printf("gc:%c\n",g_volume_condition);
    printf("----------------\n");
}

void printPtradeOrderInfo(CUstpFtdcInputOrderField* ord)
{
    printf("--------������Ϣ--------\n");
    printf("BrokerID:%s\n",ord->BrokerID);
    printf("UserID:%s\n",ord->UserID);
    printf("��Լ���:%s\n",ord->InstrumentID);
    if(ord->OrderPriceType=='1')
    {printf("�м�\n");}
    else if(ord->OrderPriceType=='2')
    {printf("�޼�\n");}

    if(ord->Direction=='0')
    {printf("��\n");}
    else if(ord->Direction=='1')
    {printf("��\n");}

    if(ord->OffsetFlag=='0')
    {printf("����\n");}
    else if(ord->OffsetFlag=='1')
    {printf("ƽ��\n");}

    if(ord->HedgeFlag=='1')
    {printf("Ͷ��\n");}
    else if(ord->HedgeFlag=='2')
    {printf("�ױ�\n");}
    else if(ord->HedgeFlag=='3')
    {printf("����\n");}

    printf("�޼�:%f\n",ord->LimitPrice);

    printf("����:%d\n",ord->Volume);

    if(ord->TimeCondition=='1')
    {printf("IOC\n");}
    else if(ord->TimeCondition=='2')
    {printf("������Ч\n");}
    else if(ord->TimeCondition=='3')
    {printf("������Ч\n");}

    if(ord->VolumeCondition=='1')
    {printf("FAK\n");}
    else if(ord->VolumeCondition=='2')
    {printf("ANY\n");}
    else if(ord->VolumeCondition=='3')
    {printf("FOK\n");}
 //   printf("gc:%c\n",g_volume_condition);
    printf("----------------\n");
}

void StartInputOrder ()
{
	if (g_puserapi==NULL)
	{
		printf("StartInputOrder  USERAPIδ����");
		return ;
	}
	//CUstpFtdcInputOrderField* pord=g_pOrd->at(1);
	CUstpFtdcInputOrderField ord;
	memset(&ord,0,sizeof(CUstpFtdcInputOrderField));

    strcpy(ord.InvestorID,"01937643");
    strcpy(ord.InstrumentID,g_instrumentID);
    ord.OrderPriceType=g_pricetype;//[1:�м� 2:�޼�]
    ord.Direction=g_direction;//[0:�� 1:��]
    ord.OffsetFlag=g_offsetflag;//[0:���� 1:ƽ��]
    ord.HedgeFlag=g_hedgeflag;//[1:Ͷ�� 2:�ױ� 3:����]
    ord.LimitPrice=g_limitprice;
    ord.Volume=g_volume;
    ord.VolumeCondition=g_volume_condition;
    ord.TimeCondition=g_timecondition;//[1:IOC  2:������Ч 3:������Ч]
	
	strcpy(ord.BrokerID,g_BrokerID);
	strcpy(ord.UserID,g_UserID);
	strcpy(ord.ExchangeID,"CFFEX");

	ord.ForceCloseReason='0';
	sprintf(ord.UserOrderLocalID,"%012d",g_nOrdLocalID++);
    printPtradeOrderInfo(&ord);
    g_puserapi->ReqOrderInsert(&ord,g_nOrdLocalID++);
    QMetaObject::invokeMethod(object, "insertoUndealed");//append to undealed list
	return ;
}

void StartQuoteInsert()
{
	if (g_puserapi==NULL)
	{
		printf("StartInputOrder  USERAPIδ����");
		return ;
	}
	CUstpFtdcInputQuoteField QuoteInsert;
	memset(&QuoteInsert,0,sizeof(CUstpFtdcInputQuoteField));
	printf("�����뱨����Ϣ\n");

	printf("input InvestorID��\n");
	scanf("%s",(QuoteInsert.InvestorID));
	printf("InvestorID=[%s]\n",QuoteInsert.InvestorID);
	getchar();
	printf("input InstrumentID��\n");
	scanf("%s",(QuoteInsert.InstrumentID));
	printf("InstrumentID=[%s]\n",(QuoteInsert.InstrumentID));
	getchar();
	sprintf(QuoteInsert.UserQuoteLocalID,"%012d",g_nOrdLocalID++);

	printf("input BidVolume:\n");
	scanf("%d",&(QuoteInsert.BidVolume));
	printf("BidVolume=[%d]\n",(QuoteInsert.BidVolume));
	getchar();
	printf("input BidOffsetFlag:\n");
	scanf("%c",&(QuoteInsert.BidOffsetFlag));
	printf("BidOffsetFlag=[%c]\n",(QuoteInsert.BidOffsetFlag));
	getchar();
	printf("input BidHedgeFlag:\n");
	scanf("%c",&(QuoteInsert.BidHedgeFlag));
	printf("BidHedgeFlagn=[%c]\n",(QuoteInsert.BidHedgeFlag));
	getchar();
	printf("input BidPrice:\n");
	scanf("%lf",&(QuoteInsert.BidPrice));
	printf("BidPrice=[%lf]\n",(QuoteInsert.BidPrice));
	getchar();
	printf("input AskVolume:\n");
	scanf("%d",&(QuoteInsert.AskVolume));
	printf("AskVolume=[%d]\n",(QuoteInsert.AskVolume));
	getchar();
	printf("input AskOffsetFlag:\n");
	scanf("%c",&(QuoteInsert.AskOffsetFlag));
	printf("AskOffsetFlag=[%c]\n",(QuoteInsert.AskOffsetFlag));
	getchar();
	printf("input AskHedgeFlagn:\n");
	scanf("%c",&(QuoteInsert.AskHedgeFlag));
	printf("AskHedgeFlagn=[%c]\n",(QuoteInsert.AskHedgeFlag));
	getchar();
	printf("input AskPrice:\n");
	scanf("%lf",&(QuoteInsert.AskPrice));
	printf("AskPrice=[%lf]\n",(QuoteInsert.AskPrice));
	getchar();

	sprintf(QuoteInsert.BidUserOrderLocalID,"%012d",g_nOrdLocalID++);
	sprintf(QuoteInsert.AskUserOrderLocalID,"%012d",g_nOrdLocalID++);

	strcpy(QuoteInsert.BrokerID,g_BrokerID);
	strcpy(QuoteInsert.UserID,g_UserID);
	strcpy(QuoteInsert.ExchangeID,"CFFEX");

	g_puserapi->ReqQuoteInsert(&QuoteInsert,g_nOrdLocalID++);

	return;
}
void StartQuoteAction()
{  
	int SysID;
	if (g_puserapi==NULL)
	{
		printf("StartInputOrder  USERAPIδ����");
		return ;
	}
	CUstpFtdcQuoteActionField QuoteAction;
	memset(&QuoteAction,0,sizeof(CUstpFtdcQuoteActionField));

	strcpy(QuoteAction.ExchangeID,"CFFEX");
	strcpy(QuoteAction.BrokerID,g_BrokerID);
	strcpy(QuoteAction.UserID,g_UserID);

	printf("input InvestorID��\n");
	scanf("%s",(QuoteAction.InvestorID));
	printf("InvestorID=[%s]\n",QuoteAction.InvestorID);
	getchar();

	printf("�����뱻�����۵���ϵͳ���۱�� QuoteSysID:\n");
	scanf("%d",&SysID);
	sprintf(QuoteAction.QuoteSysID,"%12d",SysID);
	printf(" QuoteSysID=[%s]\n",(QuoteAction.QuoteSysID));
	getchar();
	
	strcpy(QuoteAction.UserQuoteLocalID,"");
	QuoteAction.ActionFlag=USTP_FTDC_AF_Delete;
	sprintf(QuoteAction.UserQuoteActionLocalID,"%012d",g_nOrdLocalID++);

	g_puserapi->ReqQuoteAction(&QuoteAction,g_nOrdLocalID++);

	return ;
}
void StartForQuote()
{
	if (g_puserapi==NULL)
	{
		printf("StartInputOrder  USERAPIδ����");
		return ;
	}
	CUstpFtdcReqForQuoteField ReqForQuote;
	memset(&ReqForQuote,0,sizeof(CUstpFtdcReqForQuoteField));
	strcpy(ReqForQuote.ExchangeID,"CFFEX");
	strcpy(ReqForQuote.BrokerID,g_BrokerID);
	strcpy(ReqForQuote.UserID,g_UserID);

	printf("input InvestorID��\n");
	scanf("%s",(ReqForQuote.InvestorID));
	printf("InvestorID=[%s]\n",ReqForQuote.InvestorID);

	printf("input InstrumentID��\n");
	scanf("%s",(ReqForQuote.InstrumentID));
	printf("InstrumentID=[%s]\n",(ReqForQuote.InstrumentID));
	getchar();
	
	sprintf(ReqForQuote.ReqForQuoteID,"%012d",g_nOrdLocalID++);

	g_puserapi->ReqForQuote(&ReqForQuote,g_nOrdLocalID++);

	return ;

}
//---------
void StartOrderAction()
{
	/*֧��ϵͳ�����źͱ��ر��������ֳ�����ʽ*/
	//-----------------------ϵͳ�����ų���----------------------------//
	int SysID;
	CUstpFtdcOrderActionField OrderAction;
	memset(&OrderAction,0,sizeof(CUstpFtdcOrderActionField));
	if (g_puserapi==NULL)
	{
		printf("StartOrderAction  USERAPIδ����");
		return ;
	}

	strcpy(OrderAction.ExchangeID,"CFFEX");
	strcpy(OrderAction.BrokerID,g_BrokerID);
	strcpy(OrderAction.UserID,g_UserID);
    strcpy(OrderAction.InvestorID,"01937643");
//	strcpy(OrderAction.OrderSysID,"01937643");
//	printf("������ϵͳ�����ţ�");
//	scanf("%d",&SysID);
    sprintf(OrderAction.OrderSysID,"%12d",g_drop_OrderSysID);
//	printf("����ϵͳ������[%s]\n",OrderAction.OrderSysID);
	strcpy(OrderAction.UserOrderLocalID,"");
	OrderAction.ActionFlag=USTP_FTDC_AF_Delete;
	sprintf(OrderAction.UserOrderActionLocalID,"%012d",g_nOrdLocalID++);

	g_puserapi->ReqOrderAction(&OrderAction,g_nOrdLocalID++);

	return ;
	//-----------------------ϵͳ�����ų���----------------------------//

 
	//-----------------------���ر����ų���----------------------------//
    /*
         int LocalID;
         CUstpFtdcOrderActionField OrderAction;
         memset(&OrderAction,0,sizeof(CUstpFtdcOrderActionField));
         if (g_puserapi==NULL)
         {
                   printf("StartOrderAction  USERAPIδ����");
                   return ;
         }
         strcpy(OrderAction.ExchangeID,"CFFEX");
         strcpy(OrderAction.BrokerID,g_BrokerID);
         strcpy(OrderAction.UserID,g_UserID);
		 
		 printf("input InvestorID\n");
		 scanf("%s",(OrderAction.InvestorID));
		 printf("InvestorID=[%s]\n",OrderAction.InvestorID);
         
         printf("�����뱾�ر�����:");
         scanf("%d",&LocalID);
         sprintf(OrderAction.UserOrderLocalID,"%012d",LocalID);

         printf("�������ر�����[%s]\n",OrderAction.UserOrderLocalID );
         strcpy(OrderAction.OrderSysID,"");
         
         OrderAction.ActionFlag=USTP_FTDC_AF_Delete;
         sprintf(OrderAction.UserOrderActionLocalID,"%012d",g_nOrdLocalID++);
         
         g_puserapi->ReqOrderAction(&OrderAction,g_nOrdLocalID++);
         
         return ;
    */
	//-----------------------���ر����ų���----------------------------//

}

void StartQueryExchange()
{
	CUstpFtdcQryExchangeField QryExchange;
	if (g_puserapi==NULL)
	{
		printf("StartQueryExchange  USERAPIδ����");
		return ;
	}

	strcpy(QryExchange.ExchangeID,"CFFEX");
	g_puserapi->ReqQryExchange(&QryExchange,g_nOrdLocalID++);
	return ;
}

void StartQryTrade()
{
	CUstpFtdcQryTradeField QryTrade;
	memset(&QryTrade,0,sizeof(CUstpFtdcQryTradeField));
	if (g_puserapi==NULL)
	{
		printf("StartQryTrade  USERAPIδ����");
		return ;

	}
	strcpy(QryTrade.ExchangeID,"CFFEX");
	strcpy(QryTrade.BrokerID,g_BrokerID);
	strcpy(QryTrade.UserID,g_UserID);
	//strcpy(QryTrade.TradeID,"");
	g_puserapi->ReqQryTrade(&QryTrade,g_nOrdLocalID++);
	return ;
}
void StartQryOrder()
{
	CUstpFtdcQryOrderField QryOrder;
	memset(&QryOrder,0,sizeof(CUstpFtdcQryOrderField));
	if (g_puserapi==NULL)
	{
		printf("StartQryOrder  USERAPIδ����");
		return ;

	}
	strcpy(QryOrder.ExchangeID,"CFFEX");
	strcpy(QryOrder.BrokerID,g_BrokerID);
	strcpy(QryOrder.UserID,g_UserID);
	//strcpy(QryOrder.OrderSysID,"");
	g_puserapi->ReqQryOrder(&QryOrder,g_nOrdLocalID++);
    QMetaObject::invokeMethod(object, "insertoUndealed",Q_ARG(QVariant, "abc1"),Q_ARG(QVariant, '1'),Q_ARG(QVariant, '1'),Q_ARG(QVariant, '2'),Q_ARG(QVariant, 3260),Q_ARG(QVariant, "IF1509"));
	return ;
}

void StartQryInvestorAccount()
{
	CUstpFtdcQryInvestorAccountField QryInvestorAcc;
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorAccount  USERAPIδ����");
		return ;

	}
	memset(&QryInvestorAcc,0,sizeof(CUstpFtdcQryInvestorAccountField));
	strcpy(QryInvestorAcc.BrokerID,g_BrokerID);
//	strcpy(QryInvestorAcc.InvestorID,"8");
	g_puserapi->ReqQryInvestorAccount(&QryInvestorAcc,g_nOrdLocalID++);

	return ;
}

void StartQryUserInvestor()
{
	CUstpFtdcQryUserInvestorField QryUserInvestor;
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorAccount  USERAPIδ����");
		return ;

	}
	memset(&QryUserInvestor,0,sizeof(CUstpFtdcQryUserInvestorField));
	strcpy(QryUserInvestor.BrokerID,g_BrokerID);
	strcpy(QryUserInvestor.UserID,g_UserID);
	g_puserapi->ReqQryUserInvestor(&QryUserInvestor,g_nOrdLocalID++);
	return ;
}

void StartQryInstrument()
{
	CUstpFtdcQryInstrumentField QryInstrument;
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorAccount  USERAPIδ����");
		return ;

	}
	memset(&QryInstrument,0,sizeof(CUstpFtdcQryInstrumentField));
	strcpy(QryInstrument.ExchangeID,"CFFEX");
	//strcpy(QryInstrument.InstrumentID,"IF1206");
	g_puserapi->ReqQryInstrument(&QryInstrument,g_nOrdLocalID++);
	return ;
}

void StartQryTradingCode()
{
	CUstpFtdcQryTradingCodeField QryTradingCode;
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorAccount  USERAPIδ����");
		return ;

	}
	strcpy(QryTradingCode.ExchangeID,"CFFEX");
	strcpy(QryTradingCode.BrokerID,g_BrokerID);
	strcpy(QryTradingCode.UserID,g_UserID);
	//strcpy(QryTradingCode.InvestorID,"1");
	g_puserapi->ReqQryTradingCode(&QryTradingCode,g_nOrdLocalID++);
	return ;
}

void StartQryInvestorPosition()
{
	CUstpFtdcQryInvestorPositionField QryInvestorPosition;
	memset(&QryInvestorPosition,0,sizeof(CUstpFtdcQryInvestorPositionField));
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorPosition  USERAPIδ����");
		return ;
	}
	strcpy(QryInvestorPosition.ExchangeID,"CFFEX");
	strcpy(QryInvestorPosition.BrokerID,g_BrokerID);
	printf("��Ͷ���߱�ţ�");
	scanf("%s",(QryInvestorPosition.InvestorID));
//	strcpy(QryInvestorPosition.InstrumentID,"");
	g_puserapi->ReqQryInvestorPosition(&QryInvestorPosition,g_nOrdLocalID++);
	return;
}

void StartUpdatePassword()
{
	CUstpFtdcUserPasswordUpdateField PasswordUpd;
	memset(&PasswordUpd,0,sizeof(CUstpFtdcUserPasswordUpdateField));
	if (g_puserapi==NULL)
	{
		printf("StartQryInvestorPosition  USERAPIδ����");
		return ;
	}
	strcpy(PasswordUpd.BrokerID,g_BrokerID);
	strcpy(PasswordUpd.UserID,g_UserID);
	printf("���������룺");
	scanf("%s",(PasswordUpd.OldPassword));
	printf("�����������룺");
	scanf("%s",(PasswordUpd.NewPassword));
	g_puserapi->ReqUserPasswordUpdate(&PasswordUpd,g_nOrdLocalID++);
	return;
}

void StartLogOut()
{
	CUstpFtdcReqUserLogoutField UserLogOut;
	memset(&UserLogOut,0,sizeof(CUstpFtdcReqUserLogoutField));
	strcpy(UserLogOut.BrokerID,g_BrokerID);
	strcpy(UserLogOut.UserID,g_UserID);
	
	g_puserapi->ReqUserLogout(&UserLogOut,g_nOrdLocalID++);
}

void StartQueryFee()
{
	printf("�ڲ�ѯ��������\n");
	CUstpFtdcQryInvestorFeeField InvestorFee;
	memset(&InvestorFee,0,sizeof(CUstpFtdcQryInvestorFeeField));
	strcpy(InvestorFee.BrokerID,g_BrokerID);
	strcpy(InvestorFee.UserID,g_UserID);
	g_puserapi->ReqQryInvestorFee(&InvestorFee,g_nOrdLocalID++);
}

void StartQueryMargin()
{
	printf("�ڲ�ѯ��֤����\n");
	CUstpFtdcQryInvestorMarginField InvestorMargin;
	memset(&InvestorMargin,0,sizeof(CUstpFtdcQryInvestorMarginField));
	strcpy(InvestorMargin.BrokerID,g_BrokerID);
	strcpy(InvestorMargin.UserID,g_UserID);
	g_puserapi->ReqQryInvestorMargin(&InvestorMargin,g_nOrdLocalID++);
}

void StartQueryComplianceParam()
{
	printf("�ڲ�ѯ�Ϲ����\n");
	CUstpFtdcQryComplianceParamField ComplianceParam;
	memset(&ComplianceParam,0,sizeof(CUstpFtdcQryComplianceParamField));
	strcpy(ComplianceParam.BrokerID,g_BrokerID);
	strcpy(ComplianceParam.UserID,g_UserID);
	printf("��Ͷ���߱�ţ�");
	scanf("%s",(ComplianceParam.InvestorID));
	g_puserapi->ReqQryComplianceParam(&ComplianceParam,g_nOrdLocalID++);
}

#ifdef WIN32
int WINAPI OrderFunc(LPVOID pParam)
#else
void * OrderFunc(void *pParam)
#endif
{
    ShowManu();
    g_choose=18;
    while(1){
	 	switch(g_choose)
	 	{
	 		case 0:
	 			StartLogOut();
	 			exit(0);	 			
	 		case 1:
	 			StartInputOrder ();
                g_choose=18;
	 			break;
	 		case 2:
	 			StartOrderAction();
                g_choose=18;
	 			break;
	 		case 3:
	 			StartQryOrder();
                g_choose=18;
	 			break;
	 		case 4:
	 			StartQryTrade();
                g_choose=18;
	 			break;
	 		case 5:
	 			StartQryInvestorAccount();
                g_choose=18;
	 			break;
	 		case 6:
	 			StartQryTradingCode();
                g_choose=18;
	 			break;
	 		case 7:
	 			StartQueryExchange();
                g_choose=18;
	 			break;
	 		case 8:
	 			StartQryInstrument();
                g_choose=18;
	 			break;
	 		case 9:
	 			StartQryUserInvestor();
                g_choose=18;
	 			break;
	 		case 10:
	 			StartQryInvestorPosition();
                g_choose=18;
	 			break;
	 		case 11:
	 			StartUpdatePassword();
                g_choose=18;
	 			break;
			case 12:
				StartQueryFee();
                g_choose=18;
				break;
			case 13:
				StartQueryMargin();
                g_choose=18;
				break;
			case 14:
				StartQueryComplianceParam();
                g_choose=18;
				break;
			case 15:
				StartQuoteInsert();
                g_choose=18;
				break;
			case 16:
				StartQuoteAction();
                g_choose=18;
				break;
			case 17:
				StartForQuote();
                g_choose=18;
				break;
	 		default:
//	 			printf("Input Error\n");
	 			break;		 			 	 		
	 	}
        usleep(200);
	}
	return 0;
}

bool StartAutoOrder()
{	
	//int dwIDThread;
	unsigned long dwIDThread;
	THREAD_HANDLE hThread;	/**< �߳̾�� */
	bool ret = true;
#ifdef WIN32
	hThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)OrderFunc,NULL,0,&dwIDThread);
	if(hThread==NULL)
	{
		ret = false;
	}
	SetThreadPriority(hThread,THREAD_PRIORITY_TIME_CRITICAL);
	ResumeThread(hThread);
#else
	ret = (::pthread_create(&hThread,NULL,&OrderFunc , NULL) == 0);
	
#endif
	return ret;
}

void StartTest()
{
	switch(g_nSwitch){
		case 1:
		case 2:
		case 3:
		case 4:
            StartAutoOrder();
			break;
		case 5:
			printf("StartInputOrder \n");
			StartInputOrder();
			break;
		case 6:
			printf("StartOrderAction \n");
			StartOrderAction();
			break;
		case 7:
			printf("StartQueryExchange \n");
			StartQueryExchange();
			break;
		case 8:
			printf("StartQryInvestorAccount \n");
			StartQryInvestorAccount();
			break;
		case 9:
			printf("StartQryUserInvestor \n");
			StartQryUserInvestor();
			break;
		case 10:
			printf("StartQryInstrument \n");
			StartQryInstrument();
			break;
		case 11:
			printf("StartQryTradingCode \n");
			StartQryTradingCode();
			break;
		case 12:
			printf("StartOuoteInsert \n");
			StartQuoteInsert();
			break;
		case 13:
			printf("StartQuoteAction \n");
			StartQuoteAction();
			break;
		case 14:
			printf("StartForQuote \n");
			StartForQuote();
			break;
		default :
			printf("Input arg Error\n");
			break;
	}

	return ;
}
