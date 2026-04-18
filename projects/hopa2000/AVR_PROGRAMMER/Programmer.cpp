//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Programmer.h"
#include "vlpt.h"

#include "..\V\v.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TForm1 *Form1;

VLPTPort   lpt(1);

unsigned char           port=4;
unsigned long           cycles_per_1uS;
unsigned long           cycles_limit=60000000;

unsigned char           matrix[1024*16];
int                     lastByteAddr;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{


}

//---------------------------------------------------------------------------
void pause_uS(int uS)
{
  for(int a=0;a<uS;a++)
  for(unsigned long i=0;i<10;i++)
     {

     }

}

//---------------------------------------------------------------------------
unsigned char __fastcall TForm1::SerialWrite(unsigned char data)
{
  unsigned char result=0;

  for(int i=7;i>-1;i--)
  {
    //Set data
    bool  a=(data>>i)&1;
    SetMOSI(a);
    pause_uS(1);

    //Tick On
    CLK_Clock();
    pause_uS(1);

    //Get data
    result+=GetMISO()<<i;

    //Tick Off
    CLK_Clock();
    pause_uS(1);

  }

  return result;
}

//---------------------------------------------------------------------------
int __fastcall TForm1::ProgrammingEnable()
{
 DWORD oldtick=GetTickCount();
 while(GetTickCount()-oldtick<50) { }

 unsigned char t1=SerialWrite(0xAC);
 unsigned char t2=SerialWrite(0x53);
 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

 if(t3!=0x53) return 0;

 return 1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ChipErase()
{
 DWORD oldtick=GetTickCount();
 while(GetTickCount()-oldtick<50) { }

 SerialWrite(0xAC);
 SerialWrite(0x80);
 SerialWrite(0x0);
 SerialWrite(0x0);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 AnsiString str;

 str.printf("LPT Address is %Xh", lpt.portAddr);
 Panel1->Caption=str;

 if(lpt.Initialized==true)
 {
  Panel2->Caption="Initialized";
 }
 else
 {
  Panel2->Caption="Initialization failed !!!";
  MessageBox(NULL,"Initialization failed","Failed!",MB_OK);
  Close();
 }


  SetCLK(0);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 unsigned long b;

 if(lpt.Initialized)
 {
  lpt.Read( lpt.portAddr+1, &b );

  AnsiString str;
  str.printf("%Xh",b);
  Panel4->Caption=str;

  Label9->Color=((b>>0)&1)?clTeal:clRed;
  Label8->Color=((b>>1)&1)?clTeal:clRed;
  Label7->Color=((b>>2)&1)?clTeal:clRed;
  Label6->Color=((b>>3)&1)?clTeal:clRed;
  Label5->Color=((b>>4)&1)?clTeal:clRed;
  Label4->Color=((b>>5)&1)?clTeal:clRed;
  Label3->Color=((b>>6)&1)?clTeal:clRed;
  Label2->Color=((b>>7)&1)?clTeal:clRed;

 }

}

//--------------------------------------------------
void __fastcall TForm1::SetCLK(bool a)
{
  port=(port&0xFE)+a;
  lpt.Write(lpt.portAddr, port );

}

//--------------------------------------------------
void __fastcall TForm1::CLK_Clock()
{
  port=(port&0xFE)+((~port)&1);
  lpt.Write(lpt.portAddr, port );
}

//--------------------------------------------------
void __fastcall TForm1::SetMOSI(bool a)
{

  port=(port&0xFD)+a+a;
  lpt.Write(lpt.portAddr, port);

}

//--------------------------------------------------
void __fastcall TForm1::SetRESET(bool a)
{
  DWORD oldtick=GetTickCount();
  while(GetTickCount()-oldtick<50) { }


  port&=~4;
  if(a) port+=4;
  lpt.Write(lpt.portAddr, port);

  oldtick=GetTickCount();
  while(GetTickCount()-oldtick<50) { }

}

//--------------------------------------------------
bool __fastcall TForm1::GetMISO()
{
  unsigned long b;

  lpt.Read( lpt.portAddr+1, &b );
  return ~(b>>7)&1;
}

//---------------------------------------------------
void __fastcall TForm1::ButtonSetCLKLowClick(TObject *Sender)
{
    SetCLK(false);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonEnableProgrammingClick(TObject *Sender)
{
 unsigned char t1=SerialWrite(0xAC);
 unsigned char t2=SerialWrite(0x53);
 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

 AnsiString str;

 str.printf("%Xh,%Xh,%Xh,%Xh",t1,t2,t3,t4);
 Edit1->Text=str;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonReadLocksClick(TObject *Sender)
{
 unsigned char t1=SerialWrite(0x58);
 unsigned char t2=SerialWrite(0x0);
 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

 CheckBox1->Checked=(t4&2)>>1;
 CheckBox2->Checked=(t4&4)>>2;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonReadFuseClick(TObject *Sender)
{
 unsigned char t1=SerialWrite(0x50);
 unsigned char t2=SerialWrite(0x0);
 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

 CheckBox3->Checked=(t4&1);
 CheckBox4->Checked=(t4&2)>>1;
 CheckBox5->Checked=(t4&4)>>2;
 CheckBox6->Checked=(t4&32)>>5;
 CheckBox7->Checked=(t4&8)>>3;
 CheckBox8->Checked=(t4&16)>>4;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSignClick(TObject *Sender)
{
 AnsiString str;

 unsigned char t1=SerialWrite(0x30);
 unsigned char t2=SerialWrite(0x0);
 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

 str.printf("%Xh,", t4);

 t1=SerialWrite(0x30);
 t2=SerialWrite(0x0);
 t3=SerialWrite(0x1);
 t4=SerialWrite(0x0);

 str.cat_printf("%Xh,", t4);

 t1=SerialWrite(0x30);
 t2=SerialWrite(0x0);
 t3=SerialWrite(0x2);
 t4=SerialWrite(0x0);

 str.cat_printf("%Xh", t4);
 Edit2->Text=str;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonReadClick(TObject *Sender)
{

 char memory[2048*2];

 CGauge1->Progress=0;
 CGauge1->MaxValue=2048*2;

 for(int i=0;i<2048;i++)
 {
        unsigned char t1=SerialWrite(0x20);
        unsigned char t2=SerialWrite(i>>8);
        unsigned char t3=SerialWrite(i&0xFF);
        unsigned char t4=SerialWrite(0x0);
        memory[i]=t4;

        CGauge1->AddProgress(1);
 }

 for(int i=0;i<2048;i++)
 {
        unsigned char t1=SerialWrite(0x28);
        unsigned char t2=SerialWrite(i>>8);
        unsigned char t3=SerialWrite(i&0xFF);
        unsigned char t4=SerialWrite(0x0);
        memory[2048+i]=t4;

        CGauge1->AddProgress(1);
 }

 VFile file(Edit3->Text);
 file.Write(memory,4096,0);
 CGauge1->Progress=0;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonLockWriteClick(TObject *Sender)
{
 unsigned char t1=SerialWrite(0xAC);

 unsigned char r=0xF9+(CheckBox2->Checked<<2)+(CheckBox2->Checked<<1);
 unsigned char t2=SerialWrite(r);

 unsigned char t3=SerialWrite(0x0);
 unsigned char t4=SerialWrite(0x0);

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonChipEraseClick(TObject *Sender)
{
  unsigned char t1=SerialWrite(0xAC);
  unsigned char t2=SerialWrite(0x80);
  unsigned char t3=SerialWrite(0x0);
  unsigned char t4=SerialWrite(0x0);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSelectImageNameClick(TObject *Sender)
{
 if(OpenDialog1->Execute())
 {
  Edit4->Text=OpenDialog1->FileName;

  VFile file(Edit4->Text);

  if(!file.Read(matrix,4096,0))
  {
   MessageBox(NULL, "The file is invalid !", "Error!", MB_OK );
   return;
  }
 }
}

//---------------------------------------------------------------------------
void HEX_report(int Line,AnsiString why)
{
 AnsiString str;

 str.printf("At the line %d",Line+1);
 MessageBox(NULL,str.c_str(),why.c_str(),MB_OK);
}

//------------------------------------------------------------------------------
unsigned char decode(unsigned char sym)
{
 if(sym>'0') if(sym<('9'+1)) return sym-'0';
 if(sym>('A'-1)) if(sym<('F'+1)) return sym-'A'+10;
 return 0;
}

//------------------------------------------------------------------------------
unsigned char HEX_byte(AnsiString str,int n)
{
  unsigned char b1=str[2+n*2];
  unsigned char b2=str[3+n*2];

  int n1=decode(b1);
  int n2=decode(b2);

  return n1*16+n2;
}

//------------------------------------------------------------------------------
AnsiString HEX_CRC(AnsiString src,int len, unsigned char cc)
{

  unsigned char CRC=0;

  for(int i=0;i<len;i++)
  {
      CRC+=HEX_byte(src,i);
  }
  unsigned char realCRC=~CRC;

  if(cc!=1+realCRC) return "Wrong!";

  return "OK";
}

//------------------------------------------------------------------------------
int HEX_analize(TListBox *lbx, TStringGrid *grd, TMemo *rprt, unsigned char *matrix, int *lbAddr )
{

 rprt->Clear();
 rprt->Lines->Add("Processing ...");
 *lbAddr=0;

//---------------------------------------------------------------------------------------
 for(int i=0;i<lbx->Items->Count;i++)
 {
   // Check string
   AnsiString src=lbx->Items->Strings[i];
   if(src[1]!=':') { HEX_report(i,"Not started with ´:´"); return 0; }
   if((src.Length()-1)%2) { HEX_report(i,"Length is of record is wrong ..."); return 0; }

   // Decode ...
   int ll=HEX_byte(src,0);
   int aaaa=HEX_byte(src,1)*256+HEX_byte(src,2);
   int tt=HEX_byte(src,3);
   if(tt==1) continue;

   AnsiString tts;
   if(!tt) tts="data record"; else
   if(!tt) tts="end-of-file"; else
   if(!tt) tts="extended segment address record"; else
   if(!tt) tts="extended linear address record"; else tts="unknown";

   int cc=HEX_byte(src,4+ll);
   AnsiString ccOK=HEX_CRC(src,ll+4,cc);

   // reporting ...
   AnsiString rpt;
   rpt.printf("N<%d> %d #%d %s [0x%Xh]-CRC-%s",i,ll,aaaa,tts,cc,ccOK);
   rprt->Lines->Add(rpt);

   // Fill Table
   for(int j=0;j<ll;j++) matrix[aaaa+j]=HEX_byte(src,4+j);
   if(*lbAddr<aaaa+ll-1) *lbAddr=aaaa+ll-1;

 }

 grd->ColWidths[0]=30;
 grd->RowCount=((*lbAddr+1)/16)+2;

 // Grid fill
 for(int i=0;i<16;i++)
 {
  AnsiString str;
  str.printf("0x0%hX",i);
  grd->Cells[i+1][0]=str;
 }

 // Grid fill
 for(int i=0;i<(*lbAddr+1)/16;i++)
 {
  AnsiString str;
  str.printf("0x%hX",i*16);
  grd->Cells[0][i+1]=str;
 }

 for(int i=0;i<*lbAddr+1;i++)
 {
   int ci=i%16;
   int cj=i/16;

   AnsiString str;
   str.printf("0x%hX",matrix[i]);
   grd->Cells[ci+1][cj+1]=str;
 }

 return 1;
}

//---------------------------------------------------------------------------
bool __fastcall TForm1::DecodeHEXfile( AnsiString file )
{
 //--------------------------------------------------------------------------
 ListBoxHEX->Items->LoadFromFile(file);
 LabelHEX->Caption=file;
 if(ListBoxHEX->Items->Count<1) return false;

 // Analize
 return HEX_analize(ListBoxHEX,StringGrid1,MemoHEXreport,matrix,&lastByteAddr);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSelectHEXClick(TObject *Sender)
{
 OpenDialog1->Filter="Intel Standard HEX file|*.hex";
 if(OpenDialog1->Execute()==false) return;

 DecodeHEXfile(OpenDialog1->FileName);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
 AnsiString str;
 int i=((StringGrid1->Row-1)*16)+StringGrid1->Col-1;
 str.printf("Hex: 0x%Xh  Dec: %d",i,i);
 LabelAddr->Caption=str;

 str.printf("Hex: 0x%Xh  Dec: %d",lastByteAddr,lastByteAddr);
 LabelBytes->Caption=str;
}

//---------------------------------------------------------------------------
int __fastcall TForm1::WriteFlash(TCGauge *g)
{

 DWORD oldtick=GetTickCount();
 while(GetTickCount()-oldtick<250) { }

 g->Progress=0;
 g->AddProgress(1);
 g->MaxValue=lastByteAddr;
 g->ForeColor=clBlue;

 for(int i=lastByteAddr;i<lastByteAddr+6;i++) matrix[i]=0;

 for(int i=0;i<lastByteAddr+6;i++)
 {
   unsigned char wr[2]={0x40,0x48};
   unsigned char rd[2]={0x20,0x28};

   unsigned char t1,t2,t3,t4;

   // Write
   t1=wr[i&1];
   t1=SerialWrite(t1);
   t2=i/512;
   t2=SerialWrite(t2);
   t3=(i%512)/2;
   t3=SerialWrite(t3);
   t4=matrix[i];
   t4=SerialWrite(t4);
   pause_uS(150000);

   // Verify High
   //t1=rd[i&1];
   //t1=SerialWrite(t1);
   //t2=i/512;
   //t2=SerialWrite(t2);
   //t3=(i%512)/2;
   //t3=SerialWrite(t3);
   //t4=0;
   //t4=SerialWrite(t4);

   // Alarm if something wrong ...
   //if(t4!=matrix[i])
   //{
   //  g->ForeColor=clRed;
   //  g->AddProgress(1);
   // return 0;
   //}

   g->AddProgress(1);
 }

 g->ForeColor=clGreen;
 g->AddProgress(1);

 return 1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BtnWriteClick(TObject *Sender)
{
 WriteFlash(CGauge1);
}

//---------------------------------------------------------------------------
int __fastcall TForm1::AutoWrite()
{

 TMemo *status=Memo1;

 status->Clear();

 TDateTime  dt;
 dt=dt.CurrentDateTime();

 status->Lines->Add("Task started ... (C) AVR_Programmer v.1.0.0 by Viktor Glebov");
 status->Lines->Add("Date: "+dt.DateString());
 status->Lines->Add("Time: "+dt.TimeString());
 status->Lines->Add("File: "+FileListBox1->FileName );
 status->Lines->Add("Converting from HEX to binary ..." );

 if(!DecodeHEXfile( FileListBox1->FileName ))
 {
  status->Lines->Add("Converting from HEX to binary FAILED !" );
  return 0;
 }

 //--------------------------------------------------------------------------
 AnsiString t;
 t.printf("Converted %d [0x%Xh] bytes.", lastByteAddr, lastByteAddr );
 status->Lines->Add(t);

 // Programming enable
 status->Lines->Add("Prepare processor ..." );
 if(!ProgrammingEnable())
 {
   status->Lines->Add("Device is not connected ...");
   return 0;
 }

 // Chip erase ...
 status->Lines->Add("Erase processor ..." );
 ChipErase();

 // Second Write Enable
 status->Lines->Add("Try to verify processor ..." );
 if(!ProgrammingEnable())
 {
   status->Lines->Add("Verify failed! ");
   return 0;
 }

 // Writing flash ...
 status->Lines->Add("Starting programming ...");
 if(!WriteFlash(CGaugeAuto))
 {
  status->Lines->Add("Error during programming !");
  return 0;
 }

 // Set Fuse bits ...
 status->Lines->Add("Finishing programming ... ");


 return 1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonProgramClick(TObject *Sender)
{
 SetRESET(false);
 AutoWrite();
 //SetRESET(true);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonCatchClick(TObject *Sender)
{
  int i=0;

  do
  {

  }
  while(!GetMISO());


  do
  {
   i++;
  }
  while(GetMISO());

  AnsiString t;

  t.printf("cycles:%d",i);
  Label31->Caption=t;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonRSTGNDClick(TObject *Sender)
{
  SetRESET(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonRST5Click(TObject *Sender)
{
 SetRESET(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonWriteFuseClick(TObject *Sender)
{

 unsigned char t=0xA0;

 if(CheckBox3->Checked) t+=1;
 if(CheckBox4->Checked) t+=2;
 if(CheckBox5->Checked) t+=4;
 if(CheckBox7->Checked) t+=8;
 if(CheckBox8->Checked) t+=16;


 SerialWrite(0xAC);
 SerialWrite(t);
 SerialWrite(0x0);
 SerialWrite(0x0);


}
//---------------------------------------------------------------------------

