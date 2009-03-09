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
	ReadChunk();
	ReadChunk();
	ReadChunk();	
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
	
	id=SwapUint(id);
	size=SwapUint(size);
	
	switch(id)
	{
		case MIDI_HEAD_CHUNK:
			ReadHeader();
		break;
		
		case MIDI_TRACK_CHUNK:
			ReadTrack(size);
		break;
	
	
	default:
	cout<<"Unknown chunk id "<<hex<<id<<endl;	
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
	
	type=SwapUshort(type);
	tracks=SwapUshort(type);
	division=SwapUshort(division);
	
	cout<<"type "<<type<<endl;
	cout<<"tracks "<<tracks<<endl;
	cout<<"division "<<division<<endl;
	 
		
}


void TMidiReader::ReadTrack(int size)
{
	unsigned int delta;
	unsigned char type;
	unsigned char channel;
	unsigned char p1;
	unsigned char p2;
	unsigned int tmp = 0;
	
	off_t block = file->Position() + size;
	
	cout<<"Reading Track"<<endl;
	
	while(file->Position()<block)
	{
		
		
		file->Read(&tmp,1);
		delta=tmp;
		if(tmp>0x80)
		{
			file->Read(&tmp,1);
			delta += tmp<<8;
		}
		//TODO
		
		file->Read(&tmp,1);
		type=tmp & 0x000000F0;
		type=type>>4;
		channel=tmp&0x0000000F;
		
		file->Read(&p1,1);
		file->Read(&p2,1);
		
		
		switch(type)
		{
			case 0x8:
				cout<<"Note Off "<<hex<<((int)p1)<<endl;
			break;
			
			case 0x9:
				cout<<"Note On "<<hex<<((int)p1)<<endl;
			break;
			
			
		
			default:
			cout<<"Unknown event :"<<hex<<((int)type)<<endl;	
		}
		
	}
	
}

unsigned short TMidiReader::SwapUshort(unsigned short d)
{
	unsigned short tmp;
	unsigned short res;
	
	tmp = 0x00FF & d;
	tmp = tmp<<8;
	res=tmp;
	
	tmp = 0xFF00 & d;
	tmp = tmp>>8;
	res+=tmp;
	
	return res;
}

unsigned int TMidiReader::SwapUint(unsigned int d)
{
	unsigned int tmp;
	unsigned int res;
	
	tmp = 0x000000FF & d;	
	tmp=tmp<<24;
	res=tmp;
	
	tmp = 0x0000FF00 & d;	
	tmp=tmp<<8;
	res+=tmp;
	
	tmp = 0x00FF0000 & d;	
	tmp=tmp>>8;
	res+=tmp;
	
	tmp = 0xFF000000 & d;	
	tmp=tmp>>24;
	res+=tmp;
	
	return res;
	
	
}

				