#include "cocos2d.h"
#include "chipmunk.h"

// A Cocos2D 2.0 sprite subclass that is bound to a Chipmunk body.
// It works with either regular Chipmunk or Objective-Chipmunk.

class ChipmunkSprite : public cocos2d::CCSprite
{
public:
    ChipmunkSprite() {
        this->autorelease();
    }
	cpBody	*_body;
	bool	_ignoreBodyRotation;
    virtual void setPosition(const cocos2d::CCPoint &p);
    const cocos2d::CCPoint& getPosition();
    void setBody(cpBody* body) {_body = body;}
    void setIgnoreBodyRotation(bool rot) {_ignoreBodyRotation = rot;}
    inline virtual bool isDirty(void) { return true; }
    virtual cocos2d::CCAffineTransform nodeToParentTransform();
};
extern "C" {
void JSPROXY_ChipmunkSprite_createClass(JSContext *cx, JSObject* globalObj);
}

void register_ChipmunkSprite(JSContext *cx, JSObject *obj);
