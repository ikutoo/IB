#pragma once
#include <lua/lua.hpp>

#define LUAGLUE int

namespace DxEngine
{
	//**********************************************************************************************************
	//TEMPLATE:
	template <typename Cla, typename Func>
	int callMemberFunc(lua_State *vioLuaState)
	{
		auto pBuffer = (unsigned *)lua_touserdata(vioLuaState, lua_upvalueindex(1));
		auto pCla = (Cla*)(*pBuffer);
		int (Cla::*pFunc)(lua_State *) = *(Func*)(pBuffer + 1);
		return (pCla->*pFunc)(vioLuaState);
	}

	//**********************************************************************************************************
	//TEMPLATE:
	template <typename Cla, typename Func>
	void pushMemberFuncClosure(lua_State *vioLuaState, Cla *vCla, Func vFunc, unsigned int vNupvalues)
	{
		auto pBuffer = (unsigned *)lua_newuserdata(vioLuaState, 2 * sizeof(unsigned*));
		memcpy(pBuffer, &vCla, 4);
		memcpy(pBuffer + 1, &vFunc, sizeof(unsigned*));
		lua_pushcclosure(vioLuaState, callMemberFunc<Cla, Func>, vNupvalues + 1);
	}

#define lua_registry_member_function(L, name, cla, func)\
	pushMemberFuncClosure(L, cla, func, 0);\
	lua_setglobal(L, (name));

	namespace luaGlue
	{
		LUAGLUE log(lua_State* vioLuaState);

		LUAGLUE playMusic(lua_State* vioLuaState);

		LUAGLUE setNodePosition(lua_State* vioLuaState);

		LUAGLUE setNodeRotation(lua_State* vioLuaState);
	};
}