 /*
 *
 * Copyright (c) 2002: The Trustees of Columbia University
 *    in the City of New York.  All Rights Reserved.
 *
 *
 */
// AICacheController.cpp: implementation of the AICacheController class.
//
//////////////////////////////////////////////////////////////////////

//#define AICACHE_EXPORT
#include "cssysdef.h"
#include "cssys/system.h"
#include "cssys/sysdriv.h"
#include "csws/csws.h"
#include "AICache.h"
#include "AICacheController.h"
#include "AIDownloader.h"
#include "AIVideoPlayer.h"
#include "WindowToolkit.h"
#include "AIVideoFrame.h"
#include "AI2TVConstants.h"
#include "AIVideoFrameBuffer.h"
#include "ChimeSystemDriver.h"
#include "ChimeApp.h"
#include <stdio.h>
#include <iostream.h>
extern ChimeSystemDriver* Sys;
//LoadLibrary("Cache.lib");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/***************************************
 *	Static Thread Function, used to periodically check network bandwidth
 *	This should be replaced with a more sophisticated bandwidth detection
 *	when the appropriate library is found
 ****************************************/

DWORD WINAPI runNetCheckThread(LPVOID lParam){
  AICacheController* cc = (AICacheController*)lParam;
  int curr = 0;

  // adding bandwidth checks so that each client can adjust bandwidth
  // throughout play (previously all were set to highest level) -cl

  int bandwidth = cc->getSampleBandwidth();
  cc->SetCLevel(bandwidth);

  while(1){
    if (!cc ||  !cc->Downloader || cc->EXIT) return 0;
    try{
      // if there are more frames downloaded
      if (curr!=cc->Downloader->numMeasurements){

	int bw = cc->getSampleBandwidth();
	if (bandwidth != bw) {
	  bandwidth = bw;
	  cc->SetCLevel(bandwidth);
	}

	// only master sends regular updates
	// (note: any client can force others to sync with it by pressing the network button)
	if (cc->player->isMaster) {
	  cc->checkNetwork();
	}

	curr=cc->Downloader->numMeasurements;
      }
    } catch (...){}
    Sleep(2000);
  }
  return 0;
}

/***************************************
*	The static thread-creating function
****************************************/
void doNetCheck(AICacheController *cc){
	CoInitialize(NULL);
	DWORD threadId1;
	CreateThread(NULL,0,runNetCheckThread,cc,0,&threadId1);
}

/***************************************
*	Used to test cache functionality/DEPRECATED
***************************************/
AICacheController::testDownload(char* url){
return 0;//cache->putFrame(3,4,4,10,2,5,url);
	}

/***************************************
*	Constructor. DSN is passed to AICache() constructor
*	creates cache over the database connection(ODBC)
****************************************/

//AICacheController::AICacheController(char* dsn) 
// adding player param b/c Sys not working 
AICacheController::AICacheController(char* dsn, AIVideoPlayer *p)
{
  player = p;
  currentProjectID=0;
  EXIT=false;
  //  cache = new AICache("AI2TV_CACHE"); //reduntant string -cl
  cache = new AICache(dsn);
  Downloader = new AIDownloader();
  cacheRootPathHDD="./data/ai2tv"; // 
  cacheRootPathVFS="/lib/ai2tv"; // this is mapped in VFS.cfg (in /psl/chime/client90)
  doNetCheck(this);
  // test cache - removed because it threw exceptions
  //	int clevels[3] = {4,8,12};
  //	cache->setupCache();
  //	currentProjectID = 	cache->createProject(11221, "The new video", clevels, 3, 122, 30);
}

/***************************************
*	SetupProject, same as AICache- used to
*	pass params to AICache, when AIcache starts
*	to function properly. At this time it does not.
****************************************/
int AICacheController::setupProject(int videoID, char* videoTitle, int compressionLevels[], int compLevelLength, int totalNumVideoFrames, int framesPerSecond){
return 0;//testDownload("http://www.onlysimchas.com/images/ad-logo.jpg");
	//return cache->setupProject(videoID,  videoTitle,  compressionLevels,  compLevelLength,  totalNumVideoFrames,  framesPerSecond);
}

/***************************************
*	Cleans up
***************************************/
AICacheController::~AICacheController()
{
if (Downloader) delete Downloader;
if (cache)	delete cache;
}


// new function - SetCLevel(): sets the CLevel (frame show rate) -cl
void AICacheController::SetCLevel(int c_level) {
  int oldlevel = currentCLevelIndex;
  int level = (c_level>=0)?c_level:0;
  level = ((level<=clevel_count)?level:clevel_count);

  if (currentCLevelIndex != level) {
    int current_frame_number = cframes[currentCLevelIndex][currentFrameIndex];
    currentCLevelIndex = level;
    currentFrameIndex=0;

    while(cframes[currentCLevelIndex][currentFrameIndex] < current_frame_number){
      currentFrameIndex++;
    }

    char *msg = new char[30];
    sprintf(msg, "Changed CLevel (%d, %d)", oldlevel, currentCLevelIndex);
    //    Sys->myVideoPlayer->debug(1,msg);
    player->debug(2,msg);

  } // else no change
}


