#include "adpcm2pcm.h"
#include "rockwell.cpp"

adpcm2Pcm::adpcm2Pcm()
{
wavtorockwell_init();
}


int adpcm2Pcm::DecodeBuff(BYTE *abIn, int nInLen, short *abOut)
{
    int   nOutLen = 0;
    char  tmp;
    int nFrame = (nInLen - 1) / PAGE_TOTAL_SIZE + 1;
    while (nFrame--)
    {
        abIn += (PAGE_TOTAL_SIZE - PAGE_DATA_SIZE);
        nInLen = PAGE_DATA_SIZE;
        while (nInLen--)
        {
            tmp = *abIn++;
            *abOut++ = rockwelltowav(tmp & 0x0F);
            tmp >>= 4;
            *abOut++ = rockwelltowav(tmp);
            nOutLen += 4;
        }
    }
    return nOutLen;
}

