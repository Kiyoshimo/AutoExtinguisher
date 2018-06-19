
#include "windows.h" 
#include "winBase.h" 
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
BOOL Init(void);//【串口】初始化
int ComOutPut(string str);//【串口】发送函数
void Close(void);//【串口】关闭
int ComTest(void);//【串口】测试程序

string m4str(int H, int V, int P, int C);//【定位】合并数据



//----------------------------------------------------------全域变数--------------------------------------------------------------------------------------------------------------------
HANDLE Rs_Port;//【串口】串口设置
char InputCharArray[100];//【串口】输出字符串

int X_f, Y_f;//【定位】圖像目標XY
int Angle_h=90, Angle_v = 90;//【定位】伺服马达角度
const int cam_h= 480, cam_w=640;//【定位】摄像头画面长宽
const long cam_a_h=30, cam_a_w= 30;//【定位】摄像头广角角度
int Pump = 0;

//----------------------------------------------------------主程序--------------------------------------------------------------------------------------------------------------------

int main(void)
{
	ComTest();
}




//----------------------------------------------------------串口控制--------------------------------------------------------------------------------------------------------------------

int ComTest(void)//主程序范例
{


	if (!Init()) return 0; //初始化
	while (1) {

		printf("Enter char :");
		gets_s(InputCharArray); //输入 
		string iS = InputCharArray;
		if (iS == "OFF") {
			printf("POWER OFF");
			break;
		}
		//ComOutPut(InputCharArray);
		ComOutPut(iS);
	}
	Close();

	return 0;
}

int ComOutPut(string str)//发送函数
{
	
	char InputCharArray[100];
	int stringLength;
	DWORD TxNum = 0;
	
	int i;
	for (i = 0; i<str.length(); i++)
		InputCharArray[i] = str[i];
	InputCharArray[i] = '\0';
	
	stringLength = strlen(InputCharArray); // 长度
	TxNum = stringLength;
	WriteFile(Rs_Port, InputCharArray, TxNum, &TxNum, NULL); //发送

	return 0;
}

BOOL Init(void)//初始化
{

	//Open the serial port 
	Rs_Port = CreateFile(LPTSTR("COM6"),	//FLAG 串口选择
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	DCB PortDCB;

	//Initialize the DCBlength member 
	PortDCB.DCBlength = sizeof(PortDCB);

	//Get the default port setting information. 
	GetCommState(Rs_Port, &PortDCB);

	//set BaudRate = 9600,no parity,one stopbit 
	PortDCB.BaudRate = CBR_9600;////FLAG 波特率设定
	PortDCB.ByteSize = 8;
	PortDCB.Parity = NOPARITY;
	PortDCB.StopBits = ONESTOPBIT;

	PortDCB.fBinary = TRUE;
	PortDCB.fParity = TRUE;
	PortDCB.fOutxCtsFlow = FALSE;
	PortDCB.fOutxDsrFlow = FALSE;
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE;
	PortDCB.fDsrSensitivity = FALSE;
	PortDCB.fTXContinueOnXoff = TRUE;
	PortDCB.fOutX = FALSE;
	PortDCB.fInX = FALSE;
	PortDCB.fErrorChar = FALSE;
	PortDCB.fNull = FALSE;
	PortDCB.fRtsControl = RTS_CONTROL_ENABLE;
	PortDCB.fAbortOnError = FALSE;

	if (!SetCommState(Rs_Port, &PortDCB))
	{
		printf("Unable to configure the serial port.\n");
		return FALSE;
	}

	//Retrieve the time-out parameters for all read and write operations 
	//on the port. 

	COMMTIMEOUTS CommTimeouts;

	GetCommTimeouts(Rs_Port, &CommTimeouts);


	CommTimeouts.ReadIntervalTimeout = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	CommTimeouts.ReadTotalTimeoutConstant = 0;

	CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant = 0;

	if (!SetCommTimeouts(Rs_Port, &CommTimeouts))
	{
		printf("Unable to set the time-out parameters.\n"); // error check 
		return FALSE;
	}

	return true;
}

void Close(void) //关闭串口
{
	CloseHandle(Rs_Port);
	printf("关闭串口,程序结束");
	system("PAUSE");

}


//----------------------------------------------------------定位运算--------------------------------------------------------------------------------------------------------------------
/*
int main(void)//主程序范例
{


	if (!Init()) return 0; //
	//strcpy_s(InputCharArray, "90,90,0,180");
	string sout=m4str(Angle_h, Angle_v, Pump, (Angle_h + Angle_v + Pump));
	

	ComOutPut(InputCharArray);
	Sleep(1000);
	while (1) {

		printf("Enter char :");
		gets_s(InputCharArray); //输入 
		string iS = InputCharArray;
		if (iS == "OFF") {
			printf("POWER OFF");
			break;
		}
		ComOutPut(InputCharArray);
	}
	Close();

	return 0;
}

string m4str(int H, int V, int P, int C) {
	string m4out = "";
	m4out =m4out +to_string(H);
	m4out = m4out + "," + to_string(V);
	m4out = m4out + "," + to_string(P);
	m4out = m4out + "," + to_string(C);
	return m4out;
}
*/