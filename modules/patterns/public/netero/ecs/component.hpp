/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#pragma once

#include <netero/type_id.hpp>

namespace netero {
namespace ecs {

    class Component {
        public:
        virtual ~Component() = default;
    };

    using ComponentTypeID = netero::TypeID<Component>;
} // namespace ecs
} // namespace netero
