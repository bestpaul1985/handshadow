#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofxAccelerometer.setup();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
	ofBackground(255);
    
    currentScene  = 0;
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

    coin                = XML.getValue("SETTING:COIN",1000);
    CurrentLevel        = XML.getValue("SETTING:CURRENTLEVEL", 0);
    unLackedLevel       = XML.getValue("SETTING:CURRENTUNLACKEDLEVEL", 0);
    coinChance          = XML.getValue("SETTING:COINCHANCE", 2);
    timeSlowerChance    = XML.getValue("SETTING:TIMESLOWER", 2);
    dotExtenderChance   = XML.getValue("SETTING:DOTEXTENDER", 2);
    dotFreezerChance    = XML.getValue("SETTING:FREEZERCHANCE", 2);
    
    //******Scenes*************************************
    scenes[0] = new menu();
    ((menu*)scenes[0])->currentScene = &currentScene;
    ((menu*)scenes[0])->coin = &coin;
    ((menu*)scenes[0])->coinChance = &coinChance;
    ((menu*)scenes[0])->timeSlowerChance = &timeSlowerChance;
    ((menu*)scenes[0])->dotExtenderChance = &dotExtenderChance;
    ((menu*)scenes[0])->dotFreezerChance = &dotFreezerChance;
    scenes[0]->setup();
    
    scenes[1] = new handDetector();
    ((handDetector*)scenes[1])->scene = &currentScene;
    scenes[1]->setup();
    
    scenes[2] = new Mode01();
    ((Mode01*)scenes[2])->xmlReader(points,&CurrentLevel,&currentScene);
    ((Mode01*)scenes[2])->coin = &coin;
    ((Mode01*)scenes[2])->pattern = &pattern;
    ((Mode01*)scenes[2])->coinChance = &coinChance;
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
    
    if (((Mode01*)scenes[1])->bSave || ((menu*)scenes[0])->bSave) {
        
        XML.setValue("SETTING:COIN", coin);
        XML.setValue("SETTING:CURRENTLEVEL", CurrentLevel);
        XML.setValue("SETTING:CURRENTUNLACKEDLEVEL", unLackedLevel);
        
        XML.setValue("SETTING:COINCHANCE", coinChance);
        XML.setValue("SETTING:TIMESLOWER", timeSlowerChance);
        XML.setValue("SETTING:DOTEXTENDER", dotExtenderChance);
        XML.setValue("SETTING:FREEZERCHANCE", dotFreezerChance);
        
        XML.saveFile( ofxiPhoneGetDocumentsDirectory() + "mySettings.xml" );
        ((Mode01*)scenes[1])->bSave = false;
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
    
    XML.setValue("SETTING:COIN", coin);
	XML.setValue("SETTING:CURRENTLEVEL", CurrentLevel);
	XML.setValue("SETTING:CURRENTUNLACKEDLEVEL", unLackedLevel);
    XML.setValue("SETTING:COINCHANCE", coinChance);
    XML.setValue("SETTING:TIMESLOWER", timeSlowerChance);
    XML.setValue("SETTING:DOTEXTENDER", dotExtenderChance);
    XML.setValue("SETTING:FREEZERCHANCE", dotFreezerChance);
    
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

