

#include "TGameView.h"
#include <iostream>
#include <Region.h>
#include <GL/gl.h>

using namespace org::toxic;
using namespace std;


TGameView::TGameView(BRect frame): BGLView(frame,"game view",B_FOLLOW_ALL_SIDES, 0,BGL_RGB | BGL_DOUBLE)
{
	cout<<"game view"<<endl;
	
}



TGameView::~TGameView()
{
	cout<<"game view destructor"<<endl;
}


void TGameView::Render()
{
	LockGL();
	
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	UnlockGL();
	SwapBuffers(true);
}


void TGameView::FrameResized(float x,float y)
{
	cout<<"Resized "<<x<<","<<y<<endl;	
}


void TGameView::AttachedToWindow(void)
{
	BGLView::AttachedToWindow();
	cout<<"Attached to window"<<endl; 	
}
