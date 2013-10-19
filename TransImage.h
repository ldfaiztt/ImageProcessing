#pragma once
#include <memory>

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
};

struct stImgPara
{
	int width;
	int height;
	float c;
	float y;
	CString filePath;
};

typedef shared_ptr<CImage> typeImgPtr;
typedef shared_ptr<stImgPara> typeImgParaPtr;

class TransImage
{
protected:
	int Gcd(int a, int b);
	byte * getImgBuff(typeImgPtr src);
public:
	TransImage();
	TransImage(typeImgParaPtr imgP);
	virtual ~TransImage();
	virtual typeImgPtr transit(typeImgPtr src) = 0;

	static TransImage * CreateTransition(Transitions tsType,typeImgParaPtr imgP);
	static typeImgPtr transit_img(typeImgPtr src, Transitions tsType, typeImgParaPtr imgP = NULL);
};

