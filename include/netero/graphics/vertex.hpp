/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

#include <array>
#include <vector>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <netero/graphics/device.hpp>

namespace netero::graphics {

    struct Vertex {
        glm::vec2   pos;
        glm::vec3   color;
        glm::vec2   texCord = {0, 0};

        static VkVertexInputBindingDescription  getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription = {};

            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3>    getAttributeDescription() {
            std::array<VkVertexInputAttributeDescription, 3>    attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);
            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCord);

            return attributeDescriptions;
        }
    };

    struct VertexBuffer {
        Device* _device;
        void    createVertexBuffer();
        void    createIndexBuffer(int);
    public:
        VertexBuffer(Device*);
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&&) = delete;
        ~VertexBuffer();

        void    AllocateAndTransfer(int);
        void    release();

        VkBuffer            vertexBuffer;
        VkDeviceMemory      vertexBufferMemory;
        std::vector<Vertex> vertices;
        VkBuffer                indexBuffer;
        VkDeviceMemory          indexBufferMemory;
        std::vector<uint16_t>   indices;
    };

}

