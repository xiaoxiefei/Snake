/*
* @	Copyright(C++)
* @	Instrument	:	Visual studio 2022
* @	Author		:	xie
* @	Version		:	v1.1.1
* @	Date		:	2022-10-04
*/

#include<iostream>
#include<ctime>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include<fstream>
#include <WINDOWS.H>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include<thread>
using namespace std;

#define Wallnumber 5

/*******************  全局变量  **********************/
int coord_x[100] = { 26 };
int coord_y[100] = { 12 };
int wall_x[100];
int wall_y[100];
int food_x = 0;
int food_y = 0;
int last_ch = 0;
int ch_number = 0;
int last_ch_number = 0;
int Score = 0;

void Print(int n);
void PlayMp3();
void EatPlayMp3();
void PushPlayMp3();
void PushMusic();
void EatMusic();
void Music();
/**************************************************************************/

/************************************  播放音乐  *****************************/
void Music()
{
	while (1) {
		PlayMp3();
	}
	//PlaySound("C:\\Users\\Administrator\\Desktop\\heart.wav", NULL, SND_FILENAME );
}

/************************************************
*
* @播放背景音乐
*
************************************************/
void PlayMp3()
{
	char buf[128];
	char str[128] = { 0 };
	int i = 0;
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	mciOpen.lpstrDeviceType = "mpegvideo";

	//	背景音乐绝对路径
	mciOpen.lpstrElementName = "C:\\Users\\Administrator\\Desktop\\heart.wav";
	mciOpen.lpstrElementName = "C:\\Users\\Administrator\\Desktop\\heart.wav";
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		return;
	}
	return;
}

void EatMusic()
{
	EatPlayMp3();
	Print(Score);
	return;
}

/************************************************
* 
* @播放贪吃蛇吃到食物的音效
* 
************************************************/
void EatPlayMp3()
{
	char buf[128];
	char str[128] = { 0 };
	int i = 0;
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	mciOpen.lpstrDeviceType = "mpegvideo";

	//	吃食物音效的绝对路径
	mciOpen.lpstrElementName = "F:\\CloudMusic\\吃食物.wav";
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		return;
	}
	return;
}

/************************************************
*
* @播放贪吃蛇碰撞到墙的音效
*
************************************************/
void PushMusic()
{
	EatPlayMp3();
	Print(Score);
	return;
}
void PushPlayMp3()
{
	char buf[128];
	char str[128] = { 0 };
	int i = 0;
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	mciOpen.lpstrDeviceType = "mpegvideo";

	// 碰撞的音效绝对路径
	mciOpen.lpstrElementName = "F:\\CloudMusic\\碰撞.wav";
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		return;
	}
}
/***************************************************************************************************/


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//全局句柄


/********************************  Map类  ***********************************/
class Map
{
public:
	void GameMap();					//背景
	void Move(int ch);				//移动
	void Move_();
	void HideCursor();				//隐藏光标
	int Eat(int ch);				//吃
	void food_position();			//放食物
	void temp(int x, int y);		//更新
	int Push();						//检测碰撞
	void Wall();					//障碍物
};
/******************************************************************************/


/************************************************
*
* @	定位光标
*
************************************************/
void gotoPos(SHORT x, SHORT y)                   
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

/************************************************
*
* @	写文件，记录最好成绩
*
************************************************/
void Write(int score)                            
{
	ofstream write;
	write.open("贪吃蛇.txt", ios::out);
	write << score;
}

/************************************************
*
* @	读文件，查看最好成绩
*
************************************************/
void Read()                                      
{
	int score;
	ifstream read("贪吃蛇.txt", ios::in);
	read.seekg(0, ios::beg);
	while (read >> score)
	{
		if (Score >= score)
		{
			Write(Score);
			gotoPos(26, 16);
			cout << "恭喜你，创下新纪录！  " << Score;
		}
		else
		{
			gotoPos(26, 16);
			cout << "历史记录为:" << score;
		}
	}
}

