/*
* Application core class
*/

#ifndef _TApp_
#define _TApp_

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
			public:
		
			TApp();
			~TApp();
			
			virtual void ReadyToRun();
		
		};
	}
}

#endif
