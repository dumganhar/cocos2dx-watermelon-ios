#ifndef __sae_h__
#define __sae_h__

#include "cocos2d.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

extern JSClass  *js_sae_SimpleAudioEngine_class;
extern JSObject *js_sae_SimpleAudioEngine_prototype;

JSBool js_sae_SimpleAudioEngine_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_sae_SimpleAudioEngine_finalize(JSContext *cx, JSObject *obj);
void js_register_sae_SimpleAudioEngine(JSContext *cx, JSObject *global);
void register_all_sae(JSContext* cx, JSObject* obj);
JSBool js_sae_SimpleAudioEngine_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_playEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_stopEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_end(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_sae_SimpleAudioEngine_sharedEngine(JSContext *cx, uint32_t argc, jsval *vp);
#endif

