#ifdef __WAND__
target[ name[scale.o] type[object]]
#endif

#include "scale.h"

namespace
	{
	uint8_t scale[9]={0,2,4,5,6,7,8,9,11};
	
	template<typename V>
	V mod(const V& a, const V& b)
		{
		return (a % b + b) % b;
		}
	}

Doremi::Noteset Doremi::Scale::make(char_t key,Keymode mode,int min,int max)
	{
	int N=max-min+1+9;
	Noteset ret(N);
	ret.noteBaseSet(69-12);
	int i_0=min;
	int add=0;
	int count=0;
	while(i_0<0)
		{
		i_0+=9;
		add+=9;
		++count;
		}
	for(int i=0;i<N;++i)
		{
		int k=(i+min+add)/9 - count;//   (i+min+9)/9 - 1;
		ret.append(12*k+scale[mod((i+min),9)] + keyvalGet(key,mode));
		}
	return ret;
	}
	