#include "Card.h"

USING_NS_CC;

Card::~Card() {
  CC_SAFE_RELEASE_NULL(frontSprite);
  CC_SAFE_RELEASE_NULL(backSprite);
}

bool Card::init(const uint8_t cardNumber,
                const std::string &cardFrontSpriteName,
                const std::string &cardBackSpriteName) {
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
Card *Card::create(const uint8_t cardNumber,
                   const std::string &cardFrontSpriteName,
                   const std::string &cardBackSpriteName) {
  Card *ret = new (std::nothrow) Card();

  if (ret && ret->init(cardNumber, cardFrontSpriteName, cardBackSpriteName)) {
    ret->autorelease();
    return ret;
  } else {
    delete ret;
    ret = nullptr;
    return nullptr;
  }
}

// カードをオープンする
void Card::open() {
  frontSprite->setVisible(true);
  backSprite->setVisible(false);

  bOpen = true;
}

// カードをクローズする
void Card::close() {
  frontSprite->setVisible(false);
  backSprite->setVisible(true);

  bOpen = false;
}

// カードを表示設定をONにする
void Card::visible() {
  frontSprite->setVisible(true);
  backSprite->setVisible(true);
}

// カードの表示設定をOFFにする
void Card::invisible() {
  frontSprite->setVisible(false);
  backSprite->setVisible(false);
}

// タッチ位置がカード内に存在するか判定する
bool Card::inside(const cocos2d::Vec2 &loc) const
{
  auto position = getPosition();
  auto contentSize = frontSprite->getContentSize();
  Rect rect(position, contentSize);
    
  return rect.containsPoint(loc);
}

// カードがオープン状態か判定する
bool Card::isOpen() const { return bOpen; }

// カード番号を取得する
uint8_t Card::getCardNumber() const { return number; }

// カードサイズを取得する
Size Card::getCardSize() const { return frontSprite->getContentSize(); };
