#include "BGM.h"
#include <QUrl>

BGM::BGM(QObject* parent) : QObject(parent)
{
    musicPlayer = new QMediaPlayer(this);
    connect(musicPlayer, &QMediaPlayer::mediaStatusChanged, this, &BGM::onMediaStatusChanged);
}

void BGM::playBackgroundMusic(const QString &audioPath)
{
    musicPlayer->setMedia(QUrl(audioPath));
    musicPlayer->setVolume(50);  // Set volume as desired
    musicPlayer->play();
}

void BGM::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        musicPlayer->play();  // Restart the music
    }
}
