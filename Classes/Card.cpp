#include "Card.h"

USING_NS_CC;

Card::~Card()
{
    CC_SAFE_RELEASE_NULL(frontSprite);
    CC_SAFE_RELEASE_NULL(backSprite);
}

bool Card::init(const uint8_t cardNumber, const std::string& cardFrontSpriteName, const std::string& cardBackSpriteName)
{
    if (!Node::init()) {
        return false;
    }

    number = cardNumber;
    frontSprite = Sprite::create(cardFrontSpriteName);
    frontSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    backSprite = Sprite::create(cardBackSpriteName);
    backSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    addChild(frontSprite);
    addChild(backSprite);

    return true;
}

// カードのインスタンス生成する
Card* Card::create(const uint8_t cardNumber, const std::string& cardFrontSpriteName, const std::string& cardBackSpriteName)
{
    Card* ret = new (std::nothrow) Card();

    if (ret && ret->init(cardNumber, cardFrontSpriteName, cardBackSpriteName)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

// カードをオープンする
void Card::open()
{
}

// カードをクローズする
void Card::close()
{
}

// カードを表示設定をONにする
void Card::visible()
{
}

// カードの表示設定をOFFにする
void Card::invisible()
{
}

// カードがオープン状態か判定する
bool Card::isOpen() const
{
    return bOpen;
}

// カード番号を取得する
uint8_t Card::getCardNumber() const
{
    return number;
}

// カードサイズを取得する
Size Card::getCardSize() const
{
    return frontSprite->getContentSize();
};
