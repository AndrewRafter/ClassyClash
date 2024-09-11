#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

}

void BaseCharacter::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime) {
    worldPosLastFrame = worldPos;

    // update the animation
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrames) 
            frame = 0;
    }

    if (Vector2Length(velocity) != 0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // draw the knight
    Rectangle source = {width * frame, 0.0f, rightLeft * width, height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}