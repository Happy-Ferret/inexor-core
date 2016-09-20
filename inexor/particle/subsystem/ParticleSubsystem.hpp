/*
 * ParticleSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_

#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/particle/factory/ParticleTypeFactory.hpp"
#include "inexor/particle/factory/ParticleEmitterTypeFactory.hpp"
#include "inexor/particle/factory/ParticleInitializerTypeFactory.hpp"
#include "inexor/particle/factory/ParticleModifierTypeFactory.hpp"
#include "inexor/particle/factory/ParticleRendererTypeFactory.hpp"
#include "inexor/particle/model/ParticleModel.hpp"
#include "inexor/particle/worker/EmitterWorker.hpp"
#include "inexor/particle/worker/ModifierWorker.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace entity {
namespace particle {

    class ParticleSubsystem : public SubsystemBase
    {
        public:

            ParticleSubsystem();
            ParticleSubsystem(
                std::shared_ptr<EntityTypeManager> entity_type_manager,
                std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
            );
            virtual ~ParticleSubsystem();

            /**
             * Updates the particle system by the given time step.
             */
            void Update(TimeStep time_step);

            /**
             * Initializes the graph model for the particle system.
             */
            void InitializeModel();

            /**
             * Shutdown.
             */
            void Cleanup();

            /**
             * TODO
             */
            void Reset();

            /**
             * Renders the faces.
             */
            void RenderFaces();

            /**
             * Renders the particles. This method is called in the main thread.
             */
            void RenderParticles();

            TypeRefPtr<EntityType> CreateParticleType(std::string particle_type_name, std::string renderer_instance_name);
            TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int batch_size, int lifetime, double mass, double density);
            TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density);
            TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int lifetime);
            TypeRefPtr<EntityType> CreateInitializerType(std::string initializer_type_name, FunctionRefPtr function);
            TypeRefPtr<EntityType> CreateModifierType(std::string modifier_type_name, FunctionRefPtr function);
            TypeRefPtr<EntityType> CreateRendererType(std::string renderer_type_name, FunctionRefPtr function);

            TypeRefPtr<EntityType> GetParticleType(std::string particle_type_name);
            TypeRefPtr<EntityType> GetEmitterType(std::string emitter_type_name);
            TypeRefPtr<EntityType> GetInitializerType(std::string initializer_type_name);
            TypeRefPtr<EntityType> GetModifierType(std::string modifier_type_name);
            TypeRefPtr<EntityType> GetRendererType(std::string renderer_type_name);

            TypeRefPtr<RelationshipType> GetRelationshipType(std::string relationship_type_name);

            InstanceRefPtr<EntityInstance> CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z, double vx, double vy, double vz);
            InstanceRefPtr<EntityInstance> CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z, double vx, double vy, double vz);
            InstanceRefPtr<EntityInstance> CreateInitializerInstance(std::string initializer_type_name);
            InstanceRefPtr<EntityInstance> CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type);
            InstanceRefPtr<EntityInstance> CreateModifierInstance(std::string modifier_type_name);
            InstanceRefPtr<EntityInstance> CreateModifierInstance(TypeRefPtr<EntityType> modifier_type);
            InstanceRefPtr<EntityInstance> CreateRendererInstance(std::string renderer_type_name, std::string model, vec offset);
            InstanceRefPtr<EntityInstance> CreateRendererInstance(std::string renderer_type_name, std::string shader, std::string texture, float size);
            InstanceRefPtr<EntityInstance> CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string model, vec offset);
            InstanceRefPtr<EntityInstance> CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string shader, std::string texture, float size);

            void DestroyEmitterInstance(std::string uuid);
            void DestroyEmitterInstance(InstanceRefPtr<EntityInstance> emitter_instance);
            void DestroyInitializerInstance(std::string uuid);
            void DestroyInitializerInstance(InstanceRefPtr<EntityInstance> initializer_instance);
            void DestroyModifierInstance(std::string uuid);
            void DestroyModifierInstance(InstanceRefPtr<EntityInstance> modifier_instance);
            void DestroyRendererInstance(std::string uuid);
            void DestroyRendererInstance(InstanceRefPtr<EntityInstance> renderer_instance);

            InstanceRefPtr<RelationshipInstance> AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance);
            InstanceRefPtr<RelationshipInstance> AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance);
            InstanceRefPtr<RelationshipInstance> AddRendererToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> renderer_instance);

            std::shared_ptr<ParticleWorker> CreateParticleWorker(std::string name, FunctionRefPtr function);
            std::shared_ptr<ParticleWorker> CreateParticleWorker(std::string name, FunctionRefPtr function, int maxfps);
            std::shared_ptr<EmitterWorker> CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance);
            std::shared_ptr<EmitterWorker> CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance, int maxfps);
            std::shared_ptr<ModifierWorker> CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance);
            std::shared_ptr<ModifierWorker> CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance, int maxfps);

            void DestroyParticleWorker(std::string name);
            void DestroyParticleWorker(InstanceRefPtr<EntityInstance> entity_instance);
            void DestroyEmitterWorker(InstanceRefPtr<EntityInstance> emitter_instance);
            void DestroyModifierWorker(InstanceRefPtr<EntityInstance> modifier_instance);

        private:

            /**
             * The maximum frames per second.
             */
            int maxfps;

            std::shared_ptr<ParticleTypeFactory> particle_type_factory;
            std::shared_ptr<ParticleEmitterTypeFactory> particle_emitter_type_factory;
            std::shared_ptr<ParticleInitializerTypeFactory> particle_initializer_type_factory;
            std::shared_ptr<ParticleModifierTypeFactory> particle_modifier_type_factory;
            std::shared_ptr<ParticleRendererTypeFactory> particle_renderer_type_factory;

            std::unordered_map<std::string, TypeRefPtr<EntityType> > particle_types;
            std::unordered_map<std::string, TypeRefPtr<EntityType> > emitter_types;
            std::unordered_map<std::string, TypeRefPtr<EntityType> > initializer_types;
            std::unordered_map<std::string, TypeRefPtr<EntityType> > modifier_types;
            std::unordered_map<std::string, TypeRefPtr<EntityType> > renderer_types;

            /**
             * The particle workers.
             */
            std::vector<std::shared_ptr<ParticleWorker> > particle_workers;

            /**
             * The emitter workers.
             */
            std::vector<std::shared_ptr<EmitterWorker> > emitter_workers;

            /**
             * The modifier workers.
             */
            std::vector<std::shared_ptr<ModifierWorker> > modifier_workers;

            /**
             * The modifier workers.
             */
            std::vector<InstanceRefPtr<EntityInstance> > renderers;

            TypeRefPtr<RelationshipType> emitted_by;
            TypeRefPtr<RelationshipType> modifies;
            TypeRefPtr<RelationshipType> renders;
            TypeRefPtr<RelationshipType> apply_initializer;
            TypeRefPtr<RelationshipType> apply_modifier;
            TypeRefPtr<RelationshipType> apply_renderer;

    };

}
}
}

/**
 * Provide the particle subsystem as global reference.
 */
extern std::shared_ptr<inexor::entity::particle::ParticleSubsystem> particle_subsystem;

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_ */