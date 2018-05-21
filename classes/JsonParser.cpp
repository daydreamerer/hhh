#include "JsonParser.h"
#include "platform/CCFileUtils.h"
USING_NS_CC;
JsonParser * JsonParser::createWithFile(const char * filename)
{
	JsonParser *pRet = new JsonParser();
	if (pRet->initWithFile(filename))
	{
		pRet->autorelease();		//�Զ��ͷ�
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool JsonParser::initWithFile(const char * filename)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string path = sharedFileUtils->fullPathForFilename(filename);
	Data data = sharedFileUtils->getDataFromFile(path);
	content = std::string((const char *)data.getBytes(), 0, data.getSize());

	return true;
}

void JsonParser::decode()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		//����ID��
		CC_ASSERT(records.HasMember("ID"));
		const rapidjson::Value &val_id = record["ID"];
		//�ж�ID����
		CC_ASSERT(val_id.IsString());
		row["id"] = Value(val_id.GetString());

		//����CDate��
		CC_ASSERT(record.HasMember("CDate"));
		const rapidjson::Value &val_CDate = record["CDate"];
		CC_ASSERT(val_CDate.IsString());
		row["CDate"] = Value(val_CDate.GetString());

		CC_ASSERT(record.HasMember("Content"));
		const rapidjson::Value &val_Content = record["Content"];
		CC_ASSERT(val_Content.IsString());
		row["Content"] = Value(val_Content.GetString());

		CC_ASSERT(record.HasMember("UserID"));
		const rapidjson::Value &val_UserID = record["UserID"];
		CC_ASSERT(val_UserID.IsString());
		row["UserID"] = Value(val_UserID.GetString());

		list.push_back(Value(row));
	}
}