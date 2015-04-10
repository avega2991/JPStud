#pragma once

#include "cocos2d.h"


class MediaPlayerPane : public cocos2d::Layer
{
private:
	

public:
	MediaPlayerPane();
	~MediaPlayerPane();

	static MediaPlayerPane*							create();
	static MediaPlayerPane*							create(const std::string&);
	void											closePlayer();
};
