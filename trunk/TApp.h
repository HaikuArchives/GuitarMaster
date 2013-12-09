/*
* Application core class
*/

#ifndef _TApp_
#define _TApp_

#include <String.h>
#include <Application.h>
#include "TMainWindow.h"

namespace org
{
	namespace toxic
	{
		class TApp : public BApplication
		{
			private:
			TMainWindow * window;
			BString * UserSpecifiedSongDir;
			public:
		
			TApp(BString * UserSpecifiedSongDir = NULL);
			~TApp();
			
			virtual void ReadyToRun();
		
		};
	}
}

#endif
