


#include "TApp.h"
#include "TMainWindow.h"
#include <iostream>


using namespace org::toxic;
using namespace std;


TApp::TApp(BString * UserSpecifiedSongDir):BApplication("application/x-vnd.guitar-master")
{
	cout<<"Guitar Master project"<<endl;
	cout<<"Toxic Labs 2008/2009"<<endl;
	this->UserSpecifiedSongDir = UserSpecifiedSongDir;
}


TApp::~TApp()
{
	cout<<"Closing application"<<endl;	
}


void TApp::ReadyToRun()
{
	cout<<"ready!!"<<endl;
	
	window = new TMainWindow(BRect(50,50,300,300), UserSpecifiedSongDir);
}
