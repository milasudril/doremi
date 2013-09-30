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
			{noteOff(channel,note,1.0f);}
		}
	}

void Doremi::Midiport::noteOff(unsigned int channel,unsigned int note,float value)
	{
	messageSend(messageChannelBuild(channel,0x80,note,(char)(127*value)));
	}

void Doremi::Midiport::noteOn(unsigned int channel,unsigned int note,float value)
	{
	messageSend(messageChannelBuild(channel,0x90,note,(char)(127*value)));
	}

void Doremi::Midiport::programChange(unsigned int channel,unsigned int program)
	{
	messageSend(messageChannelBuild(channel,0xc0,program,0));
	}
	
void Doremi::Midiport::messageSend(Doremi::Midiport::Message msg)
	{
	midiOutShortMsg((HMIDIOUT)handle,msg.data.value);
	}

	
Doremi::Midiport::~Midiport()
	{
	midiOutClose((HMIDIOUT)handle);
	}
