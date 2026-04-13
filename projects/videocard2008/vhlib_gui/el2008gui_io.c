#include "el2008gui.h"

extern volatile EL2008GUI_SYSTEM sGUISYSTEM;

uint16 uiBMPBytesInLine;
uint16 uiBMPPixelsInLine;
uint16 uiBMPLinesLeft;
uchar8 szBMPSPACE[400];

extern uchar8 VHLIB_EL2008GUI_OPENFILE( char *szFileName );
extern uchar8 VHLIB_EL2008GUI_READFILE( char *pResult, uint16 uiBytes );
extern uchar8 VHLIB_EL2008GUI_CLOSEFILE();

auchar8 EL2008GUI_BMP_Init( uchar8 ucBMPID, uint16 *pWidth, uint16 *pHeight )
{
 uiBMPLinesLeft = 100;
 
 if( ucBMPID >= GET_VHDBS2_COUNT( sGUISYSTEM.pFilesList ) ) return 0; // Invalid file ID
 
 char *pFileName = (char *)GET_VHDBS2_OBJECT( sGUISYSTEM.pFilesList, ucBMPID );
 
 if( !VHLIB_EL2008GUI_OPENFILE( pFileName ) ) return 0;
 if( !VHLIB_EL2008GUI_READFILE( (char *) &szBMPSPACE[0], 0x76 ) ) return 0;
 
 if( szBMPSPACE[0] != 0x42 ) return 0;
 if( szBMPSPACE[1] != 0x4D ) return 0;
 if( szBMPSPACE[10] != 0x76 ) return 0;
 
 uint16 *pPTRW = (uint16 *)&szBMPSPACE[0x12];
 uint16 *pPTRH = (uint16 *)&szBMPSPACE[0x16];
 
 *pWidth = *pPTRW;
 *pHeight = *pPTRH;
 
 uiBMPPixelsInLine = *pPTRW;
 uiBMPLinesLeft = *pPTRH;
  
 // Calculate line length in bytes
 uiBMPBytesInLine = (*pPTRW) / 2;
 uint16 uiA = uiBMPBytesInLine % 4;
 if( uiA ) uiBMPBytesInLine += 4 - uiA;
 
 return 1;
}

auchar8 EL2008GUI_BMP_ReadLine()
{
 if( !VHLIB_EL2008GUI_READFILE( (char *)&szBMPSPACE[0], uiBMPBytesInLine ) ) return 0;
 uiBMPLinesLeft--;
 if( !uiBMPLinesLeft ) VHLIB_EL2008GUI_CLOSEFILE();
 return 1;
}

uchar8 * EL2008GUI_BMP_DATA()
{
 return &szBMPSPACE[0];
}
