#include "clipboard.hpp"

void Clipboard::Write(const HBITMAP &data)
{
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, (HANDLE)data);
	CloseClipboard();
};

HBITMAP Clipboard::Read()
{
	OpenClipboard(NULL);
	HGLOBAL data;
	GlobalLock(data);
	data = GetClipboardData(CF_BITMAP);
	CloseClipboard();
	return (HBITMAP)data;
};
