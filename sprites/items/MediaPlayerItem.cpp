#include "sprites\items\MediaPlayerItem.h"

USING_NS_CC;

MediaPlayerItem*	MediaPlayerItem::s_mediaPlayer = nullptr;


MediaPlayerItem::MediaPlayerItem()
{
	m_audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	MenuItemImage* itemClick = MenuItemImage::create("textures\items\mediaplayer\player.jpg",
		"textures\items\mediaplayer\player.jpg",
		CC_CALLBACK_1(MediaPlayerItem::clickItemCallback, this));
	m_clickableItem = Menu::create(itemClick, nullptr);

	m_useCallback = CC_CALLBACK_1(MediaPlayerItem::useCallback, this);
	m_examineCallback = CC_CALLBACK_1(MediaPlayerItem::examineCallback, this);
}

MediaPlayerItem*	MediaPlayerItem::getInstance()
{
	if (!s_mediaPlayer)
	{
		s_mediaPlayer = new MediaPlayerItem();
		s_mediaPlayer->initWithSpriteFrameName("textures\items\mediaplayer\player.jpg");
		s_mediaPlayer->initPlaylists();
	}

	return s_mediaPlayer;
}

// TODO
void	MediaPlayerItem::initPlaylists()
{
	std::ifstream musicPlaylistFile("savefiles\music_playlist.sav");
	std::ifstream materialsPlaylistFile("savefiles\materials_playlist.sav");

	s_mediaPlayer->loadPlaylist(m_musicPlaylist, musicPlaylistFile);
	s_mediaPlayer->loadPlaylist(m_audioMaterialsPlaylist, materialsPlaylistFile);
}

void	MediaPlayerItem::loadPlaylist(std::vector<std::string>& container, std::ifstream& file)
{
	std::string inputString;

	while (!file.eof())
	{
		std::getline(file, inputString);

		if (inputString.length() > 0)
			container.push_back(inputString);
	}
}

// <CALLBACKS>
void	MediaPlayerItem::useCallback(Ref* pSender)
{
	this->getParent()->removeChildByTag(ITEM_MENU, true);

	MediaPlayerPane* mediaPlayer = MediaPlayerPane::create();
	this->getParent()->addChild(mediaPlayer);
}

void	MediaPlayerItem::examineCallback(Ref* pSender)
{

}

void	MediaPlayerItem::playCallback()
{

}

void	MediaPlayerItem::pauseCallback()
{

}

void	MediaPlayerItem::stopCallback()
{

}
// </CALLBACKS>