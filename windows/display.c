/*
 * DISPLAY driver
 *
 * Copyright 1998 Ulrich Weigand
 *
 */

#include "debug.h"
#include "display.h"
#include "mouse.h"
#include "windef.h"
#include "wine/winuser16.h"

DEFAULT_DEBUG_CHANNEL(cursor)

/***********************************************************************
 *           DISPLAY_Inquire			(DISPLAY.101)
 */
WORD WINAPI DISPLAY_Inquire(LPCURSORINFO lpCursorInfo) 
{
    lpCursorInfo->wXMickeys = 1;
    lpCursorInfo->wYMickeys = 1;

    return sizeof(CURSORINFO);
}

/***********************************************************************
 *           DISPLAY_SetCursor			(DISPLAY.102)
 */
VOID WINAPI DISPLAY_SetCursor( CURSORICONINFO *lpCursor )
{
   MOUSE_Driver->pSetCursor(lpCursor);
}

/***********************************************************************
 *           DISPLAY_MoveCursor			(DISPLAY.103)
 */
VOID WINAPI DISPLAY_MoveCursor( WORD wAbsX, WORD wAbsY )
{
   MOUSE_Driver->pMoveCursor(wAbsX, wAbsY);
}

/***********************************************************************
 *           DISPLAY_CheckCursor                  (DISPLAY.104)
 */
VOID WINAPI DISPLAY_CheckCursor()
{
    FIXME( cursor, "stub\n" );
}

/***********************************************************************
 *           UserRepaintDisable			(DISPLAY.500)
 */
VOID WINAPI UserRepaintDisable16( BOOL16 disable )
{
    TRACE( cursor, "(%d): stub\n", disable );
}
