#include "el2008gui.h"

VHDBS2 sDBS2TEXT, sDBS2FILES, sDBS2FILESMP3, sDBS2OBJ;

int InsertText( const char *pTEXT )
{
  uchar8 ucLEN = strlen(pTEXT)+1;
  return VHDBS2_Insert( &sDBS2TEXT, (uchar8 *)pTEXT, ucLEN );
}

int InsertFile( const char *pFile )
{
  uchar8 ucLEN = strlen(pFile)+1;
  return VHDBS2_Insert( &sDBS2FILES, (uchar8 *)pFile, ucLEN );
}

void EL2008GUI_DBS2RESET( const EL2008GUI_SYSTEM *pGUISystem )
{
 VHDBS2_Reset( &sDBS2TEXT,  	pGUISystem->pStringsList, 	30 );
 VHDBS2_Reset( &sDBS2FILES, 	pGUISystem->pFilesList, 	30 );
 //VHDBS2_Reset( &sDBS2FILESMP3,	pGUISystem->pFilesListMP3, 	30 );
 VHDBS2_Reset( &sDBS2OBJ,   	pGUISystem->pObjectsList, 	30 );
}

void VHNAVI2008_SCRMAN_InsertLabel( const EL2008GUI_SYSTEM *pGUISYSTEM, const char *pText, const VHRECT *pRECT )
{
 EL2008GUI_LABEL sLABEL;
 
 sLABEL.sPREFIX.ucTYPE = eEL2008GUI_TYPE_LABEL;
 sLABEL.sPREFIX.ucVER  = 0;
 sLABEL.sPREFIX.ucFLAGS = 0;
 sLABEL.sPREFIX.ucRES = 0;
 memcpy( &sLABEL.sPREFIX.sRECT, pRECT, sizeof(VHRECT));
 
 sLABEL.sTEXT.ucTEXTID     = InsertText( pText ); // GET_VHDBS2_COUNT(sDBS2TEXT.pBASE);
 
 sLABEL.sTEXT.ucTEXTFontID = pGUISYSTEM->ucDEFAULT_LABEL_FONT_ID;
 sLABEL.sTEXT.ucTEXTAlign  = pGUISYSTEM->ucDEFAULT_LABEL_ALIGN;
 sLABEL.sTEXT.ucTEXTColor  = pGUISYSTEM->ucDEFAULT_LABEL_FONT_COLOR;
 sLABEL.ucBACKColor        = pGUISYSTEM->ucDEFAULT_LABEL_BACK_COLOR;
 sLABEL.sTEXT.ucTEXTAttr   = 0; // pGUISYSTEM->ucDEFAULT_TEXTATTR;
 
 VHDBS2_Insert( &sDBS2OBJ, &sLABEL, sizeof(EL2008GUI_LABEL) );
}

void VHNAVI2008_SCRMAN_InsertCheckBox( const EL2008GUI_SYSTEM *pGUISYSTEM, 
                                       const char *pText,
                                       const VHRECT *pRECT,
                                       uchar8 ucState )
{
 EL2008GUI_CHECKBOX sCHECKBOX;
 
 sCHECKBOX.sPREFIX.ucTYPE = eEL2008GUI_TYPE_CHECKBOX;
 sCHECKBOX.sPREFIX.ucVER  = 0;
 sCHECKBOX.sPREFIX.ucFLAGS = EL2008GUI_FLAG_FOCUSABLE;
 sCHECKBOX.sPREFIX.ucRES = 0;
 memcpy( &sCHECKBOX.sPREFIX.sRECT, pRECT, sizeof(VHRECT));
 
 sCHECKBOX.sTEXT.ucTEXTID     = InsertText( pText ); // GET_VHDBS2_COUNT(sDBS2TEXT.pBASE);
 sCHECKBOX.sTEXT.ucTEXTFontID = pGUISYSTEM->ucDEFAULT_CHECKBOX_FONT_ID;
 sCHECKBOX.sTEXT.ucTEXTAlign  = pGUISYSTEM->ucDEFAULT_CHECKBOX_ALIGN;
 sCHECKBOX.sTEXT.ucTEXTColor  = pGUISYSTEM->ucDEFAULT_CHECKBOX_FONT_COLOR;
 sCHECKBOX.sTEXT.ucTEXTAttr   = 0; // pGUISYSTEM->ucDEFAULT_TEXTATTR;
 
 sCHECKBOX.ucBACKColor        = pGUISYSTEM->ucDEFAULT_CHECKBOX_BACK_COLOR;
 sCHECKBOX.ucSTATE = ucState;
  
 // InsertText( pText );
 VHDBS2_Insert( &sDBS2OBJ, &sCHECKBOX, sizeof(EL2008GUI_CHECKBOX) );
}

// VHRGB(2,0,0,3);
// VHRGB(3,3,3,3);
// pGUISYSTEM->ucDEFAULT_TEXTATTR;

