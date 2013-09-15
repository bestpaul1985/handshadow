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
    
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 84,true, true);
    fontSmaill.loadFont("assets/fonts/Comfortaa_Regular.ttf", 40,true, true);
    fontReallySmaill.loadFont("assets/fonts/Comfortaa_Regular.ttf", 30,true, true);
    fontReallySmaill.setLineHeight(36);
    
    itemSpriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 256);
    itemSpriteRenderer->loadTexture("assets/images/items/iconAnimation2.png", 2048, GL_NEAREST);
    
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
    
    for (int i=0; i<7; i++) {
        temImg.loadImage("assets/images/dots/C/0"+ofToString(i)+".png");
        dotFinger.push_back(temImg);
    }
   
    arrow.loadImage("assets/images/gamePlay/arrow.png");
    bgNum = -1;
    reset();
    myInGameMenu.overAllColor = &overAllColor2;
    myInGameMenu.setup(coin,level, gameTimer, fingerSize, bgScale, accFrc, unixTime);
    myInGameMenu.live = live;
    myInGameMenu.TryLive = &tryLive;

    arrowOffSet = 0;
    arrowSpeed = 0.3;
    bTutorialStep = 0;
    bCheckWinSound = false;
    bGameOver =false;
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
    tryLive = 10;
    if (*level == 3) {
        bTouchBg = false;

    }else{
        bTouchBg = true;
    }
    
    //sound
    bWinSound = false;
    bLoseSound = false;
    bCountDown = false;
    for (int i=0; i<3; i++) {
        bItemSound[i] = false;
    }
    //bg color
    if (*level<5) {
        overAllColor.set(100);
    }else{
        overAllColor.set(255);
    }

    if (*level <4) {
        overAllColor2.set(100);
    }else{
        overAllColor2.set(255);
    }
    
    if (*level == 3) {
        bTutorialStep = 0;
    }
    //sprites
    
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
    
    //dots

    dotPos = xmlPos[*level].pos;
    
    for (int i=0; i< dotPos.size(); i++) {
        dots tempDos;
        int diffX = ofGetWidth()/2-dotPos[i].x;
        int diffY = ofGetHeight()/2-dotPos[i].y;
        ofPoint temp(dotPos[i].x+(int)(diffX* (*scale)),
                     dotPos[i].y+(int)(diffY* (*scale)));
        tempDos.setup(temp.x, temp.y,&dotImgA[i], &dotImgB[0],&dotImgB[1], &dotFinger[(int)ofRandom(6)]);
        myDot.push_back(tempDos);
    
    }
    
    
    // items
    for (int i=0; i< dotPos.size(); i++) {
        item tempItem;
        tempItem.coinChance = *coinChance;
        tempItem.timeSlowerChance = *timeSlowerChance;
        tempItem.dotExtenderChance = *dotExtenderChance;
        tempItem.dotFreezerChance = *dotFreezerChance;
        tempItem.setup(&myDot[i].pos);
        if (*level  == 0 || *level == 1) {
            tempItem.myType = NONE;
        }else if (*level  == 2) {
            if (i == 0) {
                tempItem.angle = 180;
                tempItem.myType = COIN_MAKER;
            }else if (i == 1) {
                tempItem.angle = 180;
                tempItem.myType = DOT_FREEZER;
            }else if (i == 2){
                tempItem.angle = 180;
                tempItem.myType = DOT_EXTENDER;
            }
        }
        
        items.push_back(tempItem);
    }
    
    for (int i=0; i<items.size(); i++) {
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
    bgOffSetSpeed = 2;
    
    for (int i=0; i<3; i++) {
        myInGameMenu.itemSize[i] = 0;
    }
    
    //subGame;
    for (int i=0; i<8; i++) {
        bDotExtender[i] = false;
        bDotFreezer[i] = false;
        bSuperCoin[i]=false;
        dotExtenderPct[i] = 0;
        dotFreezerPct[i] = 0;
        SuperCoinPct[i] = 0;
    }
    
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

        subGameUpdate();
        itemSpriteRenderer->clear();
        itemSpriteRenderer->update(ofGetElapsedTimeMillis());
        
        int spriteSize = 0;
        for (int i=0; i<items.size(); i++) {
            if (!items[i].bFixed) {
                spriteSize++;
                items[i].update();
                sprites[i]->pos = items[i].pos;
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
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && !bLoseTimerStart && myInGameMenu.bGameStart && bWinTimerStart && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR && *level>4)
        {
            
            if (ofGetElapsedTimeMillis() - gameTimerStart >= 60*timeSpeed) {
                gameTimer = gameTimer - 0.1;
                gameTimerStart = ofGetElapsedTimeMillis();
                if (0<gameTimer&& gameTimer<10) {
                    bColorBg = true;
                    bCountDown = true;
                }
            }
            
        }
        
    if (gameTimer<0) {
            gameTimer = 0;
            *live -=1;
            bLoseTimerStart = true;
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
            bGameOver = true;
            *scene = 0;
        }
        reset();
        myInGameMenu.reset();
    }
    else if(myInGameMenu.bTryAgin){
        reset();
        myInGameMenu.reset();
    }
        
   else if(myInGameMenu.bHome){
        reset();
        myInGameMenu.reset();
        *scene = 0;
    }
    
   else if(myInGameMenu.bStore){
       reset();
       myInGameMenu.reset();
       *scene = 0;
       *bStore = true;
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

    ofSetColor(overAllColor);

    ofTranslate(512+bgOffSet.x, 384+bgOffSet.y);
    
    if (!myInGameMenu.bLevelDone) {

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

            float offset;
            if (bgNum == 0) {
                offset = 27;
            }else if(bgNum == 1){
                offset = 23;
            }else{
                offset = 27;
            }
            patterns[bgNum].draw(-bgWidth/2,-bgHight-offset,bgWidth,bgHight);
            patterns[bgNum].draw(-bgWidth/2,-bgHight/2,bgWidth,bgHight);
        }
    }
    
    else{
        
        patterns[bgNum].draw(-bgWidth/2*bgScale,-bgHight/2*bgScale,bgWidth*bgScale,bgHight*bgScale);
        
    }
    
    ofPopMatrix();
    
    //draw dots
    if(myInGameMenu.bGameStart){
        
        if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].draw();
            }
            subGameDraw();
            itemSpriteRenderer->draw();
        }

    }
    
    ofPopMatrix();
    
    //draw in game menu
    myInGameMenu.draw();
    tutorialDraw();
    
}

