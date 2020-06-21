/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

#include <vector>
#include <atomic>
#include <vulkan/vulkan.h>
#include <netero/graphics/shader.hpp>
#include <netero/graphics/device.hpp>
#include <netero/graphics/vertex.hpp>
#include <netero/graphics/texture.hpp>
#include <netero/graphics/instance.hpp>
#include <netero/graphics/descriptor_set.hpp>

namespace netero::graphics {

    /**
     * @brief Any model to render
     * Contain assets and data to be rendered.
     * @details Only one model exist per instance. Models are used to
     * hold vertices, shaders, textures...
     */
    class Model {
        friend class Pipeline;
        friend class Context;
        Model(VkInstance, Device*);

        void build(size_t, std::vector<VkBuffer>&, VkRenderPass, VkExtent2D);
        void rebuild(size_t, std::vector<VkBuffer>&, VkRenderPass, VkExtent2D);
        void release(size_t);

        void createInstanceBuffer(size_t);
        //void createDescriptorSetsLayout(DescriptorSets*);
        //void createDescriptorSetVector(uint32_t, DescriptorSets*);
        void createDescriptors(uint32_t);
        void writeToDescriptorSet(uint32_t, std::vector<VkBuffer>&);
        void createGraphicsPipeline(VkRenderPass, VkExtent2D);
        void commitRenderCommand(VkCommandBuffer, size_t);
        void update(uint32_t);

        VkInstance          _instance;
        Device*             _device;
        VertexBuffer        _vertexBuffer;
        VkPipelineLayout    _pipelineLayout;
        VkPipeline          _graphicsPipeline;
        std::vector<Shader>     _shaderModules;
        std::vector<Instance*>  _modelInstances;

        // Model Buffer
        VkBuffer            _instanceBuffer;
        VkDeviceMemory      _instanceBufferMemory;

        // Texture
        Texture _textures;

        // Descriptors
        DescriptorSets  _descriptorSets;
        Descriptor      _uboDescriptor;
        Descriptor      _textureDescriptor;
    public:
        Model(const Model&) = delete;
        Model(Model&&) = delete;
        Model& operator=(const Model&) = delete;
        Model& operator=(Model&&) = delete;
        ~Model();

        Instance* createInstance();
        void    deleteInstance(Instance*);
        void    addVertices(std::vector<Vertex>&);
        void    addVertices(std::vector<Vertex>&, std::vector<uint16_t>&);
        int     loadShader(const std::string&, ShaderStage);
        void    loadTexture(const std::string&, TextureSamplingMode);
    };
}

