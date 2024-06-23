#include "Entities.hpp"

#include "../assets/Assets.hpp"
#include "../world/Level.hpp"
#include "../physics/Hitbox.hpp"
#include "../physics/PhysicsSolver.hpp"
#include "../graphics/render/ModelBatch.hpp"
#include "../graphics/core/Model.hpp"
#include "../maths/FrustumCulling.hpp"

#include <glm/ext/matrix_transform.hpp>

void Transform::refresh() {
    combined = glm::mat4(1.0f);
    combined = glm::translate(combined, pos);
    combined = glm::scale(combined, size);
    combined = combined * glm::mat4(rot);
}

Entities::Entities(Level* level) : level(level) {
    for (int i = 0; i < 1000; i++) {
        auto entity = registry.create();
        glm::vec3 pos(0.5f+rand()%50, 100+i, 0.5f+rand()%50);
        glm::vec3 size(1);
        registry.emplace<EntityId>(entity, 1);
        registry.emplace<Transform>(entity, pos, size/4.0f, glm::mat3(1.0f));
        registry.emplace<Hitbox>(entity, pos, size/2.0f);
    }
}

void Entities::updatePhysics(float delta){
    auto view = registry.view<Transform, Hitbox>();
    auto physics = level->physics.get();
    for (auto [entity, transform, hitbox] : view.each()) {
        physics->step(
            level->chunks.get(),
            &hitbox,
            delta,
            10,
            false,
            1.0f,
            true
        );
        transform.pos = hitbox.position;
        transform.rot = glm::rotate(glm::mat4(transform.rot), delta, glm::vec3(0, 1, 0));
        if (hitbox.grounded) {
            //hitbox.velocity.y = 10;
        }
    }
}

void Entities::render(Assets* assets, ModelBatch& batch, Frustum& frustum) {
    auto view = registry.view<Transform>();
    auto model = assets->get<model::Model>("cube");
    for (auto [entity, transform] : view.each()) {
        const auto& pos = transform.pos;
        const auto& size = transform.size;
        if (frustum.isBoxVisible(pos-size, pos+size)) {
            transform.refresh();
            batch.pushMatrix(transform.combined);
            batch.draw(model);
            batch.popMatrix();
        }
    }
}
