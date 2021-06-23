#include<bits/stdc++.h>
#include<windows.h>
using namespace std;


void ScreenCapture(char* name)
{
    HDC hDC;
	HDC comHDC;
	int width;
	int height;
	HBITMAP hBitmap;
	BITMAPINFOHEADER bmiHeader;
	DWORD dwBmpSize;
	DWORD dwSizeofDIB;
	BITMAPFILEHEADER bmfHeader;
	char *lpbitmap;

	hDC = GetDC(NULL);
	comHDC = CreateCompatibleDC(hDC);

	//screen dimensions

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);



	hBitmap = CreateCompatibleBitmap(hDC, width, height);
	SelectObject(comHDC, hBitmap);

	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = width;
	bmiHeader.biHeight = height;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 16;
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biSizeImage = 0;
	bmiHeader.biXPelsPerMeter = 0;
	bmiHeader.biYPelsPerMeter = 0;
	bmiHeader.biClrUsed = 0;
	bmiHeader.biClrImportant = 0;

    //calculate the size of bmp

	dwBmpSize = (width * bmiHeader.biBitCount + 31) / 32 * 4 * height;
	dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwSizeofDIB;
	bmfHeader.bfType = 0x4D42;

	lpbitmap = new char[dwBmpSize];

    //copy screen to bitmap and save it

	if (BitBlt(comHDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY))
	{
		ZeroMemory(lpbitmap, dwBmpSize);
		GetDIBits(comHDC, hBitmap, 0, (UINT)height, lpbitmap, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS);

		ofstream of(name, ios_base::binary);
		of.write((char *)&bmfHeader, sizeof(BITMAPFILEHEADER));
		of.write((char *)&bmiHeader, sizeof(BITMAPINFOHEADER));
		of.write(lpbitmap, dwBmpSize);
		of.close();
	}

    //release the obtained memories
	DeleteDC(hDC);
	DeleteDC(comHDC);
	DeleteObject(hBitmap);
	delete lpbitmap;
}
