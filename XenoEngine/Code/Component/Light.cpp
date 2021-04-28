#include "pch.h"
#include "Light.h"
#include "Renderer/SceneRenderer.h"

Xeno::Light::Light(Entity* owner, const LightType type) :
    Component(owner),
    mType(type)
{
    SceneRenderer::RegisterLight(this);

    if (type == LightType::SPOT)
    {
        mAmbient = glm::vec3(0.0f, 0.0f, 0.0f);
        mDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        mSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    }
}

void Xeno::Light::SetLightType(const LightType type)
{
    mType = type;
}

Xeno::Light::LightType Xeno::Light::GetLightType() const
{
    return mType;
}

void Xeno::Light::SetIntensity(const float value)
{
    mIntensity = value;
}

float Xeno::Light::GetIntensity() const
{
    return mIntensity;
}

void Xeno::Light::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::Light::GetColor() const
{
    return mColor;
}

void Xeno::Light::SetAmbient(const glm::vec3& values)
{
    mAmbient = values;
}

void Xeno::Light::SetAmbient(const float v0, const float v1, const float v2)
{
    mAmbient = glm::vec3(v0, v1, v2);
}

const glm::vec3& Xeno::Light::GetAmbient() const
{
    return mAmbient;
}

void Xeno::Light::SetDiffuse(const glm::vec3& values)
{
    mDiffuse = values;
}

void Xeno::Light::SetDiffuse(const float v0, const float v1, const float v2)
{
    mDiffuse = glm::vec3(v0, v1, v2);
}

const glm::vec3& Xeno::Light::GetDiffuse() const
{
    return mDiffuse;
}

void Xeno::Light::SetSpecular(const glm::vec3& values)
{
    mSpecular = values;
}

void Xeno::Light::SetSpecular(const float v0, const float v1, const float v2)
{
    mSpecular = glm::vec3(v0, v1, v2);
}

const glm::vec3& Xeno::Light::GetSpecular() const
{
    return mSpecular;
}

void Xeno::Light::SetConstant(const float value)
{
    mConstant = value;
}

float Xeno::Light::GetConstant() const
{
    return mConstant;
}

void Xeno::Light::SetLinear(const float value)
{
    mLinear = value;
}

float Xeno::Light::GetLinear() const
{
    return mLinear;
}

void Xeno::Light::SetQuadratic(const float value)
{
    mQuadratic = value;
}

float Xeno::Light::GetQuadratic() const
{
    return mQuadratic;
}

void Xeno::Light::SetCutoff(const float value)
{
    mCutoff = value;
}

float Xeno::Light::GetCutoff() const
{
    return mCutoff;
}

void Xeno::Light::SetOuterCutoff(const float value)
{
    mOuterCutoff = value;
}

float Xeno::Light::GetOuterCutoff() const
{
    return mOuterCutoff;
}

void Xeno::Light::OnDestroy()
{
    SceneRenderer::UnregisterLight(this);
}
