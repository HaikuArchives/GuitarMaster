
#include "TGraphics.h"
#include <GL/gl.h>
#include <iostream>


using namespace org::toxic::graphics;
using namespace std;


TGraphics::TGraphics()
{
	
}

TGraphics::~TGraphics()
{
	
}

void TGraphics::Init()
{
	//disabling z-buffering gives some extra performance
	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	//glEnable(GL_DITHER);
	
	
	
	
}

void TGraphics::Resize(float w,float h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f,100.0f,100.0f,-100.0f,0.0f,100.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}


void TGraphics::Draw()
{
	Clear();
	
	
	glBegin(GL_LINES);
	
	//glColor4f(0.0f,0.0f,1.0f,1.0f);
	
	glVertex2f(0.0f,20.0f);
	glVertex2f(100.0f,20.0f);
	
	glVertex2f(0.0f,40.0f);
	glVertex2f(100.0f,40.0f);
	
		
	glVertex2f(0.0f,60.0f);
	glVertex2f(100.0f,60.0f);
	
		
	glVertex2f(0.0f,80.0f);
	glVertex2f(100.0f,80.0f);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	
	glEnd();
	
		
	
}


void TGraphics::Clear()
{
	
	glClearColor(0.3f,0.7f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
