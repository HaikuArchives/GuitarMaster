

#ifndef _TMainWindow_
#define _TMainWindow_

#include <Window.h>
#include <MessageRunner.h>
#include <String.h>
#include "TGameView.h"

#define T_MSG_FRAME 0x00FF0011
#define T_MSG_SELECT_SONG 0x00FF0022

namespace org
{
	namespace toxic
	{
		class TMainWindow : public BWindow
		{
			private:
			
			TGameView * gameview;
			BMessageRunner * timer;
			BString * SongsDirLocation;
				
			public:
		
			TMainWindow(BRect frame, BString * songDirectory = NULL);
			~TMainWindow();
			
		
		
			virtual bool QuitRequested();
			virtual void MessageReceived(BMessage * mesg);
			
		}; 	
	}
}


#endif
