#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

/* code by Jung Yu Chul---------------------------------------------------SoundObject
 * 1)this class carries a list-actually, a map- of sounds that can be played
 * 2)each sound has a string tag. you can initiallize sound/tags with 'addSound' method
 * 3)you can play any sound by specifying the tag in 'playSound' method
 * 4)if any sound is overlapped, only the last sound survives (one channel per object)
 *
 * use it by inheriting this class
 * eg) class tower : public AnimatedObject, public SoundObject
 * {
 * ...
 * };
 *
 *
 * --------------------------------------------------------------------------------*/
#include <QSoundEffect>
#include <QMap>
#include <QString>

class SoundObject
{
private:
    QMap<QString, QSoundEffect*> soundboard;//every sound is mapped to a specific string.

public:
    void addSound(const QString& tag, const QString& filename);//specify a tag and a filename
    void playSound(const QString& tag);
    bool isSoundFinished();
    ~SoundObject();
};

#endif // SOUNDOBJECT_H

