//---------------------------------------------------------------------------

#ifndef Tester5H
#define Tester5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTester : public TForm
{
__published:	// IDE-managed Components
   TEdit *HexAddress;
   TTimer *Timer;
   TEdit *OutputBytes;
   TEdit *ReturnBytes;
   TButton *Send;
   TButton *Repeat;
   TButton *Stop;
   TEdit *Changes;
   TEdit *Aborts;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
	TEdit *ReceiveDelay;
	TLabel *Label6;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall HexAddressKeyPress(TObject *Sender, char &Key);
   void __fastcall OutputBytesKeyPress(TObject *Sender, char &Key);
   void __fastcall SendClick(TObject *Sender);
   void __fastcall RepeatClick(TObject *Sender);
   void __fastcall StopClick(TObject *Sender);
   void __fastcall TimerTimer(TObject *Sender);
   void __fastcall HexAddressClick(TObject *Sender);
   void __fastcall OutputBytesClick(TObject *Sender);
private:	// User declarations

   	HANDLE comHandle;
   	bool success;
   	DCB dcb;
   	char Fstr[100];
   	char Tstr[50];
   	DWORD numWrite, numRead;
   	COMMTIMEOUTS timeouts;

	   String This, Last;
   	int RChanges;
   	int NAborts;
   	int Anum;
   	int Dnum;
   	int Count;
   	char Address;
   	char Data[15];
      
public:		// User declarations

   	void SendPacket(void);

   __fastcall TTester(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTester *Tester;
//---------------------------------------------------------------------------
#endif
