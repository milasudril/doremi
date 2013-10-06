#ifdef __WAND__
dependencies[chord.o]
target[name[chord.h] type[include]]
#endif

#ifndef CHORD_H
#define CHORD_H

#include "noteset.h"
#include "key.h"
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
		
		
		Noteset make(const Herbs::String& symbol);
		Noteset make(unsigned int note,Keymode mode);
		}
	}

#endif
