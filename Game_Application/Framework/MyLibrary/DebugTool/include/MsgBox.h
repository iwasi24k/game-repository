//==============================================================================
//
// ◆ MsgBox.h
// メッセージボックス表示ユーティリティクラス
//
// Windows API の MessageBox をラップし、エラー / 警告 / 情報 / 確認
// の4種類のメッセージボックスを簡潔に呼び出せます。
// 
// DebugTool.h のマクロ群と組み合わせることで、呼び出し元の
// ファイル名・行番号・関数名付きの詳細情報も表示可能です。
// 
// 親ウィンドウの登録機能を備えており、モーダルダイアログとして
// 呼び出し元ウィンドウに正しく関連付けられるようになっています。
//
//-------------------------------------------------------------------------------
// 
// ver : 1.0.0
// 作成者 : iwasi
// 作成日 : 2025-08-19
// 最終更新日 : 2025-08-19
//
//==============================================================================
#ifndef MSG_BOX_H
#define MSG_BOX_H

#include <Windows.h>
#include <string>
#include "Logger.h"

class MsgBox
{
public:
    //-------------------------------------------------------------------------
    // ◆ 親ウィンドウ登録
    //-------------------------------------------------------------------------
    // SetParentWindow : 表示されるメッセージボックスに対して、
    //                   親となるウィンドウを指定します。
    static void SetParentWindow(HWND hwnd);

    //-------------------------------------------------------------------------
    // ◆ エラー表示
    //-------------------------------------------------------------------------
    // ShowError : エラー内容をメッセージボックスに表示します。
    //             OKボタンのみを持ち、選択後はアプリケーションを終了します。
    // message   : 表示するメッセージ文字列
    // title     : ダイアログタイトル（既定値 "エラー"）
    // file,line,func : 呼び出し元のファイル名・行番号・関数名（DebugToolマクロから渡される）
    static void ShowError(const std::wstring& message, const std::wstring& title = L"エラー");
    static void ShowError(const std::wstring& message, const std::wstring& title, const char* file, int line, const char* func);

    //-------------------------------------------------------------------------
    // ◆ 警告表示
    //-------------------------------------------------------------------------
    // ShowWarning : 警告内容をメッセージボックスに表示します。
    //               OKボタンのみを持ち、処理は継続されます。
    static void ShowWarning(const std::wstring& message, const std::wstring& title = L"警告");
    static void ShowWarning(const std::wstring& message, const std::wstring& title, const char* file, int line, const char* func);

    //-------------------------------------------------------------------------
    // ◆ 情報表示
    //-------------------------------------------------------------------------
    // ShowInfo : 情報メッセージをメッセージボックスに表示します。
    //            OKボタンのみを持ち、処理は継続されます。
    static void ShowInfo(const std::wstring& message, const std::wstring& title = L"情報");
    static void ShowInfo(const std::wstring& message, const std::wstring& title, const char* file, int line, const char* func);

    //-------------------------------------------------------------------------
    // ◆ 確認ダイアログ表示
    //-------------------------------------------------------------------------
    // ShowYesNo : Yes/No の選択肢を持つ確認ダイアログを表示します。
    //             ユーザーの選択に応じて true (Yes) / false (No) を返します。
    static bool ShowYesNo(const std::wstring& message, const std::wstring& title = L"確認");
    static bool ShowYesNo(const std::wstring& message, const std::wstring& title, const char* file, int line, const char* func);

private:
    //-------------------------------------------------------------------------
    // ◆ 内部処理
    //-------------------------------------------------------------------------
    // ShowBox : 実際に Windows API の MessageBox を呼び出す内部関数。
    //           ログへの記録やフック処理もここで行います。
    static int ShowBox(const std::wstring& message, const std::wstring& title, UINT type,
        Logger::LogLevel level = Logger::LogLevel::Info,
        const char* file = nullptr, int line = 0, const char* func = nullptr);

    // CBTProc : ダイアログ表示のためのフックプロシージャ。
    //           メッセージボックスの位置調整などを行います。
    static LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
    //-------------------------------------------------------------------------
    // ◆ インスタンス化禁止
    //-------------------------------------------------------------------------
    MsgBox() = delete;                // インスタンス生成不可
    ~MsgBox() = delete;               // デストラクタ禁止
    MsgBox(const MsgBox&) = delete;   // コピー禁止
    MsgBox(MsgBox&&) = delete;        // ムーブ禁止
    MsgBox& operator=(const MsgBox&) = delete; // 代入禁止
    MsgBox& operator=(MsgBox&&) = delete;      // ムーブ代入禁止
};


#endif // MSG_BOX_H
