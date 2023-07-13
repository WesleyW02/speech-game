#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>

//设计演讲管理类
class SpeechManager
{
public:
	SpeechManager();//构造
	//菜单功能
	void show_menu();
	//退出系统
	void exit_system();

	//初始化容器和属性
	void InitSpeech();

	//创建12名选手
	void create_speaker();

	//开始比赛成员函数
	void StartSpeech();

	//抽签
	void speechDraw();

	//比赛成员函数
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录函数
	void saveRecord();

	//加载往届记录
	void loadRecord();

	//显示往届记录信息
	void showRecord();
	
	//文件为空标志
	bool fileIsEmpty;

	//清空比赛记录
	void clearRecord();

	//往届记录具体信息
	map<int, vector<string>> m_Record;//届数和具体信息

	vector<int> v1;//所有比赛选手

	vector<int> v2;//第一轮晋级选手，第二轮参赛选手

	vector<int> vVictory;//前三名选手
	//存放编号和对应具体选手的容器
	map<int, Speaker> m_Speaker;
	int m_Index;//比赛轮数
	~SpeechManager();//析构
};