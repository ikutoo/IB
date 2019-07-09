#pragma once
#undef max 
#undef min

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "math.h"
#include "animation.h"

namespace DxEngine
{
	class CNode;
	class CSprite;
	class CLabel;

	class CJsonReader
	{
	public:
		using TObject = rapidjson::GenericObject<true, rapidjson::Value>;

		CJsonReader(const std::string& vFilename);
		~CJsonReader();

		std::string		readString(const std::string& vAttributName);
		int				readInt(const std::string& vAttributName);
		float			readFloat(const std::string& vAttributName);
		bool			readBool(const std::string& vAttributName);
		vec2i			readVec2(const std::string& vAttributName);
		CSprite*		readSprite(const std::string& vAttributName);
		CLabel*			readLabel(const std::string& vAttributName);
		SAnimation		readAnimation(const std::string& vAttributName);

		CNode* getRootNode();

		vec2f parseVec2(const rapidjson::Value& vValue);

		const rapidjson::Document& getDocument() { return m_Doc; }

	private:
		rapidjson::Document m_Doc;

		void __fillNode(TObject& vObject, CNode* vioNode);

		vec2f __parseVec2f(TObject& vObject, const std::string& vAttributName);
		vec3i __parseVec3i(TObject& vObject, const std::string& vAttributName);
		recti __parseRecti(TObject& vObject, const std::string& vAttributName);
	};

	class CJsonWriter
	{
	public:
		CJsonWriter(const std::string& vFilename);
		~CJsonWriter();

		void writeBool(const std::string& vAttributName, bool vValue);

		void saveFile();

	private:
		std::string m_FileName;
		rapidjson::Document m_Doc;
	};
}