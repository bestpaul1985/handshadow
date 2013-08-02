


#include "dots.h"

//-------------------------------------------------------
void dots::setup(float x, float y,ofImage *A, ofImage *B){
    
    pos.set(x,y);
    radius = 83;
    dot_normal = A;
    dot_pressed = B;
    reset();
    angle = 0;
    bRadiusExtend = false;
    bFreezed = false;
    radiusPct = 0;
    radiusPctOrg = 0;
    goalRaduis = 83;
}

//-------------------------------------------------------
void dots::update(){
    
    radiusExtend();
    
}
//-------------------------------------------------------
void dots::radiusExtendReset(){
    radiusPct = 0;
    radiusPctOrg = 0;
    bRadiusExtend = false;
}
//-------------------------------------------------------
void dots::radiusExtend(){
    
    if (bRadiusExtend) {
        float speed = 0.001f;
        radiusPctOrg += speed;
        if (radiusPctOrg >=1) {
            radiusPctOrg = 1;
            bRadiusExtend = false;
        }
        radiusPct = powf(radiusPctOrg, 0.6);
        radius = (1-radiusPct)*radius + radiusPct*goalRaduis;
    }
}

//-------------------------------------------------------
void dots::reset(){
    notMyId.clear();
    myId.clear();
    bCovered = false;
    bFixed = true;
}

//-------------------------------------------------------
void dots::draw(){
    
    if (!bFixed) {
        ofPushMatrix();
        if (!bFreezed) {
            color.set(255);
        }else{
            color.set(30);
        }
        ofSetColor(color);
        ofTranslate(pos.x, pos.y);
        //        ofRotateZ(angle);
        if (bCovered) dot_pressed->draw(-radius, -radius,radius*2,radius*2);
        else dot_normal->draw(-radius, -radius,radius*2,radius*2);
        ofPopMatrix();
    }
}

//-------------------------------------------------------
void dots::touchDown(int x, int y, int touchID){
    
    
    if (!bFixed&& !bFreezed) {
        ofPoint touchPos(x,y);
        if (pos.distance(touchPos) < radius) {
            myId.push_back(touchID);
        }
        
        if (myId.size()>0) {
            bCovered = true;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
}

//-------------------------------------------------------
void dots::touchMove(int x, int y, int touchID){
    
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) > radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        if (myId.size()==0) {
            bCovered = false;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
}

//-------------------------------------------------------
void dots::touchUp(int x, int y, int touchID){
    
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) < radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        if (myId.size()==0) {
            bCovered = false;
        }
        
        if (bFreezed) {
            bCovered = true;
        }
    }
    
}





