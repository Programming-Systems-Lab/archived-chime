
//Copyright 2002 PSL lab, Columbia University



//*********************************************************************************
//*
//*  This class defines an Alternative Windowing System (AWS) window
//*	 that displays the overvhead 3D view of the scene.
//*
//*********************************************************************************

#ifndef OVERVIEWAWS_H
#define OVERVIEWAWS_H

#include <stdarg.h>
#include "csgeom/math2d.h"
#include "csgeom/math3d.h"
#include "iaws/aws.h"
#include "iaws/awscnvs.h"
#include "cstool/csview.h"
#include "csengine/sector.h"
#include "csengine/camera.h"

struct iAws;
struct iAwsWindow;
struct iSector;
struct iView;

class OverviewAWS
{

private:

  iAws *aws;				//AWS system
  iAwsWindow *window;		//AWS window
  iSector *room;			//which sector this view is in
  csView* view;				//view used by this window
  int y;					//y coordinate of the camera
  float downAngle;			//angle of rotation to look down

public:

  OverviewAWS();
  virtual ~OverviewAWS();

  //initializes this system
  void Setup (iAws *sys_aws, csView *sys_view);
  
  //starts the AWS window and view
  bool Start();

  //hides the AWS window
  bool Hide();

  //draws all inside components
  void Draw();

  //returns the camera used by this view
  iCamera* GetCamera();

  //installs the camera used by this view
  void SetCamera( iCamera* newCam );

  //update the view to the y height
  void AdjustHeight();

  //add to the y coordinate
  void AddHeight( float d_y );

  //snap this view to the main 3D view
  void SnapThisCamera();

  //snap the 3D view to this view
  void SnapMainCamera();

  //event handler
  bool HandleEvent (iEvent &Event);

};

#endif // OVERVIEWAWS_H
