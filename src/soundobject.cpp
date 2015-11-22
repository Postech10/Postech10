#include "soundobject.h"
#include <QSound>
#include <QString>
#include <iterator>


void SoundObject::addSound(const QString &tag, const QString &filename)
{
    soundboard[tag] = new QSound(filename);
    soundon[tag] = false;
    //now, the sound of the file is matched to the tag
}

void SoundObject::playSound(const QString &tag)
{
    //first, update 'soundon' map
    QMap<QString, QSound*>::iterator it;
    for(it = soundboard.begin(); it!=soundboard.end(); it++)
    {
        if((*it)->isFinished()) soundon[it.key()] = false;
        if(soundon[it.key()] == true) //playing?
        {
            (*it)->stop();//stop it
            soundon[it.key()] = false;
        }
    }

    //mark as played
    soundon[tag] = true;
    soundboard[tag]->play(); //play assigned sound
}
SoundObject::~SoundObject()
{
    QMap<QString, QSound*>::iterator it;
    for(it = soundboard.begin(); it!=soundboard.end(); it++)
    {
        delete *it;
    }

}