/************************************************
*
* @	放置障碍物
*
************************************************/
void Map::Wall()  
{
	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	for (i = 0; i < Wallnumber; i++)
	{
		gotoPos(22, i + 12);
		wall_x[i] = 22;
		wall_y[i] = i + 12;
		cout << "■";
	}

}

/************************************************
*
* @	判断食物放置的位置是否有效
*
************************************************/
int judge_food()                                     
{
	int i, k = 0,w=0;
	for (i = 0; i <= Score; i++)
	{
		if (coord_x[i] == food_x && coord_y[i] == food_y)
			k = 1;
	}
	for (i = 0; i <= Score; i++)
	{
		for (int j = 0; j < Wallnumber; j++)
			if (food_x == wall_x[j] && food_y == wall_y[j])
				w = 1;
	}
	if (k == 1)return 1;		//食物与蛇碰撞
	if (w == 1)return 1;
	if (food_x % 2 != 0)return 1;
	if ((food_x < 3 || food_x >= 52))return 1;
	if (food_y < 3 || food_y >= 28)return 1;
	else return 0;
}

/************************************************
*
* @	放置食物
*
************************************************/
void Map::food_position()   
{
	gotoPos(30, 28);
	cout << "      ";
	srand(int(time(0)));
	while (1)
	{
		food_x = rand() % 45;
		food_y = rand() % 25;
		if (judge_food() == 0)
			break;
	}

	//	设置当前颜色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	{
		gotoPos(food_x, food_y);
		cout << "■";
	}
	gotoPos(30, 28);
	cout << "放置食物   " << Score;
	gotoPos(30, 29);
	cout << "位置" << food_x << "  " << food_y << "   ";
}

/************************************************
*
* @	绘制地图
*
************************************************/
void Map::GameMap()                                     
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoPos(1, 0);
	for (int i = 0; i < 25; i++)
		cout << endl << "●";
	gotoPos(2, 1);
	for (int i = 0; i < 25; i++)
		cout << "●";
	cout << endl;
	gotoPos(2, 25);
	for (int i = 0; i < 25; i++)
		cout << "●";
	for (SHORT i = 1; i < 25; i++)
	{
		gotoPos(50, i);
		cout << "●";
	}
	gotoPos(25, 12);
}

/************************************************
*
* @	控制移动
*
************************************************/
void Map::Move(int ch)                                          
{
	if (ch == 0x48)//上
		ch_number = 1;
	else if (ch == 0x50)//下
		ch_number = 4;
	else if (ch == 0x4b)//左
		ch_number = 2;
	else if (ch == 0x4d)//右
		ch_number = 3;

	//	不能反方向移动
	if (last_ch_number + ch_number == 5)
	{
		if (ch == 0x48)
			ch = 0x50;
		else if (ch == 0x50)
			ch = 0x48;
		else if (ch == 0x4b)
			ch = 0x4d;
		else if (ch == 0x4d)
			ch = 0x4b;
	}
	Print(0);
	int now_x = coord_x[Score];
	int now_y = coord_y[Score];
	int m = coord_x[0];
	int n = coord_y[0];
	int head_x, head_y;
	if (ch == 0x48)//上
	{
		coord_y[0] -= 1;
		ch_number = 1;
	}
	else if (ch == 0x50)//下
	{
		coord_y[0] += 1;
		ch_number = 4;
	}
	else if (ch == 0x4b)//左
	{
		coord_x[0] -= 2;
		ch_number = 2;
	}
	else if (ch == 0x4d)//右
	{

		coord_x[0] += 2;
		ch_number = 3;
	}
	head_x = coord_x[0];
	head_y = coord_y[0];
	int judge = Eat(ch);
	if (judge == 0)
	{

		if (last_ch == ch || (last_ch_number + ch_number == 5))
		{
			temp(m, n);
			Print(1);
			if (Score < 30)
				Sleep(400 - (Score * 10));
			else
				Sleep(100);
		}
		else if (last_ch != ch && ch != 224)
		{
			temp(m, n);
			Print(1);
			if (Score < 30)
				Sleep(400 - (Score * 10));
			else
				Sleep(100);
		}
	}
	if (judge == 1)
	{

		food_position();
		coord_x[0] = m;
		coord_y[0] = n;
		Print(1);
		if (Score < 30)
			Sleep(400 - (Score * 10));
		else
			Sleep(100);
		coord_x[0] = head_x;
		coord_y[0] = head_y;
		temp(m, n);
		gotoPos(55, 13);
		cout << "当前分数：" << Score;

	}
	if (ch != 224)
	{
		last_ch = ch;
	}
	gotoPos(30, 29);
}

