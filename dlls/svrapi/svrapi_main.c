/*
* Part of NETAPI on Windows 9x
* http://msdn.microsoft.com/library/default.asp?url=/library/en-us/stgmgmt/fs/netshareenum.asp
*
* Copyright 2006 Konstantin Petrov
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
*/

#include "config.h"
#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "svrapi.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(svrapi);

/***********************************************************************
 *             DllMain (SVRAPI.init)
 */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID fImpLoad)
{
    TRACE("%p 0x%x %p\n", hinstDLL, fdwReason, fImpLoad);

    switch(fdwReason) {
        case DLL_WINE_PREATTACH:
            return FALSE; /*prefer native version*/
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
