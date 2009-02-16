#ifndef TGAMEVIEW_H
#define TGAMEVIEW_H

#include <GLView.h>

namespace org
{
	namespace toxic
	{
		class TGameView : public BGLView
		{
			private:
			int x;
			
			public:
			
			TGameView(BRect frame);
			~TGameView();
			
			void Render(void);
			
			virtual void FrameResized(float x,float y);
			virtual void AttachedToWindow(void);
			
		};
	}
	
	
}

#endif
