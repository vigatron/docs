//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Programmer.res");
USEFORM("Programmer.cpp", Form1);
USEUNIT("VLPT.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
