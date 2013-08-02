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

    for (int i=0; i<3; i++) {
        temImg.loadImage("assets/images/gamePlay/color"+ofToString(i)+".png");
        colorBg.push_back(temImg);
    }
    
    
    temImg.loadImage("assets/images/dots/B/dot00.png");
    dotImgB.push_back(temImg);
    
    for (int i=0; i<4; i++) {
        temImg.loadImage("assets/images/items/item0"+ofToString(i) +".png");
        itemImgs.push_back(temImg);
    }
    
    reset();
    myInGameMenu.setup(coin,level, gameTimer, fingerSize, bgScale, accFrc);
    myInGameMenu.live = &live;

}

//----------------------------------------------------------
void Mode01::reset(){
    //defult
    bgWidth = ofGetWidth();
    bgHight = ofGetHeight();
    bgScale = 1.0f;
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
        for (int i=0; i<itemImgs.size(); i++) {
            tempItem.itemImages[i] = &itemImgs[i];
        }
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
   
    
    //game timer
    gameTimer = 60;
    gameTimerStart = ofGetElapsedTimeMillis();
    bColorBg = false;
    colorBgTimer = 0;
    bgOffSet.set(0,0);
    //check Win
    winTimer = 0;
    bWinTimerStart = true;
    winEffectSpeed = 1;
    //check lose
    bLoseTimerStart = false;
    loseTimer = 0;
    translate.set(0, 0);
    PreCoverNum = 0;
    
    //subTime
    timeSlowerDuration = 0;
    timeSlowerTimer = ofGetElapsedTimeMillis();
    timeSpeed = 0.5;
    live = 2;
}

//----------------------------------------------------------
void Mode01::update(){
    
    
    //real game play
    if(myInGameMenu.bGameStart){
        
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
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bLoseTimerStart && myInGameMenu.bGameStart && bWinTimerStart)
        {
            
            if (ofGetElapsedTimeMillis() - gameTimerStart >= 100*timeSpeed) {
                gameTimer = gameTimer - 0.1;
                gameTimerStart = ofGetElapsedTimeMillis();
                if (gameTimer<10) {
                    bColorBg = true;
                }
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
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPushMatrix();
    if (bgOffSet.y>384) {
        bgOffSet.y = 0;
    }
    if (myInGameMenu.bLevelFail || myInGameMenu.bLevelDone) {
        bgOffSet.y = 0;
    }
    ofTranslate(512+bgOffSet.x, 384+bgOffSet.y);
    if (!myInGameMenu.bLevelFail && !myInGameMenu.bLevelDone) {
        ofSetColor(255);
        pattern->draw(-bgWidth/2*bgScale,-bgHight*bgScale+12,bgWidth*bgScale,bgHight*bgScale);
    }
    ofSetColor(255);
    pattern->draw(-bgWidth/2*bgScale,-bgHight/2*bgScale,bgWidth*bgScale,bgHight*bgScale);
    
    if (bColorBg && !myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail) {
        colorBgTimer++;
        float shaker = ofMap(gameTimer, 10, 0, 1, 6);
        translate.set(ofRandom(-shaker,shaker), ofRandom(-shaker,shaker));
        if (colorBgTimer%6 == 0) {
            ofSetColor(255);
            colorBg[0].draw(-bgWidth/2*bgScale+1,-bgHight/2*bgScale-1,bgWidth*bgScale,bgHight*bgScale);
        }else if(colorBgTimer%4 == 2){
            colorBg[1].draw(-bgWidth/2*bgScale-1,-bgHight/2*bgScale-1,bgWidth*bgScale,bgHight*bgScale);
        }else if(colorBgTimer%4 == 4){
            colorBg[2].draw(-bgWidth/2*bgScale+1,-bgHight/2*bgScale-1,bgWidth*bgScale,bgHight*bgScale);
        }
    }
    ofPopMatrix();
  
    //draw dots
    if(myInGameMenu.bGameStart){
        
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail) {
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
        timeSpeed = 1;
    }else{
        timeSpeed = 0.5;
    }

}

//-------------------------------------------------------
void Mode01::checkWin(){

    
    int counter = 0;
    
    for (int i=0; i<myDot.size(); i++) {
        if (myDot[i].bCovered) {
            counter++;
        }
    }
    
    if(counter == myDot.size() && bWinTimerStart){
        winTimer ++;
    }else{
        winTimer =0;
    }
    
    
    if (winTimer>0&&winTimer<150){
        
        bgOffSet.y +=2;
        if (bgOffSet.y>=300) {
            bgOffSet.y = 0;
        }
    }
    else if(winTimer>=150){
        myInGameMenu.scoreUpdate();
        bWinTimerStart = false;
        bgOffSet.y = 0;
        myInGameMenu.bLevelDone = true;
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
            
            if (unFixed == unTouched && !bLoseTimerStart) {
                bLoseTimerStart = true;
                live --;
                if (live < 0) {
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
            
            if(loseTimer<=30&&loseTimer>0){
                translate.set(ofRandom(-10,10), ofRandom(-10,10));
            }
            else if(loseTimer>30)
            {
              
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
   
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR) {
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
 

    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR)  {
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
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchUp(x, y, touchID);
        }
        checkLose(x, y, 1);
    }
    
    myInGameMenu.touchUp(x, y);
    
}








