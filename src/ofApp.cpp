// 2016.08.17 3Dモデルを使用せず画像を使用するように変更

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  // 画面設定
  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofBackground(255);
  
  // 通信関係
  // デバイスの接続するポートとスピードを設定
    ard.connect("/dev/cu.usbmodem1421", 57600); // Macbook Air
  //  ard.connect("/dev/cu.usbmodemFD121", 57600);
//    ard.connect("/dev/cu.usbmodemFA131", 57600);  // Lv.1
//  ard.connect("/dev/cu.usbmodemfa131", 57600);  // Lv.2 / 3
  

  
  // Arduinoとの接続が確立するのを監視するリスナー
  // 接続が確立したら、setupArduino()を実行
  ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
  // 接続が確立したかどうかのフラグ
  bSetupArduino = false;
  
  // 描画関係
  ofEnableDepthTest();  // 深度テストを有効に
  ofEnableSmoothing();  // 表示をスムースに
  
  // ライティング
  // ダイレクショナルライト
  directionalLight.setDiffuseColor(ofColor(0, 160, 233));  // 拡散反射光の色
  directionalLight.setSpecularColor(ofColor(0, 160, 233));  // 鏡面反射光の色
  directionalLight.setDirectional();
  directionalLight.setOrientation( ofVec3f(120, 0, 0) );
  
  // ダイレクショナルライト1
  directionalLight1.setDiffuseColor(ofColor(0, 160, 233));  // 拡散反射光の色
  directionalLight1.setSpecularColor(ofColor(0, 160, 233));  // 鏡面反射光の色
  directionalLight1.setDirectional();
//  directionalLight1.setOrientation( ofVec3f(0, 90, 0) );
  directionalLight1.setOrientation( ofVec3f(120, 90, 0) );
  //  directionalLight1.setOrientation( ofVec3f(-120, 0, 0) );


  // ダイレクショナルライト2
  directionalLight2.setDiffuseColor(ofColor(0, 160, 233));  // 拡散反射光の色
  directionalLight2.setSpecularColor(ofColor(0, 160, 233));  // 鏡面反射光の色
  directionalLight2.setDirectional();
//  directionalLight2.setOrientation( ofVec3f(0, 180, 0) );
  directionalLight2.setOrientation( ofVec3f(120, 180, 0) );

  // ダイレクショナルライト3
  directionalLight3.setDiffuseColor(ofColor(0, 160, 233));  // 拡散反射光の色
  directionalLight3.setSpecularColor(ofColor(0, 160, 233));  // 鏡面反射光の色
  directionalLight3.setDirectional();
//  directionalLight3.setOrientation( ofVec3f(90, 0, 0) );
  directionalLight3.setOrientation( ofVec3f(120, -90, 0) );
  
  
  // Meshのポイント定義
  setupMesh();
  
  // カメラ設定 ofCamera
  cam.setPosition(0, 100, 150);
  cam.setNearClip(0.01f);
  cam.setFarClip(1000.0f);
  cam.lookAt(ofVec3f(0,0,1));
  
