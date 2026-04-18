//---------------------------------------------------------------------------

#ifndef AVR_ProgrammerH
#define AVR_ProgrammerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "CGAUGES.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl2;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet6;
        TTabSheet *TabSheet7;
        TTimer *Timer1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TLabel *Label18;
        TLabel *Label19;
        TButton *ButtonEnableProgramming;
        TEdit *Edit1;
        TTabSheet *TabSheet3;
        TButton *ButtonReadLocks;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TButton *ButtonReadFuse;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TButton *ButtonSign;
        TEdit *Edit2;
        TButton *ButtonWriteFuse;
        TTabSheet *TabSheet4;
        TGroupBox *GroupBox1;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label10;
        TLabel *Label11;
        TPanel *Panel4;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TButton *ButtonLockWrite;
        TButton *ButtonChipErase;
        TGroupBox *GroupBox2;
        TLabel *Label21;
        TEdit *Edit3;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox3;
        TLabel *Label22;
        TEdit *Edit4;
        TButton *ButtonSelectImageName;
        TOpenDialog *OpenDialog1;
        TTabSheet *TabSheet8;
        TStaticText *StaticText1;
        TBevel *Bevel9;
        TBevel *Bevel10;
        TBevel *Bevel12;
        TBevel *Bevel13;
        TGroupBox *GroupBox8;
        TLabel *Label20;
        TCGauge *CGauge1;
        TPageControl *PageControl3;
        TTabSheet *TabSheet9;
        TTabSheet *TabSheet10;
        TLabel *LabelHEX;
        TListBox *ListBoxHEX;
        TButton *ButtonSelectHEX;
        TStringGrid *StringGrid1;
        TMemo *MemoHEXreport;
        TLabel *Label28;
        TLabel *LabelAddr;
        TLabel *Label29;
        TLabel *LabelBytes;
        TBitBtn *BtnWrite;
        TDriveComboBox *DriveComboBox1;
        TDirectoryListBox *DirectoryListBox1;
        TFileListBox *FileListBox1;
        TLabel *Label30;
        TMemo *Memo1;
        TButton *ButtonProgram;
        TCGauge *CGaugeAuto;
        TGroupBox *GroupBox4;
        TButton *ButtonCatch;
        TLabel *Label31;
        TButton *ButtonRSTGND;
        TButton *ButtonRST5;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ButtonSetCLKLowClick(TObject *Sender);
        void __fastcall ButtonEnableProgrammingClick(TObject *Sender);
        void __fastcall ButtonReadLocksClick(TObject *Sender);
        void __fastcall ButtonReadFuseClick(TObject *Sender);
        void __fastcall ButtonSignClick(TObject *Sender);
        void __fastcall ButtonReadClick(TObject *Sender);
        void __fastcall ButtonLockWriteClick(TObject *Sender);
        void __fastcall ButtonChipEraseClick(TObject *Sender);
        void __fastcall ButtonSelectImageNameClick(TObject *Sender);
        void __fastcall ButtonSelectHEXClick(TObject *Sender);
        void __fastcall StringGrid1Click(TObject *Sender);
        void __fastcall BtnWriteClick(TObject *Sender);
        void __fastcall ButtonProgramClick(TObject *Sender);
        void __fastcall ButtonCatchClick(TObject *Sender);
        void __fastcall ButtonRSTGNDClick(TObject *Sender);
        void __fastcall ButtonRST5Click(TObject *Sender);
        void __fastcall ButtonWriteFuseClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void            __fastcall SetCLK(bool high);
        void            __fastcall SetMOSI(bool high);
        bool            __fastcall GetMISO();
        unsigned char   __fastcall SerialWrite(unsigned char data);
        void            __fastcall CLK_Clock();
        bool            __fastcall DecodeHEXfile( AnsiString file );
        int             __fastcall WriteFlash(TCGauge *g);
        int             __fastcall AutoWrite();

        int             __fastcall ProgrammingEnable();
        void            __fastcall ChipErase();
        void            __fastcall SetRESET(bool a);        
                
};

//---------------------------------------------------------------------------

extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
