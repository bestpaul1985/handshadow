//
//  Mode01.cpp
//  handShadow
//
//  Created by PengCheng on 7/22/13.
//
//

#include "Mode01.h"

void Mode01::xmlReader(vector<xmlPointer> pointer, int *CurrentLevel, int *CurrentScene){
    
    live =5;
    xmlPos = pointer;
    level = CurrentLevel;
    scene = CurrentScene;
    myInGameMenu.live = &live;
    
}

//----------------------------------------------------------
void Mode01::setup(){
    
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 84);
    fontSmaill.loadFont("assets/fonts/Comfortaa_Regular.ttf", 46);
    
    ofImage temImg;
    
    temImg.loadImage("assets/images/dots/A/Dot_Ghost.png");
    dotImgA.push_back(temImg);
    temImg.loadImage("assets/images/dots/A/Dot_Monster.png");
    dotImgA.push_back(temImg);
    temImg.loadImage("assets/images/dots/A/Dot_Women.png");
    dotImgA.push_back(temImg);
    temImg.loadImage("assets/images/dots/A/Dot_Robot.png");
    dotImgA.push_back(temImg);
    temImg.loadImage("assets/images/dots/B/Dot_Pressed.png");
    dotImgB.push_back(temImg);

    myInGameMenu.setup(coin);
    reset();

}

//----------------------------------------------------------
void Mode01::reset(){
    //defult
    bgWidth = ofGetWidth();
    bgHight = ofGetHeight();

    dotPos.clear();
    myDot.clear();
    items.clear();

    dotPos = xmlPos[*level].pos;
    
    for (int i=0; i< dotPos.size(); i++) {
        dots tempDos;
        tempDos.setup(dotPos[i].x, dotPos[i].y,&dotImgA[(int)ofRandom(dotImgA.size())], &dotImgB[(int)ofRandom(dotImgB.size())]);
        tempDos.angle = ofRandom(360);
        myDot.push_back(tempDos);
    
        item tempItem;
        tempItem.coinChance = *coinChance;
        tempItem.timeSlowerChance = *timeSlowerChance;
        tempItem.dotExtenderChance = *dotExtenderChance;
        tempItem.dotFreezerChance = *dotFreezerChance;

        tempItem.setup(myDot[i].pos.x,myDot[i].pos.y);
        items.push_back(tempItem);
    }
    
    if (myDot.size()>0) {
        myDot[0].bFixed =false;
    }
    if (items.size()>0) {
        items[0].bFixed =false;
    }
    //game start
    bGameStart = true;
    gameStartTimer = 0;
    gameStartNumber = 3;
    
    //game timer
    gameTimer = 60;
    gameTimerStart = ofGetElapsedTimeMillis();
    //check Win
    winTimer = 0;
    bWinTimerStart = false;
    myInGameMenu.bwellDone = false;
    winEffectSpeed = 1;
    //check lose
    bLoseTimerStart = false;
    loseTimer = 0;
    translate.set(0, 0);
    PreCoverNum = 0;
    
    //subTime
    timeSlowerDuration = 0;
    timeSlowerTimer = ofGetElapsedTimeMillis();
    timeSpeed = 1;
    
}



//----------------------------------------------------------
void Mode01::update(){
    
    //counter down to start game
    if (bGameStart && !myInGameMenu.bPause) {
        gameStartTimer++;
        if (gameStartTimer>50) {
            gameStartNumber --;
            gameStartTimer = 0;
        }
        
        if (gameStartNumber <0) { 
            gameTimerStart = ofGetElapsedTimeMillis();
            bGameStart = false;
        }
        
    }
    
    //real game play
    else{
        
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].update();
        }
        
        
        for (int i=0; i<(myDot.size()-1); i++) {
            if (myDot[i].bCovered && myDot[i+1].bFixed) {
                myDot[i+1].bFixed = false;
                items[i+1].bFixed = false;
            }
        }
        
    //subGame
        
       
        
        for (int i=0; i<items.size(); i++) {
            if (!items[i].bFixed) {
                items[i].update();
            }
        }
        
        subGame();
        
    //timer
        if (!myInGameMenu.bPause && !myInGameMenu.bwellDone && !bLoseTimerStart && !bGameStart) {
            
            if (ofGetElapsedTimeMillis() - gameTimerStart >= 100*timeSpeed) {
                gameTimer = gameTimer - 0.1;
                gameTimerStart = ofGetElapsedTimeMillis();
            }
        }
        
    //check winning situation
        checkLose(0, 0, 2);
        checkWin();
    }
    
    // in game menu update
    myInGameMenu.update();
    if (myInGameMenu.bBackToMainMenu) {
        *scene = 0;
        myInGameMenu.bBackToMainMenu = false;
    }
    
}

//----------------------------------------------------------
void Mode01::draw(){
    
    //shaking effect
    ofPushMatrix();
    ofTranslate(translate);
    
    //background
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(512, 384);
    pattern->draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
    ofPopMatrix();
    //draw counter
    if (bGameStart) {

        ofSetColor(30);
        string num = ofToString(gameStartNumber);
        font.drawString(num, ofGetWidth()/2 - (int)font.stringWidth(num)/2, ofGetHeight()/2+(int)font.stringHeight(num)/2);
       
    }
    //draw dots
    else{
        
        if (!myInGameMenu.bwellDone) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].draw();
                items[i].draw();
            }
        }
    }
    
    
    ofPopMatrix();
    
    //draw timer
    string sTime = ofToString(gameTimer,1);
    ofSetColor(30);
    fontSmaill.drawString(sTime, 900, 80);
    if (gameTimer<0) {
        gameTimer = 0;
        bLoseTimerStart = true;
    }
    
    
    //draw in game menu
    myInGameMenu.draw();

    ofSetColor(230);
    fontSmaill.drawString("LEVEL: "+ofToString(*level), 400, 80);
    
}

