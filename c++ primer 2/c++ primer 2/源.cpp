#include<iostream>
#include<fstream>
//#include<vector>
#include<string>
using namespace std;

int main() {
	string filename;
	cout << "��������Ҫ�򿪵��ļ���:";
	cin >> filename;

	ifstream infile(filename.c_str(), ios::in);//�����ļ��Ƿ����
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
	cout << "��������Ҫͳ�Ƶĵ��ʣ�";
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
		cout << "û���ҵ�����Ҫ��ĵ���!";
	else cout << "�������ҵĵ��ʹ����֣�" << total << " ��!";

	cout << endl;
	system("pause");
	return 0;
}