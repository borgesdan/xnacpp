#ifndef _CONTENTMANAGER_HPP_
#define _CONTENTMANAGER_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <type_traits>
#include <fstream>
#include <iostream>

#include "ContentReader.hpp"
#include "../Graphics/GraphicsResource.hpp"

namespace Xna {
	namespace Content {

		class ContentReader;

		class ContentManager {
		private:
			static constexpr int8_t contentCompressedLzx = 0x80;
			static constexpr int8_t contentCompressedLz4 = 0x40;

			std::string _rootDirectory;
			std::vector<std::shared_ptr<ContentManager>> contentManagers;
			std::map<std::string, std::shared_ptr<void>> loadedAssets;

			static void AddContentManager(std::shared_ptr<ContentManager>& contentManager);
			static void RemoveContentManager(std::shared_ptr<ContentManager>& contentManager);

			std::shared_ptr<ContentReader> GetContentReaderFromXnb(std::string const& originalAssetName, std::ifstream const& binaryStream);

		protected:
			template <class T>
			std::shared_ptr<T> ReadAsset(std::string const& assetName) {
				if (assetName.empty())
					return nullptr;

				auto originalAssetName = assetName;

				auto stream = std::ifstream(assetName, std::ios::binary);		
				auto reader = GetContentReaderFromXnb(assetName, stream);

				std::shared_ptr<T> result = reader->ReadAsset<T>();
				std::shared_ptr<Graphics::GraphicsResource> graphics =
					dynamic_cast<std::shared_ptr<Graphics::GraphicsResource>>(result);				

				if (graphics != nullptr) 
					graphics->Name(originalAssetName);

				stream.close();
				//TODO: reader close

				return result;
			}			

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
					std::shared_ptr<T> returnAsset = std::static_pointer_cast<T>(asset);

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