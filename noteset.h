#ifdef __WAND__
target[name[noteset.h] type[include]]
#endif

#ifndef NOTESET_H
#define NOTESET_H

#include <herbs/array.h>

namespace Doremi
	{
	class Noteset
		{
		public:
			Noteset(size_t N):data_array(N){}
			
			Noteset& noteBaseSet(unsigned int note)
				{
				note_base=note;
				return *this;
				}
			
			unsigned noteBaseGet() const
				{return note_base;}
			
			Noteset& append(unsigned int note)
				{
				data_array.append(note);
				return *this;
				}
		
			unsigned int operator[](size_t index) const
				{return data_array[index] + note_base;}
			
			size_t nNotes() const
				{return data_array.length();}
			
		private:
			unsigned int note_base;
			Herbs::Array<unsigned int> data_array;
		};
	};

#endif
