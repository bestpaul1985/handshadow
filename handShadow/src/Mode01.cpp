//
//  Mode01.cpp
//  handShadow
//
//  Created by PengCheng on 7/22/13.
//
//

#include "Mode01.h"

void Mode01::xmlReader(vector<xmlPointer> pointer, int *CurrentLevel, int *CurrentScene){

    xmlPos = pointer;
    level = CurrentLevel;
    scene = CurrentScene;
    
    
}

//----------------------------------------------------------
void Mode01::setup(){
    
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 84);
    fontSmaill.loadFont("assets/fonts/Comfortaa_Regular.ttf", 46);
    
    ofImage temImg;
    for (int i =0; i<7; i++) {
        temImg.loadImage("assets/images/dots/A/dot0"+ofToString(i)+".png");
        dotImgA.push_back(temImg);
    }

    temImg.loadImage("assets/images/dots/B/dot00.png");
    dotImgB.push_back(temImg);
    reset();
    myInGameMenu.setup(coin,level, gameTimer, fingerSize);
    myInGameMenu.live = &live;

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
        int diffX = ofGetWidth()/2-dotPos[i].x;
        int diffY = ofGetHeight()/2-dotPos[i].y;
        ofPoint temp(dotPos[i].x+(int)(diffX* (*scale)),
                     dotPos[i].y+(int)(diffY* (*scale)));
        tempDos.setup(temp.x, temp.y,&dotImgA[i], &dotImgB[0]);
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
    
    fingerSize = myDot.size();
    
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
    live = 2;
}

//----------------------------------------------------------
void Mode01::update(){
    
    //counter down to start game
    if (bGameStart) {
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
        if (!myInGameMenu.bLevelDone && !bLoseTimerStart && !bGameStart) {
            
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
    
    if (myInGameMenu.bNextLevel) {
        live = 5;
        *level += 1;
        bSave = true;
        if (*level>=xmlPos.size()) {
            *level = 0;
        }
        reset();
        myInGameMenu.reset();
    }
    else if(myInGameMenu.bHome){
        live = 5;
        *level += 1;
        bSave = true;
        if (*level>=xmlPos.size()) {
            *level = 0;
        }
        reset();
        *scene = 0;
        myInGameMenu.reset();
    }
    else if(myInGameMenu.bTryAgin){
        reset();
        myInGameMenu.reset();
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
        
        if (!myInGameMenu.bLevelDone) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].draw();
                items[i].draw();
            }
        }
    }
    
    
    ofPopMatrix();
    
 
    if (gameTimer<0) {
        gameTimer = 0;
        
        bLoseTimerStart = true;
    }
    
    
    //draw in game menu
    myInGameMenu.draw();

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
            
            winEffectSpeed = 1000;
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
            
            myInGameMenu.bLevelDone = true;
            
        }
    }
   

    
}

//-------------------------------------------------------
void Mode01::checkLose(int x, int y, int situation){
    
    ofPoint touch(x,y);
    switch (situation) {
        case 0:{
           
            int unFixed = 0;
            int unTouched = 0;
            
            for (int i=0; i<myDot.size(); i++) {
                if (!myDot[i].bFixed){
                    unFixed ++;
                    if(myDot[i].pos.distance(touch)>myDot[i].radius && !myInGameMenu.bgRect.inside(touch)) {
                       unTouched ++;
                    }
                }
            }
            
            if (unFixed == unTouched) {
                bLoseTimerStart = true;
                live --;
                if (live <0) {
                    live = 0;
                }
                loseTimer = 0;
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
                live -= PreCoverNum-coveredNum;
                if (live <0) {
                    live = 0;
                }
                loseTimer = 0;
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
              
                if (live == 0 ||  gameTimer == 0) {
                    myInGameMenu.bLevelFail = true;
                }
                
                translate.set(0, 0);
                loseTimer = 0;
                bLoseTimerStart = false;
            }
        }break;
            
    }
             
}

//----------------------------------------------------------
void Mode01::touchDown(int x, int y, int touchID){
   
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bGameStart && live>0) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchDown(x, y, touchID);
            items[i].touchDown(x, y, touchID);
        }
        
        checkLose(x, y, 0);
    }
    
    
   
    myInGameMenu.touchDown(x, y);
  
}

//----------------------------------------------------------
void Mode01::touchMove(int x, int y, int touchID){
 

    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bGameStart&& live>0) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchMove(x, y, touchID);
            items[i].touchMove(x, y, touchID);
        }
        checkLose(x, y, 0);
    }
  
    myInGameMenu.touchMove(x, y);

    
}

//----------------------------------------------------------
void Mode01::touchUp(int x, int y, int touchID){
    
    for (int i=0; i<myDot.size(); i++) {
        if(myDot[i].bCovered){
            PreCoverNum ++;
        }
    }
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bGameStart && live>0) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchUp(x, y, touchID);
        }
        checkLose(x, y, 1);
    }
    
    myInGameMenu.touchUp(x, y);
    
}








