


#include "TMainWindow.h"
#include "TMidiReader.h"
#include <Application.h>
#include <MenuItem.h>
#include <MenuBar.h>
#include <Menu.h>
#include <Directory.h>
#include <String.h>
#include <iostream>

using namespace org::toxic;
using namespace org::toxic::resources;
using namespace std;


TMainWindow::TMainWindow(BRect frame): BWindow(frame,"Guitar Master",B_TITLED_WINDOW,B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	cout<<"Main window"<<endl;
	
	
	timer = new BMessageRunner(this,new BMessage(T_MSG_FRAME),50000,-1);
	
	
	
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
	cout<<"Reading songs directory..."<<endl;
	
	BDirectory songs_dir("songs");
	BEntry entry;
	char str[B_FILE_NAME_LENGTH];
	BMessage * message;
	
	if(songs_dir.InitCheck()!=B_OK)
	{
		cout<<"Songs dir not found"<<endl;	
	}
	else
	{
		int num = songs_dir.CountEntries();
		cout<<"Found :"<<num<<endl;
		
		for(int i=0;i<num;i++)
		{
			songs_dir.GetNextEntry(&entry,false);
			entry.GetName(str);
			cout<<"name: "<<str<<endl;
			
			message = new BMessage(T_MSG_SELECT_SONG);
			message->AddString("song",str);
			item = new BMenuItem(str,message);
			menu->AddItem(item);
				
		}	
	}
	menubar->AddItem(menu);
	
	//Play menu
	menu = new BMenu("Play");
	item = new BMenuItem("Easy",NULL);
	menu->AddItem(item);
	item = new BMenuItem("Normal",NULL);
	menu->AddItem(item);
	item = new BMenuItem("Amazing",NULL);
	menu->AddItem(item);
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
	const char * str;
	BString spath;
	
	switch(mesg->what)
	{
		case T_MSG_FRAME:
			gameview->Render();
		break;
		
		case T_MSG_SELECT_SONG:
			mesg->FindString("song",&str);
			
			spath<<"songs/"<<str<<"/notes.mid";
			
			cout<<"Selected: "<<spath.String()<<endl;
			
			TMidiReader * reader = new TMidiReader(spath.String());
			delete reader;
			
		break;
	
		
	}	
}


bool TMainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
