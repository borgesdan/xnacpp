#ifndef _ICURVEEVALUATOR_HPP_
#define _ICURVEEVALUATOR_HPP_

//TODO: verificar se ICurveEvaluator � necess�rio

namespace Xna {
	
	template<typename T>
	class ICurveEvaluator {
		virtual T Evaluate(float position) = 0;
	};
}

#endif