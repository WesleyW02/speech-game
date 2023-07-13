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

//����ݽ�������
class SpeechManager
{
public:
	SpeechManager();//����
	//�˵�����
	void show_menu();
	//�˳�ϵͳ
	void exit_system();

	//��ʼ������������
	void InitSpeech();

	//����12��ѡ��
	void create_speaker();

	//��ʼ������Ա����
	void StartSpeech();

	//��ǩ
	void speechDraw();

	//������Ա����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼����
	void saveRecord();

	//���������¼
	void loadRecord();

	//��ʾ�����¼��Ϣ
	void showRecord();
	
	//�ļ�Ϊ�ձ�־
	bool fileIsEmpty;

	//��ձ�����¼
	void clearRecord();

	//�����¼������Ϣ
	map<int, vector<string>> m_Record;//�����;�����Ϣ

	vector<int> v1;//���б���ѡ��

	vector<int> v2;//��һ�ֽ���ѡ�֣��ڶ��ֲ���ѡ��

	vector<int> vVictory;//ǰ����ѡ��
	//��ű�źͶ�Ӧ����ѡ�ֵ�����
	map<int, Speaker> m_Speaker;
	int m_Index;//��������
	~SpeechManager();//����
};