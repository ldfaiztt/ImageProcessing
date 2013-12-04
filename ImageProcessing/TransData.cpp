#include "stdafx.h"
#include "TransData.h"

#include "RLC_BitPlanesEncoder.h"
#include "RLC_BitPlanesDecoder.h"
#include "RLC_BytesEncoder.h"
#include "RLC_BytesDecoder.h"
#include "DPCM_Encoder.h"
#include "DPCM_Decoder.h"
#include "LZW_Encoder.h"
#include "LZW_Decoder.h"
#include "VLC_HuffmanEncoder.h"
#include "VLC_HuffmanDecoder.h"
#include "BitPlaneBuilder.h"

#include "TimeRecorder.h"

TransData::TransData()
{
}


TransData::~TransData()
{
}

void TransData::testRLC_Byte(typeImgPtr img)
{
	ByteVecotrPtr src = img->toByteVector();

	RLC_BytesEncoder rlcE(0, 0xff);
	RLC_BytesDecoder rlcD(0, 0xff);

	TimeRecorder tr;

	/*********************************************************************************/
	/**** encoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	ByteVecotrPtr tmp = rlcE.transitData(src);
	tr.end();

	/*********************************************************************************/
	/**** decoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	ByteVecotrPtr dst = rlcD.transitData(tmp);
	tr.end();
}

void TransData::testRLC_Bit(typeImgPtr img)
{
	vector<BitVectorPtr> bitplanes;
	vector<ByteVecotrPtr> tmps;
	int countTmp = 0;
	BitPlaneBuilder bpB;
	int line_num = bpB.build(img, bitplanes);
	bool preBit = false;

	TimeRecorder tr;
	/*********************************************************************************/
	/**** encoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	for each (BitVectorPtr bitplane in bitplanes)
	{
		RLC_BitPlanesEncoder encoder(line_num, preBit);
		ByteVecotrPtr tmp = encoder.transitData(bitplane);

		tmps.push_back(tmp);
		countTmp += tmp->size();
	}
	tr.end();
	/*********************************************************************************/
	/**** decoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	for each (ByteVecotrPtr bitplane in tmps)
	{
		RLC_BitPlanesDecoder decoder(line_num, preBit);
		BitVectorPtr dst = decoder.transitData(bitplane);
	}
	tr.end();
}

void TransData::testLZW(typeImgPtr img)
{
	ByteVecotrPtr srcVec = img->toByteVector();

	TimeRecorder tr;
	/*********************************************************************************/
	/**** encoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	int compress_data_length = 12;
	LZW_Encoder encoder(compress_data_length);
	BitVectorPtr tmp = encoder.transitData(srcVec);
	tr.end();

	/*********************************************************************************/
	/**** decoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	LZW_Decoder decoder(compress_data_length);
	ByteVecotrPtr dst = decoder.transitData(tmp);
	tr.end();
}

void TransData::testHuffman(typeImgPtr img)
{
	int width = img->GetWidth();
	int BytesPerPixel = (img->GetBPP() + 7) / 8;
	int LineNum = width * BytesPerPixel;

	ByteVecotrPtr srcVec = img->toByteVector();

	HuffmanTreeBuilder treeBuilder;
	unordered_map<stKey, shared_ptr<typeTreeNode>> leafMap;

	TimeRecorder tr;
	/*********************************************************************************/
	/**** encoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	shared_ptr<MyBinaryTree<stNodeData>> tree = treeBuilder.BuildTrees(img, leafMap);
	VLC_HuffmanEncoder encoder(*tree, leafMap);
	BitVectorPtr tmp = encoder.transitData(srcVec);
	tr.end();

	/*********************************************************************************/
	/**** decoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	VLC_HuffmanDecoder decoder(tree);
	ByteVecotrPtr dst = decoder.transitData(tmp);
	tr.end();
}

void TransData::testDPCM(typeImgPtr img)
{
	ByteVecotrPtr srcVec = img->toByteVector();

	TimeRecorder tr;
	/*********************************************************************************/
	/**** encoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	int compress_data_length = 6;
	byte placeHolder = 0xff;
	DPCM_Encoder encoder(compress_data_length, placeHolder);
	BitVectorPtr tmp = encoder.transitData(srcVec);
	tr.end();

	/*********************************************************************************/
	/**** decoder                                                                  ***/
	/*********************************************************************************/
	tr.start();
	DPCM_Decoder decoder(compress_data_length, placeHolder);
	ByteVecotrPtr dst = decoder.transitData(tmp);
	tr.end();
}

bool TransData::EnDecOder(Transitions tsType, typeImgPtr img)
{
	bool bRet = false;

	switch (tsType)
	{
	case Transitions::RLC_Byte:
		testRLC_Byte(img);
		bRet = true;
		break;

	case Transitions::RLC_Bit:
		testRLC_Bit(img);
		bRet = true;
		break;

	case Transitions::Huffman:
		testHuffman(img);
		bRet = true;
		break;

	case Transitions::DPCM:
		testDPCM(img);
		bRet = true;
		break;

	case Transitions::LZW:
		testLZW(img);
		bRet = true;
		break;

	default:
		break;
	}

	return bRet;
}
