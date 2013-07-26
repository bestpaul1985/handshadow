#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofxAccelerometer.setup();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
	ofBackground(255);
    
    currentScene  = 0;
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 80);
    pattern.loadImage("assets/images/gamePlay/pattern02.png");
    
    
    //****XML******************************************
    if( XML.loadFile(ofxiPhoneGetDocumentsDirectory() + "mySettings.xml") ){
		message = "mySettings.xml loaded from documents folder!";
	}else if( XML.loadFile("mySettings.xml") ){
		message = "mySettings.xml loaded from data folder!";
	}else{
		message = "unable to load mySettings.xml check data/ folder";
	}
    
    int levels = XML.getNumTags("STROKE:PT");
    
     if(levels > 0){
        for (int i=0; i<levels; i++) {
            
            xmlPointer tempPoints;
            
            XML.pushTag("STROKE", i);
            int numPtTags = XML.getNumTags("PT");
            if(numPtTags > 0){
                for(int i = 0; i < numPtTags; i++){
                    int x = XML.getValue("PT:X", 0, i);
                    int y = XML.getValue("PT:Y", 0, i);
                    ofPoint temp(x,y);
                    tempPoints.pos.push_back(temp);
                }
            }
            points.push_back(tempPoints);
            XML.popTag();
        }
    }

    CurrentLive             = XML.getValue("SETTING:CURRENTLIVE", 5);
    CurrentLevel            = XML.getValue("SETTING:CURRENTLEVEL", 0);
    CureentUnLackedLevel	= XML.getValue("SETTING:CURRENTUNLACKEDLEVEL", 0);
    CurrentLive = 5;
    //******Scenes*************************************
    scenes[0] = new menu();
    ((menu*)scenes[0])->font = &font;
    ((menu*)scenes[0])->currentScene = &currentScene;
    scenes[0]->setup();
    
    scenes[1] = new Mode01();
    ((Mode01*)scenes[1])->xmlReader(points,&CurrentLive,&CurrentLevel,&currentScene);
    ((Mode01*)scenes[1])->pattern = &pattern;
    scenes[1]->setup();

}

//--------------------------------------------------------------
void testApp::update(){
    
    
    scenes[currentScene]->update();
    
    if (((Mode01*)scenes[1])->bSave) {
        XML.setValue("SETTING:CURRENTLEVEL", CurrentLevel);
        XML.setValue("SETTING:CURRENTLIVE", CurrentLive);
        XML.setValue("SETTING:CURRENTUNLACKEDLEVEL", CureentUnLackedLevel);
        XML.saveFile( ofxiPhoneGetDocumentsDirectory() + "mySettings.xml" );
        message = "mySettings.xml saved to app documents folder";
        ((Mode01*)scenes[1])->bSave = false;
        cout<<message<<endl;
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    scenes[currentScene]->draw();
    
    if (CurrentLive ==0) {
        ofSetColor(255, 240);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(30);
        font.drawString("Buy Lives", 512- font.stringWidth("Purchase")/2,384+font.stringHeight("Purchase")/2);
    }



//    cout<<"CurrentLevel: "<<CurrentLevel<<endl;
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    if (CurrentLive>0) {
        scenes[currentScene]->touchDown(touch.x, touch.y, touch.id);
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    if (CurrentLive>0) {
        scenes[currentScene]->touchMove(touch.x, touch.y, touch.id);
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if (CurrentLive>0) {
        scenes[currentScene]->touchUp(touch.x, touch.y, touch.id);
    }
}
//--------------------------------------------------------------
void testApp::exit(){
    
	XML.setValue("SETTING:CURRENTLEVEL", CurrentLevel);
	XML.setValue("SETTING:CURRENTLIVE", CurrentLive);
	XML.setValue("SETTING:CURRENTUNLACKEDLEVEL", CureentUnLackedLevel);
//    XML.setValue("SETTING:LASTTIME", systemTime);
	XML.saveFile( ofxiPhoneGetDocumentsDirectory() + "mySettings.xml" );
	message = "mySettings.xml saved to app documents folder";
    cout<<message<<endl;
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}

