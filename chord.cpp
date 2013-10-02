#ifdef __WAND__
target[name[chord.o] type[object]]
#endif

#include "chord.h"

#include <herbs/string.h>
#include <herbs/exceptionmissing.h>

#include <herbs/stringformat.h>
#include <herbs/intformat.h>
#include <herbs/application.h>

const uint8_t Doremi::Chord::keys[7]=
	{
	0,2,3,5,7,8,10
	};

Doremi::Chord::Chord(const Herbs::String& symbol)
	{
	auto i=symbol.begin();
	size_t pos=0;
	m_mode=0;
	while(i!=symbol.end())
		{
		if(pos==0)
			{
			if(*i<'A' || *i>'G')
				{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
			keySet(*i, Keymode::NONE);
			}
		else
			{
			switch(*i)
				{
				case CHAR('#'):
				case CHAR('♯'):
					m_key=(m_key+1);
					if(m_key > 11)
						{m_key=0;}
					break;
				case CHAR('b'):
				case CHAR('♭'):
					m_key=(m_key-1)%12;
					if(m_key == 255)
						{m_key=11;}
					break;
				case CHAR('m'):
					m_mode|=MODE_MINOR;
					break;
				case CHAR('7'):
					m_mode|=MODE_SEVEN;
					break;
				case CHAR('d'):
					m_mode|=MODE_DIM;
					break;
				case CHAR('5'):
					m_mode|=MODE_MINUS5;
					break;
				default:
					throw Herbs::ExceptionMissing(___FILE__,__LINE__);
				}
			}
		
		++i;
		++pos;
		}
	Herbs::application().sysout().print(Herbs::format(STR("Key: %0. Mode %1")
		,{Herbs::IntFormat<int>(m_key),Herbs::IntFormat<int>(m_mode,16)}));
	}

void Doremi::Chord::play(Midiport& port,unsigned int channel)
	{}

void Doremi::Chord::stop(Midiport& port,unsigned int channel)
	{}
