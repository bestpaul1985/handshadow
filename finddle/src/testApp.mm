#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofxAccelerometer.setup();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetCircleResolution(400);
    ofEnableSmoothing();
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	ofBackground(255);
    
    currentScene  = 0;
    pattern.loadImage("assets/images/gamePlay/bg.png");
    
    scale = 0.0f;
    accFrc = &ofxAccelerometer.getForce();
    touchNum = 0;
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

    coin                = XML.getValue("SETTING:COIN",1000);
    level               = XML.getValue("SETTING:LEVEL", 0);
    unLockedLevel       = XML.getValue("SETTING:UNLACKEDLEVEL", 0);
    coinChance          = XML.getValue("SETTING:COINCHANCE", 2);
    
    timeSlowerChance    = XML.getValue("SETTING:TIMESLOWER", 2);
    dotExtenderChance   = XML.getValue("SETTING:DOTEXTENDER", 2);
    dotFreezerChance    = XML.getValue("SETTING:FREEZERCHANCE", 2);
    firstPlay           = XML.getValue("SETTING:FIRST", 0);
    //******Scenes*************************************
    scenes[0] = new menu();
    ((menu*)scenes[0])->scene = &currentScene;
    ((menu*)scenes[0])->coin = &coin;
    ((menu*)scenes[0])->level = &level;
    ((menu*)scenes[0])->unLockedLevel = &unLockedLevel;
    ((menu*)scenes[0])->coinChance = &coinChance;
    ((menu*)scenes[0])->timeSlowerChance = &timeSlowerChance;
    ((menu*)scenes[0])->dotExtenderChance = &dotExtenderChance;
    ((menu*)scenes[0])->dotFreezerChance = &dotFreezerChance;
    ((menu*)scenes[0])->firstPlay = &firstPlay;
    scenes[0]->setup();
    
    scenes[1] = new handDetector();
    ((handDetector*)scenes[1])->scene = &currentScene;
    ((handDetector*)scenes[1])->firstPlay = &firstPlay;
    ((handDetector*)scenes[1])->scale = &scale;
    ((handDetector*)scenes[1])->touchNum = &touchNum;
    scenes[1]->setup();
    
    scenes[2] = new Mode01();
    ((Mode01*)scenes[2])->xmlReader(points,&level,&currentScene);
    ((Mode01*)scenes[2])->coin = &coin;
    ((Mode01*)scenes[2])->scale = &scale;
    ((Mode01*)scenes[2])->pattern = &pattern;
    ((Mode01*)scenes[2])->coinChance = &coinChance;
    ((Mode01*)scenes[2])->accFrc = accFrc;
    ((Mode01*)scenes[2])->timeSlowerChance = &timeSlowerChance;
    ((Mode01*)scenes[2])->dotExtenderChance = &dotExtenderChance;
    ((Mode01*)scenes[2])->dotFreezerChance = &dotFreezerChance;
    scenes[2]->setup();

    //feedback
//     cout<<"coinChance: "<<coinChance<<" timeSlowerChance: "<<timeSlowerChance<<" dotExtenderChance: "<<dotExtenderChance<<" dotFreezerChance"<<dotFreezerChance<<endl;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    scenes[currentScene]->update();
    
    if (level>unLockedLevel) {
        unLockedLevel = level;
    }
    
    if (((menu*)scenes[0])->bSave || ((Mode01*)scenes[2])->bSave ) {
        
        XML.setValue("SETTING:COIN", coin);
        XML.setValue("SETTING:LEVEL", level);
        XML.setValue("SETTING:UNLACKEDLEVEL", unLockedLevel);
        XML.setValue("SETTING:FIRST", firstPlay);
        
        XML.setValue("SETTING:COINCHANCE", coinChance);
        XML.setValue("SETTING:TIMESLOWER", timeSlowerChance);
        XML.setValue("SETTING:DOTEXTENDER", dotExtenderChance);
        XML.setValue("SETTING:FREEZERCHANCE", dotFreezerChance);
        
        XML.saveFile( ofxiPhoneGetDocumentsDirectory() + "mySettings.xml" );
        ((Mode01*)scenes[2])->bSave = false;
        ((menu*)scenes[0])->bSave =false;
        
        message = "mySettings.xml saved to app documents folder";
        cout<<message<<endl;
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    scenes[currentScene]->draw();
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    scenes[currentScene]->touchDown(touch.x, touch.y, touch.id);
    touchNum = touch.numTouches;

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    scenes[currentScene]->touchMove(touch.x, touch.y, touch.id);
    touchNum = touch.numTouches;

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    scenes[currentScene]->touchUp(touch.x, touch.y, touch.id);
    touchNum = touch.numTouches;
}
//--------------------------------------------------------------
void testApp::exit(){
    
    XML.setValue("SETTING:COIN", coin);
	XML.setValue("SETTING:LEVEL", level);
	XML.setValue("SETTING:UNLACKEDLEVEL", unLockedLevel);
    XML.setValue("SETTING:COINCHANCE", coinChance);
    XML.setValue("SETTING:TIMESLOWER", timeSlowerChance);
    XML.setValue("SETTING:DOTEXTENDER", dotExtenderChance);
    XML.setValue("SETTING:FREEZERCHANCE", dotFreezerChance);
    XML.setValue("SETTING:FIRST", firstPlay);
    
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

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

    if (newOrientation == 4) {
        iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    }else if(newOrientation ==3){
        iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    }

}

