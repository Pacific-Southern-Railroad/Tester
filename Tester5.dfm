object Tester: TTester
  Left = 1511
  Top = 121
  Caption = 'Tester'
  ClientHeight = 369
  ClientWidth = 242
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 96
    Top = 56
    Width = 60
    Height = 13
    Caption = 'Hex Address'
  end
  object Label2: TLabel
    Left = 96
    Top = 112
    Width = 61
    Height = 13
    Caption = 'Output Bytes'
  end
  object Label3: TLabel
    Left = 96
    Top = 176
    Width = 61
    Height = 13
    Caption = 'Return Bytes'
  end
  object Label4: TLabel
    Left = 24
    Top = 283
    Width = 77
    Height = 13
    Caption = 'Return Changes'
  end
  object Label5: TLabel
    Left = 112
    Top = 352
    Width = 22
    Height = 13
    Caption = 'Stop'
  end
  object Label6: TLabel
    Left = 144
    Top = 283
    Width = 70
    Height = 13
    Caption = 'Receive Delay'
  end
  object HexAddress: TEdit
    Left = 112
    Top = 24
    Width = 25
    Height = 24
    CharCase = ecUpperCase
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Microsoft Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = HexAddressClick
    OnKeyPress = HexAddressKeyPress
  end
  object OutputBytes: TEdit
    Left = 16
    Top = 80
    Width = 217
    Height = 21
    CharCase = ecUpperCase
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = OutputBytesClick
    OnKeyPress = OutputBytesKeyPress
  end
  object ReturnBytes: TEdit
    Left = 16
    Top = 144
    Width = 217
    Height = 21
    CharCase = ecUpperCase
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object Send: TButton
    Left = 16
    Top = 216
    Width = 49
    Height = 25
    Caption = 'Send'
    TabOrder = 3
    OnClick = SendClick
  end
  object Repeat: TButton
    Left = 96
    Top = 216
    Width = 57
    Height = 25
    Caption = 'Repeat'
    TabOrder = 4
    OnClick = RepeatClick
  end
  object Stop: TButton
    Left = 176
    Top = 216
    Width = 51
    Height = 25
    Caption = 'Stop'
    TabOrder = 5
    OnClick = StopClick
  end
  object Changes: TEdit
    Left = 40
    Top = 256
    Width = 41
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object Aborts: TEdit
    Left = 104
    Top = 320
    Width = 41
    Height = 21
    TabOrder = 7
    Text = '0'
  end
  object ReceiveDelay: TEdit
    Left = 168
    Top = 256
    Width = 34
    Height = 21
    TabOrder = 8
    Text = '0'
  end
  object Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerTimer
    Left = 184
    Top = 32
  end
end
