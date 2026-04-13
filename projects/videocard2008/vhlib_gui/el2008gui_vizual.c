#include "el2008gui.h"

extern volatile EL2008GUI_SYSTEM sGUISYSTEM;
extern void Debug( char *pText, int i );

const uchar8 arrayPALETTE[16] =
{
  VHRGB(0,0,0,0),
  VHRGB(1,3,0,0),
  VHRGB(1,0,3,0),
  VHRGB(1,3,3,0),
  VHRGB(1,0,0,3),
  VHRGB(1,3,0,3),
  VHRGB(1,0,3,3),
  VHRGB(1,3,3,3),

  VHRGB(2,0,0,0),
  VHRGB(3,3,0,0),
  VHRGB(3,0,3,0),
  VHRGB(3,3,3,0),
  VHRGB(3,0,0,3),
  VHRGB(3,3,0,3),
  VHRGB(3,0,3,3),
  VHRGB(3,3,3,3)
};

avoid EL2008GUI_DrawRect( const VHRECT *pRect, uchar8 ucCOL )
{
      uint16 uiWidth = pRect->uiX2-pRect->uiX1+1;
      uint16 uiHeight= pRect->uiY2-pRect->uiY1+1;
      uint16 uiY;
      for ( uiY= pRect->uiY1; uiY <= pRect->uiY2; uiY ++ )
      {
       EL2008GUI_SetPointer( pRect->uiX1, uiY );
	   uint16 t;
       for(  t = 0; t< uiWidth; t++ ) EL2008GUI_DrawPixelAndRight( ucCOL ); 
      }
}

avoid EL2008GUI_DrawFrame( const VHRECT *pRect, uchar8 ucCOL1, uchar8 ucCOL2 )
{
      uint16 uiWidth = pRect->uiX2 - pRect->uiX1 + 1;
      uint16 uiHeight= pRect->uiY2 - pRect->uiY1 + 1;
      
	  // Debug( "W", uiWidth );
	  // Debug( "H", uiHeight );
	  
      EL2008GUI_SetPointer( pRect->uiX1 + 1, pRect->uiY1 );
	  uint16 t;
      for( t = 0; t < (uiWidth-2); t++ ) EL2008GUI_DrawPixelAndRight( ucCOL1 ); 
	  
      EL2008GUI_SetPointer( pRect->uiX1 + 1, pRect->uiY2 );
      for( t = 0; t < (uiWidth-2); t++ ) EL2008GUI_DrawPixelAndRight( ucCOL1 ); 
      uint16 uiY;
      for ( uiY = (pRect->uiY1+1); uiY <= (pRect->uiY2-1); uiY ++ )
      {
       EL2008GUI_SetPointer( pRect->uiX1, uiY );
       EL2008GUI_DrawPixelAndRight( ucCOL1 );
	   uint16 i;
       for( i=0; i<(uiWidth-2); i++ ) EL2008GUI_DrawPixelAndRight( ucCOL2 );
       EL2008GUI_DrawPixelAndRight( ucCOL1 ); 
      }
}

avoid EL2008GUI_DrawLabel( const EL2008GUI_LABEL *pLabel )
{
   const VHRECT *pRect = &pLabel->sPREFIX.sRECT;
   EL2008GUI_DrawRect( pRect, pLabel->ucBACKColor );
   EL2008GUI_DrawText( pRect, &pLabel->sTEXT );
   
  //const char *pText = (const char *)GET_VHDBS2_OBJECT( sGUISYSTEM.pStringsList, pLabel->ucTEXTID );
  //EL2008GUI_DrawText( pText, pRect, pLabel->ucTEXTAlign, pLabel->ucTEXTFontID, pLabel->ucTEXTColor );
}


avoid EL2008GUI_DrawButton( const EL2008GUI_BUTTON *pButton )
{
  const VHRECT *pRect = &pButton->sPREFIX.sRECT;
  
  if( !EL2008GUI_GetFlag( (EL2008GUI_PREFIX *)pButton, EL2008GUI_FLAG_FOCUS ) )
  {
    EL2008GUI_DrawFrame( pRect, pButton->ucBUTTONFrameColor, pButton->ucBUTTONColor );
	EL2008GUI_DrawText(  pRect, &pButton->sTEXT );
  }
  else
  {
    EL2008GUI_DrawFrame( pRect, pButton->ucBUTTONSELFrameColor, pButton->ucBUTTONSELColor );
	EL2008GUI_DrawText(  pRect, &pButton->sTEXTSEL );
	
	// const EL2008GUI_TEXT *pTEXT = &pButton->sTEXT;
	// const char *pText = (const char *)GET_VHDBS2_OBJECT( sGUISYSTEM.pStringsList, pTEXT->ucTEXTID );
	// EL2008GUI_DrawTextA( pText, pRect, pTEXT->ucTEXTAlign, pTEXT->ucTEXTFontID, 0x3 );
  }
}

