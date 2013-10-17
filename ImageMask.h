typedef int coordinate;

class CImageMask :
	public CImage
{
private:
	CImage & ori_img;
	int mask_size;
	coordinate median_x;
	coordinate median_y;

protected:
	coordinate route(coordinate src) const throw();

public:
	CImageMask(CImage & img, int size, coordinate x, coordinate y);
	virtual ~CImageMask();

	int GetHeight() const throw();
	int GetWidth() const throw();

	COLORREF GetPixel(int x, int y) const throw();
	void SetPixel(int x,int y, COLORREF color) throw();
	void SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw();
};
