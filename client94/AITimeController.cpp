 /*
 *
 * Copyright (c) 2002: The Trustees of Columbia University
 *    in the City of New York.  All Rights Reserved.
 *
 *
 */
// AITimeController.cpp: implementation of the AITimeController class.
//
//////////////////////////////////////////////////////////////////////

#include "AITimeController.h"
#include <windows.h>

// dp2041
#include <iostream.h>
#include <time.h>

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
  pause_time=0;  // this time is added to the AI2TV's time whenever we press pause.
  adjust_time=0; // used to "speed up" or "slow down" time

  // run the timer loop to wait for start signal
  runTimerLoop();
}

AITimeController::~AITimeController()
{

}

// start() called from AICommController (when PLAY is pressed)
void AITimeController::start(){stopped=false;}
void AITimeController::stop(){stopped=true;}

// dp2041: I haven't considered the case if the 
// time "overflows" yet.
int AITimeController::get_system_time(){
  time_t t;
  int now = time(&t);
  int new_time =(now - big_bang - pause_time + adjust_time);
  adjust_time=0;
  return new_time;
}

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
  // sleep_per_frame = 1000 msecs / 30 = 33 (+ 1 ever third count)

  // note: all time calculations (elsewhere also) are
  // performed in terms of this current_frame_number
  // [current_time is never used]

  // dp2041 sleep_per_frame: the sleep time per frame is the
  // granularity at which the AI2TV Time Controller is set at.
  // because the frames at max can be 30 frames per second, we
  // only update the clock every 1/3 second.

  // I set the beginning of time here instead of in the constructor
  // because there could be some discrepencies to when the thread
  // actually gets started.  granted, they could be on the order
  // of milliseconds, so maybe this could be done in the ctor without
  // any serious consequences, and added coherency in the code.
  time_t t;
  tc->big_bang = time(&t);  // the beginning of time
  int sleep_per_frame = 33;  
  double delay = 1; // I'm going to try to start off with a delay of 1 second in between time_changed
  while(true){
    if (tc->EXIT) return 0;
    if (tc->stopflag>0&&tc->current_frame_number>=tc->stopflag){
      tc->stopped=true; tc->stopflag=0;
    }
    if (!tc->stopped) tc->pause_time += tc->get_system_time();
    while (!tc->stopped){
      /// sleep until next frame
      // tc->current_frame_number = tc->current_frame_number+1;
	    
      if (tc->master_adj > 0) { // we're behind
	tc->master_adj--;
	// Sleep(adj + sleep_per_frame); // sleep half time
	// Sleep(adj + sleep_per_frame); // sleep half time
	// tc->adjust_time = 1;  // this has the effect of advancing time...	
	delay = 2;
	tc->last_action = "catchup";
	
      } else if (tc->master_adj < 0) { // we're ahead
	tc->master_adj++;
	// Sleep(4*(adj+sleep_per_frame));
	// dp2041
	// Sleep(adj + sleep_per_frame); // sleep double time
	//tc->adjust_time = -1;  // this has the effect of stopping time...
	delay = .5;
	tc->last_action = "wait"; 
	
      } else { // we're synced
	// Sleep(adj+sleep_per_frame);
	// dp2041
	tc->last_action = "normal";
      }

      Sleep(delay);
      tc->current_time = tc->get_system_time();
      int adj = ((tc->current_frame_number % 3 ==2)?1:0);
      tc->current_frame_number = tc->current_time * 30 + adj; // 30 frames/sec
      // time is not used
      // tc->current_time+=(adj+sleep_per_frame);
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
