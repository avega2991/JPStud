#pragma once

#include "cocos2d.h"
#include <vector>
#include <map>


class Kanji
{
private:
	int																m_id;
	std::string														m_symbol;
	cocos2d::Sprite*												m_image;
	std::map<std::string, std::vector<std::string>>					m_description;	// reading -> examples

	static int														s_idCounter;


public:
	Kanji(const std::string& formatString);	// TODO : EXCLUDE PARSE PARTS IN ANOTHER FUNC
	// ~Kanji();

	int																getID();
	std::string														getSymbol();
	cocos2d::Sprite*												getSprite();
	std::map<std::string, std::vector<std::string>>					getDescription();

};