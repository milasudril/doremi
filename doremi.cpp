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
#include <herbs/string.h>
#include <herbs/stringformat.h>
#include <herbs/intformat.h>

#include <windows.h>

namespace
	{
	struct Note
		{
		unsigned int value;
		unsigned int duration;
		};
		
	void tunePlay(const Note* tune,const Note* end,Doremi::Midiport& port)	
		{
		while(tune!=end)
			{
			port.noteOn(0,tune->value,1.0f);
			Sleep(tune->duration);
			port.noteOff(0,tune->value,1.0f);
			++tune;
			}
		};
	}

void Doremi::Doremi::init(Herbs::Directory&& options)
	{
	midi_out=Midiport::deviceFind(Herbs::String(STR("UA-25")));
	sysout().print(Herbs::format(STR("Found %0 at slot %1")
		,{STR("UA-25"),Herbs::IntFormat<unsigned int>(midi_out)}));
	}

int Doremi::Doremi::run()
	{
	Midiport output(midi_out);
	Note tune[8]=
		{
			{60,500}
			,{62,500}
			,{64,500}
			,{65,500}
			,{67,500}
			,{69,500}
			,{71,500}
			,{72,500}
		};
	output.programChange(0,81);
	tunePlay(tune,tune+8,output);
	tunePlay(tune,tune+8,output);
	
	return STATUS_OK;
	}

void Doremi::Doremi::destroy()
	{
	delete this;
	}
