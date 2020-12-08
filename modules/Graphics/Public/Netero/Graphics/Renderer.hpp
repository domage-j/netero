/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

#include <memory>

#include <Netero/Graphics/Errors.hpp>
#include <Netero/Graphics/Drawable.hpp>

namespace Netero::Gfx {

class Camera;

class Renderer {
    public:
    virtual ~Renderer() = default;

    virtual void AttachCamera(Camera*) = 0;
    virtual void DetachCamera() = 0;

    virtual GfxResult RegisterDrawable(std::shared_ptr<Drawable> anObject) = 0;
    virtual GfxResult UnRegisterDrawable(std::shared_ptr<Drawable> anObject) = 0;
};

} // namespace Netero::Gfx
