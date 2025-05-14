#include "GameScene.h"
#include <random>

using namespace KamataEngine;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> Distribution(-1.0f, 1.0f);

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	delete modelParticle_;
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
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
	for (int i = 0; i < 150; i++) {
		// 生成
		Particle* particle = new Particle();
		// 位置
		Vector3 position = { 0.0f, 0.0f, 0.0f };
		// 速度
		Vector3 velocity = { Distribution(randomEngine), Distribution(randomEngine), 0 };
		// 初期化
		particle->Initialize(modelParticle_, position, velocity);
		// リストに追加
		particles_.push_back(particle);
	}
}

void GameScene::Update() {
	// パーティクル
	for (Particle* particle : particles_) {
		particle->Update();
	}
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}