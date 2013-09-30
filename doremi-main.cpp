#ifdef __WAND__

target[
	name[
		doremi.exe
	]
	type[
		application
	]
	platform[
		win32
	]
]
#endif
#ifdef __WAND__

target[
	name[
		doremi
	]
	type[
		application
	]
]
#endif


#include "doremi.h"

#include <herbs/maindefault.h>

Herbs::Application* Herbs::Application::instanceCreate()
	{
	return new Doremi::Doremi();
	}
