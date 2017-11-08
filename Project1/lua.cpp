#include"main.h"
#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */
bool Lua_Init()
{lua_State*
	lua = lua_open();
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_math(lua);
	luaopen_table(lua);
	luaL_dofile(lua, "date_init.lua");
	return 1;
}
int Lua_GetInt(lua_State* lua, const string &zname)
{
	lua_settop(lua, 0);
	lua_getglobal(lua, zname.c_str());
	if(!lua_isnumber(lua, -1))	MessageBox(NULL,"Error get int from lua","Error",MB_OK);
	int num=(int)lua_tonumber(lua, -1);
	lua_pop(lua, -1);
	return num;
}