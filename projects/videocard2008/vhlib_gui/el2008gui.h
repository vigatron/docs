#ifndef _VHLIB_EL2008GUI_H_
#define _VHLIB_EL2008GUI_H_

#include "vhplatform.h"

// FASTCALLS used only on embedded platform
#define achar8 		char
#define auchar8 	uchar8
#define auint16 	uint16
#define avoid 		void

// mini-vector implementation
#define GET_VHDBS2_COUNT(PTR)       (*((uint16 *)PTR))
#define GET_VHDBS2_OBJECT(PTR,N)    (((uchar8 *)PTR) + (*(((uint16 *)PTR)+1+(N*2))))

#include "guicolors.h"

#define EL2008GUI_FLAG_VISIBLE       0x01
#define EL2008GUI_FLAG_UPDATE        0x02
#define EL2008GUI_FLAG_DISABLE       0x04
#define EL2008GUI_FLAG_COLOR         0x08
#define EL2008GUI_FLAG_FOCUS         0x10
#define EL2008GUI_FLAG_FOCUSABLE     0x20
#define EL2008GUI_FLAG_SYSTEMTXT     0x40

#define EL2008GUI_EVENT_GOTO_MENU 0x01

#define EL2008GUI_STYLE_TRANSPARENT 0x01
#define EL2008GUI_STYLE_DBLCOLOR    0x02

// defined as 0 for B&W
#define SCREEN_COLOR 1
// #define SCREEN_MAX_WIDTH    320
// #define SCREEN_MAX_HEIGHT   240
#define SCREEN_MAX_WIDTH    640
#define SCREEN_MAX_HEIGHT   480
#define SCREEN_FACTOR 1

#define SYMMINWIDTH 10

#include "guitypes.h"
#include "guievents.h"
#include "guiirda.h"
#include "guidbs2.h"

VHSTRUCT(VHRECT)
{
 sint16 uiX1;
 sint16 uiY1;
 sint16 uiX2;
 sint16 uiY2;
};

typedef struct VHRECT VHRECT;

VHSTRUCT(EL2008GUI_SYSTEM)
{
 void *pStringsList;
 void *pFilesList;
//  void *pFilesListMP3;
 void *pObjectsList;
 uint16 uiSCREENID;
 uchar8 ucFocusID;
 
 // Default settings of the selected button
 uchar8 ucDEFAULT_BUTTON_SELECTED_FONT_ID;
 uchar8 ucDEFAULT_BUTTON_SELECTED_FONT_COLOR;
 uchar8 ucDEFAULT_BUTTON_SELECTED_BACK_COLOR;
 uchar8 ucDEFAULT_BUTTON_SELECTED_FRAME_COLOR;
 uchar8 ucDEFAULT_BUTTON_SELECTED_TEXT_ALIGN;

 // Default settings of the Button
 uchar8 ucDEFAULT_BUTTON_FONT_ID;
 uchar8 ucDEFAULT_BUTTON_FONT_COLOR;
 uchar8 ucDEFAULT_BUTTON_BACK_COLOR;
 uchar8 ucDEFAULT_BUTTON_FRAME_COLOR;
 uchar8 ucDEFAULT_BUTTON_TEXT_ALIGN;

 // Default settings of the Checkbox
 uchar8 ucDEFAULT_CHECKBOX_FONT_ID;
 uchar8 ucDEFAULT_CHECKBOX_FONT_COLOR;
 uchar8 ucDEFAULT_CHECKBOX_BACK_COLOR;
 uchar8 ucDEFAULT_CHECKBOX_FRAME_COLOR;
 uchar8 ucDEFAULT_CHECKBOX_ALIGN;
 
 // Default settings of the Label
 uchar8 ucDEFAULT_LABEL_FONT_ID;
 uchar8 ucDEFAULT_LABEL_FONT_COLOR;
 uchar8 ucDEFAULT_LABEL_BACK_COLOR;
 uchar8 ucDEFAULT_LABEL_ALIGN;
 
 // Default settings of the Window
 uchar8 ucDEFAULT_WINDOW_FONT_ID;
 uchar8 ucDEFAULT_WINDOW_FONT_COLOR;
 uchar8 ucDEFAULT_WINDOW_BACK_COLOR;
 uchar8 ucDEFAULT_WINDOW_BODY_COLOR;
 uchar8 ucDEFAULT_WINDOW_CAPTION_WIDTH;
 uchar8 ucDEFAULT_WINDOW_ALIGN;
 
 
 
 
 
 /* 
 uchar8 ucDEFAULT_TEXTALIGN;
 uchar8 ucDEFAULT_TEXTFONTID;
 uchar8 ucDEFAULT_TEXTATTR;
 uchar8 ucDEFAULT_TEXTCOLOR;
 uchar8 ucDEFAULT_OBJCOLOR;
 uchar8 ucDEFAULT_OBJBORDERCOLOR;
 uchar8 ucDEFAULTCOLOR_WINDOW_CAPTION_TEXT;
 uchar8 ucDEFAULTCOLOR_WINDOW_CAPTION;
 uchar8 ucDEFAULTCOLOR_WINDOW_BODY;
 uchar8 ucDEFAULTCOLOR_BUTTON_TEXT;
 */
};

