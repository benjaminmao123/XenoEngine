#include "pch.h"
#include "SpriteRenderer.h"
#include "Component/Sprite.h"
#include "Renderer/SceneRenderer.h"
#include "Entity/Entity.h"

Xeno::SpriteRenderer::SpriteRenderer(Entity* owner) :
    Renderer(owner)
{
    GetEntity()->AddComponent<Sprite>();
}

void Xeno::SpriteRenderer::OnStart()
{
    mSprite = GetEntity()->GetComponent<Sprite>();
}

void Xeno::SpriteRenderer::OnRender() const
{
    SceneRenderer::Submit(
    { 
        SceneRenderer::RenderCommand::CommandType::SPRITE, 
        &GetTransform(), 
        &mSprite->GetQuad(), 
        &GetMaterial() 
    });
}