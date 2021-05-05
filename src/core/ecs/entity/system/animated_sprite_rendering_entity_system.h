#ifndef ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H
#define ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/animated_sprite_component.h"

class AnimatedSpriteRenderingEntitySystem : public EntitySystem {
  private:
    Renderer *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
  public:
    AnimatedSpriteRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        enabled = true;
    }

    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}
    void UnregisterEntity(Entity entity) override {}

    void Render() {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
                AnimatedSpriteComponent animatedSpriteComponent = componentManager->GetComponent<AnimatedSpriteComponent>(entity);
                Animation currentAnimation = animatedSpriteComponent.currentAnimation;
                AnimationFrame currentFrame = currentAnimation.animationFrames[animatedSpriteComponent.currentFrameIndex];
                if (animatedSpriteComponent.isPlaying) {
                    unsigned int newIndex = static_cast<unsigned int>((SDL_GetTicks() / currentAnimation.speed) % currentAnimation.frames);
                    if (newIndex != animatedSpriteComponent.currentFrameIndex) {
                        // Index changed
                        currentFrame = currentAnimation.animationFrames[newIndex];
                        if (newIndex + 1 == currentAnimation.frames) {
                            // Animation Finished
                        }
                        animatedSpriteComponent.currentFrameIndex = newIndex;
                        componentManager->UpdateComponent(entity, animatedSpriteComponent);
                    }
                }
                Camera camera = cameraManager->GetCurrentCamera();
                Vector2 drawDestinationPosition = transform2DComponent.position - (!transform2DComponent.ignoreCamera ? (camera.viewport + camera.offset) * camera.zoom : Vector2(0, 0));
                Vector2 drawScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * camera.zoom : transform2DComponent.scale;
                Vector2 drawDestinationSize = Vector2(currentFrame.drawSource.w * drawScale.x, currentFrame.drawSource.h * drawScale.y);
                Rect2 drawDestination = Rect2(drawDestinationPosition, drawDestinationSize);
                assert(currentFrame.texture != nullptr && "Current frame texture is null");
                renderer->DrawSprite(currentFrame.texture, &currentFrame.drawSource, &drawDestination, transform2DComponent.zIndex, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
            }
        }
    }
};

#endif //ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H
