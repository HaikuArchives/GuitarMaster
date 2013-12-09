/*
* Guitar Master for Haiku
* Toxic Labs
*/

#include <String.h>
#include "TApp.h"

using namespace org::toxic;

int main (int argc,char * argv[])
{
	BString * UserSpecifiedSongDir;
	UserSpecifiedSongDir = NULL;
	// see if song directory was specified
	if(argc > 1)
	{
		UserSpecifiedSongDir = new BString(argv[1]);
	}
	
	TApp app(UserSpecifiedSongDir);
	
	app.Run();


return 0;	
}