typedef struct EL2008GUI_SYSTEM EL2008GUI_SYSTEM;

VHSTRUCT(EL2008GUI_PREFIX)
{
  uchar8 ucTYPE;
  uchar8 ucVER;
  uchar8 ucFLAGS;
  uchar8 ucRES;
  VHRECT sRECT;
};

typedef struct EL2008GUI_PREFIX EL2008GUI_PREFIX;

VHSTRUCT(EL2008GUI_TEXT)
{
  char   ucTEXTID;
  uchar8 ucTEXTAlign;
  uchar8 ucTEXTFontID;
  uchar8 ucTEXTAttr;
  uchar8 ucTEXTColor;
};

typedef struct EL2008GUI_TEXT EL2008GUI_TEXT;

VHSTRUCT(EL2008GUI_LABEL)
{
  EL2008GUI_PREFIX sPREFIX;
  EL2008GUI_TEXT sTEXT;
  uchar8 ucBACKColor;
};

typedef struct EL2008GUI_LABEL EL2008GUI_LABEL;

VHSTRUCT(EL2008GUI_BUTTON)
{
  EL2008GUI_PREFIX sPREFIX;
  EL2008GUI_TEXT   sTEXT;
  EL2008GUI_TEXT   sTEXTSEL;
  
  uchar8           ucBUTTONColor;
  uchar8           ucBUTTONFrameColor;
  uchar8           ucBUTTONSELColor;
  uchar8           ucBUTTONSELFrameColor;
  
  uchar8 ucEVENT;
  uchar8 ucEVENTARG;
};

VHSTRUCT(EL2008GUI_CHECKBOX)
{
  EL2008GUI_PREFIX sPREFIX;
  EL2008GUI_TEXT sTEXT;
  uchar8 ucBACKColor;
  uchar8 ucSTATE;
};

VHSTRUCT(EL2008GUI_BITMAP)
{
  EL2008GUI_PREFIX sPREFIX;
  uchar8 ucBMPID;
  uchar8 ucCOLORSMAP;
};

VHSTRUCT(EL2008GUI_WINDOW)
{
  EL2008GUI_PREFIX sPREFIX;
  EL2008GUI_TEXT   sTEXT;
  uchar8 ucCaptionColor;
  uchar8 ucBodyColor;
  uchar8 ucCaptionWidth;
};


typedef struct EL2008GUI_BUTTON EL2008GUI_BUTTON;
typedef struct EL2008GUI_CHECKBOX EL2008GUI_CHECKBOX;
typedef struct EL2008GUI_BITMAP EL2008GUI_BITMAP;
typedef struct EL2008GUI_WINDOW EL2008GUI_WINDOW;


void MoveRect( VHRECT *pRECT, sint16 uiX, sint16 uiY );


// *** Fonts routines
achar8  FONT_GET_SYM_T( uchar8 ucSYM, uchar8 ucFONT );
auchar8 FONT_GET_SYM_W( uchar8 ucSYM, uchar8 ucFONT );
auchar8 FONT_GET_SYM_H( uchar8 ucSYM, uchar8 ucFONT );
auint16 FONT_GET_SYM_O( uchar8 ucSYM, uchar8 ucFONT );
auchar8 FONT_GET_SYM_B( uint16 uiOFFSET, uchar8 ucFONT );

auint16 EL2008GUI_GetTextWidth( const char *pText, uchar8 ucFont );
auint16 EL2008GUI_GetTextHeight( uchar8 ucFont );

// *** GUI Objects FLAGS routines
avoid EL2008GUI_SetFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG );
avoid EL2008GUI_ClearFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG );
auchar8 EL2008GUI_GetFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG );

