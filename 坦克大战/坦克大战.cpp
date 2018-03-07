// Ì¹¿Ë´óÕ½.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
# include <cv.h>
# include <highgui.h>
# include "Mange.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <stdio.h>

int main(int argc, char* argv[])
{
	CMange mange;
	mange.GameRrsourceInit();
	mange.Run();
	mange.GameRrsourceRelease();
	return 0;
}
