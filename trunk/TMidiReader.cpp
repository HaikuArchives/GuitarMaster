#include "TMidiReader.h"

#include <iostream>

#include <File.h>


using namespace org::toxic::resources;
using namespace std;


TMidiReader::TMidiReader(const char * filename)
{
	
	cout<<"Opening MIDI file"<<endl;
	
	file = NULL;
	file = new BFile(filename,B_READ_ONLY);
	
}



TMidiReader::~TMidiReader()
{
	Close();
}

void TMidiReader::Close()
{
	if(file!=NULL)delete file;
}



bool TMidiReader::ReadChunk()
{
	unsigned int id;
	unsigned int size;
	
	file->Read(&id,4);
	file->Read(&size,4);
	
	switch(id)
	{
		case MIDI_HEAD_CHUNK:
			ReadHeader();
		break;
		
		case MIDI_TRACK_CHUNK:
		
		break;
	
	
	default:
	cout<<"Unknown chunk id"<<endl;	
	}
	
	return true;
}


void TMidiReader::ReadHeader()
{
	unsigned short type,tracks,division;
	
	cout<<"Reading header"<<endl;
	
	file->Read(&type,2);
	file->Read(&tracks,2);
	file->Read(&division,2);
	
	cout<<"type "<<type<<endl;
	cout<<"tracks "<<tracks<<endl;
	cout<<"division "<<division<<endl;
	 
		
}


void TMidiReader::ReadTrack()
{
	
}


