#include "stdio.h"
#include "stdint.h"

int main()
{
	uint8_t data[] = {0x01, 0x00, 0xF9, 0xDA, 0xAB};
	uint8_t w_data[24] = {0};
	uint8_t ch_idx = 25; // 27
	uint8_t whitening[7] = {0};
	uint8_t data_bit[24 * 8] = {0};
	uint8_t whitening_data[24*8] = {0};
	uint8_t temp = 0;
	uint32_t i,j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 8; j++)
		{
			data_bit[i*8 + j] = (data[i] >> j) & 0x01;
		}
	}

	printf("Raw data:");
	for(i = 0; i < 40; i++)
	{
		if (!(i%8))
			printf("\r\n");
		printf("%1d ", data_bit[i]);
		w_data[i/8] |= (data_bit[i] << (i%8));

		if (!((i+1)%8))
			printf(" (0x%02x)", w_data[i/8]);
	}
	printf("\r\n");

	whitening[0] = 1;
	for (i = 0; i < 6; i++)
	{
		//whitening[i+1] = (ch_idx >> i) & 0x01;
		whitening[i+1] = (ch_idx & 0x20) >> 5;
		ch_idx = ch_idx << 1;
	}

	printf("\r\nWhitening:\r\n");
	for (i = 0; i < 7; i++)
	{
		printf("%1d ", whitening[i]);
	}
	printf("\r\n");

	for (i = 0; i < 5*8; i++)
	{
		whitening_data[i] = data_bit[i] ^ whitening[6];
		whitening[3] = whitening[3] ^ whitening[6];

		temp = whitening[6];

		for (j = 6; j > 0; j--)
		{
			whitening[j] = whitening[j - 1];
		}
		whitening[0] = temp;
	}

	printf("\r\nWhitening Data:");
	for(i = 0; i < 40; i++)
	{
		if(!(i%8))
			printf("\r\n");
		printf("%1d ", whitening_data[i]);
		w_data[i/8] |= (whitening_data[i] << (i%8));
		if (!((i+1)%8))
			printf(" (0x%02x)", w_data[i/8]);
	}


	printf("\r\n");
}