//-------------------------------------------------------
void Mode01::subGameUpdate(){
    
    for (int i=0; i<items.size(); i++) {
        //Coin
        if (items[i].bCoin) {
            *coin +=50;
            items[i].bCoin = false;
            bSuperCoin[i] = true;
            bItemSound[0] = true;
            myInGameMenu.itemSize[0]++;
        }
        //time slower
//        else if (items[i].bTimeSlower) {
//            items[i].bTimeSlower = false;
//            timeSlowerDuration = 5;
//            timeSlowerTimer = ofGetElapsedTimeMillis();
//
//        }
        //dot extender
        else if (items[i].bDotExtender) {
            for (int i=0; i<myDot.size(); i++) {
                myDot[i].radiusExtendReset();
                myDot[i].goalRaduis +=10;
                myDot[i].frezzerGoalRadiusX +=10;
                myDot[i].frezzerGoalRadiusY +=10;
                myDot[i].bRadiusExtend = true;
            }
            bDotExtender[i] = true;
            myInGameMenu.itemSize[1]++;
            bItemSound[1] = true;
            items[i].bDotExtender = false;
        }
        //dot freezer
        else if (items[i].bDotFreezer) {
            myDot[i].bFreezed = true;
            bDotFreezer[i] = true;
            bItemSound[2] = true;
            items[i].bDotFreezer = false;
            myInGameMenu.itemSize[2]++;
        }
        
    }
    
//time slower update
    
//    if (timeSlowerDuration>0) {
//        if (ofGetElapsedTimeMillis() - timeSlowerTimer >= 100) {
//            timeSlowerDuration -= 0.1;
//            timeSlowerTimer = ofGetElapsedTimeMillis();
//        }
//        timeSpeed = 1;
//        myInGameMenu.bTimeSlower = true;
//    }else{
//        timeSpeed = 0.5;
//        myInGameMenu.bTimeSlower = false;
//
//    }

}

