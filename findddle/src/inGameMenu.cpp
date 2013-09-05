//
//  inGameMenu.cpp
//  handShadow
//
//  Created by PengCheng on 7/23/13.
//
//

#include "inGameMenu.h"

void inGameMenu::setup(int *Coin , int *Level , float &GameTimer, int &FingerSize, float &BGScale,  ofPoint *AccFrc, int *UnixTime){
    
    coin = Coin;
    level = Level;
    gameTimer = &GameTimer;
    fingerSize = &FingerSize;
    bgScale = &BGScale;
    accFrc = AccFrc;
    unixTime = UnixTime;
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 30,true, true);
    fontBig.loadFont("assets/fonts/Comfortaa_Regular.ttf", 60,true, true);
    fontSmall.loadFont("assets/fonts/Comfortaa_Regular.ttf", 26,true, true);
    fontSmall2.loadFont("assets/fonts/Comfortaa_Regular.ttf", 20,true, true);
    
    superCoin.loadImage("assets/images/inGameMenu/item00.png");
    bgImg.loadImage("assets/images/inGameMenu/bg.png");
    clockOutLine.loadImage("assets/images/inGameMenu/outline.png");
    
    LDBackgroudImg[0].loadImage("assets/images/inGameMenu/bg_success.png");
    LDBackgroudImg[1].loadImage("assets/images/inGameMenu/bg_unsuccess.png");

    
    for (int i=0; i<6; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/"+ofToString(i)+".png");
        fingerImg.push_back(temp);
    }
    for (int i=0; i<9; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/Dot"+ofToString(i)+"_Small.png");
        iconImg.push_back(temp);
    }
    
    bgRect.set(0, 0, bgImg.getWidth(),bgImg.getHeight());
    for (int i=0; i<3; i++) {
        ofRectangle temp;
        temp.set(140+220*i, 500, 40, 30);
        buttons.push_back(temp);
        
        ofColor tempColor;
        tempColor.set(200);
        buttonColor.push_back(tempColor);
    }
    
    for (int i=0; i<4; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/321_"+ofToString(i)+".png");
        readyImg.push_back(temp);
    }
    
    for (int i=0; i<3; i++) {
        ofImage temp;
        LDbtttonImg[i].loadImage("assets/images/inGameMenu/bg_button0"+ofToString(i)+".png");
    }
    
    homeImgA.loadImage("assets/images/inGameMenu/menu.png");
    homeImgB.loadImage("assets/images/inGameMenu/menu_b.png");
    resumeImgA.loadImage("assets/images/inGameMenu/resume.png");
    resumeImgB.loadImage("assets/images/inGameMenu/resume_b.png");
    
    
    homeRect.button = &homeImgA;
    homeRect.buttonTouchOver= &homeImgB;
    resumeRect.button = &resumeImgA;
    resumeRect.buttonTouchOver = &resumeImgB;
    
    
    reset();
        
};

//-----------------------------------------------------------------------
void inGameMenu::update(){
    
    scoreUpdate();
    
    angle = (int)ofMap((60-*gameTimer), 0, 60, 0, 360);
    
    if (angle-preAngle == 1) {
        
        lineColor[angle].set(255,30);
    }
    
    for (int i=(angle+1); i<360; i++) {
        if (bTimeSlower) {
            lineColor[i].set(153,201,235);
        }else{
            lineColor[i].set(30);
        }
    }
    
    
    preAngle = angle;
    
    if (!bPauseL && !bPauseR) {
        if (accFrc->y > 0.5){
            bPauseL = true;
        }else if(accFrc->y<-0.5){
            bPauseR = true;
        }
    }
    
}

//-----------------------------------------------------------------------
void inGameMenu::starter(){

    if (!bGameStart) {
        
        gameStartAlpha += gameStartSpeed;
        
        if (gameStartAlpha>255&& gameStartCounter < 3) {
            gameStartAlpha = 255;
            
            gameStartOffset.y-=1;
            if (gameStartOffset.y > 2) {
                gameStartOffset.y = 2;
            }
            
            gameStartTimer ++;
            
        }
        
        if (gameStartTimer > 15 && gameStartCounter < 3) {
            gameStartSpeed *= -1;
            gameStartTimer = 0;
        }
        
        if(gameStartAlpha<0 && gameStartCounter < 3){
            gameStartAlpha = 0;
            gameStartSpeed *= -1;
            gameStartCounter++;
            gameStartOffset.y = 0;
        }
        
        if (gameStartCounter == 3) {
            gameStartPct +=0.2f;
            gameStartScale = (1-gameStartPct)*0.6+gameStartPct;
            if (gameStartPct > 1) {
                gameStartPct = 1;
                gameStartTimer ++;
            }
            
            if (gameStartTimer>15) {
                bGameStart = true;
            }
        }
        
       
        if (gameStartCounter==readyImg.size()) {
            gameStartCounter = readyImg.size()-1;
        }
       
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2+gameStartOffset.y);
        ofSetColor(255,gameStartAlpha);
        readyImg[gameStartCounter].draw(-readyImg[gameStartCounter].getWidth()/2*gameStartScale,
                                        -readyImg[gameStartCounter].getHeight()/2*gameStartScale,
                                        readyImg[gameStartCounter].getWidth()*gameStartScale,
                                        readyImg[gameStartCounter].getHeight()*gameStartScale);
                                        
        ofPopMatrix();
    }
    
    if (gameStartCounter != preGameStartCounter) {
        b321GO = true;
    }
    
    preGameStartCounter = gameStartCounter;
}

