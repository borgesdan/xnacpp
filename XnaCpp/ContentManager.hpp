#ifndef _CONTENTMANAGER_HPP_
#define _CONTENTMANAGER_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <type_traits>

namespace Xna {
	namespace Content {
		class ContentManager {
		private:
			static constexpr int8_t contentCompressedLzx = 0x80;
			static constexpr int8_t contentCompressedLz4 = 0x40;

			std::string _rootDirectory;
			std::vector<std::shared_ptr<ContentManager>> contentManagers;
			std::map<std::string, std::shared_ptr<void>> loadedAssets;

			static void AddContentManager(std::shared_ptr<ContentManager>& contentManager);
			static void RemoveContentManager(std::shared_ptr<ContentManager>& contentManager);

		protected:
			template <class T>
			std::shared_ptr<T> ReadAsset(std::string const& assetName);

		public:
			ContentManager();
			ContentManager(std::string const& rootDirectory);
			~ContentManager();

			static void ReloadGraphicsContent();

			std::string RootDirectory() const;
			void RootDirectory(std::string const& value);

			template <class T>
			std::shared_ptr<T> Load(std::string const& assetName) {
				//TODO: Verificar exceções				
				//TODO: verificar string replace

				if (loadedAssets.find(assetName) != loadedAssets.end()) {
					//TODO: verificar se asset é T
					auto asset = loadedAssets[assetName];
					auto returnAsset = std::static_pointer_cast<T>(asset);

					return returnAsset;
				}

				std::shared_ptr<T> result = ReadAsset(assetName);

				loadedAssets.insert({ assetName, result });

				return result;
			}
		};
	}
}

#endif