
#include "ofApp.h"

void ofApp::setup(){
    string path;
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
        path = result.getPath();
        vr.setup((path).c_str());
    }
    else{
        return;
    }

 
  startedVTK = false;
    ofVec2f v;
    v.set(255,500);
    points.push_back(v);
    ofVec2f v2;
    v2.set(505,250);
    points.push_back(v2);
    pointsColor.push_back(vr.range[0]);
    pointsColor.push_back(vr.range[1]);
    ofVec3f v3;
    v3.set(0.24,0.28,0.73);
    ofVec3f v4;
    v4.set(0.69,0.02,0.16);
    colors.push_back(v3);
    colors.push_back(v4);
    
    colora2=false;
    colora=false;
    selected=false;
  //now that we've read the data, set up the gui
  //we'll make the slider have a callback to re-run MC
  isovalueSlider.addListener(this, &ofApp::updateIsovalue);
  red.addListener(this, &ofApp::updateRed);
  green.addListener(this, &ofApp::updateGreen);
  blue.addListener(this, &ofApp::updateBlue);
  shadingToggle.addListener(this, &ofApp::toggleShading);

  guiPanel.setup();
  guiPanel.add(isovalueSlider.setup("isovalue", 0.5*(vr.range[1]-vr.range[0]) + vr.range[0], vr.range[0], vr.range[1]));
  guiPanel.add(shadingToggle.setup("Draw with Shading", true));

  

  //vtkSmartPointer<vtkDataArray> scalar=vr.image->GetPointData()->GetScalars();
    
//    cout<<vr.dims[0]<<endl;
//  float*data = new float[vr.dims[0]*vr.dims[1]*vr.dims[2]];
//    int i=0;
//    int i2=0;
//    for (int z=0; z<vr.dims[2]; z++) {
//        for (int y=0; y<vr.dims[1]; y++) {
//            for(int x=0; x<vr.dims[0]; x++) {
//                data[i2] = scalar->GetTuple1(i);
//                i2++;
//                i++;
//            }
//        }
//    }
//    for (int i=0; i<vr.range[1]; i++) {
//        foo.push_back(0);
//    }
//    //int foo [(int)vr.range[1]];
//    i2=0;
//    int tot=0;
//    for (int i=0; i<vr.dims[0]*vr.dims[1]*vr.dims[2]; i++) {
//        tot=tot+foo[static_cast<int>(data[i])];
//        if(i2==1800){
//            i2=0;
//            tot=0;
//            
//            foo[static_cast<int>(data[i])]=c+1;
//            if(max<c+1)
//                max=c+1;
//        }
//        i2++;
//    }
}



//--------------------------------------------------------------
void ofApp::update(){
}




int foo = 0;