//  // font settting
//  font.load("franklinGothic.otf", 20);
  
  // font setting ofxTrueTypeFontUC
  fontUC.loadFont("Yu Gothic Bold.otf", 40);
  
  // 音
  sound.load("se_maoudamashii_se_pc01.wav");
  sound.setLoop(false); // ループ再生をoffに
  sound.setMultiPlay(true);
  
  // 画像
  imgLv1_A.load("Lv1_A.png");
  imgLv1_B.load("Lv1_B.png");
  imgLv2_A.load("Lv2_A.png");
  imgLv2_B.load("Lv2_B.png");
  imgLv3_A.load("Lv3_A.png");
  imgLv3_B.load("Lv4_B.png");
  
  
  // 初期設定
  didAnswered = true;
  isCorrect = true;
  level = "1";  // デフォルトはレベル１
  didSoundPlayed = false;
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  // Arduinoを更新
  updateArduino();
  
  angleY += 0.5; // 角度の更新
  
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version){
  
  // 接続が確立したら、リスナーを削除
  ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
  
  // 接続確率のフラグをtrueに
  bSetupArduino = true;
  
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
  
  // Arduinoをアップデート、すべてのデータとメッセージを取得
  ard.update();
  // もしArduinoが接続されていたら
  if(bSetupArduino){
    //
    ofLog( OF_LOG_NOTICE, "Arduino connected");
  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  float x, y; // 文字を表示する位置を決める変数
//  int m = ofGetSeconds();
//  m = m % (9 * 1000); // 0~8999
  
  // キューブが認識されていない状態 (cubeType == "0")
  // 問題文描画
  if(cubeType == "0"){
    didSoundPlayed = false;
    if(didAnswered == true && isCorrect == true){
//    if(isCorrect == true){
      // 回答されていたら次の問題に
      nRandom = ofRandom(0, 1);
      didAnswered = false;
      
//
//      ofSetColor(0, 160, 233);
//      ofDrawRectangle(0, 0, 1024, 768);
//      ofSleepMillis(1000);
      
    }
//    else{
//      didSoundPlayed = false;
//    }
    
    // 問題文表示
    if(nRandom < 0.5){
      // center the word on the screen
      x = (ofGetWidth() - fontUC.stringWidth("Aはどっちでしょう?")) / 2;
      y = ofGetHeight() / 3;
      ofSetColor(0, 160, 233);
      fontUC.drawString("Aはどっちでしょう?", x, y);
      
      // 文字列変数設定
      question = "A";
      if(level == "1"){
        questionImg = imgLv1_A;
      }
      else if (level == "2"){
        questionImg = imgLv2_A;
      }
      else if (level == "3"){
        questionImg = imgLv3_A;
      }
      
    }
    else if(nRandom >= 0.5){
      // center the word on the screen
      x = (ofGetWidth() - fontUC.stringWidth("Bはどっちでしょう?")) / 2;
      y = ofGetHeight() / 3;
      
      ofSetColor(0, 160, 233);
      fontUC.drawString("Bはどっちでしょう?", x, y);
      
      // 文字列変数設定
      question = "B";
      if(level == "1"){
        questionImg = imgLv1_B;
      }
      else if (level == "2"){
        questionImg = imgLv2_B;
      }
      else if (level == "3"){
        questionImg = imgLv3_B;
      }
    }
    
    // レベル表示
    x = (ofGetWidth() - fontUC.stringWidth("レベル"+level)) / 2;
    y = ofGetHeight() / 5;
    ofSetColor(0, 160, 233);
    fontUC.drawString("レベル"+level, x, y);
    
    // 画像表示
    questionImg.draw(ofGetWidth()/2 - questionImg.getWidth()/(4*2), ofGetHeight()/2 - questionImg.getHeight()/(4*4), questionImg.getWidth()/4, questionImg.getHeight()/4);
    
    // 画像のキャプション(A/B)表示
    x = (ofGetWidth() - fontUC.stringWidth(question)) / 2;
    y = ofGetHeight() /2 + imgLv1_B.getHeight()/4 - fontUC.stringHeight(question)/2;
    ofSetColor(0, 160, 233);
    fontUC.drawString(question, x, y);
    
  }
  // キューブが認識されていない状態 (cubeType != "0")
  else if( ( (cubeType == "1" || cubeType == "2") && level == "1" ) ||
           ( (cubeType == "3" || cubeType == "4") && level == "2" ) ||
           ( (cubeType == "5" || cubeType == "6") && level == "3" )  ){
  
    // 回答描画
    if(isCorrect){
      // クリック音再生
      if(didSoundPlayed == false){
        sound.play();
        didSoundPlayed = true;
      }
      // 正解
      x = (ofGetWidth() - fontUC.stringWidth("せいかい！")) / 2;
      y = ofGetHeight() / 5;
      
      ofSetColor(0, 160, 233);
      fontUC.drawString("せいかい！", x, y);
    }
    else{
      // クリック音再生
      if(didSoundPlayed == false){
        sound.play();
        didSoundPlayed = true;
      }
      // 不正解
      x = (ofGetWidth() - fontUC.stringWidth("ざんねん！")) / 2;
      y = ofGetHeight() / 5;
      
      ofSetColor(0, 160, 233);
      fontUC.drawString("ざんねん！", x, y);
    }
  }
  else if (bSetupArduino == true){ // Arduinoと接続されてるがレベルと違う四角が置かれた時
    
    x = (ofGetWidth() - fontUC.stringWidth("ちがうつくえのしかくだよ")) / 2;
    y = ofGetHeight() / 5;
    
    ofSetColor(0, 160, 233);
    fontUC.drawString("ちがうつくえのしかくだよ", x, y);
  }
  else{
    // クリック音再生
    if(didSoundPlayed == false){
      sound.play();
      didSoundPlayed = true;
    }
    
    // center the word on the screen
    x = (ofGetWidth() - fontUC.stringWidth("じゅんびちゅう")) / 2;
    y = ofGetHeight() / 2;
    
    ofSetColor(0, 160, 233);
    fontUC.drawString("じゅんびちゅう", x, y);
    
  }
  
  
  // ライティング有効化
  directionalLight.enable();
//  directionalLight1.enable();
//  directionalLight2.enable();
//  directionalLight3.enable();
  
  cam.begin();  // カメラ開始
  
  // 通信関係
  ofSetColor(255, 255, 255);
  // Arduinoの状態を画面に出力
  if(!bSetupArduino){
//    font.drawString("arduino not ready\n", 0, 150);
    ofLog( OF_LOG_NOTICE, "arduino not ready" );
    
  }else{
    cubeType = ofToString(ard.getString());
//    font.drawString("String : " + cubeType, 0, 150);
    ofLog( OF_LOG_NOTICE, cubeType );
  }
  
  
  // 原点移動
  ofRotateY(angleY);
  ofTranslate(-35, -35, -35);
  
  if(cubeType == "1"){
    answerImg = imgLv1_A;
    
    if(level == "1" && question == "A"){
      // 正解
      isCorrect = true;
    }
    else if(level == "1" && question == "B"){
      // 不正解
      isCorrect = false;
    }
    didAnswered = true;
    
    // No.1
    //Lv.1 A (空)
    // 内側描画
    //    ofSetColor(255, 255, 255);
    //    cubeInner1.set(65); // サイズ設定
    //    cubeInner1.setResolution(100); // 解像度設定
    //    cubeInner1.setPosition(35, 35, 35); //  位置 65 / 2 + 2.5
    //    cubeInner1.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(0, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();
    
  }
  else if(cubeType == "2"){
    answerImg = imgLv1_B;
    
    if(level == "1" && question == "A"){
      // 不正解
      isCorrect = false;
    }
    else if(level == "1" && question == "B"){
      // 正解
      isCorrect = true;
    }
    didAnswered = true;
    
    // No.2 32.5x32.5x65
    
    // 内側描画
    ofSetColor(0, 160, 233);
    cubeInnerLv1B.set(65); // サイズ設定
    cubeInnerLv1B.setResolution(100); // 解像度設定
    cubeInnerLv1B.setPosition(35, 35, 35); //  位置 65 / 2 + 2.5
    cubeInnerLv1B.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(0, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();
    
  }
  else if(cubeType == "3"){
    answerImg = imgLv2_A;
    
    // Lv.2 A 四角柱中央
    // 内側描画
    ofSetColor(0, 160, 233);
    meshInnerLv2A.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(0, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();
    
    if(level == "2" && question == "A"){
      // 正解
      isCorrect = true;
    }
    else if(level == "2" && question == "B"){
      // 不正解
      isCorrect = false;
    }
    didAnswered = true;
    
  }
  else if(cubeType == "4"){
    answerImg = imgLv2_B;
    
    // Lv.2 B 四角柱端
    // 内側描画
    ofSetColor(0, 160, 233);
    meshInnerLv2and3B.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(0, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();
    
    if(level == "2" && question == "A"){
      // 不正解
      isCorrect = false;
    }
    else if(level == "2" && question == "B"){
      // 正解
      isCorrect = true;
    }
    didAnswered = true;
    
  }
  else if(cubeType == "5"){
    answerImg = imgLv3_A;
    
    //No.5 32.5x32.5x65  
    // 内側描画
    ofSetColor(0, 160, 233);
    meshInnerLv3A.drawFaces();
//    meshInner2.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(0, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();

    
    if(level == "3" && question == "A"){
      // 正解
      isCorrect = true;
    }
    else if(level == "3" && question == "B"){
      // 不正解
      isCorrect = false;
    }
    didAnswered = true;
    
  }
  else if(cubeType == "6"){
    answerImg = imgLv3_B;
    
    // Lv.2 B 四角柱端
    // 内側描画
    ofSetColor(0, 160, 233);
    meshInnerLv2and3B.drawFaces();
    
    // 外側のキューブ描画
    ofSetColor(20, 160, 233, 100);
    cubeOuter.set(70); // サイズ設定
//    cubeOuter.setResolution(100); // 解像度設定
    cubeOuter.setPosition(35, 35, 35); //  位置 70 / 2
    cubeOuter.drawWireframe();
    
    if(level == "3" && question == "A"){
      // 不正解
      isCorrect = false;
    }
    else if(level == "3" && question == "B"){
      // 正解
      isCorrect = true;
    }
    didAnswered = true;
  }
  
  cam.end();
  
}

//--------------------------------------------------------------
void ofApp::setupMesh(){
  // Lv.2 A 四角柱中央
  meshInnerLv2A.addVertex(ofVec3f(20, 5, 20));
  meshInnerLv2A.addVertex(ofVec3f(50, 5, 20));
  meshInnerLv2A.addVertex(ofVec3f(50, 5, 50));
  meshInnerLv2A.addVertex(ofVec3f(20, 5, 50));
  meshInnerLv2A.addVertex(ofVec3f(20, 65, 20));
  meshInnerLv2A.addVertex(ofVec3f(50, 65, 20));
  meshInnerLv2A.addVertex(ofVec3f(50, 65, 50));
  meshInnerLv2A.addVertex(ofVec3f(20, 65, 50));
  
  meshInnerLv2A.usingIndices();
  
  meshInnerLv2A.addIndex(0);
  meshInnerLv2A.addIndex(1);
  meshInnerLv2A.addIndex(2);
  meshInnerLv2A.addIndex(0);
  meshInnerLv2A.addIndex(3);
  meshInnerLv2A.addIndex(2);
  
  meshInnerLv2A.addIndex(0);
  meshInnerLv2A.addIndex(1);
  meshInnerLv2A.addIndex(5);
  meshInnerLv2A.addIndex(0);
  meshInnerLv2A.addIndex(4);
  meshInnerLv2A.addIndex(5);
  
  meshInnerLv2A.addIndex(1);
  meshInnerLv2A.addIndex(2);
  meshInnerLv2A.addIndex(6);
  meshInnerLv2A.addIndex(1);
  meshInnerLv2A.addIndex(5);
  meshInnerLv2A.addIndex(6);
  
  meshInnerLv2A.addIndex(2);
  meshInnerLv2A.addIndex(3);
  meshInnerLv2A.addIndex(6);
  meshInnerLv2A.addIndex(3);
  meshInnerLv2A.addIndex(7);
  meshInnerLv2A.addIndex(6);
  
  meshInnerLv2A.addIndex(3);
  meshInnerLv2A.addIndex(0);
  meshInnerLv2A.addIndex(7);
  meshInnerLv2A.addIndex(3);
  meshInnerLv2A.addIndex(4);
  meshInnerLv2A.addIndex(7);
  
  meshInnerLv2A.addIndex(4);
  meshInnerLv2A.addIndex(5);
  meshInnerLv2A.addIndex(6);
  meshInnerLv2A.addIndex(4);
  meshInnerLv2A.addIndex(7);
  meshInnerLv2A.addIndex(6);
  
  // Lv.3 A 三角柱端
  meshInnerLv3A.addVertex(ofVec3f(5,    5, 5));
  meshInnerLv3A.addVertex(ofVec3f(47.4, 5, 5));
  meshInnerLv3A.addVertex(ofVec3f(5,    5, 47.4));
  meshInnerLv3A.addVertex(ofVec3f(5,    65, 5));
  meshInnerLv3A.addVertex(ofVec3f(47.4, 65, 5));
  meshInnerLv3A.addVertex(ofVec3f(5,    65, 47.4));
  
  meshInnerLv3A.usingIndices();
  
  meshInnerLv3A.addIndex(0);
  meshInnerLv3A.addIndex(1);
  meshInnerLv3A.addIndex(2);
  
  meshInnerLv3A.addIndex(0);
  meshInnerLv3A.addIndex(1);
  meshInnerLv3A.addIndex(4);
  meshInnerLv3A.addIndex(0);
  meshInnerLv3A.addIndex(3);
  meshInnerLv3A.addIndex(4);
  
  meshInnerLv3A.addIndex(1);
  meshInnerLv3A.addIndex(2);
  meshInnerLv3A.addIndex(5);
  meshInnerLv3A.addIndex(1);
  meshInnerLv3A.addIndex(4);
  meshInnerLv3A.addIndex(5);
  
  meshInnerLv3A.addIndex(2);
  meshInnerLv3A.addIndex(0);
  meshInnerLv3A.addIndex(3);
  meshInnerLv3A.addIndex(2);
  meshInnerLv3A.addIndex(5);
  meshInnerLv3A.addIndex(3);
  
  meshInnerLv3A.addIndex(3);
  meshInnerLv3A.addIndex(4);
  meshInnerLv3A.addIndex(5);
  
  // Lv.2 B 四角柱端
  // Lv.3 B (四角柱)
  meshInnerLv2and3B.addVertex(ofVec3f(5, 5, 5));
  meshInnerLv2and3B.addVertex(ofVec3f(35, 5, 5));
  meshInnerLv2and3B.addVertex(ofVec3f(35, 5, 35));
  meshInnerLv2and3B.addVertex(ofVec3f(5, 5, 35));
  meshInnerLv2and3B.addVertex(ofVec3f(5, 65, 5));
  meshInnerLv2and3B.addVertex(ofVec3f(35, 65, 5));
  meshInnerLv2and3B.addVertex(ofVec3f(35, 65, 35));
  meshInnerLv2and3B.addVertex(ofVec3f(5, 65, 35));
  
  meshInnerLv2and3B.usingIndices();
  
  meshInnerLv2and3B.addIndex(0);
  meshInnerLv2and3B.addIndex(1);
  meshInnerLv2and3B.addIndex(2);
  meshInnerLv2and3B.addIndex(0);
  meshInnerLv2and3B.addIndex(3);
  meshInnerLv2and3B.addIndex(2);
  
  meshInnerLv2and3B.addIndex(0);
  meshInnerLv2and3B.addIndex(1);
  meshInnerLv2and3B.addIndex(5);
  meshInnerLv2and3B.addIndex(0);
  meshInnerLv2and3B.addIndex(4);
  meshInnerLv2and3B.addIndex(5);
  
  meshInnerLv2and3B.addIndex(1);
  meshInnerLv2and3B.addIndex(2);
  meshInnerLv2and3B.addIndex(6);
  meshInnerLv2and3B.addIndex(1);
  meshInnerLv2and3B.addIndex(5);
  meshInnerLv2and3B.addIndex(6);
  
  meshInnerLv2and3B.addIndex(2);
  meshInnerLv2and3B.addIndex(3);
  meshInnerLv2and3B.addIndex(6);
  meshInnerLv2and3B.addIndex(3);
  meshInnerLv2and3B.addIndex(7);
  meshInnerLv2and3B.addIndex(6);
  
  meshInnerLv2and3B.addIndex(3);
  meshInnerLv2and3B.addIndex(0);
  meshInnerLv2and3B.addIndex(7);
  meshInnerLv2and3B.addIndex(3);
  meshInnerLv2and3B.addIndex(4);
  meshInnerLv2and3B.addIndex(7);
  
  meshInnerLv2and3B.addIndex(4);
  meshInnerLv2and3B.addIndex(5);
  meshInnerLv2and3B.addIndex(6);
  meshInnerLv2and3B.addIndex(4);
  meshInnerLv2and3B.addIndex(7);
  meshInnerLv2and3B.addIndex(6);
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  if (key == '1'){
    level = "1";
  }
  else if (key == '2'){
    level = "2";
  }
  else if (key == '3'){
    level = "3";
  }
  
  if (key == 'f')
  {
    ofToggleFullscreen();
  }
  
//  if (key == 'q'){
//    directionalLight.enable();
//  }
//  else if (key == 'w'){
//    directionalLight1.enable();
//  }
//  else if (key == 'e'){
//    directionalLight2.enable();
//  }
//  else if (key == 'r'){
//    directionalLight3.enable();
//  }
//  else if (key == 'z'){
//    directionalLight.disable();
//  }
//  else if (key == 'x'){
//    directionalLight1.disable();
//  }
//  else if (key == 'c'){
//    directionalLight2.disable();
//  }
//  else if (key == 'v'){
//    directionalLight3.disable();
//  }
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
