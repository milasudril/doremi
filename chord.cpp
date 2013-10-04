#ifdef __WAND__
target[name[chord.o] type[object]]
#endif

#include "chord.h"

#include <herbs/string.h>
#include <herbs/exceptionmissing.h>

#include <herbs/stringformat.h>
#include <herbs/intformat.h>
#include <herbs/application.h>
#include <herbs/findbinary.h>

namespace
	{
	const uint8_t keys[7]={0,2,3,5,7,8,10};
	uint8_t keySet(char_t key,Doremi::Chord::Keymode mode)
		{
		return keys[key-CHAR('A')]+(int8_t)mode;
		}
		
	struct Chordtype
		{
		const char_t* name;
		static const uint8_t N_NOTES=4;	
		uint8_t index[N_NOTES];
		};
	
	
	bool operator<(const Chordtype& type,const char_t* str)
		{
		return Herbs::String::compare(type.name,str)<0;
		}
	
	bool operator==(const Chordtype& type,const char_t* str)
		{
		return Herbs::String::compare(type.name,str)==0;
		}
	
	static const uint8_t N_TYPES=11;
	static const Chordtype chord_type_lookup[N_TYPES]=
		{
			 {STR(""),{0,4,7}}
		    ,{STR("7"),{0,4,7,10}}
			,{STR("aug"),{0,4,8}}
			,{STR("dim"),{0,3,6}}
			,{STR("dim7"),{0,3,6,9}}
			,{STR("m"),{0,3,7}}
			,{STR("m7"),{0,3,7,10}}
			,{STR("m7-5"),{0,3,6,10}}
			,{STR("maj7"),{0,4,7,11}}
			,{STR("sus4"),{0,5,7}}
			,{STR("sus47"),{0,5,7,10}}
		};
		
	
	Doremi::Noteset notesetMake(uint8_t key,const char_t* i)
		{
		Doremi::Noteset ret(Chordtype::N_NOTES);
		auto chord_type=Herbs::findBinary(chord_type_lookup
			,chord_type_lookup+N_TYPES,i);
		Herbs::application().sysout().print
			(
			Herbs::format
				(
				 STR("%4: %0 %1 %2 %3")
				,
					{
					 Herbs::IntFormat<int>(chord_type->index[0])
					,Herbs::IntFormat<int>(chord_type->index[1])
					,Herbs::IntFormat<int>(chord_type->index[2])
					,Herbs::IntFormat<int>(chord_type->index[3])
					,Herbs::IntFormat<const void*>(chord_type,16)
					}
				)
			);
		return ret;
		}
	
	}

Doremi::Noteset Doremi::Chord::make(const Herbs::String& symbol)
	{
	size_t pos=0;
	uint8_t m_key=0;
	Noteset ret(Chordtype::N_NOTES);
	ret.noteBaseSet(69-12);
	auto i=symbol.begin();
	while(i!=symbol.end())
		{
		switch(pos)
			{
			case 0:
				if(*i<'A' || *i>'G')
					{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
				m_key=keySet(*i, Keymode::NORMAL);
				break;
			case 1:
				switch(*i)
					{
					case CHAR('#'): //Accept # and b for convinience
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
					default:
						return notesetMake(m_key,i);
					}
				break;
			default:
				return notesetMake(m_key,i);
			}
		++i;
		++pos;
		}
	return notesetMake(m_key,i);
	}

