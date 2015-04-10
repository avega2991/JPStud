#pragma once

#include <fstream>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "sprites\items\Item.h"
#include "panes\items\MediaPlayerPane.h"

// <FOR_SUBTITLES>
#define COLOR_RED				cocos2d::Color3B(255, 0, 0)
#define COLOR_GREEN				cocos2d::Color3B(0, 255, 0)
#define COLOR_LIGHT_BLUE		cocos2d::Color3B(149, 193, 208)	
#define COLOR_YELLOW			cocos2d::Color3B(255, 215, 0)
#define COLOR_WHITE				cocos2d::Color3B(255, 255, 255)
#define COLOR_BLACK				cocos2d::Color3B(0, 0, 0)
// </FOR_SUBTITLES>


// SINGLETON
class MediaPlayerItem : public InventoryItem
{
private:
	std::vector<std::string>										m_musicPlaylist;
	std::vector<std::string>										m_audioMaterialsPlaylist;

	std::string														m_currentSubtitleLine;
	std::pair<int, int>												m_startAndEndOfSubtitleLine;

	CocosDenshion::SimpleAudioEngine*								m_audioEngine;

	static MediaPlayerItem*											s_mediaPlayer;

private:
	void															loadPlaylist(std::vector<std::string>& container, std::ifstream& file);

	// CALLBACKS
	virtual void													useCallback(Ref*);
	virtual void													examineCallback(Ref*);

	void															playCallback();
	void															pauseCallback();
	void															stopCallback();

public:
	MediaPlayerItem();
	// ~MediaPlayerItem();

	static MediaPlayerItem*											getInstance();
	void															initPlaylists();
};
