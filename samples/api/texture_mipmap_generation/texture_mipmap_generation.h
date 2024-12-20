/* Copyright (c) 2019-2024, Sascha Willems
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 the "License";
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Runtime mip map generation
 */

#pragma once

#include <ktx.h>

#include "api_vulkan_sample.h"

// Vertex layout for this example
struct TextureMipMapGenerationVertexStructure
{
	float pos[3];
	float uv[2];
	float normal[3];
};

class TextureMipMapGeneration : public ApiVulkanSample
{
  public:
	struct Texture
	{
		VkImage        image;
		VkImageLayout  image_layout;
		VkDeviceMemory device_memory;
		VkImageView    view;
		uint32_t       width, height;
		uint32_t       mip_levels;
	} texture;

	// To demonstrate mip mapping and filtering this example uses separate samplers
	std::vector<std::string> sampler_names{"No mip maps", "Mip maps (bilinear)", "Mip maps (anisotropic)"};
	std::vector<VkSampler>   samplers;

	std::unique_ptr<vkb::sg::SubMesh> scene;

	bool rotate_scene = false;

	struct
	{
		glm::mat4 projection;
		glm::mat4 model;
		float     lod_bias      = 0.0f;
		int32_t   sampler_index = 2;
	} ubo;
	std::unique_ptr<vkb::core::BufferC> uniform_buffer;

	VkPipeline            pipeline              = VK_NULL_HANDLE;
	VkPipelineLayout      pipeline_layout       = VK_NULL_HANDLE;
	VkDescriptorSet       descriptor_set        = VK_NULL_HANDLE;
	VkDescriptorSetLayout descriptor_set_layout = VK_NULL_HANDLE;

	VkPipeline            compute_pipeline              = VK_NULL_HANDLE;
	VkPipelineLayout      compute_pipeline_layout       = VK_NULL_HANDLE;
	VkDescriptorSet       compute_descriptor_set[10]     = {VK_NULL_HANDLE};
	VkDescriptorSetLayout compute_descriptor_set_layout = VK_NULL_HANDLE;
	VkImageView           compute_view[10]               = {VK_NULL_HANDLE};

	TextureMipMapGeneration();
	~TextureMipMapGeneration();
	virtual void request_gpu_features(vkb::PhysicalDevice &gpu) override;
	void         load_texture_generate_mipmaps(std::string file_name);
	void         destroy_texture(Texture texture);
	void         load_assets();
	void         build_command_buffers() override;
	void         draw();
	void         setup_descriptor_pool();
	void         setup_descriptor_set_layout();
	void         setup_descriptor_set();
	void         prepare_pipelines();
	void         prepare_uniform_buffers();
	void         update_uniform_buffers(float delta_time = 0.0f);
	bool         prepare(const vkb::ApplicationOptions &options) override;
	virtual void render(float delta_time) override;
	virtual void view_changed() override;
	virtual void on_update_ui_overlay(vkb::Drawer &drawer) override;
};

std::unique_ptr<vkb::Application> create_texture_mipmap_generation();
