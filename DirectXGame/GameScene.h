#pragma once
#include "Player.h"
#include "Stage.h"
#include "Graph2D.h"
#include "Score.h"

#include <KamataEngine.h>

class GameScene
{
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤー
	Player* player_ = nullptr;

	// ステージ
	Stage* stage_ = nullptr;

	// グラフ
	Graph2D* graph_ = nullptr;

	// スコア
	Score* score_ = nullptr;
};