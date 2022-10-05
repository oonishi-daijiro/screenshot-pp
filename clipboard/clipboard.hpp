#pragma once
#include <Windows.h>

class Clipboard
{
public:
	static void Write(const HBITMAP &);
	static HBITMAP Read();
};
