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
	bool fpsmode = false;
	
	cout<<"Reading header"<<endl;
	
	file->Read(&type,2);
	file->Read(&tracks,2);
	file->Read(&division,2);
	
	type=SwapUshort(type);
	tracks=SwapUshort(type);
	division=SwapUshort(division);
	
	if(division & 0x8000 == 0x8000)fpsmode = true;
	else fpsmode = false;
	division = division & 0x7FFF;
		

	
	cout<<"type "<<type<<endl;
	cout<<"tracks "<<tracks<<endl;
	
	if(fpsmode)
		cout<<"division "<<division<<" fps"<<endl;
		else
		cout<<"division "<<division<<" ticks per beat"<<endl;
	 
		
}


void TMidiReader::ReadTrack(int size)
{
	unsigned int delta;
	unsigned char type;
	unsigned char channel;
	unsigned char p1;
	unsigned char p2;
	unsigned char meta_event;
	unsigned int meta_event_length;
	unsigned int tmp = 0;
	unsigned char sink[256];
	
	
	off_t block = file->Position() + size;
	
	cout<<"Reading Track"<<endl;
	
	while(file->Position()<block)
	{
		
		//This variable length reader can be improved :)
		file->Read(&tmp,1);
		delta=tmp;
		if(tmp > 127)
		{
			file->Read(&tmp,1);
			delta = ((delta & 0x0000007F)<<8) | tmp;
		}
		
		
		file->Read(&tmp,1);
		type=tmp & 0x000000F0;
		type=type>>4;
		channel=tmp&0x0000000F;
		
		
		
		
		//cout<<"Event: "<<hex<<(int)type<<","<<(int)p1<<","<<(int)p2<<endl;
		
		//event case
		switch(type)
		{
			case 0xF:
				file->Read(&meta_event,1);
				
				file->Read(&tmp,1);
				meta_event_length=tmp;
				if(tmp & 0x80)
				{
					file->Read(&tmp,1);
					meta_event_length = tmp | (meta_event_length<<8);
				}
				if(meta_event_length>0)
					file->Read(sink,meta_event_length);
					
				//meta event case	
				switch(meta_event)
				{
					case 0x51:
					tempo=sink[0] | (sink[1]<<8) | (sink[2]<<16);
					tempo = 60000000 / tempo;
					cout<<delta<<" Set Tempo: "<<(unsigned int)tempo<< " bpm"<<endl;
					break;
					
					default:
					cout<<delta<<" Meta event: "<<(int)meta_event<<endl;
					break;
				}	
					
			break;
			
			case 0x8:
				file->Read(&p1,1);
				file->Read(&p2,1);
				cout<<delta<<" Note Off "<<((int)p1)<<endl;
			break;
			
			case 0x9:
				file->Read(&p1,1);
				file->Read(&p2,1);
				cout<<delta<<" Note On "<<((int)p1)<<endl;
			break;
			
			
		
			//default:
			//cout<<"Unknown event :"<<((int)type)<<endl;	
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

				
