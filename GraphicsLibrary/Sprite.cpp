#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
#include "ResourceManager.h"

Sprite::Sprite(Point _location, Size _size, std::string _texturePath) : 
	location(_location),
	size(_size),
	texturePath(_texturePath)
{
	
}

Sprite::~Sprite()
{
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::Init()
{
	location = location;
	size = size;

	_texture = GraphicsLibrary::ResourceManager::getTexture(texturePath);

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	vertexData[0].setPosition(location.x + size.width, location.y + size.height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(location.x, location.y + size.height);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(location.x, location.y);
	vertexData[2].setUV(0.0f, 0.0f);

	vertexData[3].setPosition(location.x, location.y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(location.x + size.width, location.y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(location.x + size.width, location.y + size.height);
	vertexData[5].setUV(1.0f, 1.0f);


	for (int i = 0; i < sizeof(vertexData); i++) {
		vertexData[4].setColor(255, 0, 255, 255);
	}

	vertexData[4].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Update()
{
	Vertex vertexData[6];

	vertexData[0].setPosition(location.x + size.width, location.y + size.height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(location.x, location.y + size.height);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(location.x, location.y);
	vertexData[2].setUV(0.0f, 0.0f);

	vertexData[3].setPosition(location.x, location.y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(location.x + size.width, location.y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(location.x + size.width, location.y + size.height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertexData[5].setColor(255, 0, 255, 255);
	}

	vertexData[4].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw() const
{
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, location));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Getters
Point			Sprite::getLocation() const { return location; }
Size			Sprite::getSize() const { return size; }
std::string		Sprite::getTexturePath() const { return texturePath; }

// Setters
void Sprite::setLocation(Point e) { location = e; }
void Sprite::setSize(Size e) { size = e; }
void Sprite::setTexturePath(std::string e) { texturePath = e; }
