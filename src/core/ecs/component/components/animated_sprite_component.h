#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include <map>

#include "../component.h"
#include "../../../animation/animation.h"
#include "../../../math/rect2.h"

struct AnimatedSpriteComponent {
    std::map<std::string, Animation> animations;
    Animation currentAnimation; // Preselects first added animation
    int currentFrameIndex;
    bool isPlaying;
    bool flipX = false;
    bool flipY = false;
};

#endif //ANIMATED_SPRITE_COMPONENT_H
