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

void OverviewAWS::Setup(iAws *sys_aws, csView *sys_view)
{
	aws = sys_aws;
	view = sys_view;
	window = aws->CreateWindowFrom("Overview");
	window->SetEngineView(sys_view);
	view->GetCamera ()->Move (CS_VEC_UP * y);
	view->GetCamera ()->GetTransform().RotateThis (CS_VEC_TILT_DOWN, downAngle);
}

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

void OverviewAWS::Draw()
{
	view->Draw();
}

void OverviewAWS::SetCamera(iCamera* newCam)
{
	view->SetCamera(newCam);
}

iCamera* OverviewAWS::GetCamera()
{
	return view->GetCamera();
}

void OverviewAWS::AdjustHeight()
{
	csVector3 origin = view->GetCamera()->GetTransform().GetOrigin();
	origin.y = y;
	view->GetCamera()->GetTransform().SetOrigin(origin);
}

void OverviewAWS::AddHeight(float d_y)
{
	y = y + d_y;
}

void OverviewAWS::SnapMainCamera()
{
	if (view->GetCamera()->GetSector() != Sys->view->GetCamera()->GetSector())
		Sys->view->GetCamera()->SetSector(view->GetCamera()->GetSector());
	csVector3 pos2 = view->GetCamera()->GetTransform().GetOrigin();
	pos2.y = Sys->view->GetCamera()->GetTransform().GetOrigin().y;
	Sys->view->GetCamera()->GetTransform().SetOrigin(pos2);
	Sys->sprite->GetMovable()->GetTransform().SetOrigin(pos2);
	Sys->sprite->GetMovable()->UpdateMove();
	pos2.y = y;
	view->SetCamera( Sys->view->GetCamera()->Clone() );
	view->GetCamera()->GetTransform().SetOrigin(pos2);
	//view->GetCamera()->Move( CS_VEC_BACKWARD );
	view->GetCamera()->GetTransform().RotateThis( CS_VEC_TILT_DOWN, downAngle );
	Sys->view->Draw();
	aws->Redraw();
}

void OverviewAWS::SnapThisCamera()
{
	if (view->GetCamera()->GetSector() != Sys->view->GetCamera()->GetSector())
		view->GetCamera()->SetSector(Sys->view->GetCamera()->GetSector());
	csVector3 pos2 = Sys->view->GetCamera()->GetTransform().GetOrigin();
	pos2.y = y;
	view->SetCamera( Sys->view->GetCamera()->Clone() );
	view->GetCamera()->GetTransform().SetOrigin(pos2);
	//view->GetCamera()->Move( CS_VEC_BACKWARD );
	view->GetCamera()->GetTransform().RotateThis( CS_VEC_TILT_DOWN, downAngle );
}

bool OverviewAWS::HandleEvent(iEvent &Event)
{
	bool r = false;
	try {
		r = aws->HandleEvent(Event);
		//aws->Redraw();
		Start();
	}
	catch (...) {return false;}
	return r;
}

//////////////////////////////////////////////////////////////////////
// OverviewAWS Class
//////////////////////////////////////////////////////////////////////

