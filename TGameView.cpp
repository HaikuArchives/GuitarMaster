

#include "TGameView.h"
#include <iostream>
#include <Region.h>
#include <GL/gl.h>

using namespace org::toxic::graphics;
using namespace org::toxic;
using namespace std;


TGameView::TGameView(BRect frame): BGLView(frame,"game view",B_FOLLOW_ALL_SIDES, 0,BGL_RGB | BGL_DOUBLE)
{
	cout<<"game view"<<endl;
	graphics = new TGraphics();
	
}



TGameView::~TGameView()
{
	cout<<"game view destructor"<<endl;
	delete graphics;
}


void TGameView::Render()
{
	LockGL();
	
	graphics->Draw();
	SwapBuffers();	
	UnlockGL();
	
}


void TGameView::FrameResized(float w,float h)
{
	cout<<"Resized "<<w<<","<<h<<endl;
	
	LockGL();
	graphics->Resize(w,h);
	
	UnlockGL();	
}


void TGameView::AttachedToWindow(void)
{
	BGLView::AttachedToWindow();
	cout<<"Attached to window"<<endl;
	FrameResized(Bounds().right,Bounds().bottom); 	
	
	LockGL();
	graphics->Init();
	UnlockGL();
	
}
