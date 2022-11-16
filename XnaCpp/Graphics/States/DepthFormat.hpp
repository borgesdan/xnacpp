#ifndef _DEPTHFORMAT_HPP_
#define _DEPTHFORMAT_HPP_

namespace Xna {
    namespace Graphics {
        enum class DepthFormat
        {
            // Depth-stencil buffer will not be created.
            None,

            // 16-bit depth buffer.
            Depth16,

            // 24-bit depth buffer. Equivalent of <see cref="DepthFormat.Depth24Stencil8"/> for DirectX platforms.
            Depth24,

            // 32-bit depth-stencil buffer. Where 24-bit depth and 8-bit for stencil used.
            Depth24Stencil8
        };
    }
}

#endif