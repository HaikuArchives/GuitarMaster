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
