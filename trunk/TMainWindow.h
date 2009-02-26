

#ifndef _TMainWindow_
#define _TMainWindow_

#include <Window.h>
#include <MessageRunner.h>
#include "TGameView.h"

#define T_MSG_FRAME 0xFF00FFAA

namespace org
{
	namespace toxic
	{
		class TMainWindow : public BWindow
		{
			private:
			
			TGameView * gameview;
			BMessageRunner * timer;
				
			public:
		
			TMainWindow(BRect frame);
			~TMainWindow();
			
		
		
			virtual bool QuitRequested();
			virtual void MessageReceived(BMessage * mesg);
			
		}; 	
	}
}


#endif
