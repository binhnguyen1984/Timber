/*
 * SpriteLoader.h
 *
 */

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;
class TextureLoader {
private:
	static map<string, Texture> store;
public:
	static Texture& getTexture(string const path);
};

#endif /* TEXTURELOADER_H_ */
