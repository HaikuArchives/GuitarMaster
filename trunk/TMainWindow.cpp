


#include "TMainWindow.h"
#include "Application.h"
#include <iostream>

using namespace org::toxic;
using namespace std;


TMainWindow::TMainWindow(BRect frame): BWindow(frame,"Guitar Master",B_TITLED_WINDOW,B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	cout<<"Main window"<<endl;
	
	timer = new BMessageRunner(this,new BMessage(T_MSG_FRAME),50000,-1);
	
	ResizeTo(640,480);
	gameview = new TGameView(BRect(5,5,635,400));
	AddChild(gameview);
	Show();
}


TMainWindow::~TMainWindow()
{
	
	cout<<"main window destructor"<<endl;
	delete timer;
}


void TMainWindow::MessageReceived(BMessage * mesg)
{
	switch(mesg->what)
	{
		case T_MSG_FRAME:
			gameview->Render();
		break;
	
		
	}	
}


bool TMainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
