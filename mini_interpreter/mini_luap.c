#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luajit.h"


int test_export(lua_State * L) {
    int n;
    
    n = lua_tonumber(L, 1);
    
    printf("test_export called with %i\n", n);
    
    lua_pushnumber(L, -n);
    
    return 1;
}

int test_error(lua_State * L) {
    int n = lua_gettop(L);
    int i;
    
    printf("Got LUA error.\n");
    
    if (n == 0) {
	printf("Stack is empty.\n");
	return 0;
    }
    
    for (i = 1; i <= n; i++) {
	printf("%i: ", i);
        switch(lua_type(L, i)) {
        case LUA_TNONE:
	    printf("Invalid");
            break;
        case LUA_TNIL:
            printf("(Nil)");
            break;
        case LUA_TNUMBER:
            printf("(Number) %f", lua_tonumber(L, i));
            break;
        case LUA_TBOOLEAN:
            printf("(Bool)   %s", (lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TSTRING:
            printf("(String) %s", lua_tostring(L, i));
            break;
        case LUA_TTABLE:
            printf("(Table)");
            break;
        case LUA_TFUNCTION:
            printf("(Function)");
            break;
        default:
            printf("Unknown");
	}

	printf("\n");
    }

    return 0;
}


int main(int argc, char ** argv) {
    lua_State * L;
    int stt;
    int script;
    int flags = 0;
    
    // Create lua VM
       
    if (!(L = lua_open())) {
	printf("Error creating lua_State\n");
	return -1;
    }

    
    printf("Creating luaVM... ");
    lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
    luaL_openlibs(L); 
    lua_gc(L, LUA_GCRESTART, -1);
    
    
    printf("Loading script file: `%s'\n", "host:hello.lua");
    
    // load script
    int status = luaL_loadfile(L, "host:hello.lua");
	
    // call script
    if (status == 0) 
    {
	printf("Running.\n");
    	status = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    
    // show error, if any
    if (status != 0) 
    {
	printf("error: %s\n", lua_tostring(L, -1));
	lua_pop(L, 1);  // remove error message
    }

   
    printf("Done!.\n");
    
    // cleanup
    lua_close(L);


    
    return 0;
}