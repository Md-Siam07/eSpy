
#include<bits/stdc++.h>
#include <windows.h>

int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
    HBITMAP offScreenBitmap=NULL;
    HDC offScreenDeviceContext=NULL;
    LPBITMAPINFO bitMapFormatInfo=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;


    if ((offScreenBitmap = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return false;

    if ((offScreenDeviceContext = CreateCompatibleDC(bitmapDC)) == NULL)
        return false;
    HBITMAP OldBmp = (HBITMAP)SelectObject(offScreenDeviceContext, offScreenBitmap);
    BitBlt(offScreenDeviceContext, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((bitMapFormatInfo = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return false;


    ZeroMemory(&bitMapFormatInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
    bitMapFormatInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(offScreenDeviceContext, OldBmp);
    if (!GetDIBits(offScreenDeviceContext, offScreenBitmap, 0, height, NULL, bitMapFormatInfo, DIB_RGB_COLORS))
        return false;
    if ((lpvBits = new char[bitMapFormatInfo->bmiHeader.biSizeImage]) == NULL)
        return false;
    if (!GetDIBits(offScreenDeviceContext, offScreenBitmap, 0, height, lpvBits, bitMapFormatInfo, DIB_RGB_COLORS))
        return false;
    if ((BmpFile = CreateFile(filename,GENERIC_WRITE,0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
        return false;

    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return false;

    if (Written < sizeof(bmfh))
        return false;
    if (!WriteFile(BmpFile, &bitMapFormatInfo->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return false;

    if (Written < sizeof(BITMAPINFOHEADER))
        return false;
    int PalEntries;

    if (bitMapFormatInfo->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else

        PalEntries = (bitMapFormatInfo->bmiHeader.biBitCount <= 8) ? // bitmap is palettized?
                     // 2^biBitCount palette entries max.:
                     (int)(1 << bitMapFormatInfo->bmiHeader.biBitCount)
                     // bitmap is TrueColor -> no palette:
                     : 0;
    if(bitMapFormatInfo->bmiHeader.biClrUsed)
        PalEntries = bitMapFormatInfo->bmiHeader.biClrUsed;
    if(PalEntries)
    {
        if (!WriteFile(BmpFile, &bitMapFormatInfo->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
            return false;

        if (Written < PalEntries * sizeof(RGBQUAD))
            return false;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);

    // Write bitmap bits to the file:
    if (!WriteFile(BmpFile, lpvBits, bitMapFormatInfo->bmiHeader.biSizeImage, &Written, NULL))
        return false;

    if (Written < bitMapFormatInfo->bmiHeader.biSizeImage)
        return false;
    bmfh.bfSize = GetFilePointer(BmpFile); // The current pos. in the file is the final file size and will be saved:

    // We have all the info for the file header. Save the updated version:
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return false;

    if (Written < sizeof(bmfh))
        return false;

    return true;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename)
{
    HDC hDc = CreateCompatibleDC(0);
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
    SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
    bool value = SaveBMPFile(filename, hBmp, hDc, width, height);
    DeleteObject(hBmp);
    return value;
}

main()
{
    ScreenCapture(0, 0, 1500, 1000, "testScreenCap.bmp");
    printf("wrote to testScreenCap.bmp");
}

