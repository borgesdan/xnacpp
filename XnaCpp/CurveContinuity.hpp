#ifndef _CURVECONTINUITY_HPP_
#define CURVECONTINUITY_HPP_

namespace Xna {
    enum class CurveContinuity
    {

        // Interpolation can be used between this key and the next.        
        Smooth,

        // Interpolation cannot be used. A position between the two points returns this point.        
        Step
    };
}

#endif