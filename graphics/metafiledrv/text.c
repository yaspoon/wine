/*
 * metafile driver text functions
 *
 * Copyright 1993, 1994 Alexandre Julliard
 *
 */

#include "windef.h"
#include "metafiledrv.h"
#include "debug.h"
#include "heap.h"

DEFAULT_DEBUG_CHANNEL(metafile)


/******************************************************************
 *         MFDRV_MetaExtTextOut
 */
static BOOL MFDRV_MetaExtTextOut(DC*dc, short x, short y, UINT16 flags,
				 const RECT16 *rect, LPCSTR str, short count,
				 const INT16 *lpDx)
{
    BOOL ret;
    DWORD len;
    METARECORD *mr;
    
    if((!flags && rect) || (flags && !rect))
	WARN(metafile, "Inconsistent flags and rect\n");
    len = sizeof(METARECORD) + (((count + 1) >> 1) * 2) + 2 * sizeof(short)
	    + sizeof(UINT16);
    if(rect)
        len += sizeof(RECT16);
    if (lpDx)
     len+=count*sizeof(INT16);
    if (!(mr = HeapAlloc( SystemHeap, HEAP_ZERO_MEMORY, len)))
	return FALSE;

    mr->rdSize = len / 2;
    mr->rdFunction = META_EXTTEXTOUT;
    *(mr->rdParm) = y;
    *(mr->rdParm + 1) = x;
    *(mr->rdParm + 2) = count;
    *(mr->rdParm + 3) = flags;
    if (rect) memcpy(mr->rdParm + 4, rect, sizeof(RECT16));
    memcpy(mr->rdParm + (rect ? 8 : 4), str, count);
    if (lpDx)
     memcpy(mr->rdParm + (rect ? 8 : 4) + ((count + 1) >> 1),lpDx,
      count*sizeof(INT16));
    ret = MFDRV_WriteRecord( dc, mr, mr->rdSize * 2);
    HeapFree( SystemHeap, 0, mr);
    return ret;
}



/***********************************************************************
 *           MFDRV_ExtTextOut
 */
BOOL
MFDRV_ExtTextOut( DC *dc, INT x, INT y, UINT flags,
                  const RECT *lprect, LPCSTR str, UINT count,
                  const INT *lpDx )
{
    RECT16	rect16;
    LPINT16	lpdx16 = NULL;
    BOOL	ret;
    int		i;

    if(lpDx)
        lpdx16 = HeapAlloc( SystemHeap, 0, sizeof(INT16)*count );
    if (lprect)	CONV_RECT32TO16(lprect,&rect16);
    if (lpdx16)
        for (i=count;i--;)
	    lpdx16[i]=lpDx[i];
    ret = MFDRV_MetaExtTextOut(dc,x,y,flags,lprect?&rect16:NULL,str,count,
			       lpdx16);
    if (lpdx16)	HeapFree( SystemHeap, 0, lpdx16 );
    return ret;
}



