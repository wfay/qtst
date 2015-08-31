///@system	 飞马行情接受系统
///@company  上海金融期货信息技术有限公司
///@file	 USTPMDHandler.h
///@brief	 api实现
///@history 
///20130502: 徐忠华 创建
//////////////////////////////////////////////////////////////////////
#include "USTPFtdcMduserApi.h"
#include "USTPMDHandler.h"
#include "custom.hpp"
#include <ctime>
extern char *INI_FILE_NAME;
using namespace::std;
CUSTPMDHandler::CUSTPMDHandler(CUstpFtdcMduserApi *pUserApi,char *  number,MyClass* t) : m_pUserApi(pUserApi)
{
    time_t tt = time(0);   // get time now
    char filename[50];
        struct tm * now = localtime( & tt );
        sprintf(filename,"%d-%d-%d.csv",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
 //       cout << (now->tm_year + 1900) << '-'
 //            << (now->tm_mon + 1) << '-'
 //            <<  now->tm_mday
 //            << endl;
    panel=t;
	strcpy(m_number,number);
	if (!tf.Open(INI_FILE_NAME))
	{
        printf("can not open ini file\n");
		exit(-1000);
    }
	tf.ReadString(m_number,"OutPutFile","output.csv",tmp,sizeof(tmp)-1);
    m_pFileOutput = fopen(filename,"wt");

}

CUSTPMDHandler::~CUSTPMDHandler() 
{
	fclose(m_pFileOutput);
}


void CUSTPMDHandler::OnFrontConnected()
{
 //   printf("Calling Front Connected\n");
//printf("read from panleshow:%s:",panel->current_show);
    CUstpFtdcReqUserLoginField reqUserLogin;
    strcpy(reqUserLogin.TradingDay, m_pUserApi->GetTradingDay());
	tf.ReadString(m_number,"BrokerID","",tmp,sizeof(tmp)-1);
	strcpy(reqUserLogin.BrokerID,tmp);
	tf.ReadString(m_number,"UserID","",tmp,sizeof(tmp)-1);
    strcpy(reqUserLogin.UserID, tmp);
	tf.ReadString(m_number,"PassWD","",tmp,sizeof(tmp)-1);
    strcpy(reqUserLogin.Password,tmp);
    strcpy(reqUserLogin.UserProductInfo, "mduserdemo v1.0");
    m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
}


void CUSTPMDHandler::OnFrontDisconnected() 
{
    printf("OnFrontDisconnected.\n");
}

void CUSTPMDHandler::OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	printf("OnRspQryTopic: %d ,%d\n",pDissemination->SequenceSeries,pDissemination->SequenceNo);
}

// 当客户端发出登录请求之后，该方法会被调用，通知客户端登录是否成功
void CUSTPMDHandler::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    printf("OnRspUserLogin:\n");
	printf("UserID:[%s] \n",pRspUserLogin->UserID);
	printf("ParticipantID:[%s] \n",pRspUserLogin->BrokerID);
    printf("DataCenterID:[%d] \n",pRspUserLogin->DataCenterID);
	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);

    if (pRspInfo->ErrorID != 0)
    {
        // login failed
        printf("Failed to login, errorcode=%d errormsg=%s requestid=%d chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
    }
 
	//订阅合约信息
    // 	char* contracts[3]={"","",""};
    // 	contracts[0]="*";
    // 	contracts[1]="IF1212";
    // 	contracts[2]="IF1303";
    //	m_pUserApi->SubMarketData(contracts, 3);
	
	int subnum = tf.ReadInt(m_number,"SubInsNum",0);
	char** contracts = new char*[subnum];
	int i=0;
	char instmp[128];
	for(;i<subnum;i++)
	{
		sprintf(instmp,"SubIns%d",i+1);
		tf.ReadString(m_number,instmp,"",tmp,sizeof(tmp)-1);
		contracts[i]=new char[strlen(tmp)+1];
		strncpy(contracts[i],tmp,strlen(tmp)+1);
	}
	m_pUserApi->SubMarketData(contracts, subnum);

	// 	char* uncontracts[3]={"","",""};
	// 	uncontracts[0]="IF1211";
	// 	uncontracts[1]="IF1212";
	// 	uncontracts[2]="IF1303";
	//	m_pUserApi->UnSubMarketData(uncontracts, 3);
#if 0
	int unsubnum = tf.ReadInt(m_number,"UnSubInsNum",0);
	char** uncontracts = new char*[unsubnum];
	i=0;
	for(;i<unsubnum;i++)
	{
		sprintf(instmp,"UnSubIns%d",i+1);
		tf.ReadString(m_number,instmp,"",tmp,sizeof(tmp)-1);
		uncontracts[i]=new char[strlen(tmp)+1];
		strncpy(uncontracts[i],tmp,strlen(tmp)+1);
	}
	m_pUserApi->UnSubMarketData(uncontracts, unsubnum);
#endif
}

///用户退出应答
void CUSTPMDHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	printf("OnRspUserLogout:\n");
	printf("UserID:[%s] \n",pRspUserLogout->UserID);
	printf("ParticipantID:[%s] \n",pRspUserLogout->BrokerID);
	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
}
extern void printOrderInfo(void);
// 深度行情通知，行情服务器会主动通知客户端
void CUSTPMDHandler::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pMarketData) 
{
    // 客户端按需处理返回的数据
 //   printf("read from panleshow:%s\n",panel->current_show);
//    printOrderInfo();
 //   if(!strcmp(pMarketData->InstrumentID,"IF1509"))
 //   {
//        printf("data matched\n");
 //       panel->IF1509.ask[panel->IF1509.idx]=pMarketData->AskPrice1;
 //       panel->IF1509.bid[panel->IF1509.idx++]=pMarketData->BidPrice1;
 //       panel->setdata_count_1(panel->IF1509.idx);
 //   }
    fprintf(m_pFileOutput,"%s,%s,%d,",pMarketData->InstrumentID,pMarketData->UpdateTime,pMarketData->UpdateMillisec);
	if (pMarketData->AskPrice1==DBL_MAX)
    {
        fprintf(m_pFileOutput,"%s,","");
    }
	else
    {
        fprintf(m_pFileOutput,"%f,",pMarketData->AskPrice1);
        if(!strcmp(panel->current_show,pMarketData->InstrumentID))
        {
            panel->setask(pMarketData->AskPrice1);
        }
    }

	if (pMarketData->BidPrice1==DBL_MAX)
    {
        fprintf(m_pFileOutput,"%s \n","");
    }
	else
    {
        fprintf(m_pFileOutput,"%f \n",pMarketData->BidPrice1);
        if(!strcmp(panel->current_show,pMarketData->InstrumentID))
        {
            panel->setbid(pMarketData->BidPrice1);
        }
    }
    fflush(m_pFileOutput);
}

// 针对用户请求的出错通知
void CUSTPMDHandler::OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    printf("OnRspError:\n");
    printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
    // 客户端需进行错误处理
}

///订阅合约的相关信息
void CUSTPMDHandler::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("Sub 返回订阅合约：%s \n",pSpecificInstrument->InstrumentID);
}

///订阅合约的相关信息
void CUSTPMDHandler::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("UnSub 返回订阅合约：%s \n",pSpecificInstrument->InstrumentID);
}