//-------------------------------------------------------
void Mode01::subGameDraw(){

    for (int i=0; i<8; i++) {
        if (bSuperCoin[i]) {
            float speed = 0.1f;
            SuperCoinPct[i]+=speed;
            if (SuperCoinPct[i]>1) {
                SuperCoinPct[i]=0;
                bSuperCoin[i] = false;
            }
            float radius0 = SuperCoinPct[i]*1024;
            float radius1 = SuperCoinPct[i]*512;
            float radius2 = SuperCoinPct[i]*256;
            float alpha = (1-SuperCoinPct[i])*100;
            
            ofSetColor(243, 226, 0, alpha);
            ofCircle(items[i].pos, radius0);
            ofCircle(items[i].pos, radius1);
            ofCircle(items[i].pos, radius2);
        }
        
        if (bDotExtender[i]) {
            float speed = 0.1f;
            dotExtenderPct[i]+=speed;
            if (dotExtenderPct[i]>1) {
                dotExtenderPct[i]=0;
                bDotExtender[i] = false;
            }
            float radius0 = dotExtenderPct[i]*1024;
            float radius1 = dotExtenderPct[i]*512;
            float radius2 = dotExtenderPct[i]*256;
            float alpha = (1-dotExtenderPct[i])*100;
            ofSetColor(247, 90, 146, alpha);
            ofCircle(items[i].pos, radius0);
            ofCircle(items[i].pos, radius1);
            ofCircle(items[i].pos, radius2);

        }
        
        if (bDotFreezer[i]) {
            float speed = 0.1f;
            dotFreezerPct[i]+=speed;
            if (dotFreezerPct[i]>1) {
                dotFreezerPct[i]=0;
                bDotFreezer[i] = false;
            }
            float radius0 = dotFreezerPct[i]*1024;
            float radius1 = dotFreezerPct[i]*512;
            float radius2 = dotFreezerPct[i]*256;
            float alpha = (1-dotFreezerPct[i])*100;
            ofSetColor(16, 297, 232, alpha);
            ofCircle(items[i].pos, radius0);
            ofCircle(items[i].pos, radius1);
            ofCircle(items[i].pos, radius2);
        }
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
        
        if (*level == 2) {
            
            int itemNum = 0;
            for (int i=0; i<sprites.size(); i++) {
                if (sprites[i]->animation.frame == 8) {
                    itemNum ++;
                }
            }
            
            if (itemNum == 3) {
                winTimer ++; 
            }else{
                bgOffSet.y = 0;
                winTimer =0;
            }
        
        }else if(*level == 3){
        
            if (bTouchBg) {
                winTimer ++;
            }else{
                bgOffSet.y = 0;
                winTimer =0;
            }
        
            }else{
            
            winTimer ++;

            }
        }
        else{
            
        bgOffSet.y = 0;
        winTimer =0;
    }

    if (winTimer>0&&winTimer<150){
        bgOffSet.y +=bgOffSetSpeed;
        bCheckWinSound = true;
    }
    
    else if(winTimer>=150){
        bWinSound = true;
        bCheckWinSound = false;
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
               
                if (*level == 3) {
                    bTouchBg = true;
                    bTutorialStep = 1;
                }
                
                if (*level <5) {
                    tryLive -=1;
                    if (tryLive<1) {
                        tryLive = 10;
                    }
                }else{
                    *live -=1;
                    if (*live < 0) {
                        *live = 0;
                    }
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
                
                if (*level <5) {
                    tryLive -= PreCoverNum-coveredNum;
                    
                    if (tryLive<1) {
                        tryLive = 10;
                    }
                    
                }else{
                    
                    *live -= PreCoverNum-coveredNum;                    
                  
                    if (*live < 0) {
                        *live = 0;
                    }
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
                overAllColor.set((int)ofRandom(180,255));
            }
            
            else if(loseTimer>30)
            {
              
                if (*live == 0 ||  gameTimer == 0)
                {
                    myInGameMenu.bLevelFail = true;
                    bLoseSound = true;
                }
                
                
                if (*level<5) {
                    overAllColor.set(100);
                }else{
                    overAllColor.set(255);
                }
                
                translate.set(0, 0);
                loseTimer = 0;
                bLoseTimerStart = false;
                bCountDown = false;
            }
        }break;
            
    }
             
}

//----------------------------------------------------------
void Mode01::touchDown(int x, int y, int touchID){
   
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && *live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR) {
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
 

    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && *live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR)  {
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
    if (!myInGameMenu.bLevelDone && !myInGameMenu.bLevelFail && myInGameMenu.bGameStart && *live>0 && !myInGameMenu.bPauseL && !myInGameMenu.bPauseR) {
        for (int i=0; i<myDot.size(); i++) {
            myDot[i].touchUp(x, y, touchID);
        }
        
        if (*level == 3) {
            if (bTouchBg) {
                checkLose(x, y, 1);
            }
        }else{
            checkLose(x, y, 1);
        }
    }
    
    myInGameMenu.touchUp(x, y);

}

