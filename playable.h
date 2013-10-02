#ifdef __WAND__
target[type[include] name[playable.h]]
#endif

#ifndef PLAYABLE_H
#define PLAYABLE_H

namespace Doremi
	{
	class Midiport;
	class Playable
		{
		public:
			virtual void play(Midiport& port,unsigned int channel)=0;
			virtual void stop(Midiport& port,unsigned int channel)=0;
			
		};
	};

#endif
