#include "testApp.h"
#include "ofAppiOSWindow.h"
#import "AlertViewDelegate.h"

AlertViewDelegate * alertViewDelegate = nil;
//--------------------------------------------------------------
void testApp::setup(){
    
    coins00 = new ofxInAppProduct("com.handshadow.finddle.IAP005");
    coins01 = new ofxInAppProduct("com.handshadow.finddle.IAP006");
    coins02 = new ofxInAppProduct("com.handshadow.finddle.IAP007");

    //    restoreAllPreviousTransactions();
	ofTrueTypeFont::setGlobalDpi(72);
	ofxAccelerometer.setup();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetCircleResolution(400);
    ofEnableSmoothing();
    
	ofBackground(255);
    currentScene  = 0;
    preScene = 0;
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
    int upGrades = XML.getNumTags("UPGRADE:PT");
    if(upGrades > 0){
        for (int i=0; i<upGrades; i++) {
            
            xmlPointer tempPoints;
            XML.pushTag("UPGRADE", i);
            int numPtTags = XML.getNumTags("PT");
            if(numPtTags > 0){
                for(int i = 0; i < numPtTags; i++){
                    int x = XML.getValue("PT:X", 0, i);
                    int y = XML.getValue("PT:Y", 0, i);
                    ofPoint temp(x,y);
                    tempPoints.pos.push_back(temp);
                }
            }
            
            upGradePrices.push_back(tempPoints);
            XML.popTag();
        }
    }
    
    live                = XML.getValue("SETTING:LIVE",0);
    preLive             = live;
    coin                = XML.getValue("SETTING:COIN",1000);
    level               = XML.getValue("SETTING:LEVEL", 0);
    unLockedLevel       = XML.getValue("SETTING:UNLACKEDLEVEL", 0);
    coinChance          = XML.getValue("SETTING:COINCHANCE", 2);
    unixTime            = XML.getValue("SETTING:TIME", (int)ofGetUnixTime());
    timeSlowerChance    = XML.getValue("SETTING:TIMESLOWER", 2);
    dotExtenderChance   = XML.getValue("SETTING:DOTEXTENDER", 2);
    dotFreezerChance    = XML.getValue("SETTING:FREEZERCHANCE", 2);
    firstPlay           = XML.getValue("SETTING:FIRST", 0);
    
    //******Scenes*************************************
    
    scenes[0] = new menu();
    ((menu*)scenes[0])->upGradePrices = upGradePrices;
    ((menu*)scenes[0])->live = &live;
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
    ((Mode01*)scenes[2])->live = &live;
    ((Mode01*)scenes[2])->xmlReader(points,&level,&currentScene);
    ((Mode01*)scenes[2])->coin = &coin;
    ((Mode01*)scenes[2])->scale = &scale;
    ((Mode01*)scenes[2])->coinChance = &coinChance;
    ((Mode01*)scenes[2])->accFrc = accFrc;
    ((Mode01*)scenes[2])->timeSlowerChance = &timeSlowerChance;
    ((Mode01*)scenes[2])->dotExtenderChance = &dotExtenderChance;
    ((Mode01*)scenes[2])->dotFreezerChance = &dotFreezerChance;
    scenes[2]->setup();
    
    //sound;
    soundSetup();
    
    //live increase
    
    
    int liveAdder = 0;
    liveAdder = (int)(ofGetUnixTime() - unixTime)/600;
    live+=liveAdder;
    if (live>10) {
        live = 10;
    }
    if (liveAdder>0) {
        preLive = live;
        unixTime = ofGetUnixTime();
    }
    
}

