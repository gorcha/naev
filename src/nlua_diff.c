/*
 * See Licensing and Copyright notice in naev.h
 */

/**
 * @file nlua_diff.c
 *
 * @brief Unidiff Lua module.
 */


#include "nlua_diff.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lua.h"
#include "lauxlib.h"

#include "nlua.h"
#include "nluadef.h"
#include "log.h"
#include "naev.h"
#include "unidiff.h"


/* diffs */
static int diff_applyL( lua_State *L );
static int diff_removeL( lua_State *L );
static int diff_isappliedL( lua_State *L );
static const luaL_reg diff_methods[] = {
   { "apply", diff_applyL },
   { "remove", diff_removeL },
   { "isApplied", diff_isappliedL },
   {0,0}
}; /**< Unidiff Lua methods. */
static const luaL_reg diff_cond_methods[] = {
   { "isApplied", diff_isappliedL },
   {0,0}
}; /**< Unidiff Lua read only methods. */


/**
 * @brief Loads the diff Lua library.
 *    @param L Lua state.
 *    @param readonly Load read only functions?
 *    @return 0 on success.
 */
int lua_loadDiff( lua_State *L, int readonly )
{
   if (readonly == 0)
      luaL_register(L, "diff", diff_methods);
   else
      luaL_register(L, "diff", diff_cond_methods);
   return 0;
}


/**
 * @brief Lua bindings to apply/remove Universe Diffs.
 *
 * Universe Diffs are patches you can apply to the universe to do permanent
 *  changes.  They are defined in dat/unidiff.xml.
 *
 * Typical usage would be:
 * @code
 * diff.apply( "collective_dead" )
 * @encode
 *
 * @luamod diff
 */
/**
 * @brief Applies a diff by name.
 *
 *    @luaparam name Name of the diff to apply.
 * @luafunc apply( name )
 */
static int diff_applyL( lua_State *L )
{
   char *name;

   if (lua_isstring(L,1)) name = (char*)lua_tostring(L,1);
   else NLUA_INVALID_PARAMETER();

   diff_apply( name );
   return 0;
}
/**
 * @brief Removes a diff by name.
 *
 *    @luaparam name Name of the diff to remove.
 * @luafunc remove( name )
 */
static int diff_removeL( lua_State *L )
{
   char *name;

   if (lua_isstring(L,1)) name = (char*)lua_tostring(L,1);
   else NLUA_INVALID_PARAMETER();

   diff_remove( name );
   return 0;
}
/**
 * @brief Checks to see if a diff is currently applied.
 *
 *    @luaparam name Name of the diff to check.
 *    @luareturn true if is applied, false if it isn't.
 * @luafunc isApplied( name )
 */
static int diff_isappliedL( lua_State *L )
{
   char *name;

   if (lua_isstring(L,1)) name = (char*)lua_tostring(L,1);
   else NLUA_INVALID_PARAMETER();

   lua_pushboolean(L,diff_isApplied(name));
   return 1;
}