//-----------------------------------------------------------------------
void inGameMenu::reset(){

    LDType = BG_FADE;
    bButtonSound = false;
    bLevelDone = false;
    bNextLevel = false;
    bTryAgin   = false;
    bHome      = false;
    bStore     = false;
    bLevelFail = false;
    bTimeSlower = false;
    b321GO = false;
    angle      = 0;
    preAngle   = 0;
    
    linePos.clear();
    lineColor.clear();
    
    for (int i=0; i<360; i++) {
        ofPoint temp;
        temp.x = 20*cos(i*DEG_TO_RAD - PI/2);
        temp.y = 20*sin(i*DEG_TO_RAD - PI/2);
        linePos.push_back(temp);
        
        ofColor color(30);
        lineColor.push_back(color);
    }
    //game starter
    if (*level<5) {
        bGameStart = true;
    }else{
        bGameStart = false;
    }
    
    gameStartCounter = 0;
    preGameStartCounter = -1;
    gameStartAlpha = 0;
    gameStartSpeed = 90;
    gameStartOffset.set(0, 0);
    gameStartPct = 0;
    gameStartScale = 1;
    gameStartTimer = 0;
    //level done
    *bgScale = 1;
    LDVelocity.set(0, 0);
    LDGravity = 10;
    LDFriction = -0.75;
    LDRadius = 332;
    LDPos.set(ofGetWidth()/2, -LDRadius);
    LDAlpha = 0;

    LDButton[0].button =&LDbtttonImg[0];
    LDButton[1].button =&LDbtttonImg[1];
    LDButton[2].button =&LDbtttonImg[2];
  
    //score
    preCoin = *coin;
    score = 0;
    timer = 0;
    
    if (*fingerSize <=5) {
        fingerRate = 30;
    }else if(*fingerSize ==6){
        fingerRate = 50;
    }else if(*fingerSize ==7){
        fingerRate = 100;
    }else if(*fingerSize ==8){
        fingerRate = 200;
    }
    
    //pause
    bPauseL = false;
    bPauseR = false;
    
    pausePct = 0;
    homeRect.shaper = 0.6;
    resumeRect.shaper = 0.6;
    homeRect.pos.set(-1000, ofGetHeight()/2);
    resumeRect.pos.set(-1000, ofGetHeight()/2);
    
    //small icon
    for (int i=0; i<8; i++) {
        bSmallIconCovered[i] = false;
    }
}

//-----------------------------------------------------------------------
void inGameMenu::draw(){
    
    if (!bPauseL && !bPauseR) {
        starter();
    }
    
    if (LDType == BG_FADE) {
        
        ofSetColor(*overAllColor);
        bgImg.draw(bgRect);
        
        //life
        if (*level < 5) {
            nowLive = *TryLive;
        }else{
            nowLive = *live;
        }
        int num;
        int NUM;
        if (nowLive<=5) {
            num = 0;
            NUM = nowLive;
        }else{
            num = (int)nowLive/5;
            NUM = nowLive-num*5;
            if (NUM ==0) {
                num -=1;
                NUM = 5;
            }
        }
        
        
        ofSetColor(*overAllColor);
        fingerImg[NUM].draw(140,-5,fingerImg[NUM].getWidth()/4*3,fingerImg[NUM].getHeight()/4*3);
        ofSetColor(30);
        font.drawString("  x "+ofToString(num), 165, 40);
        
        liveCounter(260, 40, 0);
        
        ofSetColor(30);
        font.drawString("lv"+ofToString(*level+1), 930, 37);
        
        ofPushMatrix();
        ofTranslate(56, 27);
        for (int i=0; i<linePos.size(); i++) {
            ofSetColor(lineColor[i]);
            ofLine(0, 0, linePos[i].x, linePos[i].y);
        }
        ofPopMatrix();
        
        ofSetColor(*overAllColor);
        clockOutLine.draw(56-clockOutLine.getWidth()/2, 27-clockOutLine.getHeight()/2);
        
        
        for (int i=0; i<8; i++) {
           
            if (bSmallIconCovered[i]) {
                ofSetColor(100);
            }else{
                ofSetColor(*overAllColor);
            }
            
            if (i<*fingerSize) {
                iconImg[i].draw(405+50*i,10);
            }else{
                iconImg[8].draw(405+50*i,10);
            }
        }
    }
   
    if (!bPauseL && !bPauseR) {
        levelDoneDraw();
    }
    
    pause();

}

