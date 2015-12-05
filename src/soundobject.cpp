#include "soundobject.h"
#include <QSoundEffect>
#include <QString>
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <iterator>


void SoundObject::addSound(const QString &tag, const QString &filename)
{
    QSoundEffect* sound = new QSoundEffect;
    //qDebug()<<QDir::currentPath() + "/" + filename;
    QUrl file = QUrl::fromLocalFile(filename);
    if(file.isEmpty()) qDebug()<<"Open File Not Found. Tag : "<<tag;
    else sound->setSource(file);
    sound->setVolume(0.8f);
    soundboard[tag] = sound;

    //now, the sound of the file is matched to the tag
}

void SoundObject::playSound(const QString &tag)
{
    //if any of the sound of this is playing, stop it.
    //QMap<QString, QSoundEffect*>::iterator it;
    /*for(it = soundboard.begin(); it!=soundboard.end(); it++)
    {
        if((*it)->isPlaying()){
            (*it)->stop();
        }
    }*/

    try{
    soundboard[tag]->play(); //play assigned sound
    }
    catch(...){
        qDebug()<<"Sound Not Found. Tag : "<<tag;
    }
}
bool SoundObject::isSoundFinished()
{
    QMap<QString, QSoundEffect*>::iterator it;
    for(it = soundboard.begin(); it!=soundboard.end(); it++)
    {
        if((*it)->isPlaying()){
            return false;
        }
    }
    return true;
}

SoundObject::~SoundObject()
{
    QMap<QString, QSoundEffect*>::iterator it;
    for(it = soundboard.begin(); it!=soundboard.end(); it++)
    {
        delete *it;
    }

}
