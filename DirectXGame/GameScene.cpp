#include "GameScene.h"

using namespace KamataEngine;

// コンストラクタ
GameScene::GameScene() {
}

// デストラクタ
GameScene::~GameScene() { 
	delete modelParticle_; 
}

void GameScene::Initialize() {
	// パーティクル
	modelParticle_ = Model::CreateSphere(4, 4);

	// カメラ
	camera_ = new Camera();
}

void GameScene::Update() {

}

void GameScene::Draw() {

}