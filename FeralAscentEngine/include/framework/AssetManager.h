#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

using namespace sf;
using namespace std;

namespace fa
{
	class AssetManager
	{
	public:
		static AssetManager& Get();

		shared<Texture> LoadTexture(const string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const string& directory);

	protected:
		AssetManager();

	private:
		static unique<AssetManager> assetManager;
		Dictionary<string, shared<Texture>> m_LoadedTextureMap;

		string m_rootDirectory;
	};




}