#ifdef __WAND__
target[name[midiport.o] type[object] platform[win32]
dependencies[winmm]]
#endif

#include "midiport.h"
#include <herbs/string.h>
#include <herbs/exceptionmissing.h>
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

Doremi::Midiport::Midiport(unsigned int id)
	{
	MMRESULT res;
	assert(sizeof(handle)==sizeof(HMIDIOUT));
	res=midiOutOpen((HMIDIOUT*)(&handle),id,0,0,CALLBACK_NULL);
	if(res!=MMSYSERR_NOERROR)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	statusReset();
	}

void Doremi::Midiport::statusReset()
	{
	for(unsigned int channel=0;channel<16;++channel)
		{
		for(unsigned int note=0;note<128;++note)
			{
			noteOff(channel,note,1.0f);
			Sleep(1);
			}
		programChange(channel,0);
		Sleep(1);
		}
	}
	
static void peak(void* handle,std::deque<std::pair<unsigned int,Doremi::Midiport::Message>& msg)
	{
	if(msg.empty())
		{return;}
	auto message=msg.first();

	do
		{
		if(message.first)
			{
			Sleep(250); //Use interval timer!
			--message.first;
			}
		else
			{
			msg.pop_front();
			midiOutShortMsg((HMIDIOUT)handle,message.second.data.value);
			message=msg.first();
			}
		}
	while(!msg.empty());
	}

	
Doremi::Midiport::~Midiport()
	{
	statusReset();
	midiOutClose((HMIDIOUT)handle);
	}
