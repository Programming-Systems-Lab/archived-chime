 /*
 *
 * Copyright (c) 2002: The Trustees of Columbia University
 *    in the City of New York.  All Rights Reserved.
 *
 *
 */
#define SYSDEF_PATH
#include "cssysdef.h"
#include "cssys/sysdriv.h"
#include "csws/csws.h"
#include "csver.h"
#include "ivideo/fontserv.h"
#include "ChimeWindow.h"

Ai2tvWindow::~Ai2tvWindow() {}


Ai2tvWindow::Ai2tvWindow(csComponent *iParent)
  : ChimeWindow(iParent, "AI2TV Settings", CSWS_TITLEBAR | CSWS_BUTCLOSE |
    CSWS_BUTMAXIMIZE)
  {

  this->SetSize (500, 250);
  this->Center ();

  px = 15;
  py = 20;
  int labelw = 400;

  state = SET_SIZE_STATE;

  //open file were data will be written
  File.open("./data/ai2tv/session_temp.txt", ios::trunc);
  if (!File.good()) {
	OpenErrorScreen();
	return;
  }
  
  //////////create the dialog///////////////
  d = new csDialog(this);
  this->SetDragStyle (this->GetDragStyle () & ~CS_DRAG_SIZEABLE);

  lblTop = new csStatic(d, csscsLabel);
  lblTop->SetText("Size of your group (including yourself):");
  lblTop->SetRect(px, py, px+labelw, py+30);
  
  txtGroupSize = new csInputLine(d);
  txtGroupSize->SetSize(300, 30);
  txtGroupSize->SetPos(2*px, 3*py);

  //setup the accept and cancel buttons
  btnOK = new csButton(d, 66800);
  btnOK->SetText("Set group size");
  btnOK->SetSuggestedSize(16,8);
  btnOK->SetPos(70, 175);

  //cancel button
  btnCAN = new csButton(d, 66801);
  btnCAN->SetText("Cancel");
  btnCAN->SetSuggestedSize(16,8);
  btnCAN->SetPos(300, 175);
}

  void Ai2tvWindow::OpenErrorScreen() {
	  d = new csDialog(this);
	  lblTop = new csStatic(d, csscsLabel);
	  lblTop->SetText("ERROR: Could not open settings file!");
	  lblTop->SetRect(px, py, px+400, py+30);
	  btnOK = new csButton(d, 66801);
	  btnOK->SetText("OK");
	  btnOK->SetSuggestedSize(16, 8);
	  btnOK->SetPos(70, 175);
  }
  
  void Ai2tvWindow::SetupInput() {
	  this->SetSize(500, 400);
	  btnOK->SetPos(70, 325);
	  if (groupSize <= PAGE_SIZE)
		  btnOK->SetText("Done");
	  else
		  btnOK->SetText("Next");
	  btnCAN->SetPos(300, 325);
	  d->Delete(txtGroupSize);
      lblTop->SetText("Enter each group member's IP (including yourself) :");
	  char lblBuf[40];
	  char numBuf[10];
	  for (int i = 0; i<PAGE_SIZE; i++) {
		  txtGroupIP[i] = new csInputLine(d);
		  txtGroupIP[i]->SetSize(300, 30);
		  txtGroupIP[i]->SetPos(8*px, 80+py*i*2);
		  lblIP[i] = new csStatic(d, csscsLabel);
		  lblIP[i]->SetRect(px, 80+py*i*2, 5*px, 110+py*i*2);
		  itoa(i+1, numBuf, 10);
		  strcpy(lblBuf, "IP ");
		  strcat(lblBuf, numBuf);
		  strcat(lblBuf, ":");
		  lblIP[i]->SetText(lblBuf);
		  if (i+1 > groupSize) {
			  lblIP[i]->Hide();
			  txtGroupIP[i]->Hide();
		  }
	  }
  }

  void Ai2tvWindow::ReadInput() {
	  char buffer[100], lblBuf[40], numBuf[10];
	  int firstLine = (pageNumber-1)*PAGE_SIZE + 1;
	  for (int i = 0; i<PAGE_SIZE; i++) {
		  if (firstLine+i <= groupSize) {
			itoa(250+i+firstLine, buffer, 10);
			File<<buffer;
			File<<" ";
			strcpy(buffer, txtGroupIP[i]->GetText());
			File<<buffer;
			File<<"\n";
            txtGroupIP[i]->SetText("");
			itoa(firstLine+i+PAGE_SIZE, numBuf, 10);
			strcpy(lblBuf, "IP ");
			strcat(lblBuf, numBuf);
			strcat(lblBuf, ":");
			lblIP[i]->SetText(lblBuf);
			if (firstLine+i+PAGE_SIZE > groupSize) {
				txtGroupIP[i]->Hide();
				lblIP[i]->Hide();
			}
			if (firstLine + 2*PAGE_SIZE >= groupSize)
				btnOK->SetText("Done");
		  }
	  }
	  pageNumber++;
  }	  


bool Ai2tvWindow::HandleEvent (iEvent &Event)
{

  if (csWindow::HandleEvent (Event))
    return true;

  switch (Event.Type)
  {
    case csevCommand:
      switch (Event.Command.Code)
      {
	    //OK button was pressed
        case 66800:
			if (state == SET_SIZE_STATE) {
				char groupSizeBuf[5];
				txtGroupSize->GetText(groupSizeBuf, 5);
				groupSize = atoi(groupSizeBuf);
				File<<groupSizeBuf;
				File<<"\n";
				pageNumber = 1;
				SetupInput();
				state = ENTER_IP_STATE;
				return true;
			}
			if (state == ENTER_IP_STATE && pageNumber*PAGE_SIZE < groupSize) {
				ReadInput();
				return true;
			}
			if (state == ENTER_IP_STATE && pageNumber*PAGE_SIZE >= groupSize) {
				ReadInput();
				lblTop->SetText("Enter server address and name of file:");
				int i = 0;
				for (i = 0; i<PAGE_SIZE; i++) {
					txtGroupIP[i]->Show();
					lblIP[i]->Show();
				}
				txtGroupIP[0]->SetText("");
				lblIP[0]->SetText("Server:");
				txtGroupIP[1]->SetText("");
				lblIP[1]->SetText("File:");
				for (i = 2; i<PAGE_SIZE; i++) {
					txtGroupIP[i]->Hide();
					lblIP[i]->Hide();
				}
				btnOK->SetText("Save");
				state = SET_SERVER_STATE;
				return true;
			}
			if (state == SET_SERVER_STATE) {
				File<<txtGroupIP[0]->GetText();
				File<<"\n";
				File<<txtGroupIP[1]->GetText();
				File.close();
				CopyFile("./data/ai2tv/session_temp.txt", "./data/ai2tv/session.txt", false);
				Close();
				return true;
			}
			return true;

		 //Cancel Button has been pressed
		case 66801:
		  Close();
		  return true;
	  }

      break;

  }

  return false;
}
