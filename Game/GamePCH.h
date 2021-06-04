#pragma once
#ifndef PCH_H
#define PCH_H

//// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib")  

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#include <windows.h>

#include <vld.h>
#include <Structs.h>

//Own files
#include <Structs.h>
#include <MathHelper.h>
#include <Logger.h>
#include <IPoint2Operators.h>
#include "HelperFunctions.h"

//credit to Rhidian De Wit
template<typename Type>
constexpr void SafeDelete(Type* pData)
{
    if (pData)
    {
        delete pData;
        pData = nullptr;
    }
}

#endif