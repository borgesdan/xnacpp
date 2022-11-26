#ifndef _CONTENTTYPEREADERMANAGER_HPP_
#define _CONTENTTYPEREADERMANAGER_HPP_

#include <map>
#include <memory>
#include <typeinfo>

namespace Xna {
	namespace Content {

		class ContentTypeReader;

		class ContentTypeReaderManager {
		private:
			static std::map<type_info, std::shared_ptr<ContentTypeReader>> _contentReadersCache;
			std::map<type_info, std::shared_ptr<ContentTypeReader>> _contentReaders;

		public:
			std::shared_ptr<ContentTypeReader> GetTypeReader(type_info& targetType);
		};
	}
}

#endif