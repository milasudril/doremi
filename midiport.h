#ifdef __WAND__
dependencies[midiport.o]
target[name[midiport.h] type[include]]
#endif

#ifndef MIDIPORT_H
#define MIDIPORT_H

#include <herbs/chartype.h>
#include <deque>
#include <utility>

namespace Herbs
	{
	template<class T>
	class Stringbase;
	
	typedef Stringbase<char_t> String;
	
	class EventQueue;
	}

namespace Doremi
	{
	/**MIDI I/O class.
	*/
	class Midiport
		{
		public:
			struct Message
				{
				Message(uint8_t byte_0,uint8_t byte_1,uint8_t byte_2)
					{
					data.bytes[0]=byte_0;
					data.bytes[1]=byte_1;
					data.bytes[2]=byte_2;
					data.bytes[3]=0;
					}
				union
					{
					uint8_t bytes[4];
					uint32_t value;
					} data;
				};
			
			static unsigned int deviceFind(const Herbs::String& name);
			
			/**Initiates midiport id.
			* \param ticlenth is the delay between tics in seconds.
			*/
			Midiport(unsigned int id, Herbs::EventQueue& event_queue);
			
			Midiport(const Midiport&)=delete;
			Midiport& operator=(const Midiport& port)=delete;
			
			~Midiport();
			
			void statusReset();
			void noteOn(unsigned int channel,unsigned int note
				,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0x90,note,midiVal(value)),delay);}
				
			void noteOff(unsigned int channel,unsigned int note
				,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0x80,note,midiVal(value)),delay);}
				
			void aftertouch(unsigned int channel,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xD0,midiVal(value),0),delay);}
				
			void aftertouch(unsigned int channel,unsigned int note
				,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xA0,note,midiVal(value)),delay);}
				
			void programChange(unsigned int channel,unsigned int program
				,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xC0,program,0),delay);}
			
			void pitchBend(unsigned int channel,float value,uintptr_t delay);
			
			void bankSelect(unsigned int channel,unsigned int bank,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xB0,0x00,bank),delay);}
			
			void modwheel(unsigned int channel,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xB0,0x01,midiVal(value)),delay);}

			void breath(unsigned int channel,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0xB0,0x02,midiVal(value)),delay);}
			void foot(unsigned int channel,float value,uintptr_t delay)
				{messageSend(messageChannelBuild(channel,0XB0,0x04,midiVal(value)),delay);}
				
			void portamento(unsigned int channel,float value,uintptr_t delay);
			void volume(unsigned int channel,float value,uintptr_t delay);
			void balance(unsigned int channel,float value,uintptr_t delay);
			void pan(unsigned int channel,float value,uintptr_t delay);
			void sustain(unsigned int channel, float value,uintptr_t delay);
			
			Message messageChannelBuild(unsigned int channel,unsigned int code
				,unsigned int v_0,unsigned int v_1)
				{
				return Message(channel|code,v_0,v_1);
				}
			
			void messageSend(Message msg,uintptr_t delay);
			
			uint8_t midiVal(float x)
				{return (uint8_t)(x*127);}
			
			
		private:
			Herbs::EventQueue& q;
			void* handle;
		};
	}

#endif
