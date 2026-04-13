#include "el2008gui.h"

avoid EL2008GUI_SetFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG )
{
      pPREFIX->ucFLAGS |= ucFLAG;
}

avoid EL2008GUI_ClearFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG )
{
      pPREFIX->ucFLAGS &= ~ucFLAG;
}

auchar8 EL2008GUI_GetFlag( EL2008GUI_PREFIX *pPREFIX, uchar8 ucFLAG )
{
  return (pPREFIX->ucFLAGS & ucFLAG) == ucFLAG;
}
