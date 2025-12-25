#include "LevelBrowserLayer.hpp"
#include "../NearbyShareManager.hpp"

bool HookedLevelBrowserLayer::init(GJSearchObject* object) {
    if (!LevelBrowserLayer::init(object)) return false;
    if (m_searchObject->m_searchType != SearchType::MyLevels) return true;

    auto button = geode::cocos::CCMenuItemExt::createSpriteExtraWithFilename(
        "among-us-upload-x2.png"_spr, .7f,
        [this](auto) {
            $async() {
                auto& manager = NearbyShareManager::get();

                auto res = co_await manager.requestPermissionsIfNeeded();
                if (!res) co_return;

                NearbyDownloadPopup::create()->show();
            };
        }
    );

    button->setPosition({ 170.f, 122.f });

    auto menu = cocos2d::CCMenu::create();
    menu->setPosition(cocos2d::CCDirector::get()->getWinSize() / 2.f);
    menu->addChild(button);
    addChild(menu);

    auto label = cocos2d::CCSprite::create("download-nearby-levels.png"_spr);
    label->setPosition(menu->convertToWorldSpace(button->getPosition()) + cocos2d::CCPoint{ 20.f, -20.f });
    addChild(label);

    return true;
}
