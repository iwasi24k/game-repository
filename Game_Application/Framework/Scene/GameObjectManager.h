//==============================================================================
// File        : GameObjectManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// GameObjectManager はシーン内に存在する全ての GameObject を統括する中心的な管理クラスです。
// CreateObject() により新しいオブジェクトを安全に生成し、タグ検索用マップに登録します。
// 実体は PendingAdd に蓄え、FlushPending() によってフレーム境界で確実に m_Objects へ反映。
// Awake / Start / Update / FixedUpdate / LateUpdate / OnEnable / OnDisable / OnDestroy など、
// ライフサイクルコールはすべて全オブジェクトへ順番に一括伝播します。
// FindObject / FindObjects によるタグ検索、ExistsTag での存在確認も可能です。
// FinalizeInternal では全データを綺麗に解放し、次のシーンへの安全な引き継ぎを保証します。
//==============================================================================
#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

namespace Framework {

	class GameObject;
    //class PhysicsManager;
	//class RenderManager;

    class GameObjectManager {
    private:
        std::vector<std::unique_ptr<GameObject>> m_Objects;
        std::vector<std::unique_ptr<GameObject>> m_PendingAdd;
        std::unordered_map<std::string, GameObject*> m_TagMap;

		//std::unique_ptr<PhysicsManager> m_PhysicsManager;
		//std::unique_ptr<RenderManager> m_RenderManager;

    public:
        GameObjectManager();
        ~GameObjectManager();

        GameObject* CreateObject(const std::string& tag);
        GameObject* FindObject(const std::string& tag);
        std::vector<GameObject*> FindObjects(const std::string& tag);

		bool ExistsTag(const std::string& tag) const;

    private:
        void Awake();
        void OnEnable();
        void Start();
        void FixedUpdate();
        void Update();
        void LateUpdate();
        void DrawGizmos();
        void Draw();
        void OnDisable();
        void OnDestroy();
        void FinalizeInternal();

        // 更新中に生成された GameObject を安全に追加
        void FlushPending();

		friend class Scene;
    };

} // namespace Framework

#endif // GAME_OBJECT_MANAGER_H