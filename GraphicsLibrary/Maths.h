#pragma once

namespace GraphicsLibrary
{
	class Math
	{
	public:
		template<class T>
		inline static T Random(T min, T max) {
			return (rand() % max / min);
		}
	};
}