//-----------------------------------------------------------------------
void inGameMenu::touchDown(int x, int y){

    if (bPauseL || bPauseR) {
    
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = true;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = true;
        }
        
        
    }
    
    
    if (bLevelDone || bLevelFail) {
        if(LDButton[0].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDButton[0].bTouchOver = true;
        }
        
        if(LDButton[1].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDButton[1].bTouchOver = true;
        }
    }

}

//-----------------------------------------------------------------------
void inGameMenu::touchMove(int x, int y){

    if (bPauseL || bPauseR) {
        
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = true;
        }else{
            resumeRect.bTouchOver = false;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = true;
        }else{
            homeRect.bTouchOver = false;
        }
        
     
        
    }
    
    if (bLevelDone || bLevelFail) {
        if(LDButton[0].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDButton[0].bTouchOver = true;
        }else{
            LDButton[0].bTouchOver = false;
        }
        
        if(LDButton[1].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDButton[1].bTouchOver = true;
        }else{
            LDButton[1].bTouchOver = false;
        }
        
        if(LDButton[2].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDButton[2].bTouchOver = true;
        }else{
            LDButton[2].bTouchOver = false;
        }
    }

}

//-----------------------------------------------------------------------
void inGameMenu::touchUp(int x, int y){
    
    if (bPauseL || bPauseR) {
        
        if (resumeRect.bgRect.inside(x, y)) {
            resumeRect.bTouchOver = false;
            bPauseL = false;
            bPauseR = false;
            pausePct = 0;
            bButtonSound = true;
        }
        
        if (homeRect.bgRect.inside(x, y)) {
            homeRect.bTouchOver = false;
            bPauseL = false;
            bPauseR = false;
            pausePct = 0;
            bHome = true;
            bButtonSound = true;
        }
        
    }
    
    if (bLevelDone || bLevelFail) {
    
        if(LDButton[0].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            bHome = true;
            if (bLevelDone) {
                *level+=1;
            }
            LDButton[0].bTouchOver = false;
            bButtonSound = true;

        }
        
        if(LDButton[1].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            LDType = ICON_FADE;
            LDButton[1].bTouchOver = false;
            bButtonSound = true;
        }
        
        if(LDButton[2].bgRect.inside(x-LDPos.x, y-LDPos.y)){
            bStore = true;
            if (bLevelDone) {
                *level+=1;
            }
            LDButton[2].bTouchOver = false;
            bButtonSound = true;
        }
        
    }

}

