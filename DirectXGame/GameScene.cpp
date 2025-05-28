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
	modelEffect_ = Model::CreateFromOBJ("effect");
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
	if (rand() % 50 == 0) {
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
	const int numEffects = 10;        // 配置する個数
	const float radius = 6.0f;      // 円の半径

	for (int i = 0; i < numEffects; i++) {
		float angle = (2.0f * 3.1415926f / numEffects) * i; // 等間隔の角度
		Vector3 position = {
			center.x + std::cos(angle) * radius,
			center.y + std::sin(angle) * radius,
			center.z
		};

		// エフェクト生成
		Effect* effect_ = new Effect();
		Vector3 scale = { 0.1f, 2.0f, 1.0f };
		Vector3 rotation = { 0.0f, 0.0f, angle }; // 角度に応じて回転を変えても良い
		effect_->Initialize(modelEffect_, scale, rotation, position);
		effects_.push_back(effect_);

		// 円周上に被せる縦に伸びたエフェクト
		Effect* verticalEffect = new Effect();
		Vector3 verticalScale = { 2.0f + distribution(randomEngine), 0.1f, 1.0f };
		Vector3 verticalRotation = { 0.0f, 0.0f, angle };
		Vector3 verticalPosition = position;
		verticalEffect->Initialize(modelEffect_, verticalScale, verticalRotation, verticalPosition);
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