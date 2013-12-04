#pragma once
#include "MyImage.h"

using namespace std;

enum class Transitions
{
	none,
	graying,
	subsampling,
	replication,
	nearest_neighbor,
	bilinear_interpolation,
	gray_level,
	pow_scale,
	log_scale,
	histogram_eq,
	histogram_match,
	histogram_local,
	smoothing,
	median,
	sharpening_laplacian,
	high_boosting,
	bit_slicing_set,
	bit_slicing_reconstruct,
	max,
	min,
	midpoint,
	arithmetic,
	geometic,
	harmonic,
	contraharmonic,
	alpha_trimmed,
	RLC_Byte,
	RLC_Bit,
	Huffman,
	LZW,
	DPCM,
};

class TransImage
{
protected:
	int Gcd(int a, int b);
	byte * getImgBuff(typeImgPtr src);
public:
	TransImage();
	TransImage(typeImgParaPtr imgP);
	virtual ~TransImage();

	int ResetDstColorTable(typeImgPtr src, typeImgPtr dst);
	virtual typeImgPtr transit(typeImgPtr src) = 0;

	static TransImage * CreateTransition(Transitions tsType,typeImgParaPtr imgP);
	static typeImgPtr transit_img(typeImgPtr src, Transitions tsType, typeImgParaPtr imgP = NULL);
};

