#include "ContentTypeReaderManager.hpp"
#include <type_traits>

using std::shared_ptr;
using std::make_shared;
using std::is_array;

namespace Xna {
	namespace Content {
		/*shared_ptr<ContentTypeReader> ContentTypeReaderManager::GetTypeReader(type_info& targetType) {
			auto& i = typeid(targetType);			
		}*/
	}
}