#ifndef Card_hpp
#define Card_hpp

#include "cocos2d.h"

class Card : public cocos2d::Node {
protected:
    Card() = default;
    ~Card();
    bool init(const uint8_t cardNumber, const std::string& cardFrontSpriteName, const std::string& cardBackSpriteName);

public:
    static Card* create(const uint8_t cardNumber, const std::string& cardFrontSpriteName, const std::string& cardBackSpriteName);

    void open();
    void close();

    void visible();
    void invisible();
    bool isOpen() const;

    uint8_t getCardNumber() const;
    cocos2d::Size getCardSize() const;

private:
    uint8_t number{ 0 };
    cocos2d::Sprite* frontSprite{ nullptr };
    cocos2d::Sprite* backSprite{ nullptr };
    bool bOpen{ false };
};

#endif /* Card_hpp */
