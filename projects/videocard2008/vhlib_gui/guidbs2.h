VHSTRUCT(VHDBS2)
{
  uchar8 *pBASE;
  uchar8 *pDATA;
  uint16 *pPTRCOUNT;
  uint16 *pPTRINT;
  uchar8 ucItemsCount;
};

typedef struct VHDBS2 VHDBS2;

void VHDBS2_Reset( VHDBS2 *pDBS2, void *pBASE, uchar8 ucItemsCount );
int  VHDBS2_Insert( VHDBS2 *pDBS2, void *pOBJ, uchar8 ucSize );
void VHDBS2_Save( VHDBS2 *pDBS2, char *pFileName );

