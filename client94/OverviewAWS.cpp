//*******************************************************************
//*
//* Implementation of OverviewAWS class.
//*
//*******************************************************************

#include "cssysdef.h"
#include "cssys/system.h"
#include "OverviewAWS.h"
#include "ChimeSystemDriver.h"
#include <stdio.h>

extern ChimeSystemDriver *Sys;

OverviewAWS::OverviewAWS()
{
  aws = NULL;
  window = NULL;
  room = NULL;
  view = NULL;
  y = 13.0f;
  downAngle = 1.57f;
}

OverviewAWS::~OverviewAWS()
{
  if(aws) aws->DecRef();
  if(window) window->DecRef();
  if(room) room->DecRef();
  if(view) view->DecRef();
}

//****************************************
//**** Initialize components
//****************************************
void OverviewAWS::Setup(iAws *sys_aws, csView *sys_view)
{
	aws = sys_aws;
	view = sys_view;
	//create the window from definition file awstest.def
	window = aws->CreateWindowFrom("Overview");
	window->SetEngineView(sys_view);
	view->GetCamera ()->Move (CS_VEC_UP * y);
	view->GetCamera ()->GetTransform().RotateThis (CS_VEC_TILT_DOWN, downAngle);
}

//***************************************************
//**** Show the window and start updating the screen
//***************************************************
bool OverviewAWS::Start()
{
	if (window) {
		window->Show();
		aws->Redraw();
		return true;
	}
	else
		return false;
}

//****************************************
//**** Hide the window
//****************************************
bool OverviewAWS::Hide()
{
	if (window) {
		window->Hide();
		aws->Redraw();
		return true;
	}
	else
		return false;
}

//*********************************************
//**** Start drawing the view into the window
//*********************************************
void OverviewAWS::Draw()
{
	view->Draw();
}

//****************************************
//**** Setup camera
//****************************************
void OverviewAWS::SetCamera(iCamera* newCam)
{
	view->SetCamera(newCam);
}

//****************************************
//**** Return camera
//****************************************
iCamera* OverviewAWS::GetCamera()
{
	return view->GetCamera();
}

//********************************************
//**** Move camera to new height (value of y)
//********************************************
void OverviewAWS::AdjustHeight()
{
	csVector3 origin = view->GetCamera()->GetTransform().GetOrigin();
	origin.y = y;
	view->GetCamera()->GetTransform().SetOrigin(origin);
}

//********************************************
//**** Increase/decrease height (value of y)
//********************************************
void OverviewAWS::AddHeight(float d_y)
{
	y = y + d_y;
}

//****************************************
//**** Snap the main 3D camera to the
//**** location of this camera
//****************************************
void OverviewAWS::SnapMainCamera()
{
	//if in different sectors, move main camera
	//to the this sector
	if (view->GetCamera()->GetSector() != Sys->view->GetCamera()->GetSector())
		Sys->view->GetCamera()->SetSector(view->GetCamera()->GetSector());

	//set main camera to the position of the this camera
	//but at height 0
	csVector3 pos2 = view->GetCamera()->GetTransform().GetOrigin();
	pos2.y = Sys->view->GetCamera()->GetTransform().GetOrigin().y;
	Sys->view->GetCamera()->GetTransform().SetOrigin(pos2);

	//move the sprite that represents the user to
	//the same coordinates
	if (Sys->sprite)
	{
		Sys->sprite->GetMovable()->GetTransform().SetOrigin(pos2);
		Sys->sprite->GetMovable()->UpdateMove();
	}
	
	pos2.y = y;
	
	//set this camera to the orientation of the main camera
	//by using a clone of main camera and then raising it up
	//to height y
	view->SetCamera( Sys->view->GetCamera()->Clone() );
	view->GetCamera()->GetTransform().SetOrigin(pos2);
	view->GetCamera()->GetTransform().RotateThis( CS_VEC_TILT_DOWN, downAngle );

	//update views
	Sys->view->Draw();
	aws->Redraw();
}

//****************************************
//**** Snap this camera to the
//**** location of the main camera
//****************************************
void OverviewAWS::SnapThisCamera()
{

	//change sectors, if necessary
	if (view->GetCamera()->GetSector() != Sys->view->GetCamera()->GetSector())
		view->GetCamera()->SetSector(Sys->view->GetCamera()->GetSector());
	csVector3 pos2 = Sys->view->GetCamera()->GetTransform().GetOrigin();
	
	//set this camera as a clone of main camera
	//but at height y
	pos2.y = y;
	view->SetCamera( Sys->view->GetCamera()->Clone() );
	view->GetCamera()->GetTransform().SetOrigin(pos2);
	view->GetCamera()->GetTransform().RotateThis( CS_VEC_TILT_DOWN, downAngle );
}

//*********************************************
//**** Handle window events (moving, resizing)
//*********************************************
bool OverviewAWS::HandleEvent(iEvent &Event)
{
	bool r = false;
	try {
		//just let the AWS system to handle events
		r = aws->HandleEvent(Event);
		Start();
	}
	catch (...) {return false;}
	return r;
}

//////////////////////////////////////////////////////////////////////
// OverviewAWS Class
//////////////////////////////////////////////////////////////////////

