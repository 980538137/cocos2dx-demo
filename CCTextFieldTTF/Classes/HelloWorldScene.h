#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
class HelloWorld : public cocos2d::CCLayer,cocos2d::CCTextFieldDelegate
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

	//当用户启动虚拟键盘时的回调函数

	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);

	//当用户关闭虚拟键盘时的回调函数

	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF *pSender);

	//当用户进行输入时的回调函数

	virtual bool onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen);

	//当用户删除文字时的回调函数

	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen);

};

#endif // __HELLOWORLD_SCENE_H__
