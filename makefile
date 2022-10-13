lib:screenshot/screenshot.cpp clipboard/clipboard.cpp ./win32SharedMem/win32SharedMem.cpp
	cl /c ./screenshot/screenshot.cpp
	cl /c ./clipboard/clipboard.cpp
	cl /c ./win32SharedMem/win32SharedMem.cpp
build:screenshotpp.cpp
	make lib
	cl screenshotpp.cpp clipboard.obj screenshot.obj win32SharedMem.obj /EHsc /link /SUBSYSTEM:WINDOWS
