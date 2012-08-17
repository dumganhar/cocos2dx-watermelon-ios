//
//  js_bindings_ccbreader.cpp
//  watermelon
//
//  Created by Rohan Kuruvilla on 14/08/2012.
//
//

#include "js_bindings_ccbreader.h"
#include "ScriptingCore.h"


USING_NS_CC;
USING_NS_CC_EXT;




static CCNode* loadReader(const char *file, jsval owner) {
    /* Create an autorelease CCNodeLoaderLibrary. */
    
    /* Create an autorelease CCBReader. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("visible", JSLayerLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    //ccbReader->mOwner = owner;
    
    CCBCallbackProxy *ccBCallbackProxy = new CCBCallbackProxy();
    //ccbReader->setOwner(dynamic_cast<CCObject *>(ccBCallbackProxy));
    
    CCNode * node = ccbReader->readNodeGraphFromFile("./", file, dynamic_cast<CCObject *>(ccBCallbackProxy));
    
    return node;
}


JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
		const char *arg0;
        do {
            JSString *tmp = JS_ValueToString(cx, argv[0]);
            arg0 = JS_EncodeString(cx, tmp);
        }
        while (0);
        //jsval jsret;
        //        do {
        //            if (ret) {
        //                js_proxy_t *proxy = js_get_or_create_proxy<CocosBuilderTestScene>(cx, ret);
        //                jsret = OBJECT_TO_JSVAL(proxy->obj);
        //            } else {
        //                jsret = JSVAL_NULL;
        //            }
        //        } while (0);
        //        JS_SET_RVAL(cx, vp, jsret);
        //        return JS_TRUE;
        //
        jsval obj =  argc == 2 ? argv[1] : JSVAL_NULL;
        js_log("%s: + ", JSVAL_TO_OBJECT(obj));
        CCNode * ret = loadReader(arg0, obj);
        jsval jsret;
		if (ret) {
			js_proxy_t *proxy;
			JS_GET_PROXY(proxy, ret);
			if (proxy) {
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				// create a new js obj of that class
				proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			}
		} else {
			jsret = JSVAL_NULL;
		}
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;

    }
    return JS_FALSE;
}


void registerCocosBuilder(JSContext *cx, JSObject *obj) {
    
    
    jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

    JSObject *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, obj, "(function () { cc = cc || {}; cc.Reader = cc.Reader || {}; return cc.Reader; })()"));
    JS_DefineFunction(cx, tmpObj, "load", js_CocosBuilder_Run, 2, JSPROP_READONLY | JSPROP_PERMANENT)    ;
    
}
