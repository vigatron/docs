#include "el2008gui.h"

#include "font0.c"
#include "font1.c"
#include "font2.c"
#include "font3.c"
#include "font4.c"


char FONT_TOP_CORRECTION[5] = { 2, 0, 0, -1,0 };

const uchar8 *pPTR[5] =
{
      &arrayDATAFONT0[0],
      &arrayDATAFONT1[0],
      &arrayDATAFONT2[0],
      &arrayDATAFONT3[0],
	&arrayDATAFONT4[0]
};

achar8 FONT_GET_SYM_T( uchar8 ucSYM, uchar8 ucFONT )
{
 const uchar8 *pFONT = pPTR[ucFONT];
 uchar8 ucOFFS = (*(pFONT + 2 + ucSYM ));
 uchar8 ucCOR = FONT_TOP_CORRECTION[ucFONT];
 // if( ucCOR > ucOFFS ) return 0;
 return ucOFFS-ucCOR;
}

auchar8 FONT_GET_SYM_W( uchar8 ucSYM, uchar8 ucFONT )
{
 const uchar8 *pFONT = pPTR[ucFONT];
 return *(pFONT + 2 + ucSYM + 256);
}

auchar8 FONT_GET_SYM_H( uchar8 ucSYM, uchar8 ucFONT )
{
 const uchar8 *pFONT = pPTR[ucFONT];
 return *(pFONT + 2 + ucSYM + (256*2) );
}

auint16 FONT_GET_SYM_O( uchar8 ucSYM, uchar8 ucFONT )
{
 const uchar8 *pFONT = pPTR[ucFONT];
 uchar8 ucOFFSET1 = *( pFONT + 2 + (ucSYM*2) + (256*3) + 0 );
 uchar8 ucOFFSET2 = *( pFONT + 2 + (ucSYM*2) + (256*3) + 1 );
 uint16 uiOFFSET = (((uint16)ucOFFSET2)<<8) + ucOFFSET1;
 return uiOFFSET;
}

auchar8 FONT_GET_SYM_B( uint16 uiOFFSET, uchar8 ucFONT )
{
 const uchar8 *pFONT = pPTR[ucFONT];
 return *(pFONT + uiOFFSET) ;
}

auint16 EL2008GUI_GetTextWidth( const char *pText, uchar8 ucFont )
{
 uint16 uiResult=0;
 uchar8 ucLen = strlen( pText );
 
 uchar8 i;
 for( i=0;i<ucLen;i++ )
 {
     uchar8 ucW = FONT_GET_SYM_W( pText[i], ucFont );
     if( pText[i] == ' ' ) ucW = SYMMINWIDTH;
     uiResult += ucW + 1;
 }
 
 return uiResult;
}

auint16 EL2008GUI_GetTextHeight( uchar8 ucFont )
{
 const uchar8 *pFONT = pPTR[ucFont];
 uchar8 ucH = *(pFONT + 1);
 return ucH;
}
