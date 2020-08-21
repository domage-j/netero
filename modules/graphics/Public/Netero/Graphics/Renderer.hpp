/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

namespace Netero::Gfx {

class Renderer {
    public:
    virtual ~Renderer() = default;

    virtual void RegisterDrawable() = 0;
    virtual void UnRegisterDrawable() = 0;
};

} // namespace Netero::Gfx