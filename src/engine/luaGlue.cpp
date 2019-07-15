#include "luaGlue.h"
#include <DXLib/DxLib.h>
#include "resourceManager.h"
#include "common.h"
#include "node.h"

namespace DxEngine
{
	namespace luaGlue
	{
		//**********************************************************************************************************
		//FUNCTION:
		LUAGLUE log(lua_State* vioLuaState)
		{
			auto logMsg = lua_tostring(vioLuaState, 1);
			CHECK_RESULT(DxLib::LogFileAdd(logMsg));

			return 0;
		}

		//**********************************************************************************************************
		//FUNCTION:
		LUAGLUE playMusic(lua_State* vioLuaState)
		{
			auto filePath = lua_tostring(vioLuaState, 1);
			CHECK_RESULT(DxLib::PlayMusic(CResourceManager::getInstance()->locateFile(filePath).c_str(), DX_PLAYTYPE_LOOP));
			return 0;
		}

		//**********************************************************************************************************
		//FUNCTION:
		LUAGLUE setNodePosition(lua_State* vioLuaState)
		{
			int index = 0;
			auto pNode = static_cast<CNode*>(lua_touserdata(vioLuaState, ++index));
			auto posX = lua_tonumber(vioLuaState, ++index);
			auto posY = lua_tonumber(vioLuaState, ++index);
			pNode->setPosition(posX, posY);
			return 0;
		}

		//**********************************************************************************************************
		//FUNCTION:
		LUAGLUE setNodeRotation(lua_State* vioLuaState)
		{
			int index = 0;
			auto pNode = static_cast<CNode*>(lua_touserdata(vioLuaState, ++index));
			auto rotation = lua_tonumber(vioLuaState, ++index);
			pNode->setRotation(rotation);
			return 0;
		}
	};
}