#version 460 core

#define MAX_LIGHTS 50

out vec4 vFragColor;

struct Material 
{
    sampler2D mTexture;
    float mShininess;
}; 

struct Light 
{
    vec3 mPosition;
    vec3 mDirection;

    vec3 mAmbient;
    vec3 mDiffuse;
    vec3 mSpecular;
    vec4 mColor;

    float mConstant;
    float mLinear;
    float mQuadratic;

    float mCutoff;
    float mOuterCutoff;

    float mIntensity;

    int mLightType;
};

in vec3 vFragPosition;
in vec3 vNormal;
in vec2 vUV;

uniform vec3 uViewPosition;
uniform Light uLights[MAX_LIGHTS];
uniform Material uMaterial;
uniform int uNumLights;
uniform vec4 uColor;

// function prototypes
vec3 computeLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor);
vec3 computeDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor);
vec3 computePointLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor);
vec3 computeSpotLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor);

void main()
{    
    vec3 normal = normalize(vNormal);
    vec3 viewDir = normalize(uViewPosition - vFragPosition);
    vec4 texColor = texture(uMaterial.mTexture, vUV);
    
    vec3 result;

    for (int i = 0; i < uNumLights; ++i)
        result += computeLight(uLights[i], normal, viewDir, texColor);

    vFragColor = uColor * vec4(result, 1.0);
}

vec3 computeLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor)
{
    vec3 result;

    if (light.mLightType == 0)
        result = computeDirectionalLight(light, normal, viewDir, texColor);
    else if (light.mLightType == 1)
        result = computePointLight(light, normal, viewDir, texColor);
    else if (light.mLightType == 2)
        result = computeSpotLight(light, normal, viewDir, texColor);

    return result;
}

// calculates the color when using a directional light.
vec3 computeDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor)
{
    vec3 lightDir = normalize(-light.mDirection);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.mShininess);

    // combine results
    vec3 ambient = light.mAmbient * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 diffuse = light.mDiffuse * diff * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 specular = light.mSpecular * spec * texColor.rgb * light.mColor.xyz * light.mIntensity;

    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 computePointLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor)
{
    vec3 lightDir = normalize(light.mPosition - vFragPosition);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.mShininess);

    // attenuation
    float distance = length(light.mPosition - vFragPosition);
    float attenuation = 1.0 / (light.mConstant + light.mLinear * distance + light.mQuadratic * (distance * distance));
    
    // combine results
    vec3 ambient = light.mAmbient * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 diffuse = light.mDiffuse * diff * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 specular = light.mSpecular * spec * texColor.rgb * light.mColor.xyz * light.mIntensity;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 computeSpotLight(Light light, vec3 normal, vec3 viewDir, vec4 texColor)
{
    vec3 lightDir = normalize(light.mPosition - vFragPosition);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.mShininess);

    // attenuation
    float distance = length(light.mPosition - vFragPosition);
    float attenuation = 1.0 / (light.mConstant + light.mLinear * distance + light.mQuadratic * (distance * distance)); 
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.mDirection)); 
    float epsilon = light.mCutoff - light.mOuterCutoff;
    float intensity = clamp((theta - light.mOuterCutoff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient = light.mAmbient * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 diffuse = light.mDiffuse * diff * texColor.rgb * light.mColor.xyz * light.mIntensity;
    vec3 specular = light.mSpecular * spec * texColor.rgb * light.mColor.xyz * light.mIntensity;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}