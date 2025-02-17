#include "SpotLight.h"
#include <glm/gtc/constants.hpp>
#include "../core/Application.h"

namespace BG3DRenderer::Lighting {
    SpotLight::SpotLight() : Light() {
        // Default angles (in degrees)
        cutOff = 12.5f;
        outerCutOff = 17.5f;
        
        // Default attenuation values
        constant = 1.0f;
        linear = 0.09f;
        quadratic = 0.032f;
        
        // Default direction (pointing down -Z axis)
        direction = glm::vec3(0.0f, 0.0f, -1.0f);

        type = LightType::Spot;
    }

    void SpotLight::SetCutOffAngles(float innerAngle, float outerAngle) {
        cutOff = glm::clamp(innerAngle, 0.0f, outerAngle);
        outerCutOff = glm::clamp(outerAngle, innerAngle, 90.0f);
    }

    void SpotLight::SetAttenuation(float constant, float linear, float quadratic) {
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
    }

    void SpotLight::SetDirection(const glm::vec3& direction) {
        this->direction = glm::normalize(direction);
    }

    void SpotLight::Update() {
        // Add any spotlight specific update logic here
        Light::Update();

        // EXAMPLE: Orbit the light around the origin
        static float angle = 0.0f;
        float radius = 2.0f; // Radius of the orbit
        float speed = glm::pi<float>() / 4.0f; // Speed of the orbit (radians per second)

        angle += speed * Application::DeltaTime; // Update the angle based on the frame time

        // Calculate the new position
        transform.position.x = radius * cos(angle);
        transform.position.z = radius * sin(angle);

        // Rotate to face 0,0,0
        transform.Rotate(glm::vec3(0, glm::degrees(angle), 0));
        direction = -transform.position;
    }

    void SpotLight::Render(std::shared_ptr<Graphics::Shader> shader, Core::Camera* camera) {
        // Call base class Render to handle common light properties
        Light::Render(shader, camera);

        // Add spotlight specific uniforms
        shader->SetVec3("spotLight.position", transform.position);
        shader->SetVec3("spotLight.direction", direction);
        shader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
        shader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));
        shader->SetFloat("spotLight.constant", constant);
        shader->SetFloat("spotLight.linear", linear);
        shader->SetFloat("spotLight.quadratic", quadratic);
        shader->SetVec3("spotLight.ambient", ambient.ToVec3());
        shader->SetVec3("spotLight.diffuse", diffuse.ToVec3());
        shader->SetVec3("spotLight.specular", specular.ToVec3());

        // Enable spotlight in the shader
        shader->SetBool("useSpotLight", true);

        std::cout << "Spot Light" << std::endl;
    }
}