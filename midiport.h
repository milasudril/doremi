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
	}

namespace Doremi
	{
	/**MIDI I/O class.
	* \todo This class needs a que based on Herbs::Memblock since the que is
	* less likely to grow.
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
			Midiport(unsigned int id /*, double ticlength*/);
			Midiport(const Midiport&)=delete;
			Midiport& operator=(const Midiport& port)=delete;
			
			~Midiport();
			
			void statusReset();
			void noteOn(unsigned int channel,unsigned int note,float value)
				{messageSend(messageChannelBuild(channel,0x90,note,midiVal(value)));}
				
			void noteOff(unsigned int channel,unsigned int note,float value)
				{messageSend(messageChannelBuild(channel,0x80,note,midiVal(value)));}
				
			void aftertouch(unsigned int channel,float value)
				{messageSend(messageChannelBuild(channel,0xD0,midiVal(value),0));}
				
			void aftertouch(unsigned int channel,unsigned int note
				,float value)
				{messageSend(messageChannelBuild(channel,0xA0,note,midiVal(value)));}
				
			void programChange(unsigned int channel,unsigned int program)
				{messageSend(messageChannelBuild(channel,0xC0,program,0));}
			
			void pitchBend(unsigned int channel,float value);
			
			void bankSelect(unsigned int channel,unsigned int bank)
				{messageSend(messageChannelBuild(channel,0XB0,0x00,bank));}
			
			void modwheel(unsigned int channel,float value)
				{messageSend(messageChannelBuild(channel,0XB0,0x01,midiVal(value)));}

			void breath(unsigned int channel,float value)
				{messageSend(messageChannelBuild(channel,0XB0,0x02,midiVal(value)));}
			void foot(unsigned int channel,float value)
				{messageSend(messageChannelBuild(channel,0XB0,0x04,midiVal(value)));}
				
			void portamento(unsigned int channel,float value);
			void volume(unsigned int channel,float value);
			void balance(unsigned int channel,float value);
			void pan(unsigned int channel,float value);
			void sustain(unsigned int channel, float value);
			
			Message messageChannelBuild(unsigned int channel,unsigned int code
				,unsigned int v_0,unsigned int v_1)
				{
				return Message(channel|code,v_0,v_1);
				}
			
			void messageSend(Message msg,unsigned int delay=0)
				{
				messages.push_back(std::pair<unsigned int,Message>(delay,msg));
				}
			
			uint8_t midiVal(float x)
				{return (uint8_t)(x*127);}
			
			
		private:
			std::deque<std::pair<unsigned int,Message> > messages;
			void* handle;
		};
	}

#endif
