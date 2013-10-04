#ifdef __WAND__
dependencies[chord.o]
target[name[chord.h] type[include]]
#endif

#ifndef CHORD_H
#define CHORD_H

#include "noteset.h"
#include <herbs/chartype.h>

namespace Herbs
	{
	template<class T>
	class Stringbase;
	
	typedef Stringbase<char_t> String;
	}

namespace Doremi
	{
	namespace Chord
		{
		const uint8_t MODE_MINOR=0x1;
		const uint8_t MODE_SEVEN=0x2;
		const uint8_t MODE_DIM=0x4;
		const uint8_t MODE_MINUS5=0x8;
		const uint8_t MODE_MAX=0xf;
		
		enum class Keymode{FLAT=-1,NORMAL=0,SHARP=1};
		
		Noteset make(const Herbs::String& symbol);
		Noteset make(unsigned int note,unsigned int mode);
		}
	}

#endif