//-------------------------------------------------------
void Mode01::subGame(){
    
    for (int i=0; i<items.size(); i++) {
        //Coin
        if (items[i].bCoin) {
            *coin +=50;
            bSave = true;
            items[i].bCoin = false;
        }
        //time slower
        else if (items[i].bTimeSlower) {
            items[i].bTimeSlower = false;
            timeSlowerDuration = 5;
            timeSlowerTimer = ofGetElapsedTimeMillis();
        }
        //dot extender
        else if (items[i].bDotExtender) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].radiusExtendReset();
                myDot[i].goalRaduis +=10;
                myDot[i].bRadiusExtend = true;
            }
            items[i].bDotExtender = false;
        }
        //dot freezer
        else if (items[i].bDotFreezer) {
            myDot[i].bFreezed = true;
            
            items[i].bDotFreezer = false;
        }

    
    }
    
    //time slower update
    if (timeSlowerDuration>0) {
        if (ofGetElapsedTimeMillis() - timeSlowerTimer >= 100) {
            timeSlowerDuration -= 0.1;
            timeSlowerTimer = ofGetElapsedTimeMillis();
        }
        timeSpeed = 3;
    }else{
        timeSpeed = 1;
    }

}

//-------------------------------------------------------
void Mode01::checkWin(){

    if (!bLoseTimerStart) {
        int counter = 0;
        
        for (int i=0; i<myDot.size(); i++) {
            if (myDot[i].bCovered) {
                counter++;
            }
        }
        
        if(counter == myDot.size())bWinTimerStart = true;
        
        if(bWinTimerStart)  winTimer ++;
        
        
        if (winTimer>0&&winTimer<100){
            
            winEffectSpeed = 500;
            bgWidth+= winEffectSpeed;
        }
        
        else if(winTimer>=100 && winTimer<=200) {
            
            if(bgWidth>ofGetWidth()){
                winEffectSpeed+=500;
                bgWidth -=winEffectSpeed;
            }else{
                bgWidth = ofGetWidth();
                bgHight+=ofGetHeight();
            }
            
            myInGameMenu.bwellDone = true;
            
        }
        
        else if(winTimer>=200){
            live = 5;
            *level += 1;
            bSave = true;
            if (*level>=xmlPos.size()) {
                *level = 0;
            }
            reset();
        }
    }
   
    
}


//-------------------------------------------------------
void Mode01::checkLose(int x, int y, int situation){
    
    ofPoint touch(x,y);
    switch (situation) {
        case 0:{
            int unLackNum = 0;
            int noTouchNum =0;
            for (int i=0; i<myDot.size(); i++) {
                if (!myDot[i].bFixed){
                    unLackNum ++;
                    if(myDot[i].pos.distance(touch)>myDot[i].radius && !myInGameMenu.imgRect.inside(touch)) {
                        noTouchNum++;
                    }
                }
            }
            
            if (noTouchNum == unLackNum) {
                
                    bLoseTimerStart = true;
            }
            
        }break;
            
        case 1:{
            int coveredNum = 0;
            for (int i=0; i<myDot.size(); i++) {
                    if(myDot[i].bCovered){
                        coveredNum ++;
                }
            }
            
            if (PreCoverNum>coveredNum) {
                bLoseTimerStart = true;
            }
            
            PreCoverNum = 0;
        }break;
    
        case 2:{
            
            if (bLoseTimerStart) {
                loseTimer ++;
            }
            
            if(loseTimer<50&&loseTimer>0){
                translate.set(ofRandom(-10,10), ofRandom(-10,10));
            }else if(loseTimer>50){
               
                live --;
                if (live == 0) {
                    live = 5;
                    reset();
                }else{
                    reset();
                }
                
                
                bSave = true;
                bLoseTimerStart = false;
            }
        }break;
            
    }
             
}



//----------------------------------------------------------
void Mode01::touchDown(int x, int y, int touchID){
   
    if (!myInGameMenu.bPause && !myInGameMenu.bwellDone && !bLoseTimerStart && !bGameStart) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchDown(x, y, touchID);
            items[i].touchDown(x, y, touchID);
        }
        
        checkLose(x, y, 0);
    }
    
    
   
    myInGameMenu.touchDown(x, y, touchID);
  
}

//----------------------------------------------------------
void Mode01::touchMove(int x, int y, int touchID){
 

    if (!myInGameMenu.bPause && !myInGameMenu.bwellDone && !bLoseTimerStart&& !bGameStart) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchMove(x, y, touchID);
            items[i].touchMove(x, y, touchID);
        }
        checkLose(x, y, 0);
    }
  
    myInGameMenu.touchMove(x, y, touchID);

    
}

//----------------------------------------------------------
void Mode01::touchUp(int x, int y, int touchID){
    
    for (int i=0; i<myDot.size(); i++) {
        if(myDot[i].bCovered){
            PreCoverNum ++;
        }
    }
    if (!myInGameMenu.bPause && !myInGameMenu.bwellDone && !bLoseTimerStart && !bGameStart) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchUp(x, y, touchID);
        }
        checkLose(x, y, 1);
    }
    
    
    myInGameMenu.touchUp(x, y, touchID);

}








