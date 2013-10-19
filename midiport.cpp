#ifdef __WAND__
target
	[
	name[midiport.o] type[object] platform[win32]
	dependencies[winmm]
	]
#endif

#include "midiport.h"
#include <herbs/string.h>
#include <herbs/exceptionmissing.h>
#include <herbs/eventqueue.h>
#include <windows.h>



unsigned int Doremi::Midiport::deviceFind(const Herbs::String& name)
	{
	UINT n_devs=midiOutGetNumDevs();
	MIDIOUTCAPS caps;
	unsigned int ret=0;
	while(n_devs)
		{
		midiOutGetDevCaps(ret,&caps,sizeof(caps));
		if(name==Herbs::String(caps.szPname))
			{return ret;}
		++ret;
		--n_devs;
		}
	return -1;
	}

Doremi::Midiport::Midiport(unsigned int id,Herbs::EventQueue& event_queue):
q(event_queue)
	{
	MMRESULT res;
	assert(sizeof(handle)==sizeof(HMIDIOUT));
	res=midiOutOpen((HMIDIOUT*)(&handle),id,0,0,CALLBACK_NULL);
	if(res!=MMSYSERR_NOERROR)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
//	statusReset();
	}

void Doremi::Midiport::statusReset()
	{
	for(unsigned int channel=0;channel<16;++channel)
		{
		for(unsigned int note=0;note<128;++note)
			{
			noteOff(channel,note,1.0f,0);
			}
		programChange(channel,0,0);
		}
	}

namespace
	{
	bool messagePlay(Herbs::EventQueue::Event& event,uintmax_t time_epoch)
		{
		HMIDIOUT port=event.dataGet<HMIDIOUT>(0);
		uint32_t data=event.dataGet<uint32_t>(2);
		midiOutShortMsg(port,data);
		return 1;
		}
	}
	
void Doremi::Midiport::messageSend(Message msg,uintptr_t delay)
	{
	Herbs::EventQueue::Event event_next(messagePlay);
	event_next.dataSet(0,handle)
		.dataSet(sizeof(handle)/sizeof(msg.data),msg.data);
	q.entryAdd(Herbs::EventQueue::Entry(delay,event_next));
	}
	
Doremi::Midiport::~Midiport()
	{
	statusReset();
	midiOutClose((HMIDIOUT)handle);
	}