/************************************************
*
* @	打印蛇
*
************************************************/
void Print(int n)                             
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	int i, j;
	if (n == 0)
	{
		for (i = 0; i <= Score; i++)
		{
			gotoPos(coord_x[i], coord_y[i]);
			cout << "  ";
		}
	}
	if (n == 1)
	{
		for (i = 0; i <= Score; i++)
		{
			gotoPos(coord_x[i], coord_y[i]);
			cout << "■";
		}
	}
}

/************************************************
*
* @	数字值转换（更新蛇的位置）
*
************************************************/
void Map::temp(int x, int y)                                      
{
	for (int i = Score; i > 0; i--)
	{
		if (i == 1)
		{
			coord_x[i] = x;
			coord_y[i] = y;
		}
		else
		{
			coord_x[i] = coord_x[i - 1];
			coord_y[i] = coord_y[i - 1];
		}
	}
}

/************************************************
*
* @	游戏开始/结束
*
************************************************/
void Map::Move_()                                       
{
	Map a;
	int ch;
	int sign = 0;
	do
	{
		if (Push() == 1)
		{
			thread Push(PushMusic);
			Push.detach();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			gotoPos(26, 12);
			cout << "游戏结束!";
			gotoPos(26, 14);
			cout << "你的分数为:" << Score;
			Read();
			break;
		}
		if (_kbhit())
		{

			ch = _getch();
			//ch = _getch();
			sign = 1;
		}
		if (sign)
		{

			a.Move(ch);

			last_ch = ch;
			last_ch_number = ch_number;
		}
	} while (true);
}

/************************************************
*
* @	蛇吃食物
*
************************************************/
int Map::Eat(int ch)   
{
	if (coord_x[0] == food_x && coord_y[0] == food_y)
	{
		Score++;
		coord_x[0] = food_x;
		coord_y[0] = food_y;
		thread mu1(EatMusic);
		mu1.detach();
		return 1;
	}
	else
	{
		return 0;
	}
}


/************************************************
*
* @	判断蛇是否碰撞/游戏结束
*
************************************************/
int Map::Push()                            
{
	int i,k=0;
	if (coord_x[0] <= 0 || coord_x[0] >= 50)
		return 1;
	if (coord_y[0] < 2 || (coord_y[0] >= 25))
		return 1;
	if (coord_x[Score] == coord_x[0] && coord_y[Score] == coord_y[0] && Score > 1)
		return 1;
	for (i = 2; i <= Score; i++)
		if (coord_x[0] == coord_x[i] && coord_y[0] == coord_y[i])
			break;
	if (i < Score)return 1;
	for (int j = 0; j < Wallnumber; j++)
		if (coord_x[0] == wall_x[j] && coord_y[0] == wall_y[j])
			k = 1;
	if (k == 1)return 1;
	else return 0;
}
void Map::HideCursor()                                   //隐藏光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}


/************************************************
*
* @	函数入口
*
************************************************/
int main()
{
	thread  mu(Music);

	//thread  mu1(Music);
	mu.detach();
	//mu1.detach();
	Map Game;
	Game.Wall();
	Game.GameMap();
	Game.food_position();
	Game.HideCursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoPos(26, 12);
	cout << "■";
	Game.Move_();
	while (1);
}

