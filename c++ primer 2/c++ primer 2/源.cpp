#include<iostream>
#include<fstream>
//#include<vector>
#include<string>
using namespace std;
int main() {
	string filename;
	cout << "请输入要打开的文件名:";
	cin >> filename;

	ifstream infile(filename.c_str(), ios::in);//测试文件是否存在
	if (!infile) {
		cerr << "oops!unable to open file " << filename << " --bailing out!\n";
		return(-1);
	}

	string word;
	/*	vector<string> vec;
	vector<string>::iterator iter=vec.begin();
	while(infile>>word){
	vec.push_back(word);
	}
	*/
	string name;
	cout << "请输入你要统计的单词：";
	cin >> name;
	int total = 0;
	while (infile >> word) {
		if (word == name) ++total;;
	}
	/*
	for(iter=vec.begin();iter!=vec.end();++iter){
	if(*iter==name) ++total;
	}
	*/
	if (total == 0)
		cout << "没有找到你所要查的单词!";
	else cout << "你所查找的单词共出现：" << total << " 次!";

	cout << endl;
	system("pause");
	return 0;
}
