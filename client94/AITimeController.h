 /*
 *
 * Copyright (c) 2002: The Trustees of Columbia University
 *    in the City of New York.  All Rights Reserved.
 *
 *
 */
// AITimeController.h: interface for the AITimeController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AITIMECONTROLLER_H__2E21EA5E_0BD6_4102_9BE6_65F4FD64750B__INCLUDED_)
#define AFX_AITIMECONTROLLER_H__2E21EA5E_0BD6_4102_9BE6_65F4FD64750B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class AIVideoPlayer;
class AITimeController {  

public:
	int stopflag;
	AIVideoPlayer* player;
	bool stopped;
	bool EXIT;
	AITimeController(AIVideoPlayer* p);
	virtual ~AITimeController();
	void runTimerLoop();
	int current_frame_number;
	int current_time;
	int master_frame_number;  
	int master_adj;
	char* last_action;
	void start();
	void stop();
	void setMaster(int mast_frame);
};

#endif // !defined(AFX_AITIMECONTROLLER_H__2E21EA5E_0BD6_4102_9BE6_65F4FD64750B__INCLUDED_)
