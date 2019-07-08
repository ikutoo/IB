#include "jsonUtil.h"
#include "utility.h"
#include "resourceManager.h"
#include "node.h"
#include "sprite.h"
#include "label.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
CJsonReader::CJsonReader(const std::string& vFilename)
{
	auto FileContent = Utility::readFileToString(LOCATE_FILE(vFilename));
	m_Doc.Parse<0>(FileContent.c_str());
	_ASSERTE(!m_Doc.HasParseError());
	_ASSERTE(!m_Doc.IsArray());
}

//*********************************************************************
//FUNCTION:
CJsonReader::~CJsonReader()
{
}

//**********************************************************************************************************
//FUNCTION:
std::string CJsonReader::readString(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	return p[vAttributName.c_str()].GetString();
}

//**********************************************************************************************************
//FUNCTION:
int CJsonReader::readInt(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	return p[vAttributName.c_str()].GetInt();
}

//**********************************************************************************************************
//FUNCTION:
float CJsonReader::readFloat(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	return p[vAttributName.c_str()].GetFloat();
}

//**********************************************************************************************************
//FUNCTION:
bool CJsonReader::readBool(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	return p[vAttributName.c_str()].GetBool();
}

//**********************************************************************************************************
//FUNCTION:
vec2f CJsonReader::parseVec2(const rapidjson::Value& vValue)
{
	return vec2f{ vValue["x"].GetFloat(), vValue["y"].GetFloat() };
}

//*********************************************************************
//FUNCTION:
vec2i CJsonReader::readVec2(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));

	return vec2i{};
}

//*********************************************************************
//FUNCTION:
CSprite* CJsonReader::readSprite(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	auto Obj = p[vAttributName.c_str()].GetObject();

	CSprite* pSprite = new CSprite;
	__fillNode(Obj, pSprite);
	if (Obj.HasMember("file")) pSprite->setImageFile(Obj["file"].GetString());
	if (Obj.HasMember("rect")) pSprite->setRect(__parseRecti(Obj, "rect"));
	if (Obj.HasMember("flip") && Obj["flip"].GetBool()) pSprite->flip();

	return pSprite;
}

//*********************************************************************
//FUNCTION:
CLabel* CJsonReader::readLabel(const std::string& vAttributName)
{
	const rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	auto Obj = p[vAttributName.c_str()].GetObject();

	CLabel* pLabel = new CLabel;
	__fillNode(Obj, pLabel);
	if (Obj.HasMember("text")) pLabel->setText(Obj["text"].GetString());
	if (Obj.HasMember("fontSize")) pLabel->setFontSize(Obj["fontSize"].GetInt());
	if (Obj.HasMember("fontColor")) pLabel->setFontColor(__parseVec3i(Obj, "fontColor"));
	if (Obj.HasMember("edgeColor")) pLabel->setEdgeColor(__parseVec3i(Obj, "edgeColor"));
	if (Obj.HasMember("brightness")) pLabel->setBrightness(__parseVec3i(Obj, "brightness"));

	return pLabel;
}

//*********************************************************************
//FUNCTION:
vec2f CJsonReader::__parseVec2f(TObject& vObject, const std::string& vAttributName)
{
	auto Array = vObject[vAttributName.c_str()].GetArray();
	_ASSERTE(Array.Size() == 2);
	return vec2f{ Array[0].GetFloat(), Array[1].GetFloat() };
}

//*********************************************************************
//FUNCTION:
vec3i CJsonReader::__parseVec3i(TObject& vObject, const std::string& vAttributName)
{
	auto Array = vObject[vAttributName.c_str()].GetArray();
	_ASSERTE(Array.Size() == 3);
	return vec3i{ Array[0].GetInt(), Array[1].GetInt(), Array[2].GetInt() };
}

//*********************************************************************
//FUNCTION:
recti CJsonReader::__parseRecti(TObject& vObject, const std::string& vAttributName)
{
	auto Array = vObject[vAttributName.c_str()].GetArray();
	_ASSERTE(Array.Size() == 4);
	return recti{ Array[0].GetInt(), Array[1].GetInt(), Array[2].GetInt(), Array[3].GetInt() };
}

//*********************************************************************
//FUNCTION:
void CJsonReader::__fillNode(TObject& vObject, CNode* vioNode)
{
	if (vObject.HasMember("position")) vioNode->setPosition(__parseVec2f(vObject, "position"));
	if (vObject.HasMember("rotation")) vioNode->setRotation(vObject["rotation"].GetFloat());
	if (vObject.HasMember("localZ")) vioNode->setLocalZ(vObject["localZ"].GetFloat());
	if (vObject.HasMember("scale")) vioNode->setScale(__parseVec2f(vObject, "scale"));
	if (vObject.HasMember("brightness")) vioNode->setBrightness(__parseVec3i(vObject, "brightness"));
}

//*********************************************************************
//FUNCTION:
CNode* CJsonReader::getRootNode()
{
	auto pRootNode = new CNode;

	rapidjson::Value &p = m_Doc;

	for (auto iter = p.MemberBegin(); iter != p.MemberEnd(); ++iter)
	{
		std::string Type = iter->value["type"].GetString();

		if (Type == "label") pRootNode->addChild(readLabel(iter->name.GetString()));
		if (Type == "sprite") pRootNode->addChild(readSprite(iter->name.GetString()));
	}

	return pRootNode;
}

//*********************************************************************
//FUNCTION:
CJsonWriter::CJsonWriter(const std::string& vFilename)
{
	m_FileName = vFilename;

	auto FileContent = Utility::readFileToString(LOCATE_FILE(vFilename));
	m_Doc.Parse<0>(FileContent.c_str());
	_ASSERTE(!m_Doc.HasParseError());
	_ASSERTE(!m_Doc.IsArray());
}

//*********************************************************************
//FUNCTION:
CJsonWriter::~CJsonWriter()
{
}

//**********************************************************************************************************
//FUNCTION:
void CJsonWriter::writeBool(const std::string& vAttributName, bool vValue)
{
	rapidjson::Value &p = m_Doc;
	_ASSERTE(p.HasMember(vAttributName.c_str()));
	p[vAttributName.c_str()].SetBool(vValue);
}

//**********************************************************************************************************
//FUNCTION:
void CJsonWriter::saveFile()
{
	rapidjson::StringBuffer Buffer;
	rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
	m_Doc.Accept(Writer);

	Utility::writeStringToFile(m_FileName, Buffer.GetString());
}