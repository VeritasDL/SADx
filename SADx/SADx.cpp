#include "pch.h"
extern "C"
{
	facewk* face = 0;
	void fixedFace(int old, int __new, int frame, int nbFrame);
	playerwk* playerwkptr = 0;
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
	}
	__declspec(dllexport) void __cdecl OnFrame()
	{
		// Executed every running frame of SADX
		if (PlayerPtrs[0] != nullptr) 
		{
			if (GetCharacterID(0) == Characters_Sonic)
			{
				playerwkptr = (playerwk*)CharObj2Ptrs[0];
				fixedFace(12, 1, 1, 100);
			}
		}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}
void fixedFace(int old, int __new, int frame, int nbFrame)
{
	task* player = (task*)PlayerPtrs[0];
	int faceaddress = (int)&player->twp->ewp->face;
	faceaddress = faceaddress + 8; //Adjust address because this is 8 bytes off
	face = (facewk*)faceaddress;
	face->old = old;
	face->__new = __new;
	face->frame = frame;
	face->nbFrame = nbFrame;
}