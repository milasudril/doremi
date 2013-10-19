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
#include <herbs/eventqueue.h>
#include <herbs/timer.h>
#include <herbs/thread.h>
#include <eventqueuerunner.h>

#include <windows.h>

void Doremi::Doremi::init(Herbs::Directory&& options)
	{
	midi_out=Midiport::deviceFind(Herbs::String(STR("UA-25")));
	sysout().print(Herbs::format(STR("Found %0 at slot %1")
		,{STR("UA-25"),Herbs::IntFormat<unsigned int>(midi_out)}));
	}

int Doremi::Doremi::run()
	{
	Herbs::EventQueue q_out;
	double T=60.0/(3.0*160.0);

	Herbs::Timer metronome(Herbs::Timer::frequencyGet()*T);
	Midiport synth(midi_out,q_out);
	
	Noteset scale=Scale::make(CHAR('D'),Keymode::SHARP,-5,1);

	EventQueueRunner conductor(metronome,q_out);
	Herbs::Thread player(conductor);
	
	synth.programChange(0,33,0);
	while(1)
		{
		synth.noteOn(0,scale[5]-24,0.5,1);
		synth.noteOff(0,scale[5]-24,0.5,2);
		synth.noteOn(0,scale[7]-24,0.5,1);
		synth.noteOff(0,scale[7]-24,0.5,2);
		synth.noteOn(0,scale[10]-24,0.5,1);
		synth.noteOff(0,scale[10]-24,0.5,2);
		synth.noteOn(0,scale[7]-24,0.5,1);
		synth.noteOff(0,scale[7]-24,0.5,2);
		
		q_out.wait();
		}
	
	printf("Waiting for player thread\n");
	return STATUS_OK;
	}

void Doremi::Doremi::destroy()
	{
	delete this;
	}
