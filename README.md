# Voxel Void

3D Survival Action Game built with a fully custom C++ / DirectX11 engine.  
C++ / DirectX11 によるフルスクラッチエンジンで開発した3Dサバイバルアクションゲーム。

[![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![DirectX 11](https://img.shields.io/badge/DirectX-11-0078D6?logo=windows&logoColor=white)](https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-dev)
[![HLSL](https://img.shields.io/badge/HLSL-Shader-FF6F00)](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl)
[![Assimp](https://img.shields.io/badge/Assimp-Asset%20Import-8A2BE2)](https://www.assimp.org)
[![Visual Studio 2022](https://img.shields.io/badge/Visual%20Studio-2022-5C2D91?logo=visualstudio&logoColor=white)](https://visualstudio.microsoft.com)
[![GitHub Actions](https://img.shields.io/badge/GitHub%20Actions-CI-2088FF?logo=githubactions&logoColor=white)](https://github.com/features/actions)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

---

<img width="1255" height="695" alt="voxel-void1" src="https://github.com/user-attachments/assets/61b328e9-8562-4393-967d-8899f71bb5d3" />

## Overview / 概要

**English**

Voxel Void is a 3D survival action game developed using a custom C++ engine built directly on DirectX11.  
The game takes place in a vertically dynamic voxel-based field where platforms continuously move up and down in real time.

The project focuses on low-level rendering control, deterministic update flow, and a component-oriented engine architecture implemented without relying on commercial or academic game frameworks.

**日本語**

Voxel Void は、DirectX11 を基盤として自作した C++ エンジン上で開発された3Dサバイバルアクションゲームです。  
上下に動的変化するボクセルフィールドを舞台とし、足場がリアルタイムに昇降する構造を持ちます。

本プロジェクトは、商用エンジンや授業用フレームワークに依存せず、低レイヤー描画制御・決定論的更新処理・コンポーネント指向設計の実装を目的としています。

---

## Game Concept / ゲームコンセプト

**English**

**“Order at the smallest unit within the Void.”**

The world is constructed entirely from a single voxel unit.  
A monochrome black-and-white base is disrupted by purple and yellow elements, creating controlled visual tension.

By restricting all objects to voxel primitives, the project explores structural minimalism at its extreme.

**日本語**

**「虚無（Void）の中に存在する、最小単位の秩序」**

世界は単一のボクセルモデルのみで構築されています。  
白黒のモノトーン世界に対して、異分子としての「紫」と「黄」を混入させることで、違和感と美しさを両立。

形状の最小単位のみで構成された世界により、構造的ミニマリズムを追求しています。

---

## Architecture / アーキテクチャ

**English**

The engine is built on a custom component-oriented framework centered around a `Component` base class.

- `Component` serves as the foundational abstraction    
- `Behaviour`, `Collider`, and other functional units derive from `Component`    
- Gameplay logic is implemented through classes inheriting from `Behaviour`    
- `GameObject` instances are created via `Prefab` classes    
- Components and scripts are attached using `AddComponent()`    

Object composition is defined programmatically.  
The framework does not include GUI-based editor tooling; all configuration and structure are managed in code.

Engine systems and gameplay logic are separated to maintain clear responsibility boundaries.

---

**日本語**

本エンジンは、`Component` 基底クラスを中心とした自作のコンポーネント指向フレームワークで構成されています。

- `Component` を基盤抽象クラスとする設計    
- `Behaviour` や `Collider` などが `Component` を継承    
- ゲームロジックは `Behaviour` 継承クラスとして実装    
- `Prefab` クラス経由で `GameObject` を生成    
- `AddComponent()` によりコンポーネントやスクリプトを付与    

オブジェクト構成はすべてコード上で定義されています。  
GUIベースのエディタ機能は持たず、構造管理はプログラム上で完結します。

エンジン層とゲームロジック層は分離されており、責務境界を明確にしています。

---

## Rendering System / 描画システム

**English**

Rendering is implemented directly on DirectX11.

- Device and swap chain initialization    
- Constant buffer management    
- Custom HLSL shaders    
- Matrix transformation pipeline    
- Explicit separation of Update and Draw stages    

The visual design is based on a monochrome environment with limited accent colors.

**日本語**

描画処理は DirectX11 上で直接実装しています。

- デバイスおよびスワップチェーン初期化    
- 定数バッファ管理    
- HLSL シェーダー実装    
- 行列変換パイプライン    
- Update / Draw の明確な分離    

ビジュアルはモノトーンを基調とし、限定色によるアクセント構成を採用しています。

---

## Gameplay Structure / ゲーム構造

**English**

The game world is composed entirely of voxel units.  
Platforms move vertically in real time, dynamically altering navigable space.

Core systems include:

- Real-time movement and collision handling     
- Dynamic field transformation    

**日本語**

ゲーム世界は単一のボクセル単位で構築されています。  
足場はリアルタイムで昇降し、移動可能領域が動的に変化します。

主なシステム：

- リアルタイム移動および衝突処理    
- 動的フィールド制御    

---

## Design Principles / 設計方針

**English**

- Deterministic execution order    
- Explicit lifecycle management    
- Minimal external dependencies    
- Clear responsibility boundaries    
- Code-centric configuration    

The project prioritizes structural clarity and maintainability over feature volume.

**日本語**

- 実行順序の決定性    
- 明示的ライフサイクル管理    
- 外部依存の最小化    
- 責務境界の明確化    
- コード中心の構成管理    

機能量よりも構造の明確性と保守性を優先しています。

---

## Tech Stack / 使用技術

### Core

- DirectX11
- C++20
- Assimp
- Visual Studio 2022

### Tooling & Quality

- Git / GitHub
- GitHub Actions
- OpenAI API（AIによるPRレビュー）

---

## Development Workflow / 開発フロー

**English**

To simulate real-world team development:

- Two separate development environments
- Two GitHub accounts
- Pull request–based workflow

**日本語**

実務に近い開発を再現するため：

- 2台のPC
- 2つのGitHubアカウント
- プルリクエストベースの開発

ブランチ運用・レビュー前提の変更管理を実践しました。

---

## CI & AI Code Review / CIとAIレビュー

**English**

This project integrates an automated AI-based code review pipeline using GitHub Actions.

- Triggered on internal Pull Requests    
- Extracts diff only    
- Sends diff to OpenAI API    
- Posts structured review comments    

The system is designed to minimize token usage and keep merge decisions fully manual.


**日本語**

GitHub Actionsを用いたAIコードレビュー基盤を構築しています。

- 内部プルリクエスト時に起動    
- 差分のみ抽出    
- OpenAI APIへ送信    
- 自動レビューコメントを投稿    

トークン使用量を抑制し、マージ判断は必ず人間が行う設計としています。

---

## Build Instructions / ビルド方法

**English**

1. Open the solution file in Visual Studio 2022    
2. Select `Debug` or `Release` configuration    
3. Build the solution    
4. Run the generated executable    

**日本語**

1. Visual Studio 2022でソリューションを開く    
2. `Debug` または `Release` を選択    
3. ビルド    
4. 生成された実行ファイルを起動    

---

## License

MIT
