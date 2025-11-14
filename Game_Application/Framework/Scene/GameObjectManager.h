//==============================================================================
// File        : GameObjectManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
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

        // çXêVíÜÇ…ê∂ê¨Ç≥ÇÍÇΩ GameObject Çà¿ëSÇ…í«â¡
        void FlushPending();

		friend class Scene;
    };

} // namespace Framework

#endif // GAME_OBJECT_MANAGER_H