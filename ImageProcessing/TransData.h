#pragma once
#include "TransImage.h"

class TransData
{
public:
	TransData();
	~TransData();
	static bool EnDecOder(Transitions tsYype, typeImgPtr img);

private:
	static void testRLC_Byte(typeImgPtr img);
	static void testRLC_Bit(typeImgPtr img);
	static void testHuffman(typeImgPtr img);
	static void testLZW(typeImgPtr img);
	static void testDPCM(typeImgPtr img);
};

