lib:screenshot/screenshot.cpp clipboard/clipboard.cpp ./win32SharedMem/win32SharedMem.cpp
	cl /c ./screenshot/screenshot.cpp
	cl /c ./clipboard/clipboard.cpp
	cl /c ./win32SharedMem/win32SharedMem.cpp
scrnshotpp:screenshotpp.cpp clipboard.obj screenshot.obj win32SharedMem.obj
	cl screenshotpp.cpp clipboard.obj screenshot.obj win32SharedMem.obj /EHsc /link /SUBSYSTEM:WINDOWS
	./screenshotpp.exe
