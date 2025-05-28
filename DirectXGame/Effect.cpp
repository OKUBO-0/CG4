#include "Effect.h"

#include <algorithm>
#include <cassert>

using namespace KamataEngine;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotation, Vector3 position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// 色の設定
	objectColor_.Initialize();
	color_ = { 1.0f, 0.0f, 0.0f, 1.0f };

	// 大きさ
	worldTransform_.scale_ = scale;
	// 回転
	worldTransform_.rotation_ = rotation;
	// 位置
	worldTransform_.translation_ = position;

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		// 終了扱いにする
		isFinished_ = true;
	}

	// フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// ワールド変換行列の更新
	worldTransform_.UpdateMatrix();

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Effect::Draw(Camera& camera) {
	// モデルを描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}