#ifndef _CURVETANGENT_HPP_
#define _CURVETANGENT_HPP_

namespace Xna {
	enum class CurveTangent {
        
        // The tangent which always has a value equal to zero.         
        Flat,        
        // The tangent which contains a difference between current tangent value and the tangent value from the previous CurveKey. 
        Linear,        
        // The smoouth tangent which contains the inflection between CurveKey.TangentIn and CurveKey.TangentOut by taking into account the values of both neighbors of the CurveKey.        
        Smooth
	};
}

#endif