//--------------------------------------------------------------
void ofApp::draw() {
  //draw the GUI
    if(colora){
//        guiPanel.clear();
        colora=false;
        guiPanel.add(red.setup("R", 55, 0, 255));
        guiPanel.add(green.setup("G", 200, 0, 255));
        guiPanel.add(blue.setup("B", 130, 0, 255));
        colora2=true;
    }
    if (selected) {
        selected=false;
        guiPanel.clear();
        guiPanel.add(isovalueSlider.setup("isovalue", 0.5*(vr.range[1]-vr.range[0]) + vr.range[0], vr.range[0], vr.range[1]));
        guiPanel.add(shadingToggle.setup("Draw with Shading", true));
        setOpacity();
    }
  guiPanel.draw();

  if (!startedVTK) {
    vr.setupRenderer();
    vr.startThread();
    startedVTK = true;
    float initial_iso = isovalueSlider;
    //updateIsovalue(initial_iso);
    setOpacity();
  }
    if(colora2){
        
        ofSetColor(255);
        ofRect(20,300,150,40);
        ofSetColor(0);
        ofDrawBitmapString("Select Color", 40, 320);
        //ofFill();
        ofDrawBitmapString("Preview of the color selected:", 10, 150);
        ofColor c;
        c.r=r;
        c.b=b;
        c.g=g;
        ofSetColor(c);
        ofRect(50,180,90,90);

    }
   int i =0;
    for (int color=(int)vr.range[0]; color<=(int)vr.range[1]; color+=(int)vr.range[1]/17){
       ofColor c;
       double  r =vr.color-> GetRedValue(color);
       double  g =vr.color-> GetGreenValue(color);
       double  b =vr.color-> GetBlueValue(color);
        c.r=ofMap(r, 0,1 ,0, 255);
        c.g=ofMap(g, 0,1, 0, 255);
        c.b=ofMap(b, 0,1, 0, 255);
        ofSetColor(c);
        ofRect(240+i,550,20,20);
         i=i+15;
    }
    
    ofSetColor(255,255,255);
    ofRect(255,250,250,250);
    ofSetColor(0,0,0);
    int x=255;
    
//    for (int i = 0; i < foo.size(); i++) {
//        //ofColor color = ofColor::fromHsb(data[i]*25, 255,255 );
//        //ofSetColor( color );
//        
//        //if(foo[i]>3000){
//        int height=ofMap(foo[i],0,max ,0, 255);
//        //cout<<max<<endl;
//            ofDrawRectangle(x ,500,2, -(height));
//            x=x+3;
//        //}
//    }
    for (int i=0; i<points.size(); i++) {
        ofCircle(points[i][0],points[i][1], 6);
    }
    
    for (int i=0; i<pointsColor.size(); i++) {
         float m=ofMap(pointsColor[i],vr.range[0],vr.range[1],240,515);
        ofCircle(m,560, 6);
        
    }

    if(border){
        ofSetColor(255);
        ofDrawRectangle(300 ,180,180,40);
        float x=ofMap(points[Rindex][0],255,505,vr.range[0],vr.range[1]);
        float y=ofMap(points[Rindex][1],500,250,0,1);
        char sz[64];
        char sz2[64];
        ofSetColor(0);
        sprintf(sz, "%.2lf\n", x);
        sprintf(sz2, "%.2lf\n", y);
        ofDrawBitmapString(sz, 320, 200);
        ofDrawBitmapString(",", 390, 200);
        ofDrawBitmapString(sz2, 420, 200);
        ofSetColor(255,0,0);
        ofNoFill();
        ofCircle(points[Rindex][0],points[Rindex][1], 8);
    }
    if(border2){
        ofSetColor(255);
        ofDrawRectangle(340 ,180,110,40);
        ofSetColor(0);
        char sz[64];
        sprintf(sz, "%.2lf\n", pointsColor[Rindex2]);
        ofDrawBitmapString(sz, 350, 200);
        ofNoFill();
        ofSetColor(255,0,0);
        float m=ofMap(pointsColor[Rindex2],vr.range[0],vr.range[1],240,515);
        ofCircle(m,560, 8);
    }
    ofFill();
    ofSetColor(0,0,0);
    
    for (int i=0; i<points.size()-1; i++) {
        ofPolyline line;
        ofPoint pt;
        pt.set(points[i][0],points[i][1]);
        line.addVertex(pt);
        pt.set(points[i+1][0],points[i+1][1]);
        line.addVertex(pt);
        line.draw();
    }
    ofDrawBitmapString(std::to_string((int)vr.range[0]), 240, 530);
    ofDrawBitmapString(std::to_string((int)vr.range[1]), 500, 530);

    
}

void ofApp::exit() {
  vr.stopThread();
  //::exit(0);


  vr.waitForThread();
}

void ofApp::sort(){

    int flag =1;
    for(int i = 1; (i <= points.size()) && flag; i++)
    {
        flag = 0;
        for (int j=0; j < points.size()-1; j++)
        {
            
            if (points[j+1][0] < points[j][0])      // ascending order simply changes to <
            {
                ofVec2f v2;
                v2.set(points[j][0],points[j][1]);
                //temp = num[j];             // swap elements
                points[j] = points[j+1];
                points[j+1] = v2;
                flag = 1;               // indicates that a swap occurred.
            }
        }
    }
}


//This function actually runs Marching Cubes using vtk's
//vtkMarchingCubes filter
void ofApp::updateIsovalue(float& isovalue) {
    if (startedVTK) {
        //if (vr.lock()) {
        vr.compositeOpacity->RemoveAllPoints();
        vr.compositeOpacity->AddPoint(vr.range[0],0.0);
        vr.compositeOpacity->AddPoint(isovalue-0.05*(vr.range[1]-vr.range[0]),0.0);
        vr.compositeOpacity->AddPoint(isovalue,1.0);
        vr.compositeOpacity->AddPoint(isovalue+0.05*(vr.range[1]-vr.range[0]),0.0);
        vr.compositeOpacity->AddPoint(vr.range[1],0.0);
        
        vr.color->RemoveAllPoints();
        vr.color->AddRGBPoint(vr.range[0],0.0,0.0,1.0);
        vr.color->AddRGBPoint(vr.range[0]+0.5*(vr.range[1]-vr.range[0]),1.0,0.0,0.0);
        vr.color->AddRGBPoint(vr.range[1],0.0,1.0,0.0);
        
        vr.update();
        //vr.updated = true;
        //vr.unlock();
        //}
    }
}

