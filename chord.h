#ifdef __WAND__
dependencies[chord.o]
target[name[chord.h] type[include]]
#endif

#ifndef CHORD_H
#define CHORD_H

#include "playable.h"
#include <herbs/chartype.h>

namespace Herbs
	{
	template<class T>
	class Stringbase;
	
	typedef Stringbase<char_t> String;
	}

namespace Doremi
	{
	class Midiport;
	
	class Chord:public Playable
		{
		public:
			enum class Keymode{FLAT=-1, NONE=0, SHARP=1};
		
			Chord(const Herbs::String& symbol);
		
			void play(Midiport& port,unsigned int channel);
			void stop(Midiport& port,unsigned int channel);
			
			Chord& keySet(char_t key,Keymode mode)
				{
				m_key=(keys[ (key-CHAR('A'))%7 ] + (char_t)(mode));
				return *this;
				}
			

		private:
			static const uint8_t MODE_MINOR=0x1;
			static const uint8_t MODE_SEVEN=0x2;
			static const uint8_t MODE_DIM=0x4;
			static const uint8_t MODE_MINUS5=0x8;
			
			static const uint8_t keys[7];
		
			int8_t m_key;
			int8_t m_mode;
		};
	}

#endif
