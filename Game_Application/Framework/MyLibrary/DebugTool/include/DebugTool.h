//==============================================================================
//
// ◆ DebugTool.h
// デバッグ支援用統合ヘッダ
// Logger と MsgBox を簡単に呼び出せるマクロ群を提供します。
// ファイル名・行番号・関数名情報付きでのログ出力や
// メッセージボックス表示が可能です。
//
//-------------------------------------------------------------------------------
// 
// ver：1.0.0
// 作成者 : iwasi
// 作成日 : 2025-08-19
// 最終更新日 : 2025-09-05
//
//==============================================================================
#pragma once

// --- Debugビルドでのみ有効 ---
#if _DEBUG
#else
#define DEBUG_NO_USE_LOG
#define DEBUG_NO_USE_MSGBOX
#endif

//==============================================================================
//
// ◆ ログマクロ定義 (Logger用)
//
// このセクションでは、簡単にログ出力を行えるマクロを提供します。
// DEBUG_NO_USE_LOG が定義されている場合、マクロはすべて無効化されます。
// DEBUG_NO_LOG が定義されている場合、マクロ定義がされません。
//
// 特徴：
// ・ログレベルは Info / Warning / Error の3種類を提供
// ・呼び出し元のファイル名、行番号、関数名を自動で付与可能
// ・文字列、wstring の両方に対応
//
// 使用方法：
// 1. アプリケーション開始時に LOG_INITIALIZE を呼び出してログを初期化
// 2. ログ出力マクロ LOG_I, LOG_W, LOG_E 等をコード中で呼び出す
// 3. アプリケーション終了時に LOG_SHUTDOWN() を呼び出してログを閉じる
//
// マクロ例：
// LOG_I("通常の情報ログ");
// LOG_IF("ファイル名・行番号付き情報ログ");
// LOG_IFF("ファイル名・行番号・関数名付き情報ログ");
//
//==============================================================================
#ifndef DEBUG_NO_LOG
#ifndef DEBUG_NO_USE_LOG
#include "Logger.h"

// --- ログ初期化&終了処理マクロ ---
#define LOG_INITIALIZE Logger::Initialize()
#define LOG_SHUTDOWN Logger::Shutdown()

//--------------------
// Info レベルログ
//--------------------

// --- 基本ログ(呼び出し元情報なし) ---
#define LOG_I(msg)   Logger::Log(msg, Logger::LogLevel::Info)

// --- ファイル名・行番号付き ---
#define LOG_IF(msg)  Logger::Log(msg, Logger::LogLevel::Info, __FILE__, __LINE__)

// --- ファイル名・行番号・関数名付き ---
#define LOG_IFF(msg) Logger::Log(msg, Logger::LogLevel::Info, __FILE__, __LINE__, __func__)

// --------------------
// Warning レベルログ
// --------------------

// --- 基本ログ(呼び出し元情報なし) ---
#define LOG_W(msg)   Logger::Log(msg, Logger::LogLevel::Warning)

// --- ファイル名・行番号付き ---
#define LOG_WF(msg)  Logger::Log(msg, Logger::LogLevel::Warning, __FILE__, __LINE__)

// --- ファイル名・行番号・関数名付き ---
#define LOG_WFF(msg) Logger::Log(msg, Logger::LogLevel::Warning, __FILE__, __LINE__, __func__)

//--------------------
// Error レベルログ
//--------------------

// --- 基本ログ(呼び出し元情報なし) ---
#define LOG_E(msg)   Logger::Log(msg, Logger::LogLevel::Error)

// --- ファイル名・行番号付き ---
#define LOG_EF(msg)  Logger::Log(msg, Logger::LogLevel::Error, __FILE__, __LINE__)

// --- ファイル名・行番号・関数名付き ---
#define LOG_EFF(msg) Logger::Log(msg, Logger::LogLevel::Error, __FILE__, __LINE__, __func__)

#else
// --- ログ初期化&終了処理マクロ無効化 ---
#define LOG_INITIALIZE 
#define LOG_SHUTDOWN 

// --- ログマクロ無効化 ---
#define LOG_I(msg)   ((void)0)
#define LOG_IF(msg)  ((void)0)
#define LOG_IFF(msg) ((void)0)

#define LOG_W(msg)   ((void)0)
#define LOG_WF(msg)  ((void)0)
#define LOG_WFF(msg) ((void)0)

