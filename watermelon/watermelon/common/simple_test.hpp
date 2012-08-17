#ifndef __simple_test_h__
#define __simple_test_h__

#include "cocos2d.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

extern JSClass  *js_simple_test_SimpleNativeClass_class;
extern JSObject *js_simple_test_SimpleNativeClass_prototype;

JSBool js_simple_test_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_simple_test_SimpleNativeClass_finalize(JSContext *cx, JSObject *obj);
void js_register_simple_test_SimpleNativeClass(JSContext *cx, JSObject *global);
void register_all_simple_test(JSContext* cx, JSObject* obj);
JSBool js_simple_test_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_simple_test_SimpleNativeClass_SimpleNativeClass(JSContext *cx, uint32_t argc, jsval *vp);
#endif

