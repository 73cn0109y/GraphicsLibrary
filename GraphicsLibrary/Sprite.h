#pragma once
#include "Size.h"
#include "Point.h"
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>

class Sprite
{
public:
	Sprite(Point _location, Size _size, std::string texturePath);
	~Sprite();

	void Init();
	void Draw() const;
	void Update();

	// Getters
	Point getLocation() const;
	Size getSize() const;
	std::string getTexturePath() const;

	// Setters
	void setLocation(Point e);
	void setSize(Size e);
	void setTexturePath(std::string e);

private:
	Point location;
	Size size;
	std::string texturePath;
	GLuint _vboID;
	GLTexture _texture;
};