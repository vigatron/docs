#include "el2008gui.h"

void VHDBS2_Reset( VHDBS2 *pDBS2, void *pBASE, uchar8 ucItemsCount )
{
  pDBS2->pBASE = (uchar8 *)pBASE;
  pDBS2->ucItemsCount = ucItemsCount;
  pDBS2->pDATA = (uchar8 *)pBASE;
  pDBS2->pPTRINT  = (uint16 *)pBASE;
  pDBS2->pPTRCOUNT  = (uint16 *)pBASE;
 
  uint16 *pCOUNT = pDBS2->pPTRCOUNT;
  *pCOUNT = 0;
  pDBS2->pPTRINT++;
  pDBS2->pDATA += (pDBS2->ucItemsCount * 4) + 2;
}

int VHDBS2_Insert( VHDBS2 *pDBS2, void *pOBJ, uchar8 ucSize )
{
   int iResult = *pDBS2->pPTRCOUNT; // GET_VHDBS2_COUNT( pDBS2 );
   if( *(pDBS2->pPTRCOUNT) >= pDBS2->ucItemsCount ) return -1; // Overflow
   
   memcpy( pDBS2->pDATA, pOBJ, ucSize );
   (*pDBS2->pPTRCOUNT)++;
   *pDBS2->pPTRINT = (uchar8 *)pDBS2->pDATA - (uchar8 *)pDBS2->pBASE;
   pDBS2->pPTRINT++;
   *pDBS2->pPTRINT = ucSize;
   pDBS2->pPTRINT++;
   pDBS2->pDATA += ucSize;
   
   return iResult;
}

void VHDBS2_Save( VHDBS2 *pDBS2, char *pFileName )
{
 /*
 VFile mFile;
 mFile.Open( pFileName, VFile::WRITE );
 mFile.Write( pDBS2->pBASE, pDBS2->pDATA - pDBS2->pBASE );
 mFile.Close();
 */
}
