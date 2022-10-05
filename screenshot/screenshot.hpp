#pragma once

#include <Windows.h>
#include <string>
#include <atlimage.h>

class Screenshot {
public:
	static HBITMAP Capture();
	static void Save(std::string,HBITMAP&);
};