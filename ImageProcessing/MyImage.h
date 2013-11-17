#pragma once
#include <map>
#include <memory>
#include "ByteVecotr.h"

typedef int stKey;
typedef int stVal;
typedef std::map<stKey, stVal> type_statistic_map;

const byte ByteMask[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

enum class maskType
{
	average_1_9,
	average_1_16,
	laplacian_nag4,
	laplacian_nag8,
	laplacian_pos4,
	laplacian_pos8,
};

struct stImgPara
{
	int width;
	int height;
	int mask_size;
	int bit_size;
	byte bit_mask;
	double c;
	double y;
	double A;
	maskType mask_type;
	CString filePath;
};

class MyImage :
	public CImage
{
public:
	MyImage();
	virtual ~MyImage();

	virtual byte getByteVal(int x, int y, int index);
	virtual void setByteVal(int x, int y, int index, byte val);
	virtual COLORREF GetPixel(_In_ int x, _In_ int y) const throw();
	virtual int GetHeight() const throw();
	virtual int GetWidth() const throw();
	virtual int GetBPP() const;
	virtual void SetPixel(int x, int y, COLORREF color) throw();
	virtual void SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw();

	ByteVecotrPtr toByteVector();
};

typedef std::shared_ptr<MyImage> typeImgPtr;
typedef std::shared_ptr<stImgPara> typeImgParaPtr;