//-----------------------------------------------------------------------
void inGameMenu::levelDoneDraw(){
   
    if (bLevelDone || bLevelFail) {
        
        ofPoint totalPos(0,110);
        
        switch (LDType) {
                
            case BG_FADE:{
                
                if (*bgScale>0.98) {
                    *bgScale-=0.001f;
                    LDAlpha += 10;
                }else{
                    LDType = ICON_SHOW;
                }
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
            }break;
            case ICON_SHOW:{
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                LDVelocity.y += LDGravity;
                LDPos +=LDVelocity;
               
                if (LDPos.y > ofGetHeight()/2) {
                    LDPos.y = ofGetHeight()/2;
                    LDVelocity*=LDFriction;
                }
                
                
                ofSetColor(255);
                ofPushMatrix();
                ofTranslate(LDPos);
                if (bLevelDone) {
                    LDBackgroudImg[0].draw(-165,-165);
                }else{
                    LDBackgroudImg[1].draw(-165,-165);
                }
                
                string message;
                message = ofToString(score);
                ofSetColor(30);
                fontBig.drawString(message, -fontBig.stringWidth(message)/2, -40-fontBig.stringHeight(message)/2);
                
                ofSetColor(125);
                message = "Total:"+ofToString(*coin);
                fontSmall.drawString(message,10 -fontSmall.stringWidth(message)/2, -fontSmall.stringHeight(message)/2);
                
                ofSetColor(255);
                fontSmall.drawString(ofToString(itemSize[0]), -82,50);
                fontSmall.drawString(ofToString(itemSize[1]), 25, 50);
                fontSmall.drawString(ofToString(itemSize[2]), 109,50);
                
                
                LDButton[0].pos.set(0, 115);
                LDButton[1].pos.set(62, 115);
                LDButton[2].pos.set(-62, 115);

                LDButton[0].drawInGameMenu();
                LDButton[1].drawInGameMenu();
                LDButton[2].drawInGameMenu();

                liveCounter(-80,90, 1);

                ofPopMatrix();
                
            }break;
                
            case ICON_FADE:{
                
                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                LDVelocity.y += LDGravity;
                LDPos +=LDVelocity;
                
                ofSetColor(255);
                ofPushMatrix();
                ofTranslate(LDPos);
                if (bLevelDone) {
                    LDBackgroudImg[0].draw(-165,-165);
                }else{
                    LDBackgroudImg[1].draw(-165,-165);
                }
                ofSetColor(30);
                
                string message;
                message = ofToString(score);
                ofSetColor(30);
                fontBig.drawString(message, -fontBig.stringWidth(message)/2, -40-fontBig.stringHeight(message)/2);
                
                ofSetColor(125);
                message = "Total:"+ofToString(*coin);
                fontSmall.drawString(message,50 -fontSmall.stringWidth(message)/2, -fontSmall.stringHeight(message)/2);
                
                ofSetColor(255);
                fontSmall.drawString(ofToString(itemSize[0]), -82,50);
                fontSmall.drawString(ofToString(itemSize[1]), 25, 50);
                fontSmall.drawString(ofToString(itemSize[2]), 109,50);
                                
                LDButton[0].pos.set(0, 115);
                LDButton[1].pos.set(62, 115);
                LDButton[2].pos.set(-62, 115);
                
                LDButton[0].drawInGameMenu();
                LDButton[1].drawInGameMenu();
                LDButton[2].drawInGameMenu();
                
                liveCounter(-80,90, 1);
                
                ofPopMatrix();
                
                if (LDPos.y > ofGetHeight()+LDRadius) {
                    LDType = BG_BACK;
                }
                
            }break;
            case BG_BACK:{
                
                if (*bgScale< 1) {
                    *bgScale+=0.001f;
                    LDAlpha -= 10;
                }else{
                    
                    *coin += score;
                    
                    if (nowLive == 0) {
                        bHome = true;
                    }else if (bLevelDone) {
                        bNextLevel = true;
                    }else if(bLevelFail){
                        bTryAgin = true;
                    }
                }
              

                ofSetColor(0, 0, 0,LDAlpha);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
            }break;
            
        }
    }
}

//-----------------------------------------------------------------------
void inGameMenu::scoreUpdate(){

    if (bLevelDone) {
        score = fingerRate*(*fingerSize)+ 50*itemSize[0];
        
    }else if(bLevelFail){
        score = 0;
    }else{
        score = 0;
    }

}

//-----------------------------------------------------------------------
void inGameMenu::pause(){
    
    
    if (bPauseL || bPauseR) {
        float speed = 0.1f;
       
        ofSetColor(255, 200);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        if (bPauseL) {
            resumeRect.posa.set(-resumeRect.button->getWidth(), ofGetHeight()/2);
            homeRect.posa.set(-homeRect.button->getWidth(), ofGetHeight()/2);

        }
        else if (bPauseR) {
            resumeRect.posa.set(ofGetWidth()+resumeRect.button->getWidth(), ofGetHeight()/2);
            homeRect.posa.set(ofGetWidth()+homeRect.button->getWidth(), ofGetHeight()/2);
        }
        
        homeRect.posb.set(ofGetWidth()/2+200, ofGetHeight()/2);
        resumeRect.posb.set(ofGetWidth()/2-150, ofGetHeight()/2);

        pausePct+=speed;
        if (pausePct>1) {
            pausePct = 1;
        }
        
        homeRect.interpolateByPct(pausePct);
        resumeRect.interpolateByPct(pausePct);
        
        ofSetColor(255);
        resumeRect.drawPause();
        homeRect.drawPause();
    }
    
    
//    cout<<accFrc->y<<" "<<bPauseL<<" "<<bPauseR<<" "<<pausePct<<" "<<homeRect.pos<<" "<<resumeRect.pos<<endl;


}

//-----------------------------------------------------------------------
void inGameMenu::liveCounter(int x, int y, int num){
  
    if (*live < 10) {
        
        string message;
        int time = 600 - (ofGetUnixTime() - *unixTime);
        int min = 0;
        int sec = 0;
        
        if (time > 60) {
            min = (int)(time/60);
            sec = time - 60*min;
        }else{
            sec = time;
        }
        
        message = ofToString(min)+":"+ ofToString(sec);
        
        ofSetColor(30);
      
        if (num == 0) {
            
            fontSmall.drawString("in", x, y);
            
            font.drawString(message, x+30, y);
            
        }else if(num == 1){
                    
            fontSmall.drawString(message, x, y);

        }
        
    }

}