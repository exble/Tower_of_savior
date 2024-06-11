#ifndef BGM_H
#define BGM_H

#include <QObject>
#include <QMediaPlayer>

class BGM : public QObject
{
    Q_OBJECT
public:
    BGM(QObject* parent = nullptr);
    void playBackgroundMusic(const QString &audioPath);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer* musicPlayer;
};

#endif // BGM_H
