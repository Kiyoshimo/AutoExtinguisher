
#include "windows.h" 
#include "winBase.h" 
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
BOOL Init(void);//�����ڡ���ʼ��
int ComOutPut(string str);//�����ڡ����ͺ���
void Close(void);//�����ڡ��ر�
int ComTest(void);//�����ڡ����Գ���

string m4str(int H, int V, int P, int C);//����λ���ϲ�����



//----------------------------------------------------------ȫ�����--------------------------------------------------------------------------------------------------------------------
HANDLE Rs_Port;//�����ڡ���������
char InputCharArray[100];//�����ڡ�����ַ���

int X_f, Y_f;//����λ���D��Ŀ��XY
int Angle_h=90, Angle_v = 90;//����λ���ŷ����Ƕ�
const int cam_h= 480, cam_w=640;//����λ������ͷ���泤��
const long cam_a_h=30, cam_a_w= 30;//����λ������ͷ��ǽǶ�
int Pump = 0;

//----------------------------------------------------------������--------------------------------------------------------------------------------------------------------------------

int main(void)
{
	ComTest();
}




//----------------------------------------------------------���ڿ���--------------------------------------------------------------------------------------------------------------------

int ComTest(void)//��������
{


	if (!Init()) return 0; //��ʼ��
	while (1) {

		printf("Enter char :");
		gets_s(InputCharArray); //���� 
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

int ComOutPut(string str)//���ͺ���
{
	
	char InputCharArray[100];
	int stringLength;
	DWORD TxNum = 0;
	
	int i;
	for (i = 0; i<str.length(); i++)
		InputCharArray[i] = str[i];
	InputCharArray[i] = '\0';
	
	stringLength = strlen(InputCharArray); // ����
	TxNum = stringLength;
	WriteFile(Rs_Port, InputCharArray, TxNum, &TxNum, NULL); //����

	return 0;
}

BOOL Init(void)//��ʼ��
{

	//Open the serial port 
	Rs_Port = CreateFile(LPTSTR("COM6"),	//FLAG ����ѡ��
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
	PortDCB.BaudRate = CBR_9600;////FLAG �������趨
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

void Close(void) //�رմ���
{
	CloseHandle(Rs_Port);
	printf("�رմ���,�������");
	system("PAUSE");

}


//----------------------------------------------------------��λ����--------------------------------------------------------------------------------------------------------------------
/*
int main(void)//��������
{


	if (!Init()) return 0; //
	//strcpy_s(InputCharArray, "90,90,0,180");
	string sout=m4str(Angle_h, Angle_v, Pump, (Angle_h + Angle_v + Pump));
	

	ComOutPut(InputCharArray);
	Sleep(1000);
	while (1) {

		printf("Enter char :");
		gets_s(InputCharArray); //���� 
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