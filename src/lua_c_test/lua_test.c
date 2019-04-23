//All code is found at http://www.troubleshooters.com/codecorn/lua/lua_c_calls_lua.htm

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
/*
int c_swap (lua_State *L){
    double arg1 = luaL_checknumber(L,1);
    double arg2 = luaL_checknumber(L,2);

    lua_pushnumber(L, arg2);
    lua_pushnumber(L, arg1);

    return 2;
}*/

//int bleh() {
    //lua_State *L = luaL_newstate();
    //luaL_openlibs(L);
    //luaL_dofile(L, "script.lua");
    //lua_pushcfunction(L, c_swap);
    //lua_setglobal(L, "c_swap");

    //luaL_dostring(L, "print(c_swap(8, 5))");

    //return 0;
//}

#include <stdlib.h>                             /* For function exit() */
#include <stdio.h>                              /* For input/output */

void bail(lua_State *L, char *msg){
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
	exit(1);
}

int main(void)
{
    lua_State *L;

    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */

    if (luaL_loadfile(L, "callfuncscript.lua"))    /* Load but don't run the Lua script */
	    bail(L, "luaL_loadfile() failed");      /* Error out if file can't be read */
    if (lua_pcall(L, 0, 0, 0))                  /* Run the loaded Lua script */
	   bail(L, "lua_pcall() failed");

    printf("In C, calling Lua->tellme()\n");
    
    //lua_getglobal(L, "tellme");         /* Error out if Lua file has an error */
    /*printf("In C, calling Lua\n");
    if (lua_pcall(L, 0, 0, 0))
        bail(L, "lua_pcall() failed");
    
    printf("Back in C again\n");
    printf("In C, calling Lua->square(6)\n");
    */
    lua_getglobal(L, "square");
    lua_pushnumber(L, 6);
    if (lua_pcall(L, 1, 1, 0))
        bail(L, "lua_pcall() failed");

    printf("Back in C again\n");
    int mynumber = lua_tonumber(L, -1);
    printf("Return number = %d\n", mynumber);

    lua_close(L);                               /* Clean up, free the Lua state var */

    lua_State *L2;

    L2 = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L2);

    if (luaL_loadfile(L2, "helloscript.lua"))    /* Load but don't run the Lua script */
	    bail(L2, "luaL_loadfile() failed");      /* Error out if file can't be read */
    if (lua_pcall(L2, 0, 0, 0))                  /* Run the loaded Lua script */
	   bail(L2, "lua_pcall() failed");

    lua_close(L2);    

    return 0;
}