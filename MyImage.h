#pragma once

#include <memory>

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
	double c;
	double y;
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
};

typedef std::shared_ptr<MyImage> typeImgPtr;
typedef std::shared_ptr<stImgPara> typeImgParaPtr;

