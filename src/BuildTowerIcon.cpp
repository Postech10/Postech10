#include "BuildTowerIcon.h"
#include "Game.h"
#include <qdebug.h>

extern Game *game;

BuildTowerIcon::BuildTowerIcon(char *filename,int _tower_code ,QGraphicsItem *parent){

    setPixmap(QPixmap(filename));     //constructor
    tower_code = _tower_code;
    srand(time(NULL));
    addSound("Buy Success", "resources/sounds/Select.wav");
    addSound("Move", "resources/sounds/move.wav");
    addSound("Fail", "resources/sounds/unablebutton.wav");
}
void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{   
    bool issuccess = false;
    if(tower_code == 15 && game->GetTowerinfo() == BASE){
        playSound("Move");
        issuccess = true;
        game->SetTowerinfo(LEVEL2);

        this->updatePixmap(game->getNormal_Tower_button(),":/images/IconLV2_TutorRobot.bmp");
        this->updatePixmap(game->getSplash_Tower_button(),":/images/IconLV2_Session.bmp");
        this->updatePixmap(game->getSlow_Tower_button(),":/images/IconLV2_ChemEng.bmp");
        this->updatePixmap(game->getGo_to_back_Button(),":/images/Icon_ToLevel3Tower.bmp");

        this->updatePixmap(game->getPoison_Tower_button(),":/images/IconLV2_Metal.bmp");
        this->updatePixmap(game->getChain_Tower_button(),":/images/IconLV2_JobsBook.bmp");
        game->scene->removeItem(game->getGold_Tower_button());
        this->updatePixmap(game->getRandom_Tower_Button(),":/images/Icon_BackToBaseTower.bmp");
    }

    else if(tower_code == 15 && game->GetTowerinfo() == LEVEL2){

        playSound("Move");
        issuccess = true;
        game->SetTowerinfo(LEVEL3);

        this->updatePixmap(game->getNormal_Tower_button(),":/images/IconLV3_AppleDeathMachine.bmp");
        this->updatePixmap(game->getSplash_Tower_button(),":/images/IconLV3_JobsDream.bmp");
        this->updatePixmap(game->getSlow_Tower_button(),":/images/IconLV3_3Major.bmp");
        game->scene->removeItem(game->getGo_to_back_Button());

        game->scene->removeItem(game->getPoison_Tower_button());
        game->scene->removeItem(game->getChain_Tower_button());
        this->updatePixmap(game->getRandom_Tower_Button(),":/images/Icon_BackToBaseTower.bmp");
    }

    else if(tower_code == 14 && game->GetTowerinfo() != BASE){

        playSound("Move");
        issuccess = true;

        this->updatePixmap(game->getNormal_Tower_button(),":/images/Icon_Assistant.bmp");
        this->updatePixmap(game->getSplash_Tower_button(),":/images/Icon_Mechanical.bmp");
        this->updatePixmap(game->getSlow_Tower_button(),":/images/Icon_SMP.bmp");

        if(game->GetTowerinfo() == LEVEL2){
            this->updatePixmap(game->getGo_to_back_Button(),":/images/Icon_ToLevel2Tower.bmp");
            this->updatePixmap(game->getPoison_Tower_button(),":/images/Icon_Chemical.bmp");
            this->updatePixmap(game->getChain_Tower_button(),":/images/Icon_Electronic.bmp");
        }

        if(game->GetTowerinfo() == LEVEL3){

            game->getGo_to_back_Button()->setPixmap(QPixmap(":/images/Icon_ToLevel2Tower.bmp"));
            game->scene->addItem(game->getGo_to_back_Button());

            game->getPoison_Tower_button()->setPixmap(QPixmap(":/images/Icon_Chemical.bmp"));
            game->scene->addItem(game->getPoison_Tower_button());

            game->getChain_Tower_button()->setPixmap(QPixmap(":/images/Icon_Electronic.bmp"));
            game->scene->addItem(game->getChain_Tower_button());
        }

        game->getGold_Tower_button()->setPixmap(QPixmap(":/images/Icon_IME.bmp"));
        game->scene->addItem(game->getGold_Tower_button());

        this->updatePixmap(game->getRandom_Tower_Button(),":/images/Icon_Random.bmp");

        game->SetTowerinfo(BASE);
    }

    else if(game->GetState() != Ingame && game->GetTowerinfo() == BASE){

        if(tower_code == 14){


            int random = rand() % 157 + 1;
            if(random >=1 && random <= 42)
                random = NORMAL;
            else if(random >=43 && random <= 70)
                random = SPLASH;
            else if(random >=71 && random <= 98)
                random = SLOW;
            else if(random >=99 && random <= 122)
                random = POISON;
            else if(random >=123 && random <= 143)
                random = CHAIN;
            else if(random >=144 && random <= 157)
                random = GOLD;

            switch(random){
            case NORMAL:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),NORMAL);
                    game->set_money(game->get_money()-30);
                }
                break;
            case SPLASH:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),SPLASH);
                    game->set_money(game->get_money()-30);
                }
                break;
            case SLOW:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),SLOW);
                    game->set_money(game->get_money()-30);
                }
                break;
            case POISON:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),POISON);
                    game->set_money(game->get_money()-30);
                }
                break;
            case CHAIN:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),CHAIN);
                    game->set_money(game->get_money()-30);
                }
                break;
            case GOLD:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),GOLD);
                    game->set_money(game->get_money()-30);
                }
                break;
            }
        }

        else{
            switch(tower_code){
            case NORMAL:
                if(game->get_money() >= 20){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),NORMAL);
                    game->set_money(game->get_money()-20);
                }
                break;
            case SPLASH:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),SPLASH);
                    game->set_money(game->get_money()-30);
                }
                break;
            case SLOW:
                if(game->get_money() >= 30){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),SLOW);
                    game->set_money(game->get_money()-30);
                }
                break;
            case POISON:
                if(game->get_money() >= 35){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),POISON);
                    game->set_money(game->get_money()-35);
                }
                break;
            case CHAIN:
                if(game->get_money() >= 40){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),CHAIN);
                    game->set_money(game->get_money()-40);
                }
                break;
            case GOLD:
                if(game->get_money() >= 60){
                    issuccess = true;
                    playSound("Buy Success");
                    game->SetAddMode(true);
                    game->button_Pressed(event->pos(),GOLD);
                    game->set_money(game->get_money()-60);
                }
                break;
            }
        }
    }
    if(!issuccess) playSound("Fail");
}

void BuildTowerIcon::updatePixmap(BuildTowerIcon *update, char* newImage)
{
    game->scene->removeItem(update);
    update->setPixmap(QPixmap(newImage));
    game->scene->addItem(update);
}
