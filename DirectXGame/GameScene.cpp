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
	for (Effect* effect : effects_) {
		delete effect;
	}
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

	// 乱数の初期化
	srand((unsigned)time(NULL));

	// エフェクト
	modelEffect_ = Model::CreateFromOBJ("effect");
	for (int i = 0; i < 5; i++) {
		Effect* effect_ = new Effect();
		Vector3 scale = { 0.5f, 5.0f + abs(distribution(randomEngine)), 1.0f };
		Vector3 rotation = { 0.0f, 0.0f, distribution(randomEngine) };
		effect_->Initialize(modelEffect_, scale, rotation);
		effects_.push_back(effect_);
	}
}

void GameScene::Update() {
	// エフェクトの更新
	for (Effect* effect : effects_) {
		effect->Update();
	}
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// エフェクトの描画
	for (Effect* effect : effects_) {
		effect->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}