void ofApp::updateRed(float& rosso) {
    r=rosso;
}
void ofApp::updateGreen(float& verde) {
    g=verde;
}
void ofApp::updateBlue(float& blue) {
    b=blue;
}

void ofApp::setOpacity() {
    if (startedVTK) {

        vr.compositeOpacity->RemoveAllPoints();
        for (int i=0; i<points.size(); i++) {
            float x;
            float y;
            x=ofMap(points[i][0],255,505,vr.range[0],vr.range[1]);
            y=ofMap(points[i][1],500,250,0,1);
            vr.compositeOpacity->AddPoint(x,y);
            
            
        }
        vr.color->RemoveAllPoints();
        for (int i=0; i<pointsColor.size(); i++) {
            vr.color->AddRGBPoint(pointsColor[i],colors[i][0],colors[i][1],colors[i][2]);
        }
        
        vr.update();
        
    }
}
void ofApp::setRGB() {
    
    float m=ofMap(colormap,240,515,vr.range[0],vr.range[1]);
    pointsColor.push_back(m);
    ofVec3f v4;
    float p=ofMap(r,0,255,0,1);
    float p2=ofMap(g,0,255,0,1);
    float p3=ofMap(b,0,255,0,1);
    v4.set(p,p2,p3);
    colors.push_back(v4);
    setOpacity();

}

void ofApp::toggleShading(bool& shadeOn) {
  if (startedVTK) {

      if (shadeOn) {
        vr.volumeProperty->ShadeOn();
      } else {
        vr.volumeProperty->ShadeOff();
      }

      vr.update();
  }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'd'){
        del=true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(drag){
        if(onCanvas(x,y)){
            points[Rindex][0]=x;
            points[Rindex][1]=y;
            sort();
            setOpacity();
        }
    }
    if(drag2){
        if(ofInRange(x,240,515)){
            float m=ofMap(x,240,515,vr.range[0],vr.range[1]);
            pointsColor[Rindex2]=m;
            setOpacity();}
    }
}
int ofApp::inside(int x, int y){

    for (int i=0; i<points.size(); i++) {
        if(ofInRange(x,points[i][0]-8,points[i][0]+8) && ofInRange(y,points[i][1]-8,points[i][1]+8)) {
            return i;
        }
    }
    return -1;
}
int ofApp::inside2(int x, int y){
    
    for (int i=0; i<pointsColor.size(); i++) {
        float m=ofMap(pointsColor[i],vr.range[0],vr.range[1],240,515);
        if(ofInRange(x,m-9,m+9) && ofInRange(y,550-8,570+8)) {
            return i;
        }
    }
    return -1;
}
bool ofApp::onCanvas(int x, int y){
        if(ofInRange(x,255,505) && ofInRange(y,250,500)) {

            return true;
        }
    return false;
}

bool ofApp::onColorMap(int x, int y){
    if(ofInRange(x,240,515) && ofInRange(y,550,570)) {
        colormap=x;
        return true;
    }
    return false;
}

bool ofApp::onSelect(int x, int y){

    if(colora2){
        
        if(ofInRange(x,20,170) && ofInRange(y,300,340)) {
            selected=true;
            colora2=false;
            setRGB();
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    border=false;
    border2=false;
    Rindex=inside(x,y);
    Rindex2=inside2(x,y);
    if (del){
        del=false;
        if(Rindex>0){
            if( Rindex!=points.size()-1){
                points.erase(points.begin() + Rindex);
                sort();
                setOpacity();
            }
            
        }
        if(Rindex2>0){
            cout<<pointsColor.size()<<endl;
            if( Rindex2!=1){
                pointsColor.erase(pointsColor.begin() + Rindex2);
                setOpacity();
            }
        
        }
    }
    else if (onCanvas(x,y)) {
        if(Rindex==-1){
            ofVec2f v;
            v.set(x,y);
            points.push_back(v);
            sort();
            setOpacity();
        } else {
            drag=true;
            border=true;
        }
    }
    else if(onColorMap(x,y)){
        if(Rindex2==-1){
            if (!colora2) {
                colora=true;
                
            }
        }
        else{
            border2=true;
            clicks++;
            drag2=true;
        }
    }
    else if(onSelect(x,y)){
        
    }
    if (clicks==2) {
        cout<<"double"<<endl;
        clicks=0;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    drag=false;
    drag2=false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