//--------------------------------------------------------------
void testApp::update(){

    //live add
    if (ofGetUnixTime()-unixTime>600) {
        if (live <10) {
            live += 1;
            preLive = live;
            unixTime = ofGetUnixTime();
        }else{
            unixTime = ofGetUnixTime();
        }
    }
    
//    cout<< ofGetUnixTime() <<"     "<<ofGetUnixTime() - unixTime <<endl;
    
    //for mirroring
    if (ofGetFrameNum()<10){
        if (!ofxiOSExternalDisplay::isMirroring()){
            ofxiOSExternalDisplay::mirrorOn();
            ofxiOSExternalDisplay::isMirroring();
        }
    }
    
    //sound
    soundUpdate();
    
    //level update
    if (unLockedLevel<level) {
        unLockedLevel = level;
    }
    
    
    //reset gamePlay
    if (((menu*)scenes[0])->bLevelChosen) {
        currentScene = 2;
        ((Mode01*)scenes[2])->reset();
        ((menu*)scenes[0])->bLevelChosen = false;
    }
    
    //purchase
    purchase();

    //update scenes
    scenes[currentScene]->update();
    
    //goStore
    if ((((menu*)scenes[0])->bGoStore)) {
        purchasePopup();
        (((menu*)scenes[0])->bGoStore) = false;
    }

    //save
    if(((menu*)scenes[0])->bSave){
        save();
        ((menu*)scenes[0])->bSave = false;
    }
    
    if(((handDetector*)scenes[1])->bSave){
        save();
        ((handDetector*)scenes[1])->bSave = false;
    }

    if(((Mode01*)scenes[2])->bSave){
        save();
        ((Mode01*)scenes[2])->bSave = false;
    }
    
    if (((Mode01*)scenes[2])->bGameOver) {
        gameoverPopup();
        ((Mode01*)scenes[2])->bGameOver = false;
    }
    
   
}

//--------------------------------------------------------------
void testApp::draw(){
    
    scenes[currentScene]->draw();
    preScene = currentScene;
    preLive = live;
    
}