avoid EL2008GUI_DrawCheckBox( const EL2008GUI_CHECKBOX *pCheckBox )
{
  const VHRECT *pRect = &pCheckBox->sPREFIX.sRECT;
  
  if( !EL2008GUI_GetFlag( (EL2008GUI_PREFIX *)pCheckBox, EL2008GUI_FLAG_FOCUS ) )
      EL2008GUI_DrawRect( pRect, pCheckBox->ucBACKColor );
      else
      EL2008GUI_DrawRect( pRect, VHRGB(3,3,0,0) );

  VHRECT sRECT1,sRECT2;
  memcpy( &sRECT1, pRect, sizeof( VHRECT ) );
  memcpy( &sRECT2, pRect, sizeof( VHRECT ) );
  
  uchar8 ucHeight = pRect->uiY2 - pRect->uiY1;
  
  sRECT1.uiX2 = sRECT1.uiX1 + ucHeight;
  sRECT2.uiX1 = sRECT2.uiX1 + ucHeight;

  // EL2008GUI_DrawRect( &sRECT1, (pCheckBox->ucSTATE == 0) ? VHRGB(0,0,0,0):VHRGB(3,3,0,0) );
  
  if( !EL2008GUI_GetFlag( (EL2008GUI_PREFIX *)pCheckBox, EL2008GUI_FLAG_FOCUS ) )
      EL2008GUI_DrawFrame( &sRECT1, 0, pCheckBox->ucBACKColor );
      else
      EL2008GUI_DrawFrame( &sRECT1, 0, VHRGB(3,3,0,0) );
  
  if( pCheckBox->ucSTATE != 0 )
  {
    sRECT1.uiX1 +=2;
    sRECT1.uiX2 -=2;
    sRECT1.uiY1 +=2;
    sRECT1.uiY2 -=2;
    EL2008GUI_DrawFrame( &sRECT1, 0, VHRGB(2,3,0,0) );  
  }
  
  EL2008GUI_DrawText( pRect, &pCheckBox->sTEXT );
}

avoid EL2008GUI_DrawWindow( const EL2008GUI_WINDOW *pWindow )
{
  const VHRECT *pRect = &pWindow->sPREFIX.sRECT;
  const uchar8 ucWindowCH = 30;

  VHRECT sCaption = { pRect->uiX1,pRect->uiY1, pRect->uiX2,pRect->uiY2 };
  VHRECT sBody    = { pRect->uiX1,pRect->uiY1, pRect->uiX2,pRect->uiY2 };
    
  // memcpy( &sCaption, pRect, 4 ); 
  // memcpy( &sBody, pRect, 4 );
  
  sCaption.uiY2 = sCaption.uiY1 + ucWindowCH;
  sBody.uiY1 += ucWindowCH;
  
  EL2008GUI_DrawFrame( &sCaption, 0,pWindow->ucCaptionColor );
  EL2008GUI_DrawFrame( &sBody, 0,pWindow->ucBodyColor );
  EL2008GUI_DrawText( &sCaption, &pWindow->sTEXT );
}

avoid EL2008GUI_DrawBitmap( const EL2008GUI_BITMAP * pBITMAP )
{
 uint16 uiW=0,uiH=0;
 if( !EL2008GUI_BMP_Init( pBITMAP->ucBMPID, &uiW, &uiH ) ) return;
 uint16 y;
 for( y=0; y<uiH; y++ )
 {
  if( EL2008GUI_BMP_ReadLine() != 0 )
  {
      uchar8 *pPtr = EL2008GUI_BMP_DATA();
      uint16 x = uiW;
      
      EL2008GUI_SetPointer( pBITMAP->sPREFIX.sRECT.uiX1, pBITMAP->sPREFIX.sRECT.uiY1+ uiH - y );
      
      while(x>0)
      {
       if( x>1 )
       {
        uchar8 ucCOL1 = ((*pPtr) >> 4) & 0x0F;
        uchar8 ucCOL2 = ((*pPtr) & 0x0F);
        ucCOL1 = arrayPALETTE[ucCOL1];
        EL2008GUI_DrawPixelAndRight( ucCOL1 );
        ucCOL2 = arrayPALETTE[ucCOL2];
        EL2008GUI_DrawPixelAndRight( ucCOL2 );
        x-=2;
       }
       else
       {
        uchar8 ucCOL1 = ((*pPtr) >> 4) & 0x0F;
        ucCOL1 = arrayPALETTE[ucCOL1];
        EL2008GUI_DrawPixelAndRight( ucCOL1 );
         x--;
       }
       pPtr++;
      }
  }
  else y = uiH;
 }
    
}

 
