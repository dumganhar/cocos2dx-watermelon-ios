#include "jsapi.h"
#include "jsfriendapi.h"
#include "sae.hpp"
#include "SimpleAudioEngine.h"


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


JSClass  *js_sae_SimpleAudioEngine_class;
JSObject *js_sae_SimpleAudioEngine_prototype;

JSBool js_sae_SimpleAudioEngine_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		bool ret = cobj->willPlayBackgroundMusic();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cobj->preloadBackgroundMusic(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->rewindBackgroundMusic();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cobj->preloadEffect(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
	CocosDenshion::SimpleAudioEngine* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cobj->playBackgroundMusic(arg0);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		JSBool arg1;
		JS_ValueToBoolean(cx, argv[1], &arg1);
		cobj->playBackgroundMusic(arg0, arg1);
		return JS_TRUE;
	}
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->pauseAllEffects();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		float ret = cobj->getEffectsVolume();
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
	CocosDenshion::SimpleAudioEngine* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->stopBackgroundMusic();
		return JS_TRUE;
	}
	if (argc == 1) {
		JSBool arg0;
		JS_ValueToBoolean(cx, argv[0], &arg0);
		cobj->stopBackgroundMusic(arg0);
		return JS_TRUE;
	}
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->pauseBackgroundMusic();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		bool ret = cobj->isBackgroundMusicPlaying();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->resumeBackgroundMusic();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->stopAllEffects();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		unsigned int arg0;
		JS_ValueToECMAUint32(cx, argv[0], &arg0);
		cobj->pauseEffect(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_playEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
	CocosDenshion::SimpleAudioEngine* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		unsigned int ret = cobj->playEffect(arg0);
		jsval jsret; JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		JSBool arg1;
		JS_ValueToBoolean(cx, argv[1], &arg1);
		unsigned int ret = cobj->playEffect(arg0, arg1);
		jsval jsret; JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		double arg0;
		JS_ValueToNumber(cx, argv[0], &arg0);
		cobj->setEffectsVolume(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_stopEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		unsigned int arg0;
		JS_ValueToECMAUint32(cx, argv[0], &arg0);
		cobj->stopEffect(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		cobj->resumeAllEffects();
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 0) {
		float ret = cobj->getBackgroundMusicVolume();
		jsval jsret;
		JS_NewNumberValue(cx, ret, &jsret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		double arg0;
		JS_ValueToNumber(cx, argv[0], &arg0);
		cobj->setBackgroundMusicVolume(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cobj->unloadEffect(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CocosDenshion::SimpleAudioEngine* cobj = (CocosDenshion::SimpleAudioEngine *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)

	if (argc == 1) {
		unsigned int arg0;
		JS_ValueToECMAUint32(cx, argv[0], &arg0);
		cobj->resumeEffect(arg0);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_sae_SimpleAudioEngine_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	CocosDenshion::SimpleAudioEngine::end();
	return JS_TRUE;
}

JSBool js_sae_SimpleAudioEngine_sharedEngine(JSContext *cx, uint32_t argc, jsval *vp)
{
	CocosDenshion::SimpleAudioEngine* ret = CocosDenshion::SimpleAudioEngine::sharedEngine();
	jsval jsret;
	do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<CocosDenshion::SimpleAudioEngine>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}



void js_sae_SimpleAudioEngine_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_sae_SimpleAudioEngine(JSContext *cx, JSObject *global) {
	js_sae_SimpleAudioEngine_class = (JSClass *)calloc(1, sizeof(JSClass));
	js_sae_SimpleAudioEngine_class->name = "SimpleAudioEngine";
	js_sae_SimpleAudioEngine_class->addProperty = JS_PropertyStub;
	js_sae_SimpleAudioEngine_class->delProperty = JS_PropertyStub;
	js_sae_SimpleAudioEngine_class->getProperty = JS_PropertyStub;
	js_sae_SimpleAudioEngine_class->setProperty = JS_StrictPropertyStub;
	js_sae_SimpleAudioEngine_class->enumerate = JS_EnumerateStub;
	js_sae_SimpleAudioEngine_class->resolve = JS_ResolveStub;
	js_sae_SimpleAudioEngine_class->convert = JS_ConvertStub;
	js_sae_SimpleAudioEngine_class->finalize = js_sae_SimpleAudioEngine_finalize;
	js_sae_SimpleAudioEngine_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("willPlayBackgroundMusic", js_sae_SimpleAudioEngine_willPlayBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("preloadBackgroundMusic", js_sae_SimpleAudioEngine_preloadBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("rewindBackgroundMusic", js_sae_SimpleAudioEngine_rewindBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("preloadEffect", js_sae_SimpleAudioEngine_preloadEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("playBackgroundMusic", js_sae_SimpleAudioEngine_playBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("pauseAllEffects", js_sae_SimpleAudioEngine_pauseAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getEffectsVolume", js_sae_SimpleAudioEngine_getEffectsVolume, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("stopBackgroundMusic", js_sae_SimpleAudioEngine_stopBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("pauseBackgroundMusic", js_sae_SimpleAudioEngine_pauseBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("isBackgroundMusicPlaying", js_sae_SimpleAudioEngine_isBackgroundMusicPlaying, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("resumeBackgroundMusic", js_sae_SimpleAudioEngine_resumeBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("stopAllEffects", js_sae_SimpleAudioEngine_stopAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("pauseEffect", js_sae_SimpleAudioEngine_pauseEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("playEffect", js_sae_SimpleAudioEngine_playEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("setEffectsVolume", js_sae_SimpleAudioEngine_setEffectsVolume, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("stopEffect", js_sae_SimpleAudioEngine_stopEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("resumeAllEffects", js_sae_SimpleAudioEngine_resumeAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getBackgroundMusicVolume", js_sae_SimpleAudioEngine_getBackgroundMusicVolume, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("setBackgroundMusicVolume", js_sae_SimpleAudioEngine_setBackgroundMusicVolume, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("unloadEffect", js_sae_SimpleAudioEngine_unloadEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("resumeEffect", js_sae_SimpleAudioEngine_resumeEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_sae_SimpleAudioEngine_end, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("getInstance", js_sae_SimpleAudioEngine_sharedEngine, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FS_END
	};

	js_sae_SimpleAudioEngine_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		js_sae_SimpleAudioEngine_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<CocosDenshion::SimpleAudioEngine> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = js_sae_SimpleAudioEngine_class;
		p->proto = js_sae_SimpleAudioEngine_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_sae(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
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

	js_register_sae_SimpleAudioEngine(cx, obj);
}

