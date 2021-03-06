#include <render/vulkan/sync.h>

void vulkan_sync_init(VulkanCtx *ctx)
{
    VkSemaphoreCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    VkFenceCreateInfo fence_create = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT,
    };

    vk_try$(vkCreateSemaphore(ctx->logical_device, &create_info, NULL, &ctx->image_available_semaphore));
    vk_try$(vkCreateSemaphore(ctx->logical_device, &create_info, NULL, &ctx->render_finished_semaphore));

    vk_try$(vkCreateFence(ctx->logical_device, &fence_create, NULL, &ctx->in_flight_fence));
    vk_try$(vkCreateFence(ctx->logical_device, &fence_create, NULL, &ctx->compute_fence));
}

void vulkan_sync_deinit(VulkanCtx *ctx)
{
    vkDestroySemaphore(ctx->logical_device, ctx->image_available_semaphore, NULL);
    vkDestroySemaphore(ctx->logical_device, ctx->render_finished_semaphore, NULL);

    vkDestroyFence(ctx->logical_device, ctx->in_flight_fence, NULL);
}
