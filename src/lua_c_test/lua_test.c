//All code is based on code found at http://www.troubleshooters.com/codecorn/lua/lua_c_calls_lua.htm

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"


#include <stdlib.h>                         
#include <stdio.h>                              

void bail(lua_State *L, char *msg){
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
	exit(1);
}

int main(void)
{
    //creating a lua_state variable
    lua_State *L;

    //initializing the state
    L = luaL_newstate();                       
    luaL_openlibs(L);                          

    //loading the script and running it
    if (luaL_loadfile(L, "callfuncscript.lua"))    
	    bail(L, "luaL_loadfile() failed");      
    if (lua_pcall(L, 0, 0, 0))                  
	   bail(L, "lua_pcall() failed");

    printf("In C, calling Lua->tellme()\n");
    
    //obtaining a function from the script and running it
    lua_getglobal(L, "square");
    lua_pushnumber(L, 6);
    if (lua_pcall(L, 1, 1, 0))
        bail(L, "lua_pcall() failed");

    //going back to c and obtaining return value
    printf("Back in C again\n");
    int mynumber = lua_tonumber(L, -1);
    printf("Return number = %d\n", mynumber);

    //closing the state
    lua_close(L);                               

    //doing the same in a new lua state to run a new script
    lua_State *L2;

    L2 = luaL_newstate();                        
    luaL_openlibs(L2);

    if (luaL_loadfile(L2, "helloscript.lua"))    
	    bail(L2, "luaL_loadfile() failed");      
    if (lua_pcall(L2, 0, 0, 0))                  
	   bail(L2, "lua_pcall() failed");

    lua_close(L2);    

    return 0;
}