// AITimeController.cpp: implementation of the AITimeController class.
//
//////////////////////////////////////////////////////////////////////

#include "AITimeController.h"
#include <windows.h>

#ifndef _AIVIDEOPLAYER_H_
class AIVideoPlayer{
public:
	int current_frame_number;
		void time_changed();

};
#endif // _AIVIDEOPLAYER_H_

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AITimeController::AITimeController(AIVideoPlayer* p)
{
  master_frame_number=-1;  // new master vars -cl
  master_adj = 0;
  EXIT=false;
  stopflag=-1;
  player=p;
  stopped=true;
  current_frame_number=-1;
  current_time=0;

  // run the timer loop to wait for start signal
  runTimerLoop();
}

AITimeController::~AITimeController()
{

}

// start() called from AICommController (when PLAY is pressed)
void AITimeController::start(){stopped=false;}
void AITimeController::stop(){stopped=true;}

// new function: determine how long to inc/dec speed
void AITimeController::setMaster(int mast_frame) { 
  // assume some amount of msg travel time
  master_frame_number = mast_frame + 4; 

  // estimated frame time adjustment to sync w/master
  // if > 0 we're behind; if < 0 we're ahead
  master_adj = 2 * (master_frame_number - current_frame_number);
}

// revamped timer to include synchronization -cl

// when playing, timer loop continuously sleeps for one frame length
// then signals the player to check whether it should show a new frame
// (via aivideoplayer->time_changed()) 

// for synching with master -- speed up / slow down performed here: if
// master is very behind or ahead, we will sync up without skipping
// frames 

DWORD WINAPI RunAITimeController(LPVOID lParam){
	AITimeController* tc = (AITimeController*)lParam;

	// the reasoning behind adj+fps sleep time per frame:
	// at the rate of 30 frame counts per second, 
	// fps = 1000 msecs / 30 = 33 (+ 1 ever third count)

	// note: all time calculations (elsewhere also) are
	// performed in terms of this current_frame_number
	// [current_time is never used]

	int fps = 33;  
	while(true){
	  if (tc->EXIT) return 0;
	  if (tc->stopflag>0&&tc->current_frame_number>=tc->stopflag){
	    tc->stopped=true; tc->stopflag=0;
	  }
	  while (!tc->stopped){
	    /// sleep until next frame

	    int adj = ((tc->current_frame_number % 3 ==2)?1:0);
	    tc->current_frame_number = tc->current_frame_number+1;
	    
	    if (tc->master_adj > 0) { // we're behind
	      tc->master_adj--;
	      Sleep(adj+(fps/2)); // sleep half time

	      tc->last_action = "catchup";

	    } else if (tc->master_adj < 0) { // we're ahead
	      tc->master_adj++;
	      Sleep(adj+(fps*2)); // sleep double time

	      tc->last_action = "wait"; 

	    } else { // we're synced
	      Sleep(adj+fps);

	      tc->last_action = "normal";
	    }

	    // current_time is never used
	    tc->current_time+=(adj+fps);

	    // signal player to check if time to display new frame
	    tc->player->time_changed();
	  }
	}
}



void AITimeController::runTimerLoop(){
	CoInitialize(NULL);
	DWORD threadId1;
	CreateThread(NULL,0,RunAITimeController,this,0,&threadId1);
}
