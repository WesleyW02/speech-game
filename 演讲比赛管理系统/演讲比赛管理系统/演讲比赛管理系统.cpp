#include<iostream>
#include"speechmanger.h"
#include<ctime>
using namespace std;

//����12��ѡ�ִ���
void test01(SpeechManager sm)
{
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << " ������ " << it->second.m_Name << " ѡ�ַ�����" << it->second.score[0] << endl;
	}
}

int main()
{
	//���������
	srand((unsigned int)time(NULL));
	//�������������
	SpeechManager sm;
	int choice = 0;//�����û�����
	
	//test01(sm);//����12��ѡ�ִ���
	while (true)
	{
		sm.show_menu();
		cout << "���������ѡ�� " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.StartSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exit_system();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	return 0;
}