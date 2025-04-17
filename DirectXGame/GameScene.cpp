#include "GameScene.h"

using namespace KamataEngine;

// コンストラクタ
GameScene::GameScene() {
}

// デストラクタ
GameScene::~GameScene() { 
	delete modelParticle_; 
	delete particle_;
}

void GameScene::Initialize() {
	// DirectXCommonインスタンスの取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンスの取得
	input_ = Input::GetInstance();
	// Audioインスタンスの取得
	audio_ = Audio::GetInstance();

	// カメラ
	camera_.Initialize();

	// パーティクル
	modelParticle_ = Model::CreateSphere(4, 4);
	particle_ = new Particle();
	particle_->Initialize(modelParticle_);
}

void GameScene::Update() {
	// パーティクル
	particle_->Update();
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクル
	particle_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}