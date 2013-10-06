#ifdef __WAND__
dependencies[scale.o]
target[name[scale.h] type[include]]
#endif

#ifndef SCALE_H
#define SCALE_H

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
	namespace Scale
		{
		/**Creates a new scale.
		* \param key is the chosen key.
		* \param min is the lowest note relative to key.
		* \param max is the highest note relative to key.
		*/
		Noteset make(char_t key,Keymode mode,int min,int max);
		}
	}

#endif
