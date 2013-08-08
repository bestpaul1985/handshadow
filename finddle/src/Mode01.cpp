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
    
    itemSpriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 256);
    itemSpriteRenderer->loadTexture("assets/images/items/iconAnimation.png", 2048, GL_NEAREST);
    
    ofImage temImg;
    for (int i=0; i<3; i++) {
        temImg.loadImage("assets/images/gamePlay/bg_"+ofToString(i)+".png");
        patterns.push_back(temImg);
    }
    
    for (int i =0; i<8; i++) {
        temImg.loadImage("assets/images/dots/A/dot0"+ofToString(i)+".png");
        dotImgA.push_back(temImg);
    }

    for (int i =0; i<2; i++) {
        temImg.loadImage("assets/images/dots/B/dot0"+ofToString(i)+".png");
        dotImgB.push_back(temImg);
    }
    
    for (int i=0; i<3; i++) {
        temImg.loadImage("assets/images/gamePlay/color"+ofToString(i)+".png");
        colorBg.push_back(temImg);
    }
    
   
    bgNum = -1;
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
    bgNum ++;
    if (bgNum>patterns.size()-1) {
        bgNum = 0;
    }
    if(sprites.size()>0){
        for(int i=sprites.size()-1;i>=0;i--){
            delete sprites[i];
            sprites.erase(sprites.begin()+i);
        }
    }
    
    dotPos = xmlPos[*level].pos;
    
    for (int i=0; i< dotPos.size(); i++) {
        dots tempDos;
        int diffX = ofGetWidth()/2-dotPos[i].x;
        int diffY = ofGetHeight()/2-dotPos[i].y;
        ofPoint temp(dotPos[i].x+(int)(diffX* (*scale)),
                     dotPos[i].y+(int)(diffY* (*scale)));
        tempDos.setup(temp.x, temp.y,&dotImgA[i], &dotImgB[0],&dotImgB[1]);
        tempDos.angle = ofRandom(360);
        myDot.push_back(tempDos);
    
        item tempItem;
        tempItem.coinChance = *coinChance;
        tempItem.timeSlowerChance = *timeSlowerChance;
        tempItem.dotExtenderChance = *dotExtenderChance;
        tempItem.dotFreezerChance = *dotFreezerChance;
        tempItem.setup(myDot[i].pos.x,myDot[i].pos.y);
        items.push_back(tempItem);
        
        basicSprite * newSprite = new basicSprite();
		newSprite->pos.set(items[i].pos);
        newSprite->animation = itemAnimation;
        if (items[i].myType == COIN_MAKER) {
            newSprite->animation.index = 0;
        } else if (items[i].myType == TIME_SLOWER) {
            newSprite->animation.index = 24;
        } else if (items[i].myType == DOT_EXTENDER) {
            newSprite->animation.index = 16;
        }else if (items[i].myType == DOT_FREEZER) {
            newSprite->animation.index = 8;
        }else if (items[i].myType == NONE) {
            newSprite->animation.index = 7;
        }
        newSprite->animation.total_frames = 1;
		sprites.push_back(newSprite);
        
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
    live = 3;
    
    bgOffSetSpeed = 2;
}

//----------------------------------------------------------
void Mode01::update(){
    
    
    //real game play
    if(myInGameMenu.bGameStart){
        
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].update();
            if (myDot[i].bCovered) {
                myInGameMenu.bSmallIconCovered[i] = true;
            }else{
                myInGameMenu.bSmallIconCovered[i] = false;
            }
        }
        
        for (int i=0; i<(myDot.size()-1); i++) {
            if (myDot[i].bCovered && myDot[i+1].bFixed) {
                myDot[i+1].bFixed = false;
                items[i+1].bFixed = false;
            }
        }
            
    //subGame

        subGame();

        itemSpriteRenderer->clear();
        itemSpriteRenderer->update(ofGetElapsedTimeMillis());
        
        int spriteSize = 0;
        for (int i=0; i<items.size(); i++) {
            if (!items[i].bFixed) {
                spriteSize++;
            }
            
            if (items[i].bCovered && items[i].myType != NONE) {
                sprites[i]->animation.total_frames = 9;
            }
        }
        
        
        if(sprites.size()>0){
            for(int i=0;i<spriteSize;i++){
                itemSpriteRenderer->addCenteredTile(&sprites[i]->animation, sprites[i]->pos.x, sprites[i]->pos.y);
            }
        }
    //timer
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bLoseTimerStart && myInGameMenu.bGameStart && bWinTimerStart && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR)
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
        
        *level += 1;
        bSave = true;
        if (*level>=xmlPos.size()) {
            *level = 0;
        }
        reset();
        myInGameMenu.reset();
    }
    else if(myInGameMenu.bTryAgin){
        
        reset();
        myInGameMenu.reset();
    }
        
}

//----------------------------------------------------------
void Mode01::draw(){
    
    ofBackground(0);
    
    //shaking effect
    ofPushMatrix();
    ofTranslate(translate);
    //background
    ofPushMatrix();

    ofSetColor(255);

    ofTranslate(512+bgOffSet.x, 384+bgOffSet.y);
    
    if (!myInGameMenu.bLevelFail && !myInGameMenu.bLevelDone) {
       
     
        if (bColorBg) {
            colorBgTimer++;
            float shaker = ofMap(gameTimer, 10, 0, 1, 6);
            translate.set(ofRandom(-shaker,shaker), ofRandom(-shaker,shaker));
            if (colorBgTimer%6 == 0) {
                ofSetColor(255,255,0);
                patterns[bgNum].draw(-bgWidth/2,-bgHight-30,bgWidth,bgHight);
                patterns[bgNum].draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
            }else if(colorBgTimer%6 == 2){
                ofSetColor(0,255,255);
                patterns[bgNum].draw(-bgWidth/2,-bgHight-30,bgWidth,bgHight);
                patterns[bgNum].draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
            }else if(colorBgTimer%6 == 4){
                ofSetColor(255,0,255);
                patterns[bgNum].draw(-bgWidth/2,-bgHight-30,bgWidth,bgHight);
                patterns[bgNum].draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
            }
        }
        else{
            if (myInGameMenu.bTimeSlower) {
                ofSetColor(ofMap(timeSlowerDuration, 0, 5, 255, 221,true), ofMap(timeSlowerDuration, 0, 5, 255, 198,true), ofMap(timeSlowerDuration, 0, 5, 255, 167,true));
            }
            
            patterns[bgNum].draw(-bgWidth/2,-bgHight-30,bgWidth,bgHight);
            patterns[bgNum].draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
        }
    }
    
    else{
        
        if (myInGameMenu.bTimeSlower) {
            ofSetColor(221, 198, 167,ofMap(timeSlowerDuration, 0, 5, 0, 255));
        }
        
        patterns[bgNum].draw(-bgWidth/2*bgScale,-bgHight/2*bgScale,bgWidth*bgScale,bgHight*bgScale);
        
    }
    
    ofPopMatrix();
  
    //draw dots
    if(myInGameMenu.bGameStart){
        
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].draw();
            }
            
            itemSpriteRenderer->draw();

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
        myInGameMenu.bTimeSlower = true;
    }else{
        timeSpeed = 0.5;
        myInGameMenu.bTimeSlower = false;

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
        bgOffSet.y = 0;
        winTimer =0;
    }
    
    
    if (winTimer>0&&winTimer<150){
        bgOffSet.y +=bgOffSetSpeed;
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
    if(myInGameMenu.bHome){
        reset();
        myInGameMenu.reset();
        *scene = 0;
    }
}








