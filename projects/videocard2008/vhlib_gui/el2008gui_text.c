#include "el2008gui.h"

extern EL2008GUI_SYSTEM sGUISYSTEM;

auchar8 ELGUI2008_DRAW_CHAR( uchar8 ucSYM, uint16 uiX, uint16 uiY, uchar8 ucFont, uchar8 ucCOL )
{
	
	uchar8 ucSYMWIDTH 		= FONT_GET_SYM_W( ucSYM, ucFont );
	uchar8 ucSYMHEIGHT 		= FONT_GET_SYM_H( ucSYM, ucFont );
	uint16 uiOFFSET    		= FONT_GET_SYM_O( ucSYM, ucFont );
	
	uchar8 ucBYTESINLINE 	= ucSYMWIDTH/8;
	if( ucSYMWIDTH % 8 ) ucBYTESINLINE++;
	
	uchar8 ucOFFS = 0;
	uchar8 j;
	for( j=0;j<ucSYMHEIGHT;j++)
	{
		uchar8 ucMASK = 0x80;
		uchar8 ucOFFSETBYTE = 0;
		uchar8 i;
		
		for( i=0;i<ucSYMWIDTH;i++)
		{
			uint16 uiOFF = uiOFFSET + ucOFFSETBYTE + ucOFFS;
			uchar8 ucBYTE = FONT_GET_SYM_B( uiOFF, ucFont );
			if( (ucBYTE & ucMASK) == ucMASK ) 
            {
                EL2008GUI_SetPointer( uiX+i, uiY+j );
                EL2008GUI_DrawPixelAndRight( ucCOL );
            }
            
			if( ucMASK == 0x01 ) { ucMASK = 0x80; ucOFFSETBYTE++; } else ucMASK >>= 1;
		}

		ucOFFS += ucBYTESINLINE;
	}
	
	return (ucSYM == ' ') ? SYMMINWIDTH : ucSYMWIDTH;
}

uchar8 CharMap( uchar8 ucSym )
{
 if( ( ucSym >= (12*16) ) && ( ucSym < (14*16) ) ) return (ucSym - (12*16)) + (8*16);
 if( ( ucSym >= (14*16) ) && ( ucSym < (15*16) ) ) return (ucSym - (14*16)) + (10*16);
 if( ucSym >= (15*16) )  return (ucSym - (15*16)) + (14*16);
 if( ucSym == '³' ) return 'i';
 return ucSym;
}

avoid ELGUI2008_TEXT_OUT( const char *pText, uint16 x, uint16 y, uchar8 ucFont, uchar8 ucCOL )
{
	uint16 uiCurrentX = x;
	uchar8 ucTEXTLEN = strlen( pText );
	uchar8 i;
	for( i=0;i<ucTEXTLEN;i++ )
	{
	 uchar8 ucSYM = pText[i];
	 
	 if( ucFont == 4 ) ucSYM = CharMap( ucSYM );
	 
 	 char ucTOP = FONT_GET_SYM_T( ucSYM, ucFont );

	 uchar8 ucW = ELGUI2008_DRAW_CHAR( ucSYM, uiCurrentX, y + ucTOP, ucFont, ucCOL );
	 uiCurrentX += ucW + 1;
	}
}

avoid EL2008GUI_DrawTextA( const char *pText, const VHRECT *pRect, uchar8 ucAlign, uchar8 ucFont, uchar8 ucCOL  )
{
     uint16 uiWidth  = EL2008GUI_GetTextWidth( pText, ucFont );
     uint16 uiHeight = EL2008GUI_GetTextHeight( ucFont );
     
     uint16 uiRectW = pRect->uiX2 - pRect->uiX1 + 1;
     uint16 uiRectH = pRect->uiY2 - pRect->uiY1 + 1;
     
     uint16 uiX = pRect->uiX1 + (( uiRectW - uiWidth ) / 2);
     uint16 uiY = pRect->uiY1 + (( uiRectH - uiHeight ) / 2);
     
     ELGUI2008_TEXT_OUT( pText, uiX, uiY, ucFont, ucCOL );
}

avoid EL2008GUI_DrawText( const VHRECT *pRect, const EL2008GUI_TEXT *pTEXT )
{
  if( pTEXT->ucTEXTID == -1 ) return;
  const char *pText = (const char *)GET_VHDBS2_OBJECT( sGUISYSTEM.pStringsList, pTEXT->ucTEXTID );
  EL2008GUI_DrawTextA( pText, pRect, pTEXT->ucTEXTAlign, pTEXT->ucTEXTFontID, pTEXT->ucTEXTColor );
}