avoid EL2008GUI_FOCUS_Next( EL2008GUI_SYSTEM *pGUISystem );
avoid EL2008GUI_FOCUS_Prev( EL2008GUI_SYSTEM *pGUISystem );

avoid EL2008GUI_SetPointer( uint16 uiX, uint16 uiY );
avoid EL2008GUI_DrawPixelAndRight( uchar8 ucCOL );
avoid EL2008GUI_DrawPixelAndLeft( uchar8 ucCOL );

/*
auint16 EL2008GUI_GetTextWidth( const char *pText, uchar8 ucFont );
auint16 EL2008GUI_GetTextHeight( uchar8 ucFont );
avoid EL2008GUI_DrawText( const char *pText, const VHRECT *pRect, uchar8 ucAlign, uchar8 ucFont, uchar8 ucCOL );
*/

auchar8 ELGUI2008_DRAW_CHAR( uchar8 ucSYM, uint16 uiX, uint16 uiY, uchar8 ucFont, uchar8 ucCOL );
avoid ELGUI2008_TEXT_OUT( const char *pText, uint16 x, uint16 y, uchar8 ucFont, uchar8 ucCOL );
avoid EL2008GUI_DrawTextA( const char *pText, const VHRECT *pRect, uchar8 ucAlign, uchar8 ucFont, uchar8 ucCOL );
avoid EL2008GUI_DrawText( const VHRECT *pRect, const EL2008GUI_TEXT *pTEXT );

avoid EL2008GUI_DrawFrame( const VHRECT *pRect, uchar8 ucCOL1, uchar8 ucCOL2 );

avoid EL2008GUI_DrawRect( const VHRECT *pRect, uchar8 ucCOL );
avoid EL2008GUI_DrawLabel( const EL2008GUI_LABEL *pLabel );
avoid EL2008GUI_DrawButton( const EL2008GUI_BUTTON *pButton );
avoid EL2008GUI_DrawCheckBox( const EL2008GUI_CHECKBOX *pCheckBox );
avoid EL2008GUI_DrawWindow( const EL2008GUI_WINDOW *pWindow );
avoid EL2008GUI_DrawBitmap( const EL2008GUI_BITMAP * pBITMAP );

avoid EL2008GUI_UpdateScene( EL2008GUI_SYSTEM *pGUISystem );
avoid EL2008GUI_DrawScene( EL2008GUI_SYSTEM *pGUISystem );

// avoid EL2008GUI_ProcessEvent( EL2008GUI_SYSTEM *pGUISystem, uchar8 enEvent );

// BMP Routines
auchar8 EL2008GUI_BMP_Init( uchar8 ucBMPID, uint16 *pWidth, uint16 *pHeight );
auchar8 EL2008GUI_BMP_ReadLine();
uchar8 * EL2008GUI_BMP_DATA();

// void DebugValue( uint32 uiVal );

int InsertText( const char *pTEXT );
int InsertFile( const char *pFile );

void EL2008GUI_DBS2RESET( const EL2008GUI_SYSTEM *pGUISYSTEM );

void VHNAVI2008_SCRMAN_InsertLabel( const EL2008GUI_SYSTEM *pGUISYSTEM, const char *pText, const VHRECT *pRECT );

void VHNAVI2008_SCRMAN_InsertCheckBox( const EL2008GUI_SYSTEM *pGUISYSTEM,
                                       const char *pText,
                                       const VHRECT *pRECT,
                                       uchar8 ucState );

void VHNAVI2008_SCRMAN_InsertButton( const EL2008GUI_SYSTEM *pGUISYSTEM,
                                     const char *pText,
                                     const VHRECT *pRECT,
                                     uint16 uiCMD,
                                     uint16 uiPARAM );

void VHNAVI2008_SCRMAN_InsertButtonM( 	const EL2008GUI_SYSTEM *pGUISYSTEM,
        								const char *pText,
        								VHRECT *pRECT,
        								uint16 uiCMD,
        								uint16 uiPARAM,
        								uint16 uiXDelta,
        								uint16 uiYDelta );



void VHNAVI2008_SCRMAN_InsertBitmap( const EL2008GUI_SYSTEM *pGUISYSTEM, const char *pFileName, const VHRECT *pRECT );									 

void VHNAVI2008_SCRMAN_InsertWindow( const EL2008GUI_SYSTEM *pGUISYSTEM,
                                     const char *pCaptionName,
                                     const VHRECT *pRECT );

#endif

