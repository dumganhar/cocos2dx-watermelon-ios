/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ChipmunkSprite.h"
#include "ScriptingCore.h"
#include "js_manual_conversions.h"

using namespace cocos2d;


static CCPoint cpVect_to_ccPoint(cpVect p) {
    return CCPoint(p.x, p.y);
}

static cpVect ccPoint_to_cpVect(CCPoint point) {
    cpVect t;
    t.x = point.x;
    t.y = point.y;
    return t;
}

const cocos2d::CCPoint& ChipmunkSprite::getPosition() {
    cpVect temp = cpBodyGetPos(_body);

	return cpVect_to_ccPoint(temp);
}



void ChipmunkSprite::setPosition(const cocos2d::CCPoint &pos) {
    cpBodySetPos(_body, ccPoint_to_cpVect(getPosition()));
   // CCNode::setPosition(pos);
}

cocos2d::CCAffineTransform ChipmunkSprite::nodeToParentTransform() {
    cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(m_fRotation)) : _body->rot);
    CGFloat x = _body->p.x + rot.x*-m_tAnchorPointInPoints.x - rot.y*-m_tAnchorPointInPoints.y;
    CGFloat y = _body->p.y + rot.y*-m_tAnchorPointInPoints.x + rot.x*-m_tAnchorPointInPoints.y;
    
    if(m_bIgnoreAnchorPointForPosition){
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }
    
    return (m_tTransform = cocos2d::__CCAffineTransformMake(rot.x, rot.y, -rot.y, rot.x, x,	y));
}



/*
 * ChipmunkSprite
 */
#pragma mark - ChipmunkSprite

JSClass* JSPROXY_ChipmunkSprite_class = NULL;
JSObject* JSPROXY_ChipmunkSprite_object = NULL;
// Constructor

// Destructor
void JSPROXY_ChipmunkSprite_finalize(JSFreeOp *fop, JSObject *obj)
{

}

