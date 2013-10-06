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
#include "scale.h"
#include <herbs/string.h>
#include <herbs/stringformat.h>
#include <herbs/intformat.h>

#include <windows.h>

void Doremi::Doremi::init(Herbs::Directory&& options)
	{
	midi_out=Midiport::deviceFind(Herbs::String(STR("UA-25")));
	sysout().print(Herbs::format(STR("Found %0 at slot %1")
		,{STR("UA-25"),Herbs::IntFormat<unsigned int>(midi_out)}));
	}



int Doremi::Doremi::run()
	{
	Midiport synth(midi_out);
	Noteset scale=Scale::make(CHAR('C'),Keymode::NORMAL,-5,1);
	sysout().print(Herbs::String(Herbs::IntFormat<int>(scale.nNotes())));
	int i_prev=5;
	while(1)
		{
		int i=0.5*(rand()%16 + i_prev);
		synth.noteOn(0,scale[i],1);
		Sleep(500);
		synth.noteOff(0,scale[i],1);
		i_prev=i;
		}
	
	return STATUS_OK;
	}

void Doremi::Doremi::destroy()
	{
	delete this;
	}
