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
#include <QSound>
#include <QMap>
#include <QString>

class SoundObject
{
private:
    QMap<QString, QSound*> soundboard;//every sound is mapped to a specific string.
    QMap<QString, bool> soundon;/*if sound is on, true. else, false.
                                  this map is used for stopping overlapped sounds
                                  */

public:
    void addSound(const QString& tag, const QString& filename);//specify a tag and a filename
    void playSound(const QString& tag);
    ~SoundObject();
};

#endif // SOUNDOBJECT_H

