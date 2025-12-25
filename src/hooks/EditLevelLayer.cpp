#include "EditLevelLayer.hpp"
#include "../NearbyShareManager.hpp"

bool HookedEditLevelLayer::init(GJGameLevel* level) {
    if (!EditLevelLayer::init(level)) return false;

    auto button = geode::cocos::CCMenuItemExt::createSpriteExtraWithFilename(
        "among-us-upload-x2.png"_spr, .7f,
        [this, level](auto) {
            $async(level) {
                auto& manager = NearbyShareManager::get();

                auto res = co_await manager.requestPermissionsIfNeeded();
                if (!res) co_return;

                NearbyUploadPopup::create(level)->show();
            };
        }
    );

    button->setPosition({ 180.f, 130.f });

    auto menu = cocos2d::CCMenu::create();
    menu->setPosition(cocos2d::CCDirector::get()->getWinSize() / 2.f);
    menu->addChild(button);
    addChild(menu);

    auto label = cocos2d::CCSprite::create("share-nearby.png"_spr);
    label->setPosition(menu->convertToWorldSpace(button->getPosition()) + cocos2d::CCPoint{ -50.f, 10.f });
    addChild(label);

    return true;
}
