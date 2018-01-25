#include "SceneGameOver.h"
#include "SceneGame.h"
#include "SceneMainMenu.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SceneGameOver::createScene(unsigned int score, int moneyCount)
{
    auto scene = Scene::create();
    auto layer = SceneGameOver::create();
	layer->setScore(score);
	layer->setMoneyCount(moneyCount);
	layer->handleScoreAndMoneyCount();

    scene->addChild(layer);

    return scene;
}

bool SceneGameOver::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	this->getVisible();

	this->setBackground("bg.jpg");

	this->setMenu();

    return true;
}

void SceneGameOver::setMenu()
{
	//重新开始按钮
	auto retryItem = MenuItemImage::create("Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1(SceneGameOver::goToGameScene, this));
	retryItem->setPosition(Point(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height / 4 * 3));

	//回到主界面按钮
	auto mainMenuItem = MenuItemImage::create("Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1(SceneGameOver::goToMainMenuScene, this));
	mainMenuItem->setPosition(Point(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height / 4));

	auto menu = Menu::create(retryItem, mainMenuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
}

//回到主界面
void SceneGameOver::goToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = SceneMainMenu::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

//重新开始游戏场景
void SceneGameOver::goToGameScene( cocos2d::Ref *sender )
{
    auto scene = SceneGame::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void SceneGameOver::handleScoreAndMoneyCount()
{
	//本次得分以及捡到的钱数，比本地记录大，就更新本地记录
	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE FLAPPY Score", 0);

	if (_score > highScore)
	{
		highScore = _score;

		def->setIntegerForKey("HIGHSCORE FLAPPY Score", highScore);
	}

	auto highMoneyCount = def->getIntegerForKey("HIGHSCORE FLAPPY Money", 0);

	if (_money > highMoneyCount) {
		highMoneyCount = _money;

		def->setIntegerForKey("HIGHSCORE FLAPPY Money", highMoneyCount);
	}

	def->flush();

	//本次得分
	__String *tempScore = __String::createWithFormat("score: %i", _score);

	auto currentScore = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", this->_visibleSize.height * SCORE_FONT_SIZE);
	currentScore->setPosition(Point(this->_visibleSize.width * 0.25 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y + 40));

	this->addChild(currentScore);
	//历史最高得分
	__String *tempHighScore = __String::createWithFormat("%i", highScore);

	auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/Marker Felt.ttf", this->_visibleSize.height * SCORE_FONT_SIZE);

	highScoreLabel->setColor(Color3B::YELLOW);
	highScoreLabel->setPosition(Point(this->_visibleSize.width * 0.75 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y + 40));

	this->addChild(highScoreLabel);

	//本次金币
	__String *tempMoney = __String::createWithFormat("money: %i", _money);

	auto currentMoney = Label::createWithTTF(tempMoney->getCString(), "fonts/Marker Felt.ttf", this->_visibleSize.height * SCORE_FONT_SIZE);
	currentMoney->setPosition(Point(this->_visibleSize.width * 0.25 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y - 40));

	this->addChild(currentMoney);

	//历史最高金币
	__String *tempHighMoney = __String::createWithFormat("%i", highMoneyCount);

	auto highMoneyLabel = Label::createWithTTF(tempHighMoney->getCString(), "fonts/Marker Felt.ttf", this->_visibleSize.height * SCORE_FONT_SIZE);

	highMoneyLabel->setColor(Color3B::YELLOW);
	highMoneyLabel->setPosition(Point(this->_visibleSize.width * 0.75 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y - 40));

	this->addChild(highMoneyLabel);
}

void SceneGameOver::setScore(unsigned int score)
{
	this->_score = score;
}


void SceneGameOver::setMoneyCount(int moneyCount)
{
	this->_money = moneyCount;
}
