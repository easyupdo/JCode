#ifndef ADPCM2PCM_H
#define ADPCM2PCM_H

#include <iostream>
#define DATA_DEGUB

#define		PAGE_TOTAL_SIZE		502
#define		PAGE_DATA_SIZE		480
#define		PAGE_DATA_POS		0

#define		FILE_BUFF_SIZE		(PAGE_TOTAL_SIZE * 8)
#define		DECODE_BUFF_SIZE	(PAGE_DATA_SIZE * 8 * 4)

typedef unsigned char       BYTE;
class adpcm2Pcm
{
public:
    adpcm2Pcm();
    int DecodeBuff(BYTE *abIn, int nInLen, short *abOut);
};

#endif // ADPCM2PCM_H
