/******************************************************************************
 *
 * Copyright (c) 1999 Palm Computing, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Starter.cpp
 *
 *****************************************************************************/

#include <PalmOS.h>
#include <PalmCompatibility.h>
#include "StarterRsc.h"

#define	szFileDatabase 	"FFImport.DAT"
#define	szFileTemporary	"FFImport.000"

unsigned 	char	MemPage[ 256 ];
int			comspeed = 19200;

/***********************************************************************
 *
 *   Internal Structures
 *
 ***********************************************************************/
typedef struct 
	{
	UInt8 replaceme;
	} StarterPreferenceType;

typedef struct 
	{
	UInt8 replaceme;
	} StarterAppInfoType;

typedef StarterAppInfoType* StarterAppInfoPtr;

/***********************************************************************
 *
 *   Internal Constants
 *
 ***********************************************************************/
#define	appFileCreator				'0007'
#define appVersionNum				0x01
#define appPrefID					0x00
#define appPrefVersionNum			0x01

// Define the minimum OS version we support (2.0 for now).
#define ourMinVersion	sysMakeROMVersion(2, 0, 0, sysROMStageRelease, 0)

/***********************************************************************
 *
 * FUNCTION:    RomVersionCompatible
 *
 * DESCRIPTION: This routine checks that a ROM version is meet your
 *              minimum requirement.
 *
 * PARAMETERS:  requiredVersion - minimum rom version required
 *                                (see sysFtrNumROMVersion in SystemMgr.h 
 *                                for format)
 *              launchFlags     - flags that indicate if the application 
 *                                UI is initialized.
 *
 * RETURNED:    error code or zero if rom is compatible
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
		{
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
			{
			FrmAlert (RomIncompatibleAlert);
		
			// Palm OS 1.0 will continuously relaunch this app unless we switch to 
			// another safe one.
			if (romVersion < ourMinVersion)
				{
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
				}
			}
		
		return sysErrRomIncompatible;
		}

	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  formId - id of the form to display
 *
 * RETURNED:    void *
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID)
{
	FormPtr frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

//*********************************************************************************
static void WinDrawRect( int x1, int y1, int x2, int y2)
{
 	WinDrawLine( x1, y1, x2, y1 );
 	WinDrawLine( x2, y1, x2, y2 );
 	WinDrawLine( x2, y2, x1, y2 );
 	WinDrawLine( x1, y2, x1, y1 );
}

//*********************************************************************************
static void Debug( int r, int x, int y )
{
	 char	temp[20];
	 
	 StrPrintF( temp, "[%X h ]", r );
	 WinDrawChars( temp, StrLen( temp ), x, y );
}				 

//*********************************************************************************
static void TextToField( char *str, UInt16 idFld )
{

  FieldPtr		fld;
  VoidHand	memH;
  VoidPtr		ptr;
  int			strl;
  
  fld=( FieldPtr )GetObjectPtr( idFld );
  memH=FldGetTextHandle( fld );
   if( memH!=NULL )  
   	{
   		FldSetTextHandle( fld, NULL )  ;
   		MemHandleFree( memH );
   	}
   
   if( str != NULL )
   {
    strl=StrLen( str );	
    memH=MemHandleNew( strl+1 );
     ptr=MemHandleLock( memH );
     StrCopy( (char *)ptr, str );
     MemHandleUnlock( memH );
    FldSetTextHandle ( fld, memH );
   }
   FldDrawField (fld);
}	

//*****************************************************************************
static void FieldToText( UInt16 idFld, char *str )
{
 FieldPtr		fld;
 VoidHand	memH;
 VoidPtr		ptr;
			
  fld=( FieldPtr )GetObjectPtr( idFld );
  memH=FldGetTextHandle( fld );
  if( memH==NULL) *str=0;
   else
   {
   ptr=MemHandleLock( memH );
   StrCopy( str, (char *) ptr );
   MemHandleUnlock( memH );
   }
}

//******************************************************************************
void ImportProcedure();
void ImportProcedure()
{
  #define			CrandlePortMask		0x8000

  char				*szRead = "Bytes read";
  
  UInt16			portID;
  unsigned char		resetPage	= 0x38;
  unsigned char		importPage	= 0x39;
  unsigned char		askSerial 	= 0x03;
  unsigned char		resultByte	= 0;
  Err				err;
  Err				processErr = 0;
  Int32				Delay = 100;
  UInt32			pageN = 0, byteN = 0;
  UInt16			bytesR=0;	// For display counter only !
  char				buff[30];
  FileHand			fh;
  RectangleType		rc;
  
  int				lineX = 10;
  int				lineY = 100;
  int				lineXL = 140;
  int				lineYL = 20;
  



  rc.topLeft. x = lineX;
  rc.topLeft. y = lineY - 20;
  rc.extent. x = lineXL;
  rc.extent. y = lineYL + 22;
  
  if( SrmOpen( CrandlePortMask, 19200, &portID ) ) 
   { 
    FrmAlert( PortAlert ); 
    return; 
   }
	
	// Send 0x5 - Serial number request
	SrmSend( portID, &askSerial, 1, &err );	
	SrmSendWait( portID );

	// Receive 
	while( !processErr )
	 {
 	   SrmReceive( portID, &SerialN[byteN++], 1, Delay, &err );
 	   if( err )
 	   { 
 	     processErr++;
 	     byteN--;
 	   }
 	 }
 	 
  	processErr = 0;
  	
  	// Check for correct serial number
    if( !byteN )
    {
    SrmClose( portID );
    FrmAlert( ErrorAlert );
    return;
    }
    
    SerialN[byteN] = 0;
    byteN = 0;
    
    TextToField( (char *)SerialN, MainSNField );
	
	// Begin to import 64Kb block ! 
	
	// Reset Page pointer to zero
	SrmSend( portID, &resetPage, 1, &err );

	SrmSendWait( portID );
	
    SrmReceive( portID, &resultByte, 1, Delay, &err );
    if( err ) 
    {
     SrmClose( portID );
     FrmAlert( ErrorAlert );
     return;
    }
    if( resultByte != resetPage ) 
    {
     SrmClose( portID );
     FrmAlert( ErrorAlert );
     return;
    }
   
   // Autentification process is Ok ... so make all work
   // WinDrawLine( pageN * 160 / 256 , 100 , pageN * 160 / 256, 120 );
   
   fh = FileOpen ( 0, szFileTemporary, 0, 0, fileModeReadWrite, &err );
   if( !fh )  
   {
    SrmClose( portID );
    FrmAlert( SpaceAlert );
    return;
   }

   WinDrawChars( szRead, StrLen( szRead ), 10, lineY - 12 ); // Write process string
   
   while( (pageN < 256) && ( !processErr ) )
     {
   	SrmSend( portID, &importPage, 1, &err );
   	SrmSendWait( portID );

   	byteN = 0;
   	while( (!processErr) && ( byteN< 256 ) )
   		{
    			SrmReceive( portID, &resultByte, 1, Delay, &err );
    			if( err ) processErr++; 
    			    else 
    			    {
    			    MemPage[ byteN ] = resultByte;
    			    byteN++;
    			    bytesR++;
    			    }
    			
      		}
      	 WinDrawLine( lineX + (pageN * lineXL / 256 ) , lineY , lineX + (pageN * lineXL / 256 ), lineY + lineYL );
      	 pageN++;
      	
      	 if( FileWrite( fh, MemPage, 256, 1, &err ) != 1 ) 
      	 {
      	   FileClose( fh );
      	   SrmClose( portID );
      	   FrmAlert( SpaceAlert );
      	   return;
      	 }
      	 
      	 StrPrintF( buff, "%u      ", bytesR );
      	 WinDrawChars( buff, StrLen( buff ), 110, lineY - 12 ); // Display number of bytes
   	    	 
      }

  SrmClose( portID );
  FileClose( fh );
  WinEraseRectangle( &rc, 0 );

  if( processErr ) 
  {
   FrmAlert( ErrorAlert );
   return;
  }

  FrmAlert( OkAlert );
  
 // Final step. Add new Block to Global Database 

  FileHand		srcFile = 0, dstFile = 0;
  Err			srcErr, dstErr;
  Long			srcSize, dstSize;
  DateTimeType	dt;
  ULong			scs;
    
  processErr = 0;
  
  srcFile = FileOpen( 0, szFileTemporary, 0, 0, fileModeReadOnly, &srcErr );
  dstFile = FileOpen( 0, szFileDatabase, 0, 0, fileModeAppend, &dstErr );
  
  if( !dstFile ) 
   { 
    if( srcFile ) FileClose(srcFile); 
    FrmAlert( AppendErrorAlert ); 
    return;
   }
  
	FileTell( srcFile, &srcSize, &srcErr );
	FileTell( dstFile, &dstSize, &dstErr );

	// Write 20 bytes of serial
	FileWrite( dstFile, SerialN, 20, 1, &err );
	if( err ) 
	{ 
	 FileTruncate( dstFile, dstSize );
	 FileClose( srcFile );
	 FileClose( dstFile );
	 FrmAlert( AppendErrorAlert );
	 return;
	}

	// Get current date&time	
	scs = TimGetSeconds();

	// Convert	
	TimSecondsToDateTime( scs, &dt );

	// Write time&date	
	FileWrite( dstFile, &dt, sizeof( DateTimeType), 1, &err );
	if( err ) 
	{
	 FileTruncate( dstFile, dstSize );
	 FileClose( srcFile );
	 FileClose( dstFile );
	 FrmAlert( AppendErrorAlert );
	 return;
	}
	
	int	x;

	for( 	x = 0; x<256; x++ )
	  {
	    // Read to RAM temporary file
		FileRead( srcFile, MemPage, 256, 1,  &err); 	
		if( err ) 
		{
		 FileTruncate( dstFile, dstSize );
		 FileClose( srcFile );
		 FileClose( dstFile );
		 FrmAlert( AppendErrorAlert );
		 return;
		}
		
		// Write to Database RAM		
		FileWrite( dstFile, MemPage, 256, 1, &err );	
		if( err ) 
		{
		 FileTruncate( dstFile, dstSize );
		 FileClose( srcFile );
		 FileClose( dstFile );
		 FrmAlert( AppendErrorAlert );
		 return;
		}
	  }	
	    
   	FileClose( srcFile );
  	FileClose( dstFile );
  
   FrmAlert( EraseAlert );
}

/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:  frm - pointer to the MainForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void MainFormInit(FormPtr /*frmP*/)
{
}

