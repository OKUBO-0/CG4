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

	// 乱数の初期化
	srand((unsigned)time(NULL));

	// カメラ
	camera_.Initialize();

	// エフェクト
	modelEffect_ = Model::CreateFromOBJ("effect");
}

void GameScene::Update() {
	// 終了フラグの立ったエフェクトを削除
	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect;
			return true;
		}
		return false;
		});

	// 確率で発生
	if (rand() % 20 == 0) {
		// 発生位置は乱数
		Vector3 position = { distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0 };
		// パーティクルの生成
		EffectBorn(position);
	}

	// エフェクトの更新
	for (Effect* effect : effects_) {
		effect->Update();
	}
}

// エフェクト発生
void GameScene::EffectBorn(Vector3 position) {
	for (int i = 0; i < 5; i++) {
		// 生成
		Effect* effect_ = new Effect();
		// 大きさ
		Vector3 scale = { 0.5f, 5.0f + abs(distribution(randomEngine)), 1.0f };
		// 回転
		Vector3 rotation = { 0.0f, 0.0f, distribution(randomEngine) };
		// 初期化
		effect_->Initialize(modelEffect_, scale, rotation, position);
		// リストに追加
		effects_.push_back(effect_);
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