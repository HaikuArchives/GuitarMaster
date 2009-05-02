
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
	glOrtho(0.0f,100.0f,100.0f,0.0f,0.0f,100.0f);
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
	
	glTranslatef(0.0f,10.0f,0.0f);
	DrawUserFret(0);
	glTranslatef(0.0f,20.0f,0.0f);
	DrawUserFret(1);
		
	
}


void TGraphics::Clear()
{
	
	glClearColor(0.3f,0.7f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void TGraphics::DrawUserFret(int color)
{
	glBegin(GL_QUADS);
	
	switch(color)
	{
		case 0:
			glColor3ub(60,255,60);
		break;
		
		case 1:
			glColor3ub(255,60,60);
		break;
	}
	
	glVertex2f(0.0f,0.0f);
	glVertex2f(8.0f,0.0f);
	glVertex2f(8.0f,8.0f);
	glVertex2f(0.0f,8.0f);
		
	
	glEnd();
}