/***************************************
*	This repositions download list to a higher compression level
***************************************/
void AICacheController::BetterCLevel(){
	// if better ones exist, (where they are in order of better-worse)
	if (currentCLevelIndex > 0){
		int current_frame_number = cframes[currentCLevelIndex][currentFrameIndex];
		currentCLevelIndex--;
		currentFrameIndex=0;
		while(cframes[currentCLevelIndex][currentFrameIndex] < current_frame_number){
			currentFrameIndex++;
		}
		Sys->myVideoPlayer->debug(1,"Better CLevel");
	}
}
/***************************************
*	This repositions download list to a lower compression level
***************************************/
void AICacheController::WorseCLevel(){
	// if worse ones exist, (where they are in order of better-worse)
	if ( currentCLevelIndex < clevel_count -1){
		int current_frame_number = cframes[currentCLevelIndex][currentFrameIndex];
		currentCLevelIndex++;
		currentFrameIndex=0;
		while(cframes[currentCLevelIndex][currentFrameIndex] < current_frame_number){
			currentFrameIndex++;
		}
		Sys->myVideoPlayer->debug(1,"Worse CLevel");
	}
}

/***************************************
*	This  outputs the network measurements it has been maintaining
***************************************/

// called by runNetCheckThread or by press of Network button
void AICacheController::checkNetwork(){
  //  return; // Gave problems at demo time. Simple debugging should get it back to work again
  // now not returning -cl
  try{
    char my_msg[30];

    sprintf(my_msg,"NET:FS:%d NS:%d\0",getAvgFileSize(),getAvgNetSpeed());
    player->debug(1,my_msg);

    if (clevels && cframes){
      sprintf(my_msg,"CL:%d CF:%d\0",clevels[currentCLevelIndex],
	      cframes[currentCLevelIndex][currentFrameIndex]);
      player->debug(1,my_msg);	
    }

    // broadcast current_frame_number to all clients
    Sys->myVideoPlayer->announceTime(); 
  }
  catch(...){
    Sys->myVideoPlayer->debug(1,"Error");
  }
}



/***************************************
*	SetupFrameList- This downloads and sets up
*	the list of frames. The actual file name
*	that is downloaded is determined by session_setup.txt
*	in ./data/ai2tv ... The file downloaded is then
*	parsed according to the following syntax, line by line:
*
*	NUM_OF_COMP_LEVELS
*	KeyFramesForThisLevel  - *for each level, this number represents the number of keyframes in that level, each number on a differen line
*	FrameNumber Start End - For each level, all the frame numbers, in order, plus their start time and end time, in frame numbers (since this list is sparse)
*
****************************************/
int AICacheController::setupFrameList(char* filename){
	char  file_dest[200];
	sprintf(file_dest,"%s/%s\0",cacheRootPathHDD,filename);
	char  src_url[200];
	sprintf(src_url,"%s/%s\0",cacheRootURL,filename);
	// take care of failures, while downloading at the same time
	if (Downloader->download(src_url,file_dest)!=0) return 0;
	
	// open the file we just downloaded
	FILE* pFrame_list;
	pFrame_list = fopen(file_dest,"r");
	
	if (!pFrame_list) // See if the file was opened sucessfully.
	{ 
		printf("CANNOT OPEN FILE. FATAL ERROR.");
		return 0; // throw something, we cannot proceed
	}

	// first let's get the number of compression levels
	fscanf(pFrame_list,"%d",&clevel_count);

	// allocate the 3 arrays for each frame
	clevels = new int[clevel_count];
	cframes = new int*[clevel_count];
	cframes_start = new int*[clevel_count];
	cframes_end = new int*[clevel_count];

	// load in the list of compression levels, largest first
	for (int i =0; i < clevel_count; i++){
		fscanf(pFrame_list,"%d",&clevels[i]);
		printf("New Compression Level: %d\n",clevels[i]);
		
	}
	
	// now loop through the file
	int frame_number;
	int start_fn;
	int end_fn;
	maxFrameNumber =0;
	currentFrameIndex=0;
	currentCLevelIndex=0;
	// nested loop loading of each compression level
	for (int curr_clevel = 0; curr_clevel<clevel_count;curr_clevel++){
		// allocate an array for the current compression level's framelist
		cframes[curr_clevel] = new int[clevels[curr_clevel]];
		cframes_start[curr_clevel] = new int[clevels[curr_clevel]];
		cframes_end[curr_clevel] = new int[clevels[curr_clevel]];
		for (int j =0; j < clevels[curr_clevel]; j++){
			fscanf(pFrame_list,"%d%d%d",&frame_number,&start_fn,&end_fn);
			cframes[curr_clevel][j] = frame_number;
			cframes_start[curr_clevel][j] = start_fn;
			cframes_end[curr_clevel][j] = end_fn;
			//printf("New Frame (CL=%d) %d [%d->%d]\n",clevels[curr_clevel],frame_number,start_fn,end_fn);	
			// this will guarantee that we have the total number of frames
			// because the end_fn is the end of the video for the last frame in each
			// compression level.
			if (end_fn > maxFrameNumber) maxFrameNumber = end_fn;
		}
	}


	return 1; // succeeded
	}

