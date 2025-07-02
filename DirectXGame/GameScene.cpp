#include "GameScene.h"

using namespace KamataEngine;

// コンストラクタ
GameScene::GameScene() {
}

// デストラクタ
GameScene::~GameScene() {
	// モデル2
	Model2::StaticFinalize();
	delete model_;
}

void GameScene::Initialize() {
	// DirectXCommonインスタンスの取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンスの取得
	input_ = Input::GetInstance();
	// Audioインスタンスの取得
	audio_ = Audio::GetInstance();

	// ワールドトランスフォーム
	worldTransform_.Initialize();

	// カメラ
	camera_.Initialize();

	// テクスチャ
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// モデル2
	Model2::StaticInitialize();
	model_ = Model2::CreateRing(6);
}

void GameScene::Update() {

}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	// モデル2
	model_->Draw(worldTransform_, camera_, textureHandle_);

	// 3Dモデル描画後処理
	Model2::PostDraw();
}