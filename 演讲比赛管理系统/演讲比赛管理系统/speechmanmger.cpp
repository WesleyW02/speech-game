#include"speechmanger.h"
//构造
SpeechManager::SpeechManager()
{
	this->InitSpeech();//初始化
	this->create_speaker();//创建选手
	this->loadRecord();//获取往届记录
}

//菜单功能
void SpeechManager::show_menu()
{
	cout << "******************************" << endl;
	cout << "****** 欢迎参加演讲比赛 ******" << endl;
	cout << "******* 1.开始演讲比赛 *******" << endl;
	cout << "******* 2.查看往届记录 *******" << endl;
	cout << "******* 3.清空比赛记录 *******" << endl;
	cout << "******* 0.退出比赛程序 *******" << endl;
	cout << "******************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exit_system()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);//退出系统
}

//初始化容器和属性
void SpeechManager::InitSpeech()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();//记录容器清空
	//轮数初始化
	this->m_Index = 1;
}

//创建12名选手
void SpeechManager::create_speaker()
{
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++)
	{
		string name = "选手";
		name += name_seed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}

		//创建选手编号，放入v1容器
		this->v1.push_back(i + 10001);
		//放入map容器
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//开始比赛成员函数，控制整个流程
void SpeechManager::StartSpeech()
{
	//第一轮比赛
	this->m_Index=1;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存前三的信息
	this->saveRecord();

	//重置比赛
	this->InitSpeech();
	//创建选手
	this->create_speaker();
	//获取往届记录
	this->loadRecord();

	cout << "本届比赛正式结束！" << endl;
	system("pause");
	system("cls");//清屏
}

//抽签
//打印函数
void myprint(int val)
{
	cout << val << ", ";
}
void SpeechManager::speechDraw()
{
	cout << "第 <<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------" << endl;
	cout << "抽签后演讲顺序如下:" << endl;

	if (this->m_Index == 1)//第一轮比赛
	{
		random_shuffle(v1.begin(), v1.end());//随机遍历
		for_each(v1.begin(), v1.end(), myprint);
	}
	else
	{//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(), myprint);
	}
	cout << endl;
	cout << "-----------------------------------" << endl;
	system("pause");
}

//比赛成员函数
void SpeechManager::speechContest()
{
	cout<< "------------第<<" << this->m_Index << ">>轮比赛正式开始！------------"<< endl;

	vector<int> v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//准备临时容器，存放小组成绩，允许分数相同
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//记录人员个数6人一组。

	//遍历所有选手
	for (vector<int> ::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//60.0-100.0
			//cout << score << ", ";//输出分数
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//降序排列
		d.pop_back();//去除最低分
		d.pop_front();//去除最高分
		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size();//平均分
		//cout << endl;

		//打印平均分
		//cout << "编号：" << *it << " 姓名: " << this->m_Speaker[*it].m_Name << "平均分：" << avg << endl;
		//平均分放入m_Speaker中
		this->m_Speaker[*it].score[this->m_Index - 1] = avg;

		//打分成绩放入临时小组容器
		groupScore.insert(make_pair(avg, *it));
		//每6人取出前三名
		if (num % 6 == 0)
		{
			int count = 0;
			cout << "第" << num / 6 << "小组比赛成绩如下:" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "选手编号：" << mit->second << " 姓名： " << this->m_Speaker[mit->second].m_Name << " 成绩："
					<< this->m_Speaker[mit->second].score[this->m_Index - 1] << endl;
			}
			//取走前三名，放入下一个容器
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end()&&count < 3; mit++,count++)
			{
				if (this->m_Index == 1)//第一轮
				{
					v2.push_back(mit->second);
				}
				else//第二轮
				{
					vVictory.push_back(mit->second);
				}
			}
			groupScore.clear();//临时小组清空
			cout << endl;
		}
	}

	cout << "------------第<<" << this->m_Index << ">>轮比赛已经完毕！------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore()
{
	cout << "------------第<<" << this->m_Index << ">>轮晋级选手信息如下！------------" << endl;
	vector<int> v_Src;//比赛选手容器
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
		cout << "选手编号：" << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 成绩："
			<< this->m_Speaker[*it].score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");//清屏
	this->show_menu();
}

//保存记录函数
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出方式打开文件,追加方式写文件
	
	//将选手数据写入文件
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();//关闭文件
	cout << "记录保存完毕！" << endl;
	this->fileIsEmpty = false;
}

//查看往届记录
void SpeechManager::loadRecord()
{
	this->m_Record.clear();
	ifstream ifs;
	ifs.open("speech.csv", ios::in);//读文件
	if (!ifs.is_open())//打开失败
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "记录已经被清空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件非空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取单个字符放回文件
	string data;
	int index = 1;//届数
	while (ifs >> data)
	{
		vector<string> v;
		//cout << data << endl;
		int pos = -1;//查,的位置
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
		cout << it->first << "冠军编号： " << it->second[0] << "分数：" << it->second[1]<<endl;
	}*/
}

//显示往届记录信息
void SpeechManager::showRecord()
{
	this->loadRecord();
	if (this->fileIsEmpty)
	{
		cout << " 文件不存在或者记录为空！！！" << endl;
	}
	else
	{
		for (int i = 1; i <= this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_Record[i][0] << "得分： " << this->m_Record[i][1] << " "
				<< "亚军编号：" << this->m_Record[i][2] << "得分： " << this->m_Record[i][3] << " "
				<< "季军编号：" << this->m_Record[i][4] << "得分： " << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << " 1. 确认" << endl;
	cout << " 2. 取消" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);//删除原有文件，创建新文件
		ofs.close();
		this->InitSpeech();//初始化
		this->create_speaker();//创建选手
		this->loadRecord();//获取往届记录
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager()
{

}