//**************************
static void ProcExport()
{
  UInt16			portID;
  unsigned char		askPC = 0xFE;
  unsigned char		page =  0xFC;

  unsigned char		resultPC;
  FileHand			fh;
  Err				err;
  int				Delay = 100;
  char				tmp[100];
  int				x;


  TextToField( "Try to connect", MainStatusField );
  
  if( SrmOpen( CrandlePortMask, comspeed, &portID ) ) 
  { 
   FrmAlert( PortAlert );
   return ; 
  }

	// Send 0xFE
	SrmSend( portID, &askPC, 1, &err );			
	SrmSendWait( portID );

	// Receive 0xFE  
    SrmReceive( portID, &resultPC, 1, Delay, &err );	
	if( err ) 
	{
	 SrmClose( portID );
	 FrmAlert( PCErr1Alert );
	 return; 
	}
    if( resultPC != askPC )
    {
     SrmClose( portID );
     FrmAlert( PCErr1Alert );
     return;
    }

  // Open file for send
  fh = FileOpen( 0, szFileDatabase, 0, 0, fileModeReadOnly, &err );
  if( err )
  {
   SrmClose( portID );
   FrmAlert( DatabaseEmptyAlert );
   return;
  }


while( 1 == 1 )
{

	unsigned char	slen;
	int				pagesN = 256;
	long 			l;


	// Send Serial Number
    TextToField( "Send SN ...", MainStatusField );
   	
   	l = FileRead( fh, MemPage, 1, 20, &err );
   	
//   	if( !l )
//   	{
//   	 TextToField( "Ok ...", MainStatusField );
//	 FileClose( fh );
//	 SrmClose( portID );
//   	}
   	
   	slen = StrLen( (char * )MemPage );
   	SrmSend( portID, &slen, 1, &err );
   	SrmSendWait( portID );
	SrmSend( portID, MemPage, slen, &err );			
	SrmSendWait( portID );

	// Send Attributes
    TextToField( "Send time&date", MainStatusField );
   	FileRead( fh, MemPage, 1, sizeof( DateTimeType ), &err );
   	
	slen = sizeof( DateTimeType ); 
   	SrmSend( portID, &slen, 1, &err );
   	SrmSendWait( portID );
   	SrmSend( portID, MemPage, sizeof( DateTimeType ), &err );
   	SrmSendWait( portID );

	while( pagesN-- )
	{
	// Ask PC for transmit Page and transmit page
   	SrmSend( portID, &page, 1, &err );					
	SrmSendWait( portID );
	SrmReceive( portID, &resultPC, 1, Delay, &err );
	if( ( err ) || ( resultPC != page ) )
	{
		FileClose( fh );
		SrmClose( portID );
		//FrmAlert( PCErr1Alert ); 
		// !!! Set OK!
		FileDelete ( 0 , szFileDatabase );
		return;
	}

	// Send 1 page
   	FileRead( fh, MemPage, 1, 256, &err );	
   	
   	for( x = 0; x< 256; x++ )
   	 {
   	  SrmSend( portID, &MemPage[x], 1, &err );					
   	  SrmSendWait( portID );
   	  SrmReceive( portID, &resultPC, 1, Delay, &err );
   	  if ( ( resultPC != MemPage[x] ) || ( err ) )
   	   {
			  FileClose( fh );
			  SrmClose( portID );
			FrmAlert( PCErr1Alert );   	    		
			FrmAlert( PCErr1Alert );			
			return;
   	   }
   	  
   	 }
	
	StrPrintF( tmp, "%d", pagesN );
	TextToField( tmp, MainStatusField );
	}
	
  }

}

