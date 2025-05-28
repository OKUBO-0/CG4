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

	delete modelEffect2_;
	for (Effect* effect : effects2_) {
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
	modelEffect_ = Model::CreateFromOBJ("circleEffect");
	modelEffect2_ = Model::CreateFromOBJ("effect");
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

	// ランダム位置に円を生成
	if (rand() % 20 == 0) {
		Vector3 center = { distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0 };
		EffectBorn(center); // 中心座標を渡す
	}

	// エフェクトの更新
	for (Effect* effect : effects_) {
		effect->Update();
	}
}

// エフェクト発生
void GameScene::EffectBorn(Vector3 center) {
	const int numCircleEffects = 50;     // 円周上に配置する個数
	const int numVerticalEffects = 7;   // 縦に伸びるエフェクトの個数
	const float radius = 5.0f;         // 配置半径

	// 円周上のエフェクト
	for (int i = 0; i < numCircleEffects; i++) {
		float angle = (2.0f * 3.1415926f / numCircleEffects) * i;
		Vector3 position = {
			center.x + std::cos(angle) * radius,
			center.y + std::sin(angle) * radius,
			center.z
		};

		Effect* effect_ = new Effect();
		Vector3 scale = { 0.1f, 0.2f + std::abs(distribution(randomEngine)), 1.0f };
		Vector3 rotation = { 0.0f, 0.0f, angle };
		effect_->Initialize(modelEffect_, scale, rotation, position);
		effects_.push_back(effect_);
	}

	// 縦に伸びるエフェクト（個数と位置を別に制御）
	for (int i = 0; i < numVerticalEffects; i++) {
		float angle = (2.0f * 3.1415926f / numVerticalEffects) * i;
		Vector3 position = {
			center.x + std::cos(angle) * radius,
			center.y + std::sin(angle) * radius,
			center.z
		};

		Effect* verticalEffect = new Effect();
		Vector3 scale = { 2.0f + distribution(randomEngine), 0.1f, 1.0f }; // より縦に長い
		Vector3 rotation = { 0.0f, 0.0f, angle };
		verticalEffect->Initialize(modelEffect2_, scale, rotation, position);
		effects_.push_back(verticalEffect);
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