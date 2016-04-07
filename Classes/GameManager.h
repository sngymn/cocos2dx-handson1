#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"

class GameManager : public cocos2d::Layer {

    static constexpr int MAX_CARD_NUMBER = 9;
    static constexpr int MAX_CARD_ROWS = 6;
    static constexpr int MAX_CARD_COLS = 3;

public:
    static cocos2d::Scene* createScene();

    bool init() override;

    void loadCards();
    void arrangeCards();

    CREATE_FUNC(GameManager);

private:
};

#endif // __HELLOWORLD_SCENE_H__
