#ifdef __WAND__

dependencies[
	doremi.o
]
target[
	name[
		doremi.h
	]
	type[
		include
	]
]
#endif

#ifndef guard_doremi_H
#define guard_doremi_H

#include <herbs/application.h>

namespace Doremi
	{
	class Doremi:public Herbs::Application
		{
		public:
			void init(Herbs::Directory&& options);
			int run();
			void destroy();
		private:
			unsigned int midi_out;
		};
	}

#endif