#define LOG_E(msg)   ((void)0)
#define LOG_EF(msg)  ((void)0)
#define LOG_EFF(msg) ((void)0)

#endif // DEBUG_NO_USE_LOG
#endif // DEBUG_NO_LOG

//==============================================================================
//
// ◆ メッセージボックスマクロ定義 (MsgBox用)
//
// このセクションでは、簡単にポップアップメッセージを表示できるマクロを提供します。
// DEBUG_NO_USE_MSGBOX が定義されている場合、マクロはすべて無効化されます。
// DEBUG_NO_MSGBOX が定義されている場合、マクロ定義がされません。
//
// 特徴：
// ・メッセージボックスの種類は Error / Warning / Info / YesNo を提供
// ・呼び出し元のファイル名、行番号、関数名をオプションで表示可能
// ・ポップアップ位置は親ウィンドウ設定により中央表示されます
//
// 使用方法：
// 1. 必要に応じて MSGBOX_INITIALIZE(HWND) で親ウィンドウを設定
// 2. MSG_ERR, MSG_WARN, MSG_INFO, MSG_YESNO マクロを呼び出してメッセージを表示
// 3. MSG_ERRF などの「F付き」マクロでファイル名・行番号・関数名を同時表示可能
//
// マクロ例：
// MSG_ERR("致命的なエラーを通知");
// MSG_WARNF("警告情報（ファイル・行・関数名付き）");
// MSG_YESNOF("確認ダイアログ（情報付き）");
// MSG_INFO("情報表示のみ");
//
//==============================================================================
#ifndef DEBUG_NO_MSGBOX
#ifndef DEBUG_NO_USE_MSGBOX
#include "MsgBox.h"

// --- メッセージボックス初期化&終了処理マクロ ---
#define MSGBOX_INITIALIZE(hWnd) MsgBox::SetParentWindow(hWnd)

//--------------------
// Info メッセージボックス
//--------------------

// --- 基本メッセージボックス(呼び出し元情報なし) ---
#define MSG_INFO(msg)  MsgBox::ShowInfo(msg, L"DebugTool[Info]")

// --- ファイル名・行番号・関数名付き ---
#define MSG_INFOF(msg)  MsgBox::ShowInfo(msg, L"DebugTool[Info]", __FILE__, __LINE__, __func__)

//--------------------
// Error メッセージボックス
//--------------------

// --- 基本メッセージボックス(呼び出し元情報なし) ---
#define MSG_ERR(msg)   MsgBox::ShowError(msg, L"DebugTool[Error]")

// --- ファイル名・行番号・関数名付き ---
#define MSG_ERRF(msg)   MsgBox::ShowError(msg, L"DebugTool[Error]", __FILE__, __LINE__, __func__)

//--------------------
// Warning メッセージボックス
//--------------------

// --- 基本メッセージボックス(呼び出し元情報なし) ---
#define MSG_WARN(msg)  MsgBox::ShowWarning(msg, L"DebugTool[Warning]")

// --- ファイル名・行番号・関数名付き ---
#define MSG_WARNF(msg)  MsgBox::ShowWarning(msg, L"DebugTool[Warning]", __FILE__, __LINE__, __func__)

//--------------------
// Yes/No メッセージボックス
// --------------------

// --- 基本メッセージボックス(呼び出し元情報なし) ---
#define MSG_YESNO(msg) MsgBox::ShowYesNo(msg, L"DebugTool[Confir]")

// --- ファイル名・行番号・関数名付き ---
#define MSG_YESNOF(msg) MsgBox::ShowYesNo(msg, L"DebugTool[Confir]", __FILE__, __LINE__, __func__)

#else
// --- メッセージボックス初期化&終了処理マクロ無効化 ---
#define MSGBOX_INITIALIZE(hWnd) ((void)0)

// --- メッセージボックスマクロ無効化 ---
#define MSG_ERR(msg)   ((void)0)
#define MSG_WARN(msg)  ((void)0)
#define MSG_INFO(msg)  ((void)0)
#define MSG_YESNO(msg) (false)

#define MSG_ERRF(msg)   ((void)0)
#define MSG_WARNF(msg)  ((void)0)
#define MSG_INFOF(msg)  ((void)0)
#define MSG_YESNOF(msg) (false)

#endif // DEBUG_NO_USE_MSGBOX
#endif // DEBUG_NO_MSGBOX