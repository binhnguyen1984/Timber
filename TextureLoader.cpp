/*
 * TextureLoader.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: binh
 */

#include "TextureLoader.h"
#include <iostream>

Texture& TextureLoader::getTexture(string const path)
{
	auto it = store.find(path);
	if(it!=store.end()) return it->second;
	Texture &newTexture = store[path];
	newTexture.loadFromFile(path);
	return newTexture;
}
map<string, Texture> TextureLoader::store;



