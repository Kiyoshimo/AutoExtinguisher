

#include <locale.h>
#include <iostream>
#include <string>
#include <conio.h>	//按键读取
#include "..\..\图像识别\图像识别\loc.h"	//坐标位置

#include "..\CnComm.h"	//Com口h档
using namespace std;


//! 样例程序0
class HelloComm : public CnComm
{	//! \sa CnComm::OnReceive()
	void OnReceive()
	{
		TCHAR buffer[1024];
		setlocale(LC_ALL, "chs");// Unicode下中文显示不出 配置一下 CBC 不支持 "chs"
		_tprintf(_T("\nRecv:%s\n"), ReadString(buffer, 1024));
	}
};
//! Main()  COM1 ---字符串----> COM4 (波特率9600)
int main()
{
	HelloComm Com;//! 默认模式 重叠IO 监视线程
	int CP = 6;	//COM口
	Com.Open(CP, 9600);

	std::cout << "Com:" << CP <<"已打开"<< std::endl;
	system("pause");//暂停
	while (1) {
		/*
		 *传char[]给arduino
		 *输出格式：("水平角度","竖直角度","水泵力度","校验位(前三项之和)") 
		 */
		string str ;
		cout << endl << endl;
		str =to_string(Fx)		+ ","
			+ to_string(Fy)		+ ","
			+ to_string(Pump)	+ ","
			+ to_string(CE)		;


		cout<<"输出数据"<<str << endl;
		char c[20];
		const char *c_str();
		strcpy_s(c,str.c_str());

	
		if (_kbhit()) {if (_getch() == 27) { break; }}		//按住esc退出
		
		Com.Write(_T(c));
		
		Sleep(1000);
		
	}
	cout << "Com:" << CP << "即将关闭" <<endl;
	system("pause");//暂停

	return 0;
}

