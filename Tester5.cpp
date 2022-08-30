//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Tester5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTester *Tester;
//---------------------------------------------------------------------------
__fastcall TTester::TTester(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTester::FormCreate(TObject *Sender)
{
//Variables
	Anum=0;
	Dnum = 0;
	Count=0;

//Open comm port COM1 for USB/485C converter
	comHandle = CreateFile(L"COM1",
   	GENERIC_READ|GENERIC_WRITE, 0, 0,
      	OPEN_EXISTING,
         	FILE_ATTRIBUTE_NORMAL, 0);
//Get current settings of COM3
	GetCommState(comHandle, &dcb);
//Set baud rate etc.
	dcb.BaudRate = 19200;
   dcb.ByteSize = 8;
   dcb.Parity = NOPARITY;
   dcb.StopBits = ONESTOPBIT;
//Apply settings
 	SetCommState(comHandle, &dcb);
//Set timeouts, 1ms per byte plus 2ms gap
	timeouts.ReadIntervalTimeout = MAXDWORD;
   timeouts.ReadTotalTimeoutMultiplier = 0;
   timeouts.ReadTotalTimeoutConstant = 0;
   timeouts.WriteTotalTimeoutMultiplier = 0;
   timeouts.WriteTotalTimeoutConstant = 0;
   SetCommTimeouts(comHandle, &timeouts);

   RChanges = 0;   
}
//---------------------------------------------------------------------------
void __fastcall TTester::FormDestroy(TObject *Sender)
{
	EscapeCommFunction(comHandle, CLRDTR);
   CloseHandle(comHandle);   
}
//---------------------------------------------------------------------------
void __fastcall TTester::HexAddressKeyPress(TObject *Sender,
      char &Key)
{
   if(Anum < 2 && ((Key >= '0' && Key <= '9') ||
   		(Key >= 'a' && Key <= 'f')))
   {
      Anum++;
      char tmp;
   	if (Key >= 'a' && Key <= 'f')
      	tmp = (Key + 9) & 0xf;
      else
      	tmp = Key & 0xf;
      if (Anum==1)
      	Address = tmp;
      if (Anum==2)
			Address = (Address<<4) | tmp;
	}
   else
	{
   	Key = 0;
   }   
}
//---------------------------------------------------------------------------
void __fastcall TTester::OutputBytesKeyPress(TObject *Sender,
      char &Key)
{
   if ((Key >= '0' && Key <= '9') ||
   			(Key >= 'a' && Key <= 'f'))
   {
	  	Dnum++;
	   if(Dnum>1 && Dnum%2 && Dnum<20) 				//insert spaces
	   {
			OutputBytes->Text =
	      	OutputBytes->Text + ' ';
		   OutputBytes->SelStart =
	         OutputBytes->Text.Length() + 1;
		}
	   int tmp;
	   static char byte;
	  	if (Key >= 'a' && Key <= 'f')
	     	tmp = (Key + 9) & 0xf;
	   else
	     	tmp = Key & 0xf;
	   if(Dnum%2)
	     	byte = tmp;
	   else
	  	{
	     	byte = (byte<<4) | tmp;
			Data[Count] = byte;
	      byte = 0;
	      Count++;
	   }
	}
   else
   {
     	Key = 0;
   }   
}
//---------------------------------------------------------------------------
void __fastcall TTester::SendClick(TObject *Sender)
{
	SendPacket();
}
//---------------------------------------------------------------------------
void TTester::SendPacket(void)
{
   char Buffer[20];
   for(int i=0; i<20; i++)
   	Buffer[i] = 0;
   Buffer[0] = Address;
   for(int i=0; i<Count; i++)
   	Buffer[i+1] = Data[i];
   DWORD numWrite, numRead;

   //Write bytes

   PurgeComm(comHandle, PURGE_RXCLEAR);
   WriteFile(comHandle, Buffer, Count+1, &numWrite, 0);
   bool response = false;
   for(int i=0; i<20; i++)
   	Buffer[i] = 0;

   //Wait for response and read bytes

   for(int i=0; i<5; i++)
   {
    ReceiveDelay->Text = i;
   	ReadFile(comHandle, Buffer, Count, &numRead, 0);
	if(numRead == Count)
      {
         response = true;
      	break;
      }
      else
		Sleep(1);
   }
   if(response == true)
   {
   	char inChar[50];
      for (int i=0; i<50; i++)
      	inChar[i] = 0;
      char tmp;
      int p = 0;
      for(int i=0; i<numRead; i++)
      {
      	tmp = (Buffer[i]>>4) & 0x0f;
         if(tmp>=0xa && tmp<=0xf)
          	tmp = (tmp - 9) | 0x60;
         else
         	tmp = tmp | 0x30;
         inChar[p] = tmp;
         p++;
         tmp = Buffer[i] & 0x0f;
         if(tmp>=0xa && tmp<=0xf)
         	tmp = (tmp - 9) | 0x60;
         else
         	tmp = tmp | 0x30;
         inChar[p] = tmp;
         p++;
         inChar[p] = ' ';
         p++;
      }
      ReturnBytes->Text = inChar;
      This = inChar;
      if(Timer->Enabled)
      {
      	if(This != Last)
           	RChanges++;
      	Last = This;
         Changes->Text = RChanges;
      }
   }
   else
   {
   	ReturnBytes->Text = "No Response";
      NAborts++;
      Aborts->Text = NAborts;
   }
   return;
}
//---------------------------------------------------------------------------

void __fastcall TTester::RepeatClick(TObject *Sender)
{
   HexAddress->Enabled = false;
   OutputBytes->Enabled = false;
   Send->Enabled = false;
	Repeat->Enabled = false;
   Stop->Enabled = true;
	Timer->Enabled = true;   
}
//---------------------------------------------------------------------------

void __fastcall TTester::StopClick(TObject *Sender)
{
   Timer->Enabled = false;
	Repeat->Enabled = true;
   Send->Enabled = true;
   Stop->Enabled = false;
   OutputBytes->Enabled = true;
   HexAddress->Enabled = true;
   RChanges = 0;
   Changes->Text = "0";
   NAborts = 0;
   Aborts->Text = "0";
}
//---------------------------------------------------------------------------

void __fastcall TTester::TimerTimer(TObject *Sender)
{
	SendPacket();   
}
//---------------------------------------------------------------------------

void __fastcall TTester::HexAddressClick(TObject *Sender)
{
	Address = 0;
   HexAddress->Text = "";
   Anum = 0;   
}
//---------------------------------------------------------------------------

void __fastcall TTester::OutputBytesClick(TObject *Sender)
{
	Dnum = 0;
   Count = 0;
   OutputBytes->Text = "";
   for (int i = 0; i < 15; i++)
   	Data[i] = 0;
}
//---------------------------------------------------------------------------



