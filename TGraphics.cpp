
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
	
}

void TGraphics::Resize(float w,float h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,100.0f,100.0f,0.0f,1.0f,100.0f);
	glMatrixMode(GL_MODELVIEW);	
}


void TGraphics::Draw()
{
	Clear();
	
	glColor3ub(255,0,0);
	
	glBegin(GL_QUADS);
	glVertex2f(0.0f,20.0f);
	glVertex2f(20.0f,20.0f);
	glVertex2f(20.0f,0.0f);
	glVertex2f(0.0f,0.0f);
	
	glEnd();
	
	
}


void TGraphics::Clear()
{
	
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
