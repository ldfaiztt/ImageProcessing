#include "MyImage.h"

typedef int coordinate;

class ImageMask :
	public MyImage
{
private:
	MyImage & ori_img;
	int mask_size;
	coordinate median_x;
	coordinate median_y;

protected:
	coordinate route(coordinate src) const throw();

public:
	ImageMask(MyImage & img, int size, coordinate x, coordinate y);
	virtual ~ImageMask();

	byte getByteVal(int x, int y, int index);
	int GetHeight() const throw();
	int GetWidth() const throw();
	int GetBPP() const;
	COLORREF GetPixel(int x, int y) const throw();
	void SetPixel(int x,int y, COLORREF color) throw();
	void SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw();
};
