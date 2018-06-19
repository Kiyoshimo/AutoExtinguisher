#pragma once
//FLAG �������趨
//FLAG ����ѡ��

#include "winBase.h" 
#include <cstdio>
#include <string>


BOOL Init(void);//��ʼ��
int ComOutPut(char inputString[100]);//���ͺ���
void Close(void);




HANDLE Rs_Port;
char inputString[100];







//���ͺ���
int ComOutPut(char inputString[100])
{


	int stringLength;
	DWORD TxNum = 0;
	stringLength = strlen(inputString); // ����
	TxNum = stringLength;
	WriteFile(Rs_Port, inputString, TxNum, &TxNum, NULL); //����

	return 0;
}




//��ʼ��
BOOL Init(void)
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

void Close(void) {
	CloseHandle(Rs_Port);//�رմ���
	printf("�رմ���,�������");
	system("PAUSE");

}