//----------------------------------------------------------
void Mode01::tutorialDraw(){

    //level 1
    if (!myInGameMenu.bPauseL && !myInGameMenu.bPauseR) {
        
        if (*level == 0 && bWinTimerStart && !bLoseTimerStart) {
            if(myDot[0].pct == 1){
                
                ofSetColor(255);
                fontSmaill.drawString("Hold the dot to win", 310, 600);
                arrowOffSet += arrowSpeed;
                if (arrowOffSet>5) {
                    arrowSpeed*=-1;
                }else if(arrowOffSet<0){
                    arrowSpeed*=-1;
                }
                arrow.draw(478,247+arrowOffSet);
                
            }
        }
        
        //level 2

        if (*level == 1 && bWinTimerStart && !myInGameMenu.bLevelFail) {
            
            if(myDot[0].pct == 1){
                
                ofSetColor(255);
                fontSmaill.drawString("Hold the dots", 370, 630);
                
                ofSetColor(255);
                
                arrowOffSet += arrowSpeed;
                if (arrowOffSet>5) {
                    arrowSpeed*=-1;
                }else if(arrowOffSet<0){
                    arrowSpeed*=-1;
                }
                arrow.draw(305,235+arrowOffSet);
                
            }
            
            if(myDot[1].pct == 1){
                
                ofSetColor(255);
                arrow.draw(666,235+arrowOffSet);
                
            }
        }
        
        //level 3
        if (*level == 2 && bWinTimerStart && !myInGameMenu.bLevelFail) {
        
            if(myDot[0].pct == 1){
                ofSetColor(255);
                int itemNum = 0;
                for (int i=0; i<sprites.size(); i++) {
                    if (sprites[i]->animation.frame == 8) {
                        itemNum ++;
                    }
                }
                
                if (itemNum == 3) {
                    fontSmaill.drawString("Hold left and top dots to win", 220, 670);
                }else{
                    fontSmaill.drawString("Touch items to explore rewards", 220, 670);
                }

                arrowOffSet += arrowSpeed;
                if (arrowOffSet>5) {
                    arrowSpeed*=-1;
                }else if(arrowOffSet<0){
                    arrowSpeed*=-1;
                }
            
                if (!items[0].bCovered) {
                    arrow.draw(290-20,334-40+arrowOffSet,arrow.getWidth(),arrow.getHeight());
                }
            }
            
            if(myDot[1].pct == 1){
                if (!items[1].bCovered) {
                    arrow.draw(625-10,334-40+arrowOffSet,arrow.getWidth(),arrow.getHeight());
                }
            }
            
            
            if(myDot[2].pct == 1){
                if (!items[2].bCovered) {
                    arrow.draw(446-20,76-40+arrowOffSet,arrow.getWidth(),arrow.getHeight());
                }
            }

        }
        
        
        //leve 4
        if (*level == 3 && bWinTimerStart && !myInGameMenu.bLevelFail) {
            
            if(myDot[0].pct == 1){
                ofSetColor(255);
                arrowOffSet += arrowSpeed;
                if (arrowOffSet>5) {
                    arrowSpeed*=-1;
                }else if(arrowOffSet<0){
                    arrowSpeed*=-1;
                }
              
                
                ofSetColor(255);
            
                if(bTutorialStep == 0){
                    arrow.draw(ofGetWidth()/2-40,ofGetHeight()/2+arrowOffSet-40,arrow.getWidth(),arrow.getHeight());
                    fontReallySmaill.drawString("Touch Here", ofGetWidth()/2 -fontReallySmaill.stringWidth(ofToString("Touch Here"))/2,ofGetHeight()/2+arrowOffSet-50);
                }
                
               if(bTutorialStep == 1){
                   overAllColor2.set(255);
                   ofPushMatrix();  
                   ofTranslate(219, 83);
                   ofRotateZ(180);
                   arrow.draw(-arrow.getWidth()/4, -arrow.getHeight()+arrowOffSet + 20,arrow.getWidth(),arrow.getHeight());
                   ofPopMatrix();

                   fontReallySmaill.drawString("Losing life when touching the backgournd \nIf you don't have any life, you can't play the game. ", 30,190);

                }
                
            }
        }
        
        if (*level == 4 && bWinTimerStart && !myInGameMenu.bLevelFail) {
            if(myDot[0].pct == 1){
                
                if(bTutorialStep == 1){
                    overAllColor2.set(255);
                    ofPushMatrix();
                    ofTranslate(219, 83);
                    ofRotateZ(180);
                    arrow.draw(-arrow.getWidth()/4, -arrow.getHeight()+arrowOffSet + 20,arrow.getWidth(),arrow.getHeight());
                    ofPopMatrix();
                    ofSetColor(255);

                    fontReallySmaill.drawString("Losing life when removing the finger from the pressed dot", 30,190);
                }

            }
        }
    }
}






