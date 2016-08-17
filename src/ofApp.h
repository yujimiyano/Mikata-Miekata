#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp{
  
public:
	void setup();
	void update();
	void draw();
  
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
  
  void setupMesh();
  

  // 通信関係
  void setupArduino(const int & version);
  void updateArduino();
  
//  ofImage bgImage;
//  ofTrueTypeFont font;
  ofArduino ard;      // Arduinoへの接続
  bool bSetupArduino;  // Arduinoに接続したかのフラグ
  string cubeType;
  string level;
  bool didAnswered;
  string question;
  float nRandom;
  bool isCorrect;
  bool didSoundPlayed;
  
  
  // 描画関係
  ofMesh meshInnerLv2A;  // Lv.2 A 四角柱中央
  ofMesh meshInnerLv3A;  // Lv.3 A 三角柱端
  ofMesh meshInnerLv2and3B;  // Lv.2&3 B 四角柱端
  ofBoxPrimitive cubeOuter; // 70x70x70 立方体
//  ofBoxPrimitive cubeInner1; // 65x65x65 立方体 Lv.1 B
  ofBoxPrimitive cubeInnerLv1B; // 65x65x65 立方体 Lv.1 B

  ofLight directionalLight;
  ofLight directionalLight1;
  ofLight directionalLight2;
  ofLight directionalLight3;
  
  float angleY; //角度を記録するための変数
  
  // カメラ ofCamera
  ofCamera cam;
  
  // 音
  ofSoundPlayer sound;  // ofSoundクラスをインスタンス化
  
  // 画像
  ofImage questionImg, answerImg, imgLv1_A, imgLv1_B, imgLv2_A, imgLv2_B, imgLv3_A, imgLv3_B;
  
  
private:
  ofxTrueTypeFontUC fontUC;
  
};
