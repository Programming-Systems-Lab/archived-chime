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

  int px = 15, py = 20;
  int labelw = 150;

  currentBuffer = 0;

  //////////create the dialog///////////////
  csDialog *d = new csDialog(this);
  this->SetDragStyle (this->GetDragStyle () & ~CS_DRAG_SIZEABLE);

  //open the settings text file
  File = new ifstream("./data/ai2tv/session.txt");

  //////////////////////Numner of Hosts field//////////////////////////////
  host_number = new csInputLine(d);
  host_number->SetSize(40,30);
  host_number->SetPos(px+labelw,py);

  //set the text to the previous value
  if (!File->eof()) {
    File->getline(hostNumBuf, 5);
    host_number->SetText(hostNumBuf);
	numberOfHosts = atoi(hostNumBuf);
  }
  else {
    host_number->SetText("1");
	numberOfHosts = 1;
  }

  csStatic *host_num_lbl = new csStatic(d, host_number, "Number of hosts:");
  host_num_lbl->SetRect(px, py, px+labelw,py+host_number->bound.Height());

  csButton *host_num_btn = new csButton(d, 66803);
  host_num_btn->SetText("Update");
  host_num_btn->SetSuggestedSize(16, 8);
  host_num_btn->SetPos(px+labelw+host_number->bound.Width()+px, py);

  py += py+host_number->bound.Height();

  /////////////////////Enter host IPs//////////////////////////////////
  host_ip = new csInputLine(d);
  host_ip->SetSize(200,30);
  host_ip->SetPos(px+labelw,py);

  //set the text to the previous value
  ReadNext();

  csStatic *chat_lbl = new csStatic(d, host_ip, "Host IP:");
  chat_lbl->SetRect(px, py, px+labelw,py+host_ip->bound.Height());
  host_ip_btn = new csButton(d, 66802);
  host_ip_btn->SetText("Next");
  host_ip_btn->SetSuggestedSize(16, 8);
  host_ip_btn->SetPos(px+labelw+host_ip->bound.Width()+px, py);
  py += py+host_ip->bound.Height();

  //accept button
  csButton *butOK = new csButton(d, 66800);
  butOK->SetText("OK");
  butOK->SetSuggestedSize(16,8);
  butOK->SetPos(70, py);

  //cancel button
  csButton *butCAN = new csButton(d, 66801);
  butCAN->SetText("Cancel");
  butCAN->SetSuggestedSize(16,8);
  butCAN->SetPos(300, py);

}

  //Read next ip from file or set to empty string
  void Ai2tvWindow::ReadNext()
  {
	  if (!File->eof()) {
		  File->getline(buffer[currentBuffer], 50);
		  host_ip->SetText(buffer[currentBuffer]);
	  }
	  else
		  host_ip->SetText("");
	  if (currentBuffer == numberOfHosts-1) {
		  host_ip_btn->SetState(!CSBS_SELECTABLE, false);
		  host_ip_btn->SetText("Done");
		  host_ip_btn->Hide();
	  }
  }

  //Write contents to settings file
  void Ai2tvWindow::Write()
  {
	  File->close();
	  ofstream FileWrite("./data/ai2tv/session.txt", ios::trunc);
	  FileWrite<<hostNumBuf;
	  for (int i = 0; i<numberOfHosts; i++) {
		  FileWrite<<"\n";
		  FileWrite<<buffer[i];
	  }
	  FileWrite<<"\nvesey.psl.cs.columbia.edu\nframe_index.txt";
	  FileWrite.close();
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
		//Number of hosts was updated
	    case 66803:
		  host_number->GetText(hostNumBuf, 5);
		  numberOfHosts = atoi(hostNumBuf);
		  if (currentBuffer < numberOfHosts-1) {
			host_ip_btn->SetState(CSBS_SELECTABLE, true);
			host_ip_btn->SetText("Next");
			host_ip_btn->Show();
		  }
		  return true;
		  //Next host IP button was pressed
		case 66802:
			host_ip->GetText(buffer[currentBuffer], 50);
			currentBuffer++;
			ReadNext();
			return true;
		//OK button was pressed
        case 66800:
		  host_ip->GetText(buffer[currentBuffer], 50);
		  Write();
		  Close();
		  return true;

		 //Cancel Button has been pressed
		case 66801:
		  File->close();
		  Close();
		  return true;
	  }

      break;

  }

  return false;
}
