#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int main()
{
	int nHeight = 512;
	int nWidth = 512;

	unsigned char* RGB = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth*3));

	unsigned char* ch_in_1 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_2 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_3 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));

	FILE* input;
	fopen_s(&input, "lena512.rgb", "rb");
	fread(RGB, 512*512*3, sizeof(unsigned char), input);
	cout << "파일 입력" << endl;
	fclose(input);
	
	for (int i = 0; i < nHeight*nWidth*3; i++)
	{
		if (i % 3 == 0)ch_in_3[i/3] = RGB[i];//b
		else if (i % 3 == 1)ch_in_2[i/3] = RGB[i];//g
		else if (i % 3 == 2)ch_in_1[i/3] = RGB[i];//r
	}

	for (int i = 0; i < nHeight*nWidth; i++)
	{
		if (ch_in_3[i] <= 50) ch_in_3[i] = round(0.5*ch_in_3[i]);
		else if (ch_in_3[i] > 50 && ch_in_3[i] <= 120) ch_in_3[i] = round((double)175 / 70 * (ch_in_3[i] - 50) + 25);
		else if (ch_in_3[i] > 120) ch_in_3[i] = round((double)55 / 135*(ch_in_3[i] - 120) + 200);

		if (ch_in_2[i] <= 50) ch_in_2[i] = round(0.5*ch_in_2[i]);
		else if (ch_in_2[i] > 50 && ch_in_2[i] <= 120) ch_in_2[i] = round((double)175 / 70 * (ch_in_2[i] - 50) + 25);
		else if (ch_in_2[i] > 120)ch_in_2[i] = round((double)55 / 135*(ch_in_2[i] - 120) + 200);

		if (ch_in_1[i] <= 50) ch_in_1[i] = round(0.5*ch_in_1[i]);
		else if (ch_in_1[i] > 50 && ch_in_1[i] <= 120) ch_in_1[i] = round((double)175 / 70 * (ch_in_1[i] - 50) + 25);
		else if (ch_in_1[i]> 120)ch_in_1[i] = round((double)55 / 135 * (ch_in_1[i] - 120) + 200);
	}

	for (int i = 0; i < nHeight*nWidth*3; i++)
	{
		if (i % 3 == 0)RGB[i]= (unsigned char)ch_in_3[i / 3];
		else if (i % 3 == 1)RGB[i]= (unsigned char)ch_in_2[i / 3];
		else if (i % 3 == 2)RGB[i]= (unsigned char)ch_in_1[i / 3];
	}

	FILE* output;
	fopen_s(&output, "result.rgb", "wb");
	fwrite(RGB, 512 * 512 * 3, sizeof(unsigned char), output);
	cout << "파일 출력" << endl;
	fclose(output);
	//0 , 0  50 25    120 200  255,255

	delete[] RGB;
	delete[] ch_in_1;
	delete[] ch_in_2;
	delete[] ch_in_3;
	return 0;
}

