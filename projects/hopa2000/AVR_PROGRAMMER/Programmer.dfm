object Form1: TForm1
  Left = 194
  Top = 107
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Programming AT90S4433 via LPT'
  ClientHeight = 464
  ClientWidth = 573
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindow
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl2: TPageControl
    Left = 8
    Top = 8
    Width = 553
    Height = 449
    ActivePage = TabSheet6
    Style = tsButtons
    TabOrder = 0
    object TabSheet6: TTabSheet
      Caption = 'Automatic Programming'
      ImageIndex = 1
      object Label30: TLabel
        Left = 0
        Top = 0
        Width = 545
        Height = 17
        Alignment = taCenter
        AutoSize = False
        Caption = 'C:\Programme\Borland\CBuilder5\Projects\AVR_PROGRAMMER'
        Color = clBackground
        ParentColor = False
        Layout = tlCenter
      end
      object CGaugeAuto: TCGauge
        Left = 0
        Top = 392
        Width = 465
        Height = 25
        ForeColor = clWhite
        BackColor = clScrollBar
      end
      object DriveComboBox1: TDriveComboBox
        Left = 0
        Top = 24
        Width = 273
        Height = 19
        Color = clMenu
        DirList = DirectoryListBox1
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object DirectoryListBox1: TDirectoryListBox
        Left = 0
        Top = 48
        Width = 273
        Height = 209
        Color = clMenu
        DirLabel = Label30
        FileList = FileListBox1
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemHeight = 16
        ParentFont = False
        TabOrder = 1
      end
      object FileListBox1: TFileListBox
        Left = 280
        Top = 24
        Width = 265
        Height = 233
        Color = clMenu
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemHeight = 13
        Mask = '*.hex'
        ParentFont = False
        TabOrder = 2
      end
      object Memo1: TMemo
        Left = 0
        Top = 264
        Width = 465
        Height = 121
        Color = clMenu
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
      end
      object ButtonProgram: TButton
        Left = 472
        Top = 264
        Width = 73
        Height = 33
        Caption = 'Program'
        TabOrder = 4
        OnClick = ButtonProgramClick
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Manual Programming'
      object PageControl1: TPageControl
        Left = 32
        Top = 40
        Width = 409
        Height = 265
        ActivePage = TabSheet4
        MultiLine = True
        TabOrder = 0
        TabPosition = tpBottom
        object TabSheet1: TTabSheet
          Caption = 'Step 1'
          object Bevel9: TBevel
            Left = 8
            Top = 32
            Width = 385
            Height = 9
          end
          object Bevel10: TBevel
            Left = 8
            Top = 96
            Width = 385
            Height = 9
          end
          object StaticText1: TStaticText
            Left = 8
            Top = 8
            Width = 385
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Caption = 'Follow Step-by-Step:'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object ButtonRSTGND: TButton
            Left = 8
            Top = 56
            Width = 161
            Height = 25
            Caption = 'Push RESET to GND'
            TabOrder = 1
            OnClick = ButtonRSTGNDClick
          end
          object ButtonRST5: TButton
            Left = 232
            Top = 56
            Width = 161
            Height = 25
            Caption = 'Set RESET  +5V'
            TabOrder = 2
            OnClick = ButtonRST5Click
          end
        end
        object TabSheet2: TTabSheet
          Caption = 'Step 2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBackground
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ImageIndex = 1
          ParentFont = False
          object Label18: TLabel
            Left = 8
            Top = 184
            Width = 257
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Caption = '=> ( 1010 1100, 0101 0011,  xxxx xxxx, xxxx xxxx )'
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label19: TLabel
            Left = 272
            Top = 184
            Width = 121
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Caption = 'Answer: ( 0x53 - OK )'
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Bevel12: TBevel
            Left = 8
            Top = 56
            Width = 385
            Height = 9
          end
          object Bevel13: TBevel
            Left = 8
            Top = 168
            Width = 385
            Height = 9
          end
          object ButtonEnableProgramming: TButton
            Left = 8
            Top = 200
            Width = 257
            Height = 25
            Caption = 'Enable Programming'
            TabOrder = 0
            OnClick = ButtonEnableProgrammingClick
          end
          object Edit1: TEdit
            Left = 272
            Top = 200
            Width = 121
            Height = 21
            TabOrder = 1
          end
        end
        object TabSheet3: TTabSheet
          Caption = 'Step 3'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBackground
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ImageIndex = 2
          ParentFont = False
          object Bevel1: TBevel
            Left = 8
            Top = 46
            Width = 385
            Height = 4
          end
          object Bevel2: TBevel
            Left = 8
            Top = 110
            Width = 385
            Height = 4
          end
          object ButtonReadLocks: TButton
            Left = 8
            Top = 8
            Width = 97
            Height = 33
            Caption = 'Read Lock bits'
            TabOrder = 0
            OnClick = ButtonReadLocksClick
          end
          object CheckBox1: TCheckBox
            Left = 112
            Top = 8
            Width = 81
            Height = 17
            Caption = 'Lock Bit 1'
            TabOrder = 1
          end
          object CheckBox2: TCheckBox
            Left = 112
            Top = 24
            Width = 81
            Height = 17
            Caption = 'Lock Bit 2'
            TabOrder = 2
          end
          object ButtonReadFuse: TButton
            Left = 8
            Top = 56
            Width = 97
            Height = 25
            Caption = 'Read Fuse bits'
            TabOrder = 3
            OnClick = ButtonReadFuseClick
          end
          object CheckBox3: TCheckBox
            Left = 112
            Top = 56
            Width = 97
            Height = 17
            Caption = 'CKSEL0 Fuse'
            TabOrder = 4
          end
          object CheckBox4: TCheckBox
            Left = 112
            Top = 72
            Width = 97
            Height = 17
            Caption = 'CKSEL1 Fuse'
            TabOrder = 5
          end
          object CheckBox5: TCheckBox
            Left = 112
            Top = 88
            Width = 97
            Height = 17
            Caption = 'CKSEL2 Fuse'
            TabOrder = 6
          end
          object CheckBox6: TCheckBox
            Left = 208
            Top = 56
            Width = 113
            Height = 17
            Caption = 'SPIEN Fuse'
            TabOrder = 7
          end
          object CheckBox7: TCheckBox
            Left = 208
            Top = 72
            Width = 113
            Height = 17
            Caption = 'BODEN Fuse'
            TabOrder = 8
          end
          object CheckBox8: TCheckBox
            Left = 208
            Top = 88
            Width = 113
            Height = 17
            Caption = 'BODLEVEL Fuse'
            TabOrder = 9
          end
          object ButtonSign: TButton
            Left = 8
            Top = 128
            Width = 97
            Height = 25
            Caption = 'Signature'
            TabOrder = 10
            OnClick = ButtonSignClick
          end
          object Edit2: TEdit
            Left = 8
            Top = 160
            Width = 97
            Height = 21
            TabOrder = 11
          end
          object ButtonWriteFuse: TButton
            Left = 8
            Top = 80
            Width = 97
            Height = 25
            Caption = 'Write Fuse bits'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 12
            OnClick = ButtonWriteFuseClick
          end
          object ButtonLockWrite: TButton
            Left = 192
            Top = 8
            Width = 97
            Height = 33
            Caption = 'Write Lock bits'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 13
            OnClick = ButtonLockWriteClick
          end
          object ButtonChipErase: TButton
            Left = 288
            Top = 8
            Width = 105
            Height = 33
            Caption = 'Chip Erase'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 14
            OnClick = ButtonChipEraseClick
          end
          object GroupBox8: TGroupBox
            Left = 112
            Top = 120
            Width = 281
            Height = 105
            Caption = 'Signature Description'
            TabOrder = 15
          end
        end
        object TabSheet4: TTabSheet
          Caption = 'Step 4'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBackground
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ImageIndex = 3
          ParentFont = False
          object CGauge1: TCGauge
            Left = 72
            Top = 184
            Width = 321
            Height = 41
            MaxValue = 4095
          end
          object GroupBox2: TGroupBox
            Left = 8
            Top = 8
            Width = 385
            Height = 65
            Caption = 'Reading Flash Memory'
            TabOrder = 0
            object Label21: TLabel
              Left = 8
              Top = 16
              Width = 305
              Height = 17
              Alignment = taCenter
              AutoSize = False
              Caption = 'Save image as:'
              Color = clBackground
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindow
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentColor = False
              ParentFont = False
              Layout = tlCenter
            end
            object Edit3: TEdit
              Left = 8
              Top = 32
              Width = 305
              Height = 25
              AutoSize = False
              TabOrder = 0
              Text = 'image.bin'
            end
            object BitBtn2: TBitBtn
              Left = 320
              Top = 16
              Width = 57
              Height = 41
              Caption = 'Read'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clGreen
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 1
              OnClick = ButtonReadClick
            end
          end
          object GroupBox3: TGroupBox
            Left = 8
            Top = 80
            Width = 385
            Height = 65
            Caption = 'Writing Flash Memory'
            TabOrder = 1
            object Label22: TLabel
              Left = 8
              Top = 16
              Width = 305
              Height = 17
              Alignment = taCenter
              AutoSize = False
              Caption = 'Programming image from:'
              Color = clBackground
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindow
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentColor = False
              ParentFont = False
              Layout = tlCenter
            end
            object Edit4: TEdit
              Left = 8
              Top = 34
              Width = 305
              Height = 22
              AutoSize = False
              TabOrder = 0
              Text = 'image.bin'
            end
            object ButtonSelectImageName: TButton
              Left = 320
              Top = 16
              Width = 57
              Height = 41
              Caption = '...'
              TabOrder = 1
              OnClick = ButtonSelectImageNameClick
            end
          end
          object BtnWrite: TBitBtn
            Left = 8
            Top = 184
            Width = 57
            Height = 41
            Caption = 'Write'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
            OnClick = BtnWriteClick
          end
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Hardware Info'
      ImageIndex = 2
      object GroupBox1: TGroupBox
        Left = 0
        Top = 8
        Width = 409
        Height = 121
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 64
          Width = 201
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Runtime Input'
          Color = clBackground
          DragKind = dkDock
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label12: TLabel
          Left = 216
          Top = 16
          Width = 185
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Initializatation'
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label13: TLabel
          Left = 8
          Top = 16
          Width = 201
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Port #'
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label14: TLabel
          Left = 304
          Top = 64
          Width = 97
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Legend'
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label10: TLabel
          Left = 304
          Top = 88
          Width = 49
          Height = 25
          Alignment = taCenter
          AutoSize = False
          Caption = '+5 V'
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label11: TLabel
          Left = 352
          Top = 88
          Width = 49
          Height = 25
          Alignment = taCenter
          AutoSize = False
          Caption = 'GND'
          Color = 26879
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Label20: TLabel
          Left = 216
          Top = 64
          Width = 81
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Value (HEX)'
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Panel1: TPanel
          Left = 8
          Top = 40
          Width = 201
          Height = 17
          BevelInner = bvLowered
          Caption = 'Panel1'
          TabOrder = 0
        end
        object Panel2: TPanel
          Left = 216
          Top = 40
          Width = 185
          Height = 17
          BevelInner = bvLowered
          Caption = 'Panel2'
          TabOrder = 1
        end
        object Panel3: TPanel
          Left = 8
          Top = 88
          Width = 201
          Height = 25
          BevelInner = bvLowered
          TabOrder = 2
          object Label2: TLabel
            Left = 8
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label3: TLabel
            Left = 32
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label4: TLabel
            Left = 56
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label5: TLabel
            Left = 80
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label6: TLabel
            Left = 104
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label7: TLabel
            Left = 128
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label8: TLabel
            Left = 152
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object Label9: TLabel
            Left = 176
            Top = 8
            Width = 17
            Height = 9
            Alignment = taCenter
            AutoSize = False
            Color = clTeal
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
        end
        object Panel4: TPanel
          Left = 216
          Top = 88
          Width = 81
          Height = 25
          BevelInner = bvLowered
          Caption = 'Panel4'
          TabOrder = 3
        end
      end
      object GroupBox4: TGroupBox
        Left = 0
        Top = 136
        Width = 409
        Height = 113
        Caption = 'Catch UART byte'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 1
        object Label31: TLabel
          Left = 144
          Top = 24
          Width = 73
          Height = 25
          Alignment = taCenter
          AutoSize = False
          Caption = 'Label31'
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clAqua
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object ButtonCatch: TButton
          Left = 8
          Top = 24
          Width = 129
          Height = 25
          Caption = 'Catch'
          TabOrder = 0
          OnClick = ButtonCatchClick
        end
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'Converter'
      ImageIndex = 3
      object PageControl3: TPageControl
        Left = 8
        Top = 8
        Width = 529
        Height = 409
        ActivePage = TabSheet10
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        TabPosition = tpBottom
        object TabSheet9: TTabSheet
          Caption = 'HEX Convertion'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          object LabelHEX: TLabel
            Left = 8
            Top = 8
            Width = 313
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -8
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Layout = tlCenter
          end
          object ListBoxHEX: TListBox
            Left = 8
            Top = 24
            Width = 313
            Height = 177
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 0
          end
          object ButtonSelectHEX: TButton
            Left = 328
            Top = 344
            Width = 185
            Height = 25
            Caption = 'Select HEX file'
            TabOrder = 1
            OnClick = ButtonSelectHEXClick
          end
          object MemoHEXreport: TMemo
            Left = 8
            Top = 208
            Width = 313
            Height = 161
            TabOrder = 2
          end
        end
        object TabSheet10: TTabSheet
          Caption = 'Dump'
          ImageIndex = 1
          object Label28: TLabel
            Left = 0
            Top = 344
            Width = 49
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Caption = 'Address:'
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnHighlight
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
          end
          object LabelAddr: TLabel
            Left = 48
            Top = 344
            Width = 121
            Height = 17
            AutoSize = False
            Color = clHighlight
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
          end
          object Label29: TLabel
            Left = 0
            Top = 360
            Width = 49
            Height = 17
            Alignment = taCenter
            AutoSize = False
            Caption = 'Bytes:'
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnHighlight
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
          end
          object LabelBytes: TLabel
            Left = 48
            Top = 360
            Width = 121
            Height = 17
            AutoSize = False
            Color = clHighlight
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentColor = False
            ParentFont = False
          end
          object StringGrid1: TStringGrid
            Left = 0
            Top = 0
            Width = 521
            Height = 337
            ColCount = 17
            DefaultColWidth = 29
            DefaultRowHeight = 16
            RowCount = 17
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing]
            TabOrder = 0
            OnClick = StringGrid1Click
          end
        end
      end
    end
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 504
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.bin'
    Filter = 
      'Binary data file ( *.bin )|*.bin|Intel Standard file ( *.hex )|*' +
      '.hex'
    Title = 'Select file to transfer to AT90S4433'
    Left = 536
  end
end
