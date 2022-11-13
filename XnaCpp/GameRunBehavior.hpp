#ifndef _GAMEHUNBEHAVIOR_HPP_
#define _GAMEHUNBEHAVIOR_HPP_

namespace Xna {
    enum class GameRunBehavior
    {        
        // The game loop will be run asynchronously.        
        Asynchronous,
      
        // The game loop will be run synchronously.
        Synchronous
    };
}

#endif