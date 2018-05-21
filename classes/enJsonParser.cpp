#include "enJsonParser.h"
#
USING_NS_CC;
enJsonParser * enJsonParser::createWithArray(ValueVector pListData)
{
	enJsonParser * pRef = new enJsonParser();

	if (pRef->initWithArray(pListData))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

bool enJsonParser::initWithArray(ValueVector pListData)
{
	listData = pListData;
	return true;
}

void enJsonParser::encode(Information message)		//���ﻻ��message��ֱֹ��ʹ��ȫ�ֱ���information���δ֪��bug
{
	rapidjson::Document document;
	document.SetObject();		//��ʼ��document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//����ڴ�������������˷���������ڴ�ķ���

	rapidjson::Value array(rapidjson::kArrayType);

	for (auto& v : listData)
	{
		ValueMap row = v.asValueMap();				//�����v�����ֵ䣬Value��һ�ְ�װ�࣬���԰Ѻܶ��������Ͱ�װ����

		rapidjson::Value object(rapidjson::kObjectType);

		rapidjson::Value v_id;
		v_id.SetString(row["ID"].asString().c_str(), allocator);
		object.AddMember("ID", v_id, allocator);

		rapidjson::Value v_Date;
		v_Date.SetString(row["Date"].asString().c_str(), allocator);
		object.AddMember("Date", v_Date, allocator);

		rapidjson::Value v_Content;
		v_Content.SetString(row["Content"].asString().c_str(), allocator);
		object.AddMember("Content", v_Content, allocator);

		rapidjson::Value v_UserID;
		v_UserID.SetString(row["UserID"].asString().c_str(), allocator);
		object.AddMember("UserID", v_UserID, allocator);

		array.PushBack(object, allocator);
	}

	//document.AddMember("change", true, allocator);
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson:: StringBuffer > writer(buffer);	//����writer���󣬽����ݱ��浽buffer��

	document.Accept(writer);	//ͨ��write������д��buffer
	
	message.setSendBuf(buffer.GetString());
	//log("out: %s", out);
}