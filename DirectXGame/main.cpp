#include "KamataEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	Initialize(L"LE3C_04_オオクボ_タク");

	// DirectXCommonのインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーンのインスタンス生成
	TitleScene* titleScene = new TitleScene();
	// ゲームシーンの初期化
	titleScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (Update()) {
			break;
		}

		// ゲームシーンの更新
		titleScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		titleScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete titleScene;
	// nullptrの代入
	titleScene = nullptr;

	// エンジンの終了処理
	Finalize();

	return 0;
}