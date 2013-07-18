#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofxAccelerometer.setup();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
	ofBackground(255);
    
    currentScene  = 0;
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 24);
    pattern.loadImage("assets/images/pattern01.jpg");
    
    scenes[0] = new menu();
    scenes[1] = new level01();
    scenes[2] = new mode2();

    scenes[0]->setup();
    scenes[1]->setup();
    scenes[2]->setup();

    ((menu*)scenes[0])->font = &font;
    ((menu*)scenes[0])->currentScene = &currentScene;
    
    ((level01*)scenes[1])->currentScene = &currentScene;
    ((level01*)scenes[1])->pattern = &pattern;

    ((mode2*)scenes[2])->currentScene = &currentScene;
    ((mode2*)scenes[2])->pattern = &pattern;

   
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    scenes[currentScene]->update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    scenes[currentScene]->draw();
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    scenes[currentScene]->touchDown(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

    scenes[currentScene]->touchMove(touch.x, touch.y, touch.id);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

    scenes[currentScene]->touchUp(touch.x, touch.y, touch.id);

}
//--------------------------------------------------------------
void testApp::exit(){}
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}

