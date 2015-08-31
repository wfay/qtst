///@system	 中金所行情源
///@company  上海金融期货信息技术有限公司
///@file	 CCffexMs
///@brief	 接受中金所的行情，保存并提供客户端的介入
///@history 
///20121119: 徐忠华 创建
//////////////////////////////////////////////////////////////////////

#include "profile.h"
#include "USTPMDClient.h"
#include "custom.hpp"
char *INI_FILE_NAME = "mduserdemo.ini";
extern MyClass tradepanel;
void* Msclient(void*)
{
	TIniFile tf;
	char tmp[256];	

    if (!tf.Open(INI_FILE_NAME))
    {
        printf("can not find\n");
        exit(-1000);
    }

    int marketnum = tf.ReadInt("COMMON","MARKETDATANUM",1);
	int i = 0;

	for(;i<marketnum;i++)
	{
		sprintf(tmp,"MARKETDATA%d",i+1);
		CUstpMs ustpMs;
        ustpMs.InitInstance(tmp,INI_FILE_NAME,&tradepanel);
	}
    while(false)
	{
		SLEEP_SECONDS(5000);
	}
    return 0;
}
