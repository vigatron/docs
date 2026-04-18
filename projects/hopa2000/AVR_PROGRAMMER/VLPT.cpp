#include <windows.h>
#include "VLpt.h"
#define TEST_WINDOWS_NT (!(GetVersion() & 0x80000000))

int GetParallelControllerKey(char *parKey)
{
HKEY hKey;
char myData[255];
LONG res;
DWORD mySize;
FILETIME ftLastWriteTime;

if (NULL==parKey) return(-1);

*parKey=0;

char myKey[255];
wsprintf(myKey,"HARDWARE\\DESCRIPTION\\System");

res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,myKey, 0, KEY_READ, &hKey);

if (res!=ERROR_SUCCESS) return(-1);

DWORD dwIndex1;
char myKey1[255];
        for (dwIndex1=0;dwIndex1<=10;dwIndex1++)
        {
        mySize=sizeof(myData);
        res = RegEnumKeyEx(hKey,dwIndex1,myData,&mySize,NULL,NULL,NULL,&ftLastWriteTime);
        if (res==ERROR_SUCCESS) // ERROR_SUCCESS 1
                {
                strcpy(myKey1,myKey);
                strcat(myKey1,"\\");
                strcat(myKey1,myData);

                HKEY hKey1;
                res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,myKey1, 0, KEY_READ, &hKey1);
                if (res!=ERROR_SUCCESS) return(-1);

                DWORD dwIndex2;
                char myKey2[255];
                for (dwIndex2=0;dwIndex2<=10;dwIndex2++)
                {
                mySize=sizeof(myData);
                res = RegEnumKeyEx(hKey1,dwIndex2,myData,&mySize,NULL,NULL,NULL,&ftLastWriteTime);
                if (res==ERROR_SUCCESS) // ERROR_SUCCESS 2
                        {
                                strcpy(myKey2,myKey1);
                                strcat(myKey2,"\\");
                                strcat(myKey2,myData);

                                HKEY hKey2;
                res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,myKey2, 0, KEY_READ, &hKey2);
                if (res!=ERROR_SUCCESS) return(-1);

                DWORD dwIndex3;

                for (dwIndex3=0;dwIndex3<=10;dwIndex3++)
                {
                mySize=sizeof(myData);
                res = RegEnumKeyEx(hKey2,dwIndex3,myData,&mySize,NULL,NULL,NULL,&ftLastWriteTime);

                if (res==ERROR_SUCCESS) // ERROR_SUCCESS 3
                {
                if(0==strcmp(myData,"ParallelController") )
                {

                strcpy(parKey,myKey2);
                strcat(parKey,"\\");
                strcat(parKey,myData);
                return(0);
                }
               } // ERROR_SUCCESS 3

        } // for (dwIndex3

        } // // ERROR_SUCCESS 2

        } // for (dwIndex2

        } // ERROR_SUCCESS 1

} // for (dwIndex1

return(-1);
} //GetParallelControllerKey

/**********************************************************************/
int GetAddressLptPortInTheRegistry(int myPort)
{
HKEY phkResult;
char myKey[255];
char myData[255];
LONG res;
DWORD mySize;
DWORD myType;

res=GetParallelControllerKey(myKey);
if (res < 0) return(-1);

wsprintf(myData,"%s\\%d",myKey,myPort-1);

res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,myData, 0, KEY_READ,&phkResult);
if (res != ERROR_SUCCESS) return(-1);

mySize=sizeof(myData);
myType=REG_BINARY;

res=RegQueryValueEx(    phkResult, // handle to key to query
                        "Configuration Data", // address of name of value to query
                        NULL, // reserved
                        &myType, // address of buffer for value type
                        (unsigned char *)myData, // address of data buffer
                        &mySize // address of data buffer size
                        );
if (res != ERROR_SUCCESS) return(-1);

//printf("config data port %d 0x14 = 0x%02X 0x15 = 0x%02X\n",myPort,myData[0x14],myData[0x15]);

return(myData[0x14] | myData[0x15]<<8 );
}

typedef BOOL (CALLBACK * PROCTYPE_Toolhelp32ReadProcessMemory)(DWORD,LPCVOID,LPVOID,DWORD,LPDWORD);

/**********************************************************************/
int GetAddressLptPortInTheMemory(int myPort)
{
HINSTANCE hDLL=NULL; // Handle to DLL
PROCTYPE_Toolhelp32ReadProcessMemory myProcPointer=NULL;

hDLL = LoadLibrary("kernel32");
if (hDLL==NULL) return(-1);

myProcPointer=(PROCTYPE_Toolhelp32ReadProcessMemory)GetProcAddress(hDLL,"Toolhelp32ReadProcessMemory");
if (myProcPointer==NULL) /*handle the error*/
{
FreeLibrary(hDLL);
return -1;
}

int portAddresses[]={0,0,0,0,0};
BOOL rtn=0;
DWORD cbLen=0;
//rtn = Toolhelp32ReadProcessMemory
rtn = myProcPointer(0,(LPCVOID *) 0x408,portAddresses,8,NULL);

FreeLibrary(hDLL);

if (rtn==0) return(-1);

if (portAddresses[myPort-1]<=0) return(-1);
if (portAddresses[myPort-1]>=0x1000) return(-1);

return(portAddresses[myPort-1]);
}

/*********************************************************************/
int GetAddressLptPort(int myPort)
{
 if(myPort<1) return(-1);
 if(myPort>3) return(-1);

 if(TEST_WINDOWS_NT) return(GetAddressLptPortInTheRegistry(myPort));

 return(GetAddressLptPortInTheMemory(myPort));
}


/*********************************************************************/
VLPTPort::VLPTPort( int port )
{
  Initialized=false;
  hDLL=NULL;

  portAddr=GetAddressLptPort(port);
  if(port==-1) return;

  hDLL = LoadLibrary("winio.dll");
  if (hDLL==NULL) return;

  InitializeWinIo=(PROCTYPE_1)GetProcAddress(hDLL,"InitializeWinIo");
  ShutdownWinIo=(PROCTYPE_2)GetProcAddress(hDLL,"ShutdownWinIo");
  GetPortVal=(PROCTYPE_3)GetProcAddress(hDLL,"GetPortVal");
  SetPortVal=(PROCTYPE_4)GetProcAddress(hDLL,"SetPortVal");

  if(InitializeWinIo)
  if(ShutdownWinIo)
  if(GetPortVal)
  if(SetPortVal)
  {
   if(InitializeWinIo()) Initialized=true;
  }

}

/*********************************************************************/
VLPTPort::~VLPTPort()
{

  if(Initialized) ShutdownWinIo();
  if(hDLL) FreeLibrary(hDLL);

}

/*********************************************************************/
bool VLPTPort::Write(int p,DWORD b)
{
 return SetPortVal(portAddr,b,1);
}

/*********************************************************************/
bool VLPTPort::Read(int p,PDWORD b)
{
 DWORD n;

 GetPortVal(portAddr+1,&n,1);
 *b=n;
 
 return true;
}
