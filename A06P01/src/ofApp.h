
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "volumeRenderThread.h"


class ofApp : public ofBaseApp {
  public:
    int clicks;
    void setup();
    void update();
    void draw();
    void exit();
    void updateIsovalue(float& isovalue);
    void updateRed(float& rosso);
    void updateBlue(float& blu);
    void updateGreen(float& verde);
    void toggleShading(bool& shadeOn);
    void setOpacity();
    void setRGB();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void sort();
    vector<ofVec2f> points;
    vector<float> pointsColor;
    vector<ofVec3f> colors;
    vector<int> foo;
    bool startedVTK;
    int inside(int x ,int y);
    int inside2(int x ,int y);
    bool onCanvas(int x ,int y);
    bool onColorMap(int x, int y);
    bool onSelect(int x, int y);
    volumeRenderThread vr;
    ofEasyCam cam;
    int max;
    ofxPanel guiPanel;
    ofxFloatSlider isovalueSlider;
    ofxFloatSlider red;
    ofxFloatSlider green;
    ofxFloatSlider blue;
    ofxToggle shadingToggle;
    bool del=false;
    bool border2=false;
    int r,g,b;
    bool colora=false;
    bool colora2=false;
    bool border=false;
    bool selected=false;
    bool drag=false;
    bool drag2=false;
    int Rindex;
    int Rindex2;
    int colormap;
};
