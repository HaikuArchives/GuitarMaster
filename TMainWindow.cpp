


#include "TMainWindow.h"
#include <Application.h>
#include <MenuItem.h>
#include <MenuBar.h>
#include <Menu.h>
#include <Directory.h>
#include <iostream>

using namespace org::toxic;
using namespace std;


TMainWindow::TMainWindow(BRect frame): BWindow(frame,"Guitar Master",B_TITLED_WINDOW,B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	cout<<"Main window"<<endl;
	
	
	timer = new BMessageRunner(this,new BMessage(T_MSG_FRAME),50000,-1);
	
	BDirectory songs_dir("songs");
	
	if(songs_dir.InitCheck()!=B_OK)
	{
		cout<<"Songs dir not found"<<endl;	
	}
	else
	{
		cout<<"Found :"<<songs_dir.CountEntries()<<endl;	
	}
	
	ResizeTo(640,480);
	
	BRect bounds = Bounds();
	bounds.bottom = bounds.top + 15;
	BMenuBar * menubar = new BMenuBar(bounds,"main menu");
		
	
	BMenu * menu;
	BMenuItem * item;
	
	//Game menu
	menu = new BMenu("Game");
	//----items
	item = new BMenuItem("Quit",new BMessage(B_QUIT_REQUESTED),'Q');
	menu->AddItem(item);
	
	menubar->AddItem(menu);
	
	//Songs menu
	menu = new BMenu("Songs");
	// fill with available song list...
	menubar->AddItem(menu);
	
	AddChild(menubar);
	//menubar->ResizeToPreferred();
	
	//BGLView
	bounds.top=menubar->Bounds().bottom+1;
	bounds.bottom = Bounds().bottom;
	gameview = new TGameView(bounds);
	
	
	
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
