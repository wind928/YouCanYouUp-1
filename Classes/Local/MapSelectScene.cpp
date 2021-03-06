#include "MapSelectScene.h"
#include "Battle\BattleScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool MapSelectScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("mapUI.ExportJson"));
	this->addChild(pNode);

	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_1"));
	defaultBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_3"));
	snowBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_4"));

	defaultBtn->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::selectEvent, this));
	snowBtn->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::selectEvent, this));
	return_->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::returnEvent, this));
	return true;
}

void MapSelectScene::selectEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		if(pSender == defaultBtn)
		{
			mapSelected = GameSetting::Map::FOREST;
		}
		else if(pSender == snowBtn)
		{
			mapSelected = GameSetting::Map::SNOW;
		}

		std::vector<GameSetting::Character> enemy;
		enemy.push_back(GameSetting::Character::CHARACTER2);
		enemy.push_back(GameSetting::Character::CHARACTER2);
		Scene *game = BattleScene::createScene(mapSelected, charSelected, enemy);
		TransitionScene *transition = TransitionFade::create(0.5, game);
		Director::getInstance()->replaceScene(transition);
	}
}

void MapSelectScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void MapSelectScene::setCharSelected(GameSetting::Character cha)
{
	this->charSelected = cha;
}