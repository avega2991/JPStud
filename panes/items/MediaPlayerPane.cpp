#include "panes\items\MediaPlayerPane.h"

USING_NS_CC;


MediaPlayerPane::MediaPlayerPane()
{

}

MediaPlayerPane::~MediaPlayerPane()
{

}

MediaPlayerPane*	MediaPlayerPane::create()
{
	MediaPlayerPane* pMediaPlayer = new MediaPlayerPane();

	if (pMediaPlayer->init())
	{
		pMediaPlayer->autorelease();
		return pMediaPlayer;
	}

	CC_SAFE_DELETE(pMediaPlayer);
	return nullptr;
}

void	MediaPlayerPane::closePlayer()
{

}
