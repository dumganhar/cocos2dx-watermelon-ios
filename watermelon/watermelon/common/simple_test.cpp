#include "jsapi.h"
#include "jsfriendapi.h"
#include "simple_test.hpp"
#include "simple_class.h"

/**
 * You don't need to manage the returned pointer. They live for the whole life of
 * the app.
 */
template <class T>
js_type_class_t *js_get_type_from_native(T* native_obj) {
	js_type_class_t *typeProxy;
	uint32_t typeId = reinterpret_cast<int>(typeid(*native_obj).name());
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

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *js_simple_test_SimpleNativeClass_class;
JSObject *js_simple_test_SimpleNativeClass_prototype;

JSBool js_simple_test_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		const char* ret = cobj->getAnotherMoreComplexField();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
	SimpleNativeClass* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->setSomeField();
		return JS_TRUE;
	}
	if (argc == 1) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		cobj->setSomeField(arg0);
		return JS_TRUE;
	}
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		long long arg0;
		arg0 = jsval_to_long_long(cx, argv[0]);
		long long ret = cobj->receivesLongLong(arg0);
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		long long ret = cobj->thisReturnsALongLong();
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		unsigned int ret = cobj->getObjectType();
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cobj->setAnotherMoreComplexField(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		cobj->setSomeOtherField(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		int ret = cobj->getSomeOtherField();
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		const char* ret = cobj->returnsACString();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 2) {
		std::string arg0;
		std::string arg1;
		arg0 = jsval_to_std_string(cx, argv[0]);
		arg1 = jsval_to_std_string(cx, argv[1]);
		int ret = cobj->doSomeProcessing(arg0, arg1);
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		int ret = cobj->getSomeField();
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		std::string ret = cobj->returnsAString();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	if (argc == 1) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		SimpleNativeClass::func(arg0);
		return JS_TRUE;
	}
	if (argc == 0) {
		SimpleNativeClass::func();
		return JS_TRUE;
	}
	if (argc == 2) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		double arg1;
		JS_ValueToNumber(cx, argv[1], &arg1);
		SimpleNativeClass::func(arg0, arg1);
		return JS_TRUE;
	}
	return JS_FALSE;
}
JSBool js_simple_test_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
	SimpleNativeClass* cobj;

	if (argc == 1) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		cobj = new SimpleNativeClass(arg0);
#ifdef COCOS2D_JAVASCRIPT
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
#endif
		TypeTest<SimpleNativeClass> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		js_proxy_t *proxy;
		JS_NEW_PROXY(proxy, cobj, obj);
#ifdef COCOS2D_JAVASCRIPT
		JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
#endif
	}
	if (argc == 0) {
		cobj = new SimpleNativeClass();
#ifdef COCOS2D_JAVASCRIPT
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
#endif
		TypeTest<SimpleNativeClass> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		js_proxy_t *proxy;
		JS_NEW_PROXY(proxy, cobj, obj);
#ifdef COCOS2D_JAVASCRIPT
		JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
#endif
	}
	if (argc == 2) {
		int arg0;
		JS_ValueToInt32(cx, argv[0], (int32_t *)&arg0);
		int arg1;
		JS_ValueToInt32(cx, argv[1], (int32_t *)&arg1);
		cobj = new SimpleNativeClass(arg0, arg1);
#ifdef COCOS2D_JAVASCRIPT
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
#endif
		TypeTest<SimpleNativeClass> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		js_proxy_t *proxy;
		JS_NEW_PROXY(proxy, cobj, obj);
#ifdef COCOS2D_JAVASCRIPT
		JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
#endif
	}
	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
	return JS_FALSE;
}



void js_simple_test_SimpleNativeClass_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_simple_test_SimpleNativeClass(JSContext *cx, JSObject *global) {
	js_simple_test_SimpleNativeClass_class = (JSClass *)calloc(1, sizeof(JSClass));
	js_simple_test_SimpleNativeClass_class->name = "SimpleNativeClass";
	js_simple_test_SimpleNativeClass_class->addProperty = JS_PropertyStub;
	js_simple_test_SimpleNativeClass_class->delProperty = JS_PropertyStub;
	js_simple_test_SimpleNativeClass_class->getProperty = JS_PropertyStub;
	js_simple_test_SimpleNativeClass_class->setProperty = JS_StrictPropertyStub;
	js_simple_test_SimpleNativeClass_class->enumerate = JS_EnumerateStub;
	js_simple_test_SimpleNativeClass_class->resolve = JS_ResolveStub;
	js_simple_test_SimpleNativeClass_class->convert = JS_ConvertStub;
	js_simple_test_SimpleNativeClass_class->finalize = js_simple_test_SimpleNativeClass_finalize;
	js_simple_test_SimpleNativeClass_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getAnotherMoreComplexField", js_simple_test_SimpleNativeClass_getAnotherMoreComplexField, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("setSomeField", js_simple_test_SimpleNativeClass_setSomeField, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("receivesLongLong", js_simple_test_SimpleNativeClass_receivesLongLong, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("thisReturnsALongLong", js_simple_test_SimpleNativeClass_thisReturnsALongLong, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getObjectType", js_simple_test_SimpleNativeClass_getObjectType, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("setAnotherMoreComplexField", js_simple_test_SimpleNativeClass_setAnotherMoreComplexField, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("setSomeOtherField", js_simple_test_SimpleNativeClass_setSomeOtherField, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getSomeOtherField", js_simple_test_SimpleNativeClass_getSomeOtherField, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("returnsACString", js_simple_test_SimpleNativeClass_returnsACString, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("doSomeProcessing", js_simple_test_SimpleNativeClass_doSomeProcessing, 2, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getSomeField", js_simple_test_SimpleNativeClass_getSomeField, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("returnsAString", js_simple_test_SimpleNativeClass_returnsAString, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("func", js_simple_test_SimpleNativeClass_func, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FS_END
	};

	js_simple_test_SimpleNativeClass_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		js_simple_test_SimpleNativeClass_class,
		js_simple_test_SimpleNativeClass_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<SimpleNativeClass> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = js_simple_test_SimpleNativeClass_class;
		p->proto = js_simple_test_SimpleNativeClass_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_simple_test(JSContext* cx, JSObject* obj) {

	js_register_simple_test_SimpleNativeClass(cx, obj);
}

