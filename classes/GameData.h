#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "cocos2d.h"
#include "SystemHeader.h"
//���������˽�б����м�һ������ָ�룬ͨ������ָ�������ò�ͬ�����������Ҳ�����ȷ��ֵ
USING_NS_CC;

using std::string;

class GameData
{
private:
	string order;
	//ValueVector(*func)(Value);

public:
	GameData(const char * _order);
	ValueVector toValueVector(Value value);
};

#endif