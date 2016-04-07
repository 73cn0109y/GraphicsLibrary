#pragma once
#include "GLTexture.h"

#include <string>

namespace GraphicsLibrary
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}