/***********************************************************************
 *
 * FUNCTION:    MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormDoCommand(UInt16 command)
{
	Boolean handled = false;
   FormPtr frmP;

	switch (command)
		{
		case MainOptionsAboutStarterApp:
			MenuEraseStatus(0);					// Clear the menu status from the display.
			frmP = FrmInitForm (AboutForm);
			FrmDoDialog (frmP);					// Display the About Box.
			FrmDeleteForm (frmP);
			handled = true;
			break;
		
		case MainOptionsExporttoPC:
			if(!FrmAlert( ExportAlert ) ) ProcExport();
			break;

		case ComSpeed1200:
			comspeed = 1200;
			break;	

		case ComSpeed2400:
			comspeed = 2400;
			break;	


		case ComSpeed4800:
			comspeed = 4800;
			break;	

		case ComSpeed9600:
			comspeed = 9600;
			break;	

		case ComSpeed19200:
			comspeed = 19200;
			break;	

		case ComSpeed33600:
			comspeed = 33600;
			break;	

		}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              "MainForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
   Boolean handled = false;
   FormPtr frmP;

	switch (eventP->eType) 
		{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			MainFormInit( frmP);
			FrmDrawForm ( frmP);
			handled = true;
			break;
		
		case ctlSelectEvent:
			{
			switch( eventP->data.ctlSelect.controlID )
				{
				case	MainImportButton:
					ImportProcedure();
					break;
				}
			}
			handled = true;
			break;

		default:
			break;
		
		}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and set the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventPtr eventP)
{
	UInt16 formId;
	FormPtr frmP;

	if (eventP->eType == frmLoadEvent)
		{
		// Load the form resource.
		formId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(formId);
		FrmSetActiveForm(frmP);

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
			{
			case MainForm:
				FrmSetEventHandler(frmP, MainFormHandleEvent);
				break;

			default:
//				ErrFatalDisplay("Invalid Form Load Event");
				break;

			}
		return true;
		}
	
	return false;
}


/***********************************************************************
 *
 * FUNCTION:    AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.  
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
				if (! AppHandleEvent(&event))
					FrmDispatchEvent(&event);

	} while (event.eType != appStopEvent);
}


/***********************************************************************
 *
 * FUNCTION:     AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err AppStart(void)
{
    StarterPreferenceType prefs;
    UInt16 prefsSize;

	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(StarterPreferenceType);
	if (PrefGetAppPreferences(appFileCreator, appPrefID, &prefs, &prefsSize, true) != 
		noPreferenceFound)
		{
		}
	
   return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppStop(void)
{
   StarterPreferenceType prefs;

	// Write the saved preferences / saved-state information.  This data 
	// will be backed up during a HotSync.
	PrefSetAppPreferences (appFileCreator, appPrefID, appPrefVersionNum, 
		&prefs, sizeof (prefs), true);
		
	// Close all the open forms.
	FrmCloseAllForms ();
}


/***********************************************************************
 *
 * FUNCTION:    StarterPalmMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static UInt32 StarterPalmMain(UInt16 cmd, MemPtr /*cmdPBP*/, UInt16 launchFlags)
{
	Err error;

	error = RomVersionCompatible (ourMinVersion, launchFlags);
	if (error) return (error);

	switch (cmd)
		{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error) 
				return error;
				
			FrmGotoForm(MainForm);
			AppEventLoop();
			AppStop();
			break;

		default:
			break;

		}
	
	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
UInt32 PilotMain( UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
    return StarterPalmMain(cmd, cmdPBP, launchFlags);
}