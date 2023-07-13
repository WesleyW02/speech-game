#include"speechmanger.h"
//����
SpeechManager::SpeechManager()
{
	this->InitSpeech();//��ʼ��
	this->create_speaker();//����ѡ��
	this->loadRecord();//��ȡ�����¼
}

//�˵�����
void SpeechManager::show_menu()
{
	cout << "******************************" << endl;
	cout << "****** ��ӭ�μ��ݽ����� ******" << endl;
	cout << "******* 1.��ʼ�ݽ����� *******" << endl;
	cout << "******* 2.�鿴�����¼ *******" << endl;
	cout << "******* 3.��ձ�����¼ *******" << endl;
	cout << "******* 0.�˳��������� *******" << endl;
	cout << "******************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exit_system()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);//�˳�ϵͳ
}

//��ʼ������������
void SpeechManager::InitSpeech()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();//��¼�������
	//������ʼ��
	this->m_Index = 1;
}

//����12��ѡ��
void SpeechManager::create_speaker()
{
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++)
	{
		string name = "ѡ��";
		name += name_seed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}

		//����ѡ�ֱ�ţ�����v1����
		this->v1.push_back(i + 10001);
		//����map����
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ʼ������Ա������������������
void SpeechManager::StartSpeech()
{
	//��һ�ֱ���
	this->m_Index=1;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3����ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4������ǰ������Ϣ
	this->saveRecord();

	//���ñ���
	this->InitSpeech();
	//����ѡ��
	this->create_speaker();
	//��ȡ�����¼
	this->loadRecord();

	cout << "���������ʽ������" << endl;
	system("pause");
	system("cls");//����
}

//��ǩ
//��ӡ����
void myprint(int val)
{
	cout << val << ", ";
}
void SpeechManager::speechDraw()
{
	cout << "�� <<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------" << endl;
	cout << "��ǩ���ݽ�˳������:" << endl;

	if (this->m_Index == 1)//��һ�ֱ���
	{
		random_shuffle(v1.begin(), v1.end());//�������
		for_each(v1.begin(), v1.end(), myprint);
	}
	else
	{//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(), myprint);
	}
	cout << endl;
	cout << "-----------------------------------" << endl;
	system("pause");
}

//������Ա����
void SpeechManager::speechContest()
{
	cout<< "------------��<<" << this->m_Index << ">>�ֱ�����ʽ��ʼ��------------"<< endl;

	vector<int> v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//׼����ʱ���������С��ɼ������������ͬ
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//��¼��Ա����6��һ�顣

	//��������ѡ��
	for (vector<int> ::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//60.0-100.0
			//cout << score << ", ";//�������
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//��������
		d.pop_back();//ȥ����ͷ�
		d.pop_front();//ȥ����߷�
		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����
		//cout << endl;

		//��ӡƽ����
		//cout << "��ţ�" << *it << " ����: " << this->m_Speaker[*it].m_Name << "ƽ���֣�" << avg << endl;
		//ƽ���ַ���m_Speaker��
		this->m_Speaker[*it].score[this->m_Index - 1] = avg;

		//��ֳɼ�������ʱС������
		groupScore.insert(make_pair(avg, *it));
		//ÿ6��ȡ��ǰ����
		if (num % 6 == 0)
		{
			int count = 0;
			cout << "��" << num / 6 << "С������ɼ�����:" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "ѡ�ֱ�ţ�" << mit->second << " ������ " << this->m_Speaker[mit->second].m_Name << " �ɼ���"
					<< this->m_Speaker[mit->second].score[this->m_Index - 1] << endl;
			}
			//ȡ��ǰ������������һ������
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end()&&count < 3; mit++,count++)
			{
				if (this->m_Index == 1)//��һ��
				{
					v2.push_back(mit->second);
				}
				else//�ڶ���
				{
					vVictory.push_back(mit->second);
				}
			}
			groupScore.clear();//��ʱС�����
			cout << endl;
		}
	}

	cout << "------------��<<" << this->m_Index << ">>�ֱ����Ѿ���ϣ�------------" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::showScore()
{
	cout << "------------��<<" << this->m_Index << ">>�ֽ���ѡ����Ϣ���£�------------" << endl;
	vector<int> v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v2;
	}
	else
	{
		v_Src = vVictory;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << this->m_Speaker[*it].m_Name << " �ɼ���"
			<< this->m_Speaker[*it].score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");//����
	this->show_menu();
}

//�����¼����
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//�������ʽ���ļ�,׷�ӷ�ʽд�ļ�
	
	//��ѡ������д���ļ�
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();//�ر��ļ�
	cout << "��¼������ϣ�" << endl;
	this->fileIsEmpty = false;
}

//�鿴�����¼
void SpeechManager::loadRecord()
{
	this->m_Record.clear();
	ifstream ifs;
	ifs.open("speech.csv", ios::in);//���ļ�
	if (!ifs.is_open())//��ʧ��
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "��¼�Ѿ������" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ��ǿ�
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�����ַ��Ż��ļ�
	string data;
	int index = 1;//����
	while (ifs >> data)
	{
		vector<string> v;
		//cout << data << endl;
		int pos = -1;//��,��λ��
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp<<endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	{
		cout << it->first << "�ھ���ţ� " << it->second[0] << "������" << it->second[1]<<endl;
	}*/
}

//��ʾ�����¼��Ϣ
void SpeechManager::showRecord()
{
	this->loadRecord();
	if (this->fileIsEmpty)
	{
		cout << " �ļ������ڻ��߼�¼Ϊ�գ�����" << endl;
	}
	else
	{
		for (int i = 1; i <= this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣� " << this->m_Record[i][1] << " "
				<< "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣� " << this->m_Record[i][3] << " "
				<< "������ţ�" << this->m_Record[i][4] << "�÷֣� " << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << " 1. ȷ��" << endl;
	cout << " 2. ȡ��" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);//ɾ��ԭ���ļ����������ļ�
		ofs.close();
		this->InitSpeech();//��ʼ��
		this->create_speaker();//����ѡ��
		this->loadRecord();//��ȡ�����¼
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager()
{

}