//--------------------------------------------------------------
void testApp::exit(){
    save();
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch) {
    
    scenes[currentScene]->touchDown(touch.x, touch.y, touch.id);
    touchNum = touch.numTouches;
    soundTouchDown();
    
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
void testApp::lostFocus(){
    save();
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
    int liveAdder = 0;
    liveAdder = (int)(ofGetUnixTime()- unixTime)/600;
    live+=liveAdder;
    if (live>10) {
        live = 10;
    }
    if (liveAdder>0) {
        preLive = live;
        unixTime = ofGetUnixTime();
    }
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

    if (newOrientation == 3) {
        ofSetOrientation(OF_ORIENTATION_90_LEFT);
    }else if(newOrientation == 4){
        ofSetOrientation(OF_ORIENTATION_90_RIGHT);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::save(){
    
    XML.setValue("SETTING:COIN", coin);
	XML.setValue("SETTING:LEVEL", level);
	XML.setValue("SETTING:UNLACKEDLEVEL", unLockedLevel);
    XML.setValue("SETTING:COINCHANCE", coinChance);
    XML.setValue("SETTING:TIMESLOWER", timeSlowerChance);
    XML.setValue("SETTING:DOTEXTENDER", dotExtenderChance);
    XML.setValue("SETTING:FREEZERCHANCE", dotFreezerChance);
    XML.setValue("SETTING:FIRST", firstPlay);
    XML.setValue("SETTING:TIME", (int)unixTime);
    XML.saveFile( ofxiOSGetDocumentsDirectory() + "mySettings.xml" );
    
	message = "mySettings.xml saved to app documents folder";
    cout<<message<<endl;
}

//--------------------------------------------------------------
void testApp::purchase(){

    if (((menu*)scenes[0])->bPurchaseCoin[0]) {
        coins00->buy();
        ((menu*)scenes[0])->bPurchaseCoin[0] = false;
        ((menu*)scenes[0])->bPurchaseWithMoney = false;
    }
    
    if (((menu*)scenes[0])->bPurchaseCoin[1]) {
        coins01->buy();
        ((menu*)scenes[0])->bPurchaseCoin[1] = false;
        ((menu*)scenes[0])->bPurchaseWithMoney = false;
    }
    
    if (((menu*)scenes[0])->bPurchaseCoin[2]) {
        coins02->buy();
       
        ((menu*)scenes[0])->bPurchaseCoin[2] = false;
        ((menu*)scenes[0])->bPurchaseWithMoney = false;
    }
    
    
    if (coins00->isPurchesed()) {
        coin += 10000;
        save();
        coins00->unbuy();
    }else{
        coins00->reset();
    }
    
    if (coins01->isPurchesed()) {
        coin += 50000;
        save();
        coins01->unbuy();
    }else{
        coins01->reset();
    }
    
    if (coins02->isPurchesed()) {
        coin += 100000;
        save();
        coins02->unbuy();
    }else{
        coins02->reset();
    }
    

}

//--------------------------------------------------------------
void testApp::purchasePopup(){

    UIAlertView * alert = [[[UIAlertView alloc] initWithTitle:@"You don't have lives"
                                                      message:@"Go to store to purchase more lives. Life will be increased one per 10 mins, maximum 10"
                                                     delegate:nil
                                            cancelButtonTitle:@"OK"
                                            otherButtonTitles:nil] retain];
    [alert show];
    [alert release];

}

//--------------------------------------------------------------
void testApp::gameoverPopup(){

    UIAlertView * alert = [[[UIAlertView alloc] initWithTitle:@"Congratulations!!"
                                                      message:@"You have reached to the end of Findddle season one, more levels are coming soon, thank you for playing."
                                                     delegate:nil
                                            cancelButtonTitle:@"OK"
                                            otherButtonTitles:nil] retain];
    [alert show];
    [alert release];


}

//--------------------------------------------------------------
void testApp::popupDismissed(){

    if(alertViewDelegate){
        [alertViewDelegate release];
        alertViewDelegate = nil;
    }
    
}

//--------------------------------------------------------------
void testApp::soundSetup(){
    
    sSoundSwich = [[AVSoundPlayer alloc] init];
    [sSoundSwich loadWithFile:@"assets/sounds/Swichsound.wav"]; // uncompressed wav format.
    [sSoundSwich volume:0.9];
    
    sDotPressed = [[AVSoundPlayer alloc] init];
    [sDotPressed loadWithFile:@"assets/sounds/pressDot.wav"]; // uncompressed wav format.
    [sDotPressed volume:0.5];

    sDead = [[AVSoundPlayer alloc] init];
    [sDead loadWithFile:@"assets/sounds/error.wav"]; // uncompressed wav format.
    [sDead volume: 0.8];
    
    sLose = [[AVSoundPlayer alloc] init];
    [sLose loadWithFile:@"assets/sounds/loseSound.wav"]; // uncompressed wav format.
    [sLose volume:0.9];
    
    sItem = [[AVSoundPlayer alloc] init];
    [sItem loadWithFile:@"assets/sounds/itemSound.wav"]; // uncompressed wav format.
    [sItem volume:0.9];
    
    sBuySound = [[AVSoundPlayer alloc] init];
    [sBuySound loadWithFile:@"assets/sounds/buySound.wav"]; // uncompressed wav format.
    [sBuySound volume:0.9];
    
    sNormalButton = [[AVSoundPlayer alloc] init];
    [sNormalButton loadWithFile:@"assets/sounds/normalButtonSound.wav"]; // uncompressed wav format.
    [sNormalButton volume: 1.1];
    
    sScanner = [[AVSoundPlayer alloc] init];
    [sScanner loadWithFile:@"assets/sounds/scanDone.wav"]; // uncompressed wav format.
    [sScanner volume:0.9];
    
    sWin = [[AVSoundPlayer alloc] init];
    [sWin loadWithFile:@"assets/sounds/winSound.wav"]; // uncompressed wav format.
    [sWin volume:0.3];
    
    sCounterDown = [[AVSoundPlayer alloc] init];
    [sCounterDown loadWithFile:@"assets/sounds/countingdown.wav"]; // uncompressed wav format.
    [sCounterDown volume:0.9];
    
    sFinger = [[AVSoundPlayer alloc] init];
    [sFinger loadWithFile:@"assets/sounds/fingerSound.wav"]; // uncompressed wav format.
    [sFinger volume:0.5];
    
    
    sCheckForWin = [[AVSoundPlayer alloc] init];
    [sCheckForWin loadWithFile:@"assets/sounds/checkForWin.wav"]; // uncompressed wav format.
    [sCheckForWin volume:0.5];
    
    
    s321 = [[AVSoundPlayer alloc] init];
    [s321 loadWithFile:@"assets/sounds/321.wav"]; // uncompressed wav format.
    [s321 volume:0.9];
}

//--------------------------------------------------------------
void testApp::soundTouchDown(){

     if (((menu*)scenes[0])->bSound == false) {
        for (int i=0; i<  ((Mode01*)scenes[2])->myDot.size(); i++) {
            if(((Mode01*)scenes[2])->myDot[i].bSondPlay && !((Mode01*)scenes[2])->myDot[i].bFreezed){
                [sDotPressed play];
                ((Mode01*)scenes[2])->myDot[i].bSondPlay = false;
            }
        }
     }
}

//--------------------------------------------------------------
void testApp::soundUpdate(){
    if (((menu*)scenes[0])->bSound == false) {
        
        if (live<preLive && currentScene == 2) {
             [sDead play];
        }

        if (((Mode01*)scenes[2])->bLoseSound) {
            [sLose play];
            ((Mode01*)scenes[2])->bLoseSound = false;
        }

        for (int i=0; i<3; i++) {
            if (((Mode01*)scenes[2])->bItemSound[i]) {
                [sItem play];
                ((Mode01*)scenes[2])->bItemSound[i] = false;
            }
        }

        if (((menu*)scenes[0])->bSwichSound) {
            [sSoundSwich play];
            ((menu*)scenes[0])->bSwichSound = false;
        }

        if (((menu*)scenes[0])->bBuySound) {
            [sBuySound play];
            ((menu*)scenes[0])->bBuySound = false;
        }

        if (((menu*)scenes[0])->bButtonSound) {
            [sNormalButton play];
            ((menu*)scenes[0])->bButtonSound = false;
        }

        if (((Mode01*)scenes[2])->myInGameMenu.bButtonSound) {
            [sNormalButton play];
            ((Mode01*)scenes[2])->myInGameMenu.bButtonSound = false;
        }

        //scaner
        if (((handDetector*)scenes[1])->bScannerDone) {
            [sScanner play];
            ((handDetector*)scenes[1])->bScannerDone = false;
        }

        //win
        if (((Mode01*)scenes[2])->bWinSound) {
            [sWin play];
            ((Mode01*)scenes[2])->bWinSound = false;
        }

        //counter down

        if (((Mode01*)scenes[2])->bCountDown  && [sCounterDown isPlaying] == false) {
            [sCounterDown play];
        }

        if(((Mode01*)scenes[2])->bCountDown == false && [sCounterDown isPlaying]){
            [sCounterDown stop];
        }



        //finger
        for (int i=0; i<  ((Mode01*)scenes[2])->myDot.size(); i++) {
            if(((Mode01*)scenes[2])->myDot[i].bFingerSound){
                [sFinger play];
                ((Mode01*)scenes[2])->myDot[i].bFingerSound = false;
            }
        }

        //check for win
        if (((Mode01*)scenes[2])->bCheckWinSound && ((Mode01*)scenes[2])->winTimer > 0 && [sCheckForWin isPlaying] == false) {
            [sCheckForWin play];
        }

        if (((Mode01*)scenes[2])->winTimer == 0 && [sCheckForWin isPlaying]){
            [sCheckForWin stop];
        }

        //321 GO!!
        if (((Mode01*)scenes[2])->myInGameMenu.b321GO){
            [s321 play];
            ((Mode01*)scenes[2])->myInGameMenu.b321GO = false;
        }
    }
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){}
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}