void VHNAVI2008_SCRMAN_InsertButton( const EL2008GUI_SYSTEM *pGUISYSTEM,
                                     const char *pText,
                                     const VHRECT *pRECT,
                                     uint16 uiCMD,
                                     uint16 uiPARAM )
{
 EL2008GUI_BUTTON sBUTTON;
 
 sBUTTON.sPREFIX.ucTYPE = eEL2008GUI_TYPE_BUTTON;
 sBUTTON.sPREFIX.ucVER  = 0;
 sBUTTON.sPREFIX.ucFLAGS = EL2008GUI_FLAG_FOCUSABLE;
 sBUTTON.sPREFIX.ucRES = 0;

 memcpy( &sBUTTON.sPREFIX.sRECT, pRECT, sizeof(VHRECT));

 int iTextID = InsertText( pText ); // GET_VHDBS2_COUNT(sDBS2TEXT.pBASE);

 sBUTTON.sTEXT.ucTEXTID     = iTextID;
 sBUTTON.sTEXT.ucTEXTFontID = pGUISYSTEM->ucDEFAULT_BUTTON_FONT_ID;
 sBUTTON.sTEXT.ucTEXTAlign  = pGUISYSTEM->ucDEFAULT_BUTTON_TEXT_ALIGN;
 sBUTTON.sTEXT.ucTEXTAttr   = 0; 
 sBUTTON.sTEXT.ucTEXTColor  = pGUISYSTEM->ucDEFAULT_BUTTON_FONT_COLOR;
 sBUTTON.ucBUTTONColor 		= pGUISYSTEM->ucDEFAULT_BUTTON_BACK_COLOR;
 sBUTTON.ucBUTTONFrameColor = pGUISYSTEM->ucDEFAULT_BUTTON_FRAME_COLOR; 

 sBUTTON.sTEXTSEL.ucTEXTID      = iTextID; 
 sBUTTON.sTEXTSEL.ucTEXTFontID  = pGUISYSTEM->ucDEFAULT_BUTTON_SELECTED_FONT_ID;
 sBUTTON.sTEXTSEL.ucTEXTAlign   = pGUISYSTEM->ucDEFAULT_BUTTON_SELECTED_TEXT_ALIGN;
 sBUTTON.sTEXTSEL.ucTEXTAttr    = 0; 
 sBUTTON.sTEXTSEL.ucTEXTColor   = pGUISYSTEM->ucDEFAULT_BUTTON_SELECTED_FONT_COLOR;
 sBUTTON.ucBUTTONSELColor 		= pGUISYSTEM->ucDEFAULT_BUTTON_SELECTED_BACK_COLOR;
 sBUTTON.ucBUTTONSELFrameColor  = pGUISYSTEM->ucDEFAULT_BUTTON_SELECTED_FRAME_COLOR; 
 
 sBUTTON.ucEVENT            = uiCMD;
 sBUTTON.ucEVENTARG         = uiPARAM;

 // InsertText( pText );
 VHDBS2_Insert( &sDBS2OBJ, &sBUTTON, sizeof(EL2008GUI_BUTTON) );
}

void VHNAVI2008_SCRMAN_InsertButtonM( 	const EL2008GUI_SYSTEM *pGUISYSTEM,
        								const char *pText,
        								VHRECT *pRECT,
        								uint16 uiCMD,
        								uint16 uiPARAM,
        								uint16 uiXDelta,
        								uint16 uiYDelta )
{
	VHNAVI2008_SCRMAN_InsertButton( pGUISYSTEM, pText, pRECT, uiCMD, uiPARAM );
	MoveRect( pRECT, uiXDelta, uiYDelta );
}
 
void VHNAVI2008_SCRMAN_InsertBitmap( const EL2008GUI_SYSTEM *pGUISYSTEM, const char *pFileName, const VHRECT *pRECT )
{
  EL2008GUI_BITMAP sBITMAP;
  sBITMAP.sPREFIX.ucTYPE = eEL2008GUI_TYPE_BITMAP;
  sBITMAP.sPREFIX.ucVER = 0;
  sBITMAP.sPREFIX.ucFLAGS = 0;
  sBITMAP.sPREFIX.ucRES = 0;
  memcpy( &sBITMAP.sPREFIX.sRECT, pRECT, sizeof(VHRECT));
  sBITMAP.ucBMPID = InsertFile( pFileName ); // GET_VHDBS2_COUNT(sDBS2FILES.pBASE);
    
  VHDBS2_Insert( &sDBS2OBJ, &sBITMAP, sizeof(EL2008GUI_BITMAP) );
}

void VHNAVI2008_SCRMAN_InsertWindow( const EL2008GUI_SYSTEM *pGUISYSTEM,
                                     const char *pCaptionName,
                                     const VHRECT *pRECT )
{
 EL2008GUI_WINDOW sWINDOW;

 sWINDOW.sPREFIX.ucTYPE  = eEL2008GUI_TYPE_WINDOW;
 sWINDOW.sPREFIX.ucVER   = 0;
 sWINDOW.sPREFIX.ucFLAGS = 0;
 sWINDOW.sPREFIX.ucRES   = 0;
 memcpy( &sWINDOW.sPREFIX.sRECT, pRECT, sizeof(VHRECT));

 sWINDOW.sTEXT.ucTEXTID     = InsertText( pCaptionName ); // GET_VHDBS2_COUNT(sDBS2TEXT.pBASE);
 sWINDOW.sTEXT.ucTEXTAlign  = pGUISYSTEM->ucDEFAULT_WINDOW_ALIGN;
 sWINDOW.sTEXT.ucTEXTFontID = pGUISYSTEM->ucDEFAULT_WINDOW_FONT_ID;
 sWINDOW.sTEXT.ucTEXTAttr   = 0;
 sWINDOW.sTEXT.ucTEXTColor  = pGUISYSTEM->ucDEFAULT_WINDOW_FONT_COLOR;
 sWINDOW.ucCaptionColor     = pGUISYSTEM->ucDEFAULT_WINDOW_BACK_COLOR;
 sWINDOW.ucBodyColor        = pGUISYSTEM->ucDEFAULT_WINDOW_BODY_COLOR;
 sWINDOW.ucCaptionWidth     = pGUISYSTEM->ucDEFAULT_WINDOW_CAPTION_WIDTH;
 
 // InsertText( pCaptionName );
 VHDBS2_Insert( &sDBS2OBJ, &sWINDOW, sizeof(EL2008GUI_WINDOW) );
}


