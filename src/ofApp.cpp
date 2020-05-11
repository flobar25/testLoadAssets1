#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    recorder.setPrefix(ofToDataPath("recording/frame_"));
    recorder.setFormat("bmp");
    recorder.startThread();
    ofSetFrameRate(30);
    midiIn.openPort(0);
    midiIn.addListener(this);
    model.loadModel("hands/RiggedHand.3ds");
}

void ofApp::exit(){
    recorder.waitForThread();
    recorder.stopThread();
}

//--------------------------------------------------------------
void ofApp::update(){
    // show the framerate on window title
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(0, 0, 0, 0);
    ofSetColor(255, 255, 255, 255);
    model.setPosition(ofGetWidth()*2/6, (float)ofGetHeight() * 0.75 , 0);
//    model.draw(OF_MESH_FILL); //same as model.drawFaces();
//    model.setPosition(ofGetWidth()*3/6, (float)ofGetHeight() * 0.75 , 0);
//    model.draw(OF_MESH_POINTS); // same as model.drawVertices();
//    model.setPosition(ofGetWidth()*4/6, (float)ofGetHeight() * 0.75 , 0);
//    model.draw(OF_MESH_WIREFRAME); // same as model.drawWireframe();
//
//    model.getMesh(0).drawWireframe();
//    model.getMesh(1).drawWireframe();
//    model.drawWireframe();
    
//    model.getMesh(0).set;
    auto mesh = model.getCurrentAnimatedMesh(0);
    
    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);

    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);

    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.begin();
    mesh.drawFaces();
    material.end();

    
    cam.end();
    
    // capture the image if recording is started
    // this can slow down the rendering by a lot, so be aware of the framerate...
    // if frames are skipped this is going to mess up the rendering when imported as a video
    if (recording){
        screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        recorder.addFrame(screenCapture);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'r':
            toggleRecording();
            break;
        case 'p':
            captureScreen();
            break;
        default:
            break;
    }
}

void ofApp::newMidiMessage(ofxMidiMessage& eventArgs){
    
}

void ofApp::captureScreen(){
    screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    screenCapture.save("captures/capture.bmp");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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

void ofApp::toggleRecording(){
    recording = !recording;
}

