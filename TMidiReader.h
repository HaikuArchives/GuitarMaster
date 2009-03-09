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
			class TMidiReader
			{
				private:
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
