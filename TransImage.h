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

class TransImage
{
public:
	TransImage();
	TransImage(shared_ptr<stImgPara> imgP);
	virtual ~TransImage();
	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src) = 0;

	int Gcd(int a, int b);

	static TransImage * CreateTransition(Transitions tsType,shared_ptr<stImgPara> imgP);
	static shared_ptr<CImage> transit_img(shared_ptr<CImage> src, Transitions tsType, shared_ptr<stImgPara> imgP = NULL);
};