// Arguments:
// Ret value: cpBody* (N/A)
JSBool JSPROXY_ChipmunkSprite_body(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	ChipmunkSprite* real = (ChipmunkSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
	cpBody* ret_val;
    
	ret_val = real->_body;
    jsval ret_jsval = opaque_to_jsval(cx, ret_val);
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments:
// Ret value: BOOL (b)
JSBool JSPROXY_ChipmunkSprite_ignoreBodyRotation(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	ChipmunkSprite* real = (ChipmunkSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)

	bool ret_val;
    
	ret_val = real->_ignoreBodyRotation;
	JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void (None)
JSBool JSPROXY_ChipmunkSprite_setBody_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	ChipmunkSprite* real = (ChipmunkSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	
    cpBody* arg0;
    
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
    
	real->setBody((cpBody*)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: BOOL
// Ret value: void (None)
JSBool JSPROXY_ChipmunkSprite_setIgnoreBodyRotation_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	ChipmunkSprite* real = (ChipmunkSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	JSBool arg0;
    
	ok &= JS_ValueToBoolean( cx, *argvp++, &arg0 );
	if( ! ok ) return JS_FALSE;
    
	real->setIgnoreBodyRotation((bool)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}


template <class T>
js_type_class_t *js_get_type_from_native(T* native_obj) {
	js_type_class_t *typeProxy;
	uint32_t typeId = reinterpret_cast<int>(typeid(*native_obj).name());
    const char *nam = typeid(*native_obj).name();
	HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
	if (!typeProxy) {
		TypeInfo *typeInfo = dynamic_cast<TypeInfo *>(native_obj);
		if (typeInfo) {
			typeId = typeInfo->getClassTypeInfo();
		} else {
			typeId = reinterpret_cast<int>(typeid(T).name());
		}
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
	}
	return typeProxy;
}

/**
 * you don't need to manage the returned pointer. The returned pointer should be deleted
 * using JS_REMOVE_PROXY. Most of the time you do that in the C++ destructor.
 */
template<class T>
js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj) {
	js_proxy_t *proxy;
	HASH_FIND_PTR(_native_js_global_ht, &native_obj, proxy);
	if (!proxy) {
		js_type_class_t *typeProxy = js_get_type_from_native<T>(native_obj);
		assert(typeProxy);
		JSObject* js_obj = JS_NewObject(cx, typeProxy->jsclass, typeProxy->proto, typeProxy->parentProto);
		JS_NEW_PROXY(proxy, native_obj, js_obj);
        
		JS_AddNamedObjectRoot(cx, &proxy->obj, typeid(native_obj).name());
		return proxy;
	} else {
		return proxy;
	}
	return NULL;
}


template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
    
	return JS_TRUE;
}

// Arguments: NSString*, CGRect
// Ret value: ChipmunkSprite* (o)
JSBool JSPROXY_ChipmunkSprite_spriteWithFile_rect__static(JSContext *cx, uint32_t argc, jsval *vp) {
    
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cocos2d::CCRect arg1;
		arg1 = jsval_to_ccrect(cx, argv[1]);
        ChipmunkSprite* ret = new ChipmunkSprite();
        ret->initWithFile(arg0, arg1);
		jsval jsret;
		do {
			if (ret) {
                TypeTest<ChipmunkSprite> t;
                js_type_class_t *typeClass;
                uint32_t typeId = t.s_id();
                HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
                assert(typeClass);
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
				jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p;
                JS_NEW_PROXY(p, ret, obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		ChipmunkSprite* ret = new ChipmunkSprite();
        ret->initWithFile(arg0);
//        ret = (ChipmunkSprite*)ChipmunkSprite::spriteWithFile(arg0);
        const char *nam = typeid(*ret).name();
        
		jsval jsret;
		do {
			if (ret) {
				TypeTest<ChipmunkSprite> t;
                js_type_class_t *typeClass;
                uint32_t typeId = t.s_id();
                HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
                assert(typeClass);
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
				jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p;
                JS_NEW_PROXY(p, ret, obj);
                
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	return JS_FALSE;
    
//	JSB_PRECONDITION( argc >= 1 && argc <= 2 , "Invalid number of arguments" );
//	jsval *argvp = JS_ARGV(cx,vp);
//	JSBool ok = JS_TRUE;
//	NSString* arg0; CGRect arg1;
//    
//	ok &= jsval_to_nsstring( cx, *argvp++, &arg0 );
//	if (argc >= 2) {
//		ok &= jsval_to_CGRect( cx, *argvp++, (CGRect*) &arg1 );
//	}
//	if( ! ok ) return JS_FALSE;
//	ChipmunkSprite* ret_val;
//    
//	if( argc == 1 ) {
//		ret_val = [ChipmunkSprite spriteWithFile:(NSString*)arg0  ];
//	}
//	else if( argc == 2 ) {
//		ret_val = [ChipmunkSprite spriteWithFile:(NSString*)arg0 rect:(CGRect)arg1  ];
//	}
//	else
//		return JS_FALSE;
//    
//    
//	JSObject *jsobj = get_or_create_jsobject_from_realobj( cx, ret_val );
//	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
//    
//	return JS_TRUE;
}

// Arguments: CCSpriteFrame*
// Ret value: ChipmunkSprite* (o)
JSBool JSPROXY_ChipmunkSprite_spriteWithSpriteFrame__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	cocos2d::CCSpriteFrame* arg0;
	if (argc >= 1) {
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCSpriteFrame*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, arg0)
		} while (0);
	}
    ChipmunkSprite* ret = new ChipmunkSprite();
    ret->initWithSpriteFrame(arg0);
	jsval jsret;
	do {
		if (ret) {
            TypeTest<ChipmunkSprite> t;
            js_type_class_t *typeClass;
            uint32_t typeId = t.s_id();
            HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
            assert(typeClass);
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p;
            JS_NEW_PROXY(p, ret, obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

// Arguments: NSString*
// Ret value: ChipmunkSprite* (o)
JSBool JSPROXY_ChipmunkSprite_spriteWithSpriteFrameName__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	const char* arg0;
	if (argc >= 1) {
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
	}
    ChipmunkSprite* ret = new ChipmunkSprite();
    ret->initWithSpriteFrameName(arg0);
	jsval jsret;
	do {
		if (ret) {
            TypeTest<ChipmunkSprite> t;
            js_type_class_t *typeClass;
            uint32_t typeId = t.s_id();
            HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
            assert(typeClass);
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p;
            JS_NEW_PROXY(p, ret, obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

void JSPROXY_ChipmunkSprite_createClass(JSContext *cx, JSObject* globalObj)
{
	JSPROXY_ChipmunkSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSPROXY_ChipmunkSprite_class->name = "ChipmunkSprite";
	JSPROXY_ChipmunkSprite_class->addProperty = JS_PropertyStub;
	JSPROXY_ChipmunkSprite_class->delProperty = JS_PropertyStub;
	JSPROXY_ChipmunkSprite_class->getProperty = JS_PropertyStub;
	JSPROXY_ChipmunkSprite_class->setProperty = JS_StrictPropertyStub;
	JSPROXY_ChipmunkSprite_class->enumerate = JS_EnumerateStub;
	JSPROXY_ChipmunkSprite_class->resolve = JS_ResolveStub;
	JSPROXY_ChipmunkSprite_class->convert = JS_ConvertStub;
	JSPROXY_ChipmunkSprite_class->finalize = JSPROXY_ChipmunkSprite_finalize;
	JSPROXY_ChipmunkSprite_class->flags = 0;
    
	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("getBody", JSPROXY_ChipmunkSprite_body, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("getIgnoreBodyRotation", JSPROXY_ChipmunkSprite_ignoreBodyRotation, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("setBody", JSPROXY_ChipmunkSprite_setBody_, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("setIgnoreBodyRotation", JSPROXY_ChipmunkSprite_setIgnoreBodyRotation_, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", JSPROXY_ChipmunkSprite_spriteWithFile_rect__static, 2, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrame", JSPROXY_ChipmunkSprite_spriteWithSpriteFrame__static, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrameName", JSPROXY_ChipmunkSprite_spriteWithSpriteFrameName__static, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
    TypeTest<cocos2d::CCSprite> t1;
    js_type_class_t *typeClass;
    uint32_t typeId = t1.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
    assert(typeClass);

	JSPROXY_ChipmunkSprite_object = JS_InitClass(cx, globalObj, typeClass->proto, JSPROXY_ChipmunkSprite_class, dummy_constructor<ChipmunkSprite>, 0,properties,funcs,NULL,st_funcs);
    
    TypeTest<ChipmunkSprite> t;
	js_type_class_t *p;
	typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = JSPROXY_ChipmunkSprite_class;
		p->proto = JSPROXY_ChipmunkSprite_object;
		p->parentProto = typeClass->proto;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


void register_ChipmunkSprite(JSContext *cx, JSObject *obj) {
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
    JSPROXY_ChipmunkSprite_createClass(cx, obj);
}


//

//-(BOOL) dirty
//{
//	return YES;
//}
//// Override the setters and getters to always reflect the body's properties.
//-(CGPoint)position
//{
//	return cpBodyGetPos(_body);
//}
//
//-(void)setPosition:(CGPoint)position
//{
//	cpBodySetPos(_body, position);
//}
//
//-(float)rotation
//{
//	return (_ignoreBodyRotation ? super.rotation : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(_body)));
//}
//
//-(void)setRotation:(float)rotation
//{
//	if(_ignoreBodyRotation){
//		super.rotation = rotation;
//	} else {
//		cpBodySetAngle(_body, -CC_DEGREES_TO_RADIANS(rotation));
//	}
//}
//
//// returns the transform matrix according the Chipmunk Body values
//-(CGAffineTransform) nodeToParentTransform
//{	
//	cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(rotationX_)) : _body->rot);
//	CGFloat x = _body->p.x + rot.x*-anchorPointInPoints_.x - rot.y*-anchorPointInPoints_.y;
//	CGFloat y = _body->p.y + rot.y*-anchorPointInPoints_.x + rot.x*-anchorPointInPoints_.y;
//	
//	if(ignoreAnchorPointForPosition_){
//		x += anchorPointInPoints_.x;
//		y += anchorPointInPoints_.y;
//	}
//	
//	return (transform_ = CGAffineTransformMake(rot.x, rot.y, -rot.y,	rot.x, x,	y));
//}
//
//@end
