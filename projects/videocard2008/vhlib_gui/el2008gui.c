#include "el2008gui.h"

extern void Debug( char *pText, int i );


void MoveRect( VHRECT *pRECT, sint16 uiX, sint16 uiY )
{
 pRECT->uiX1 += uiX;
 pRECT->uiY1 += uiY;
 pRECT->uiX2 += uiX;
 pRECT->uiY2 += uiY;
}

avoid EL2008GUI_UpdateScene( EL2008GUI_SYSTEM *pGUISystem )
{
 uchar8 ucObjectsCount = GET_VHDBS2_COUNT( pGUISystem->pObjectsList );
 uchar8 i;
 
 for( i=0; i<ucObjectsCount; i++ )
 {
  uchar8 *pObj = GET_VHDBS2_OBJECT( pGUISystem->pObjectsList,i);
  uchar8 ucType = *pObj;
  
  EL2008GUI_PREFIX *pPREFIX = (EL2008GUI_PREFIX *)pObj;
  
  uchar8 ucFlag1 = EL2008GUI_GetFlag( pPREFIX, EL2008GUI_FLAG_VISIBLE );
  uchar8 ucFlag2 = EL2008GUI_GetFlag( pPREFIX, EL2008GUI_FLAG_UPDATE );
  
  if( ( ucFlag1 != 0 ) &&  ( ucFlag2 != 0 ) )
  {
	   if( ucType == eEL2008GUI_TYPE_WINDOW )  EL2008GUI_DrawWindow( 	(const EL2008GUI_WINDOW *)pObj );
       if( ucType == eEL2008GUI_TYPE_LABEL  )  EL2008GUI_DrawLabel ( 	(const EL2008GUI_LABEL *)pObj );
       if( ucType == eEL2008GUI_TYPE_CHECKBOX) EL2008GUI_DrawCheckBox(	(const EL2008GUI_CHECKBOX *)pObj );
       if( ucType == eEL2008GUI_TYPE_BITMAP)   EL2008GUI_DrawBitmap(	(const EL2008GUI_BITMAP *)pObj );
       
       if( ucType == eEL2008GUI_TYPE_BUTTON )
       {
           EL2008GUI_DrawButton( 	(const EL2008GUI_BUTTON *)pObj );
       }

	   EL2008GUI_ClearFlag( pPREFIX, EL2008GUI_FLAG_UPDATE );
  }
 }
}

// TODO: Rename
avoid EL2008GUI_DrawScene( EL2008GUI_SYSTEM *pGUISystem )
{
 // Search focus
 pGUISystem->ucFocusID = 0xFF;
 uchar8 ucObjectsCount = GET_VHDBS2_COUNT( pGUISystem->pObjectsList);
 uchar8 i;
 
 for( i=0; i<ucObjectsCount; i++ )
 {
  uchar8 *pObj = GET_VHDBS2_OBJECT(pGUISystem->pObjectsList,i);
  uchar8 ucType = *pObj;
  
  EL2008GUI_PREFIX *pPREFIX = (EL2008GUI_PREFIX *)pObj;
  EL2008GUI_SetFlag( pPREFIX, EL2008GUI_FLAG_VISIBLE );
  EL2008GUI_SetFlag( pPREFIX, EL2008GUI_FLAG_UPDATE );
  
  // Search first focusable element in the list
  if( EL2008GUI_GetFlag( pPREFIX, EL2008GUI_FLAG_FOCUSABLE ) != 0 )
  {
   if( pGUISystem->ucFocusID == 0xFF )
   { 
    pGUISystem->ucFocusID = i;
    EL2008GUI_SetFlag( pPREFIX, EL2008GUI_FLAG_FOCUS );  
   }
  }
  
 }
}

