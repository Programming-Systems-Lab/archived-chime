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

  iAws *aws;
  iAwsWindow *window;
  iSector *room;
  csView* view;
  int y;
  float downAngle;

public:

  OverviewAWS();
  virtual ~OverviewAWS();

  void Setup (iAws *sys_aws, csView *sys_view);
  
  bool Start();

  bool Hide();

  void Draw();

  iCamera* GetCamera();

  void SetCamera( iCamera* newCam );

  void AdjustHeight();

  void AddHeight( float d_y );

  void SnapThisCamera();

  void SnapMainCamera();

  bool HandleEvent (iEvent &Event);

};

#endif // OVERVIEWAWS_H
