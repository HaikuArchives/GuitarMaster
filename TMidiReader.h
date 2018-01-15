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

#ifndef TMIDIREADER_H
#define TMIDIREADER_H

#include <File.h>

#define MIDI_HEAD_CHUNK 0x4D546864
#define MIDI_TRACK_CHUNK 0x4D54726B

namespace org
{
	namespace toxic
	{
		namespace resources
		{
			
			class TMidiNote
			{
				public:
				unsigned int delta;
				unsigned char type;
				unsigned char note;
				
			};
			
			
			class TMidiReader
			{
				private:
				
				unsigned int tempo;
				
				BFile * file;
				
				bool ReadChunk();
				void ReadHeader();
				void ReadTrack(int size);
				
				unsigned int SwapUint(unsigned int d);
				unsigned short SwapUshort(unsigned short d);
				
				public:
				
				
				TMidiReader(const char * file);
				~TMidiReader();
				
				void Close();
				
				
			};
		}
		
	}	
}


#endif
