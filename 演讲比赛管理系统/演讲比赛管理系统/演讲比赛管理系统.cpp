#include<iostream>
#include"speechmanger.h"
#include<ctime>
using namespace std;

//测试12名选手创建
void test01(SpeechManager sm)
{
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "选手编号：" << it->first << " 姓名： " << it->second.m_Name << " 选手分数：" << it->second.score[0] << endl;
	}
}

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	//创建管理类对象
	SpeechManager sm;
	int choice = 0;//接收用户输入
	
	//test01(sm);//测试12名选手创建
	while (true)
	{
		sm.show_menu();
		cout << "请输入你的选择： " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.StartSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exit_system();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	return 0;
}