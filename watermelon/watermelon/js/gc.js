//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helper.js");

director = cc.Director.getInstance();
_winSize = director.getWinSize();
winSize = {width:_winSize.width, height:_winSize.height};
centerPos = cc.p( winSize.width/2, winSize.height/2 );

cc.log("**** 1 ****");
dumpRoot();
garbageCollect();

//
// Simple subclass
//

cc.LayerGradient.extend = function (prop) {
    var _super = this.prototype;

    // Instantiate a base class (but only create the instance,
    // don't run the init constructor)
    initializing = true;
    var prototype = new this();
    initializing = false;
    fnTest = /xyz/.test(function(){xyz;}) ? /\b_super\b/ : /.*/;

    // Copy the properties over onto the new prototype
    for (var name in prop) {
        // Check if we're overwriting an existing function
        prototype[name] = typeof prop[name] == "function" &&
            typeof _super[name] == "function" && fnTest.test(prop[name]) ?
            (function (name, fn) {
                return function () {
                    var tmp = this._super;

                    // Add a new ._super() method that is the same method
                    // but on the super-class
                    this._super = _super[name];

                    // The method only need to be bound temporarily, so we
                    // remove it when we're done executing
                    var ret = fn.apply(this, arguments);
                    this._super = tmp;

                    return ret;
                };
            })(name, prop[name]) :
            prop[name];
    }

    // The dummy class constructor
    function Class() {
        // All construction is actually done in the init method
        if (!initializing && this.ctor)
            this.ctor.apply(this, arguments);
    }

    // Populate our constructed prototype object
    Class.prototype = prototype;

    // Enforce the constructor to be what we expect
    Class.prototype.constructor = Class;

    // And make this class extendable
    Class.extend = arguments.callee;

    return Class;
};

cc.log("**** 3 ****");
dumpRoot();
garbageCollect();

//
// Base Layer
//
var BaseLayer = cc.LayerGradient.extend({

	ctor:function () {
                                        try {
                                        log("IN HERE");
	    var parent = new cc.LayerGradient();
	    __associateObjWithNative(this, parent);
	    this.init(cc.c4(0, 0, 0, 255), cc.c4(0, 128, 255, 255));

	    // add title and subtitle
	    var label = cc.LabelTTF.create(this.title(), "Arial", 28);
	    this.addChild(label, 1);
	    label.setPosition( cc.p(winSize.width / 2, winSize.height - 40));

	    var strSubtitle = this.subtitle();
	    if (strSubtitle != "") {
		var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
		this.addChild(l, 1);
		l.setPosition( cc.p(winSize.width / 2, winSize.height - 70));
	    }

	    var strCode = this.code();
	    if( strCode !="" ) {
		var label = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
		label.setPosition( cc.p( winSize.width/2, winSize.height-120) );
		this.addChild( label,10 );

		var labelbg = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
		labelbg.setColor( cc.c3(10,10,255) );
		labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-120 -1) );
		this.addChild( labelbg,9);
	    }

	    // Menu
	    var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
	    var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
	    var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
	    var menu = cc.Menu.create(item1, item2, item3 );

	    menu.setPosition( cc.p(0,0) );
	    item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
	    item2.setPosition( cc.p(winSize.width / 2, 30));
	    item3.setPosition( cc.p(winSize.width / 2 + 100, 30));

	    this.addChild(menu, 1);

	    cc.log("**** 1 ****");
	    dumpRoot();
	    garbageCollect();
                                        } catch(e) {log(e);}
	},

	title:function () {
	    return "No Title";
	},

	subtitle:function () {
	    return "";
	},

	code:function () {
	    return "";
	},

	restartCallback:function (sender) {
	    cc.log("restart");
	    dumpRoot();
	    garbageCollect();
	},

	nextCallback:function (sender) {
	    log("next");
//	    dumpRoot();
//	    garbageCollect();
	},

	backCallback:function (sender) {
	    cc.log("back");
	    dumpRoot();
	    garbageCollect();
	},

	onEnter2:function () {
	    // DO NOT CALL this._super()
	    //        this._super();
	},

	onEnter:function () {
	    // DO NOT CALL this._super()
	    //        this._super();

	    cc.log("**** 7 ****");
	    dumpRoot();
	    garbageCollect();
	},

    });

cc.log("**** 4 ****");
dumpRoot();
garbageCollect();

//------------------------------------------------------------------
//
// Playground 
//
//------------------------------------------------------------------
var Playground = BaseLayer.extend({
	onEnter:function () {
	    this._super();

	    cc.log("Playground onEnter");
	},

	title:function () {
	    return "Testing Accelerometer";
	},

	subtitle:function () {
	    return "See console on device";
	},
	code:function () {
	    return "";
	}
    });


cc.log("**** 5 ****");
dumpRoot();
garbageCollect();

var scene = cc.Scene.create();
var layer = new Playground();
scene.addChild( layer );

var runningScene = director.getRunningScene();
if( runningScene == null )
    director.runWithScene( scene );
else
    director.replaceScene( cc.TransitionFade.create(0.5, scene ) );

