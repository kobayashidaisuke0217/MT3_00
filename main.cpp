#include <Novice.h>
#include <assert.h>
#include <math.h>

struct Matrix4x4
{
	double m[4][4];
};

struct Vector3
{
	float x;
	float y;
	float z;
};

const char kWindowTitle[] = "LE2B_12_コバヤシ_ダイスケ";
Matrix4x4 MakeRotateXMatrix(float theta) {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = cosf(theta);
	result.m[1][2] = sinf(theta);
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = -sinf(theta);
	result.m[2][2] = cosf(theta);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}
Matrix4x4 MakeRotateYMatrix(float theta) {
	Matrix4x4 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = 0;
	result.m[0][2] = -sinf(theta);
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = sinf(theta);
	result.m[2][1] = 0;
	result.m[2][2] = cosf(theta);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}
Matrix4x4 MakeRotateZMatrix(float theta) {
	Matrix4x4 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);


Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	Matrix4x4 RotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 RotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 RotateZ = MakeRotateZMatrix(rotate.z);
	Matrix4x4 RotateXYZ = Multiply(RotateX, Multiply(RotateY, RotateZ));
	result.m[0][0] = scale.x * RotateXYZ.m[0][0];
	result.m[0][1] = scale.x * RotateXYZ.m[0][1];
	result.m[0][2] = scale.x * RotateXYZ.m[0][2];
	result.m[0][3] = 0;
	result.m[1][0] = scale.y * RotateXYZ.m[1][0];
	result.m[1][1] = scale.y * RotateXYZ.m[1][1];
	result.m[1][2] = scale.y * RotateXYZ.m[1][2];
	result.m[1][3] = 0;
	result.m[2][0] = scale.z * RotateXYZ.m[2][0];
	result.m[2][1] = scale.z * RotateXYZ.m[2][1];
	result.m[2][2] = scale.z * RotateXYZ.m[2][2];
	result.m[2][3] = 0;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;
	return result;

}
static const int kRowHeight = 20;
static const int kColummWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "% .02f", vector.x);
	Novice::ScreenPrintf(x + kColummWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColummWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColummWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int columm = 0; columm < 4; ++columm)
		{
			Novice::ScreenPrintf(
				x + columm * kColummWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][columm], label);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	Vector3 scale{1.2f,0.79f,-2.1f};
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Vector3 translate{ 2.7f,-4.15f,1.57f };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
	MatrixScreenPrintf(0,0,worldMatrix,"worldMatrix");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	double term = 0.0f;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			term = 0;
			for (int k = 0; k < 4; k++) {
				term = term + m1.m[i][k] * m2.m[k][j];
				result.m[i][j] = term;
			}
		}
	}
	return result;
}