// end: setup frame list


// new function: getSampleBandwidth()  -cl 
// simple bandwidth calculator -- uses avg file size and
// avg net speed of frame downloads to approximate the bandwidth in
// kbps.  return value is level in range (0-clevel_count) (high-low) 
int AICacheController::getSampleBandwidth() {
  int bw_level = 0;
  int size = getAvgFileSize();
  int speed = getAvgNetSpeed();
  speed = ((speed>0)?speed:1);

  // division of averages - very approximate
  int bandwidth = (int)(((long)size*8)/((long)speed*1000)); //kbps
  
  if (clevel_count > 0) {
    int div = high_bandwidth;
    div = div/clevel_count;
    int band_level = (clevel_count - (bandwidth/div)) - 1;
    band_level = ((band_level > 0)?band_level:0);

    // for debugging
    char *msg = new char[30];
    sprintf(msg, "bandwidth:%d kbps, level:%d", bandwidth, band_level);
    player->debug(2,msg);

    return band_level;
  } else { return 0; }
  
  // here are some sample bandwidths for reference 
  // note - testing w/DSL during peak hours couldn't get above 128
  // tho in lab conditions, higher vals expected
  /*  28.8 Kbps    Dial-up 28.8k    
      33.6 Kbps    Dial-up 33.6k    
      53.3 Kbps    Dial-up 56k    
      64 Kbps    ISDN 64k    
      128 Kbps    ISDN 128k    
      384 Kbps    DSL 384k    
      768 Kbps    DSL 768k   
      1500 Kbps    DSL 1.5MB  
  */
}


/*******************************
*
*	Lazy Man's Bandwidth Detection, just average the last N of them
*
*******************************/
int AICacheController::getAvgFileSize(){

  int count = 0;
  int total=0;
  if (Downloader->SizeArray) {
    for (int i = count; i < Downloader->SizeArraySize; i++){
      if (Downloader->SizeArray[i] > 0){
	total+=Downloader->SizeArray[i];
	++count;
      }
    }
    return ((count>0)?(total/count):0);
  } else 
    {
      //Downloader->SizeArray = new int[Downloader->SizeArraySize];
      Downloader->SizeArray = new long[Downloader->SizeArraySize];
      return -1;
    }
}
/*******************************
*
*	Lazy Man's Bandwidth Detection, just average the last N of them
*
*******************************/
int AICacheController::getAvgNetSpeed(){
	 return 0; // stopped working, so killed it
	int count = 0;
	int total=0;
	/*	
	if (Downloader->SpeedArray) {

			for (int i = count; i < cache->SpeedArraySize; i++){
		if (Downloader->SpeedArray[i] > 0){
			total+=Downloader->SpeedArray[i];
			++count;
		}
	}
	return ((count>0)?(total/count):0);
		} else {
		Downloader->SpeedArray = new int[Downloader->SpeedArraySize];
		return -1;
	}
*/
  }

// processes next video frame

/*******************************
*
*	ProcessNextFrame puts it in the buffer
*
*******************************/
void AICacheController::processNextFrame(AIVideoPlayer* player){
  char filename[30];
  sprintf(filename,"%d.jpg\0",cframes[currentCLevelIndex][currentFrameIndex]);
  char  file_dest[200];
  sprintf(file_dest,"%s/%s\0",cacheRootPathHDD,filename);
  char  src_url[200];
  sprintf(src_url,"%s/%s\0",cacheRootURL,filename);
  char vfs_filename[100];
  sprintf(vfs_filename,"%s/%s\0",cacheRootPathVFS,filename);
  //	Sys->GetApp()->historyWindow->AddItem(src_url);
  try{
    if (!Downloader->downloadFile(src_url,file_dest)){
      // then create the frame in the player, and put in buffer;	
      AIVideoFrame* fr = player->createFrame(vfs_filename,cframes[currentCLevelIndex][currentFrameIndex],cframes_start[currentCLevelIndex][currentFrameIndex],cframes_end[currentCLevelIndex][currentFrameIndex]);
      if (fr&&fr->start&&fr->materialWrapper) {
	// adding error check -cl
	if (!player->FrameBuffer->putFrame(fr)) {
	  player->debug(1,"ProcessNextFrame() Failed - buffer full");
	}
      }
    } else { // adding error output 
      player->debug(1,"ProcessNextFrame() Failed");
    }

  } catch (...) {
    player->debug(1,"ProcessNextFrame() Failed");
  }
  // no matter what, let's move on, so we can ignore failing cases
  currentFrameIndex++;
		
}
