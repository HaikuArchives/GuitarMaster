


#include "TMainWindow.h"
#include "TMidiReader.h"
#include <Application.h>
#include <MenuItem.h>
#include <MenuBar.h>
#include <Menu.h>
#include <Directory.h>
#include <String.h>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>

using namespace org::toxic;
using namespace org::toxic::resources;
using namespace std;


TMainWindow::TMainWindow(BRect frame, BString * UserSpecifiedSongDir): BWindow(frame,"Guitar Master",B_TITLED_WINDOW,B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
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
	
	BString homeDir = getenv("HOME");
	if(homeDir == NULL) {
		struct passwd *pw = getpwuid(getuid());
		homeDir = pw->pw_dir;
 	}
	
	BString * songLocations[13];
	songLocations[0] = UserSpecifiedSongDir;
	songLocations[1] = new BString("songs");
	songLocations[2] = new BString("/music/GuitarMaster");
	songLocations[2]->Prepend(homeDir);
	songLocations[3] = new BString("/music/guitarmaster");
	songLocations[3]->Prepend(homeDir);
	songLocations[4] = new BString("/music/Guitar Master");
	songLocations[4]->Prepend(homeDir);
	songLocations[5] = new BString("/music/guitar master");
	songLocations[5]->Prepend(homeDir);
	songLocations[6] = new BString("/Music/GuitarMaster");
	songLocations[6]->Prepend(homeDir);
	songLocations[7] = new BString("/Music/guitarmaster");
	songLocations[7]->Prepend(homeDir);
	songLocations[8] = new BString("/Music/Guitar Master");
	songLocations[8]->Prepend(homeDir);
	songLocations[9] = new BString("/Music/guitar master");
	songLocations[9]->Prepend(homeDir);
	songLocations[10] = new BString("/music");
	songLocations[10]->Prepend(homeDir);
	songLocations[11] = new BString("/Music");
	songLocations[11]->Prepend(homeDir);
	songLocations[12] = new BString(homeDir);
	
	cout<<"Searching for songs directory..."<<endl;
	
	BDirectory * songs_dir_check;
	for(int i=0; i<sizeof(songLocations)/sizeof(BString *); i++) {
		if(songLocations[i] != NULL) {
			cout<<"  Checking "<<songLocations[i]->String()<<endl;
			songs_dir_check = new BDirectory(songLocations[i]->String());
			if(songs_dir_check->InitCheck() == B_OK) {
				SongsDirLocation = new BString(*songLocations[i]);
				delete songs_dir_check;
				break;
			}
			delete songs_dir_check;
		}
	}
	
	for(int i=0; i<sizeof(songLocations)/sizeof(BString *); i++) {
		delete songLocations[i];
	}
	
	cout<<"Reading songs directory..."<<endl;
	
	BDirectory songs_dir(SongsDirLocation->String());
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
			
			spath<<SongsDirLocation->String()<<"/"<<str<<"/notes.mid";
			
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
