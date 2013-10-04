#ifdef __WAND__

target[
	name[
		doremi.o
	]
	type[
		object
	]
]
#endif


#include "doremi.h"
#include "midiport.h"
#include "chord.h"
#include <herbs/string.h>
#include <herbs/stringformat.h>
#include <herbs/intformat.h>

void Doremi::Doremi::init(Herbs::Directory&& options)
	{
	midi_out=Midiport::deviceFind(Herbs::String(STR("UA-25")));
	sysout().print(Herbs::format(STR("Found %0 at slot %1")
		,{STR("UA-25"),Herbs::IntFormat<unsigned int>(midi_out)}));
	}

int Doremi::Doremi::run()
	{
	Chord::make(Herbs::String(STR("A")));
	Chord::make(Herbs::String(STR("A7")));
	Chord::make(Herbs::String(STR("Aaug")));
	Chord::make(Herbs::String(STR("Adim")));
	Chord::make(Herbs::String(STR("Adim7")));
	Chord::make(Herbs::String(STR("Am")));
	Chord::make(Herbs::String(STR("Am7")));
	Chord::make(Herbs::String(STR("Am7-5")));
	Chord::make(Herbs::String(STR("Amaj7")));
	Chord::make(Herbs::String(STR("Asus4")));
	Chord::make(Herbs::String(STR("Asus47")));
	
	
	return STATUS_OK;
	}

void Doremi::Doremi::destroy()
	{
	delete this;
	}
