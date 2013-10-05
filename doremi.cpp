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

#include <windows.h>

void Doremi::Doremi::init(Herbs::Directory&& options)
	{
	midi_out=Midiport::deviceFind(Herbs::String(STR("UA-25")));
	sysout().print(Herbs::format(STR("Found %0 at slot %1")
		,{STR("UA-25"),Herbs::IntFormat<unsigned int>(midi_out)}));
	}

void chordsPlay(const Doremi::Noteset* begin,const Doremi::Noteset* end
,Doremi::Midiport& device)
	{
	while(begin!=end)
		{
		for(size_t i=0;i<begin->nNotes();++i)
			{
			device.noteOn(0,(*begin)[i],1);
			}
		Sleep(2000);
		for(size_t i=0;i<begin->nNotes();++i)
			{
			device.noteOff(0,(*begin)[i],1);
			}		
		++begin;
		}
	}


int Doremi::Doremi::run()
	{
	Midiport synth(midi_out);
	synth.programChange(0,50);
	
	Noteset chords[11]=
		{
		 Chord::make(Herbs::String(STR("A")))
		,Chord::make(Herbs::String(STR("A7")))
		,Chord::make(Herbs::String(STR("Aaug")))
		,Chord::make(Herbs::String(STR("Adim")))
		,Chord::make(Herbs::String(STR("Adim7")))
		,Chord::make(Herbs::String(STR("Am")))
		,Chord::make(Herbs::String(STR("Am7")))
		,Chord::make(Herbs::String(STR("Am7-5")))
		,Chord::make(Herbs::String(STR("Amaj7")))
		,Chord::make(Herbs::String(STR("Asus4")))
		,Chord::make(Herbs::String(STR("Asus47")))
		};
	
	chordsPlay(chords,chords+11,synth);
	
	Noteset chords2[7*3]=
		{
		 Chord::make(Herbs::String(STR("A")))
		,Chord::make(Herbs::String(STR("A#")))
		,Chord::make(Herbs::String(STR("Ab")))
		,Chord::make(Herbs::String(STR("B")))
		,Chord::make(Herbs::String(STR("B#")))
		,Chord::make(Herbs::String(STR("Bb")))
		,Chord::make(Herbs::String(STR("C")))
		,Chord::make(Herbs::String(STR("C#")))
		,Chord::make(Herbs::String(STR("Cb")))
		,Chord::make(Herbs::String(STR("D")))
		,Chord::make(Herbs::String(STR("D#")))
		,Chord::make(Herbs::String(STR("Db")))
		,Chord::make(Herbs::String(STR("E")))
		,Chord::make(Herbs::String(STR("E#")))
		,Chord::make(Herbs::String(STR("Eb")))
		,Chord::make(Herbs::String(STR("F")))
		,Chord::make(Herbs::String(STR("F#")))
		,Chord::make(Herbs::String(STR("Fb")))
		,Chord::make(Herbs::String(STR("G")))
		,Chord::make(Herbs::String(STR("G#")))
		,Chord::make(Herbs::String(STR("Gb")))
		};
	
	chordsPlay(chords2,chords2+21,synth);
	
	
	return STATUS_OK;
	}

void Doremi::Doremi::destroy()
	{
	delete this;
	}
