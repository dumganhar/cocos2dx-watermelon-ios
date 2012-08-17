//
//  js_bindings_ccbreader.h
//  watermelon
//
//  Created by Rohan Kuruvilla on 14/08/2012.
//
//
#include "jsapi.h"
#include "cocos-ext.h"
#include "cocos2d_specifics.hpp"

class JSLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(JSLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBCallbackProxy);
};

void registerCocosBuilder(JSContext *cx, JSObject *global);
JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp);