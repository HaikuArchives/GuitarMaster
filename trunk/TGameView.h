#ifndef TGAMEVIEW_H
#define TGAMEVIEW_H

#include <GLView.h>
#include "TGraphics.h"

namespace org
{
	namespace toxic
	{
		class TGameView : public BGLView
		{
			private:
			graphics::TGraphics * graphics;
			
			public:
			
			TGameView(BRect frame);
			~TGameView();
			
			void Render(void);
			
			virtual void FrameResized(float w,float h);
			virtual void AttachedToWindow(void);
			
		};
	}
	
	
}

#endif
