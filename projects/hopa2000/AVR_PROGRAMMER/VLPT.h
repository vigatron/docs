typedef BOOL (CALLBACK * PROCTYPE_1)();
typedef void (CALLBACK * PROCTYPE_2)();
typedef bool (CALLBACK * PROCTYPE_3)(WORD,PDWORD,BYTE);
typedef bool (CALLBACK * PROCTYPE_4)(WORD,DWORD,BYTE);


class VLPTPort
{


 public:

  VLPTPort( int port );
  ~VLPTPort();
  bool  Initialized;

  bool Write(int p, DWORD b);
  bool Read( int p, PDWORD b);

  PROCTYPE_1      InitializeWinIo;
  PROCTYPE_2      ShutdownWinIo;
  PROCTYPE_3      GetPortVal;
  PROCTYPE_4      SetPortVal;
  HINSTANCE       hDLL;
  int             portAddr;

};