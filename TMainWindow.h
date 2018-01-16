/*
The MIT License (MIT)

Copyright (c) 2013 quiqueiii

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
