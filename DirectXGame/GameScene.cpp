#include "GameScene.h"
#include <random>

using namespace KamataEngine;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

// コンストラクタ
GameScene::GameScene() {
}

// デストラクタ
GameScene::~GameScene() {
	delete modelEffect_;
	delete effect_;
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

	// エフェクト
	modelEffect_ = Model::CreateFromOBJ("effect");
	effect_ = new Effect();
	Vector3 scale = { 1.0f, abs(distribution(randomEngine)), 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, distribution(randomEngine) };
	effect_->Initialize(modelEffect_, scale, rotation);
}

void GameScene::Update() {
	// エフェクトの更新
	effect_->Update();
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// エフェクトの描画
	effect_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}