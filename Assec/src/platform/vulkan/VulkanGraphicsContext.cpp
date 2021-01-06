#include "acpch.h"

#include <GLFW/glfw3.h>

#include "VulkanGraphicsContext.h"

namespace assec::graphics
{
	void VulkanGraphicsContext::init()
	{
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 2, 0);
        appInfo.pEngineName = "Assec Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 2, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;
        
        AC_CORE_ASSERT(vkCreateInstance(&createInfo, nullptr, &this->m_Instance) == VK_SUCCESS, "failed to create vulkan instance");
	    
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    }

    void VulkanGraphicsContext::cleanup()
    {
        vkDestroyInstance(this->m_Instance, nullptr);
    }
}