#ifdef __WAND__
dependencies[key.o]
target[name[key.h] type[include]]
#endif

#ifndef KEY_H
#define KEY_H

#include <herbs/chartype.h>

namespace Doremi
	{
	enum class Keymode{FLAT=-1,NORMAL=0,SHARP=1};
	
	extern const uint8_t KEYS[7];

	inline int8_t keyvalGet(char_t key,Keymode mode)
		{
		return KEYS[key-CHAR('A')]+(int8_t)mode;
		}
	
	
	}

#endif
