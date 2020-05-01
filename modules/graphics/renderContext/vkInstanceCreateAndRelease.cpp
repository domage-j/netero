/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "renderContext/vkRenderContext.hpp"
#include "utils/vkUtils.hpp"

const std::vector<char*> netero::graphics::RenderContext::impl::validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

void netero::graphics::RenderContext::impl::createVulkanContext() {
    VkInstanceCreateInfo    createInfo = {};

    if (enableValidationLayers && !this->checkValidationLayerSupport()) {
        throw std::runtime_error("There are some missing validation layer, could not create render context");
    }
    // Setup create info struct for createInstance call
    auto extension = this->getRequiredExtensions();
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &this->appInfo;
    const char** glfwExtensions = extension.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extension.size());
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.pNext = nullptr;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(impl::validationLayers.size());
        createInfo.ppEnabledLayerNames = impl::validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    const VkResult result = vkCreateInstance(&createInfo, nullptr, &this->instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance, vkCode: " + std::to_string(result));
    }
    if (enableValidationLayers) {
        this->setupDebugReportCallback();
        this->setupDebugMessenger();
    }
}

std::vector<const char*> netero::graphics::RenderContext::impl::getRequiredExtensions() const {
    uint32_t                    glfwExtensionCount = 0;
    const char**                glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*>    extension(glfwExtensions, glfwExtensions + glfwExtensionCount);

       // Check that all necessary extension are present
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    if (enableValidationLayers) {
        std::cout << "Available Vulkan extensions:" << std::endl;
        for (const auto &ext: extensions) {
            std::cout << "\t" << ext.extensionName << std::endl;
        }
    }
    for (unsigned idx = 0; idx < glfwExtensionCount; ++idx) {
        auto it = std::find_if(extensions.begin(), extensions.end(), [&] (const auto ext) -> bool {
            return strcmp(glfwExtensions[idx], ext.extensionName) == 0;
        });
        if (it == extensions.end()) {
            throw std::runtime_error("Could not create instance, missing extension: " + std::string(glfwExtensions[idx]));
        }
        if (enableValidationLayers) {
            std::cout << "Using extensions: " << glfwExtensions[idx] << std::endl;
        }
    }
    if (this->enableValidationLayers) {
        extension.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        extension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extension;
}

bool netero::graphics::RenderContext::impl::checkValidationLayerSupport() const {
    uint32_t    layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties>    availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    std::cout << "Available Vulkan validation layers:" << std::endl;
    for (auto &prop: availableLayers) {
        std::cout << "\t" << prop.layerName << std::endl;
    }
    for (auto &layerName: RenderContext::impl::validationLayers) {
        auto it = std::find_if(availableLayers.begin(), availableLayers.end(), [layerName] (VkLayerProperties &prop) ->bool {
            return !std::strcmp(layerName, prop.layerName);
        });
        if (it == availableLayers.end()) {
            std::cerr << "Error missing layer: " << layerName << std::endl;
            return false;
        }
    }
    return true;
}

void netero::graphics::RenderContext::impl::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = vkUtils::debugMessengerCallback;
    createInfo.pUserData = nullptr; // Optional    
    createInfo.pNext = nullptr;
}

void netero::graphics::RenderContext::impl::populateDebugReportCreateInfo(VkDebugReportCallbackCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    createInfo.pfnCallback = vkUtils::debugReportCallback;
    createInfo.pUserData = nullptr;
    createInfo.pNext = nullptr;
    createInfo.flags =
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_ERROR_BIT_EXT |
        VK_DEBUG_REPORT_DEBUG_BIT_EXT;
}

void netero::graphics::RenderContext::impl::setupDebugReportCallback() {
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    RenderContext::impl::populateDebugReportCreateInfo(createInfo);
    if (vkUtils::CreateDebugReportEXT(instance, &createInfo, nullptr, &this->debugReport)) {
        throw std::runtime_error("Failed to setup debug report callback.");
    }
}

void netero::graphics::RenderContext::impl::setupDebugMessenger() {
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    RenderContext::impl::populateDebugMessengerCreateInfo(createInfo);

    if (vkUtils::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &this->debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("Failed to setup debug messenger callback.");
    }
}

void netero::graphics::RenderContext::impl::releaseVulkanContext() const {
    if (enableValidationLayers) {
        vkUtils::DestroyDebugReportEXT(this->instance, this->debugReport, nullptr);
        vkUtils::DestroyDebugUtilsMessengerEXT(this->instance, this->debugMessenger, nullptr);
    }
    vkDestroyInstance(this->instance, nullptr);
}
