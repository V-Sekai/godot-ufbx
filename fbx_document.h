/**************************************************************************/
/*  gltf_document.h                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef FBX_DOCUMENT_H
#define FBX_DOCUMENT_H

#include "extensions/fbx_document_extension.h"

#include "modules/modules_enabled.gen.h" // For csg, gridmap.

class FBXDocument : public Resource {
	GDCLASS(FBXDocument, Resource);
	static Vector<Ref<FBXDocumentExtension>> all_document_extensions;
	Vector<Ref<FBXDocumentExtension>> document_extensions;

private:
	const float BAKE_FPS = 30.0f;

public:
	const int32_t JOINT_GROUP_SIZE = 4;

	enum {
		ARRAY_BUFFER = 34962,
		ELEMENT_ARRAY_BUFFER = 34963,

		TYPE_BYTE = 5120,
		TYPE_UNSIGNED_BYTE = 5121,
		TYPE_SHORT = 5122,
		TYPE_UNSIGNED_SHORT = 5123,
		TYPE_UNSIGNED_INT = 5125,
		TYPE_FLOAT = 5126,

		COMPONENT_TYPE_BYTE = 5120,
		COMPONENT_TYPE_UNSIGNED_BYTE = 5121,
		COMPONENT_TYPE_SHORT = 5122,
		COMPONENT_TYPE_UNSIGNED_SHORT = 5123,
		COMPONENT_TYPE_INT = 5125,
		COMPONENT_TYPE_FLOAT = 5126,
	};
	enum {
		TEXTURE_TYPE_GENERIC = 0,
		TEXTURE_TYPE_NORMAL = 1,
	};

protected:
	static void _bind_methods();

public:
	static void register_fbx_document_extension(Ref<FBXDocumentExtension> p_extension, bool p_first_priority = false);
	static void unregister_fbx_document_extension(Ref<FBXDocumentExtension> p_extension);
	static void unregister_all_fbx_document_extensions();

private:
	void _build_parent_hierachy(Ref<FBXState> p_state);
	double _filter_number(double p_float);
	String _get_component_type_name(const uint32_t p_component);
	int _get_component_type_size(const int p_component_type);
	Error _parse_scenes(Ref<FBXState> p_state);
	Error _parse_nodes(Ref<FBXState> p_state);
	String _get_type_name(const FBXType p_component);
	String _get_accessor_type_name(const FBXType p_type);
	String _gen_unique_name(Ref<FBXState> p_state, const String &p_name);
	String _sanitize_animation_name(const String &p_name);
	String _gen_unique_animation_name(Ref<FBXState> p_state, const String &p_name);
	String _sanitize_bone_name(const String &p_name);
	String _gen_unique_bone_name(Ref<FBXState> p_state,
			const FBXSkeletonIndex p_skel_i,
			const String &p_name);
	FBXTextureIndex _set_texture(Ref<FBXState> p_state, Ref<Texture2D> p_texture,
			StandardMaterial3D::TextureFilter p_filter_mode, bool p_repeats);
	Ref<Texture2D> _get_texture(Ref<FBXState> p_state,
			const FBXTextureIndex p_texture, int p_texture_type);
	FBXTextureSamplerIndex _set_sampler_for_mode(Ref<FBXState> p_state,
			StandardMaterial3D::TextureFilter p_filter_mode, bool p_repeats);
	Ref<FBXTextureSampler> _get_sampler_for_texture(Ref<FBXState> p_state,
			const FBXTextureIndex p_texture);
	Error _parse_json(const String &p_path, Ref<FBXState> p_state);
	Error _parse_glb(Ref<FileAccess> p_file, Ref<FBXState> p_state);
	void _compute_node_heights(Ref<FBXState> p_state);
	Error _parse_buffers(Ref<FBXState> p_state, const String &p_base_path);
	Error _parse_buffer_views(Ref<FBXState> p_state);
	FBXType _get_type_from_str(const String &p_string);
	Error _parse_accessors(Ref<FBXState> p_state);
	Error _decode_buffer_view(Ref<FBXState> p_state, double *p_dst,
			const FBXBufferViewIndex p_buffer_view,
			const int p_skip_every, const int p_skip_bytes,
			const int p_element_size, const int p_count,
			const FBXType p_type, const int p_component_count,
			const int p_component_type, const int p_component_size,
			const bool p_normalized, const int p_byte_offset,
			const bool p_for_vertex);
	Vector<double> _decode_accessor(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<float> _decode_accessor_as_floats(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<int> _decode_accessor_as_ints(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Vector2> _decode_accessor_as_vec2(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Vector3> _decode_accessor_as_vec3(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Color> _decode_accessor_as_color(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Quaternion> _decode_accessor_as_quaternion(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Transform2D> _decode_accessor_as_xform2d(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Basis> _decode_accessor_as_basis(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Vector<Transform3D> _decode_accessor_as_xform(Ref<FBXState> p_state,
			const FBXAccessorIndex p_accessor,
			const bool p_for_vertex);
	Error _parse_meshes(Ref<FBXState> p_state);
	Ref<Image> _parse_image_bytes_into_image(Ref<FBXState> p_state, const Vector<uint8_t> &p_bytes, const String &p_mime_type, int p_index, String &r_file_extension);
	void _parse_image_save_image(Ref<FBXState> p_state, const Vector<uint8_t> &p_bytes, const String &p_file_extension, int p_index, Ref<Image> p_image);
	Error _parse_images(Ref<FBXState> p_state, const String &p_base_path);
	Error _parse_textures(Ref<FBXState> p_state);
	Error _parse_texture_samplers(Ref<FBXState> p_state);
	Error _parse_materials(Ref<FBXState> p_state);
	void _set_texture_transform_uv1(const Dictionary &d, Ref<BaseMaterial3D> p_material);
	static void spec_gloss_to_metal_base_color(const Color &p_specular_factor,
			const Color &p_diffuse,
			Color &r_base_color,
			float &r_metallic);
	FBXNodeIndex _find_highest_node(Ref<FBXState> p_state,
			const Vector<FBXNodeIndex> &p_subset);
	void _recurse_children(Ref<FBXState> p_state, const FBXNodeIndex p_node_index,
			RBSet<FBXNodeIndex> &p_all_skin_nodes, HashSet<FBXNodeIndex> &p_child_visited_set);
	bool _capture_nodes_in_skin(Ref<FBXState> p_state, Ref<FBXSkin> p_skin,
			const FBXNodeIndex p_node_index);
	void _capture_nodes_for_multirooted_skin(Ref<FBXState> p_state, Ref<FBXSkin> p_skin);
	Error _expand_skin(Ref<FBXState> p_state, Ref<FBXSkin> p_skin);
	Error _verify_skin(Ref<FBXState> p_state, Ref<FBXSkin> p_skin);
	Error _parse_skins(Ref<FBXState> p_state);
	Error _determine_skeletons(Ref<FBXState> p_state);
	Error _reparent_non_joint_skeleton_subtrees(
			Ref<FBXState> p_state, Ref<FBXSkeleton> p_skeleton,
			const Vector<FBXNodeIndex> &p_non_joints);
	Error _determine_skeleton_roots(Ref<FBXState> p_state,
			const FBXSkeletonIndex p_skel_i);
	Error _create_skeletons(Ref<FBXState> p_state);
	Error _map_skin_joints_indices_to_skeleton_bone_indices(Ref<FBXState> p_state);
	Error _create_skins(Ref<FBXState> p_state);
	bool _skins_are_same(const Ref<Skin> p_skin_a, const Ref<Skin> p_skin_b);
	void _remove_duplicate_skins(Ref<FBXState> p_state);
	Error _parse_cameras(Ref<FBXState> p_state);
	Error _parse_animations(Ref<FBXState> p_state);
	BoneAttachment3D *_generate_bone_attachment(Ref<FBXState> p_state,
			Skeleton3D *p_skeleton,
			const FBXNodeIndex p_node_index,
			const FBXNodeIndex p_bone_index);
	ImporterMeshInstance3D *_generate_mesh_instance(Ref<FBXState> p_state, const FBXNodeIndex p_node_index);
	Camera3D *_generate_camera(Ref<FBXState> p_state, const FBXNodeIndex p_node_index);
	Node3D *_generate_spatial(Ref<FBXState> p_state, const FBXNodeIndex p_node_index);
	void _assign_node_names(Ref<FBXState> p_state);
	template <class T>
	T _interpolate_track(const Vector<real_t> &p_times, const Vector<T> &p_values,
			const float p_time,
			const FBXAnimation::Interpolation p_interp);
	FBXAccessorIndex _encode_accessor_as_quaternions(Ref<FBXState> p_state,
			const Vector<Quaternion> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_weights(Ref<FBXState> p_state,
			const Vector<Color> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_joints(Ref<FBXState> p_state,
			const Vector<Color> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_floats(Ref<FBXState> p_state,
			const Vector<real_t> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_vec2(Ref<FBXState> p_state,
			const Vector<Vector2> p_attribs,
			const bool p_for_vertex);

	void _calc_accessor_vec2_min_max(int p_i, const int p_element_count, Vector<double> &p_type_max, Vector2 p_attribs, Vector<double> &p_type_min) {
		if (p_i == 0) {
			for (int32_t type_i = 0; type_i < p_element_count; type_i++) {
				p_type_max.write[type_i] = p_attribs[(p_i * p_element_count) + type_i];
				p_type_min.write[type_i] = p_attribs[(p_i * p_element_count) + type_i];
			}
		}
		for (int32_t type_i = 0; type_i < p_element_count; type_i++) {
			p_type_max.write[type_i] = MAX(p_attribs[(p_i * p_element_count) + type_i], p_type_max[type_i]);
			p_type_min.write[type_i] = MIN(p_attribs[(p_i * p_element_count) + type_i], p_type_min[type_i]);
			p_type_max.write[type_i] = _filter_number(p_type_max.write[type_i]);
			p_type_min.write[type_i] = _filter_number(p_type_min.write[type_i]);
		}
	}

	FBXAccessorIndex _encode_accessor_as_vec3(Ref<FBXState> p_state,
			const Vector<Vector3> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_color(Ref<FBXState> p_state,
			const Vector<Color> p_attribs,
			const bool p_for_vertex);

	void _calc_accessor_min_max(int p_i, const int p_element_count, Vector<double> &p_type_max, Vector<double> p_attribs, Vector<double> &p_type_min);

	FBXAccessorIndex _encode_accessor_as_ints(Ref<FBXState> p_state,
			const Vector<int32_t> p_attribs,
			const bool p_for_vertex);
	FBXAccessorIndex _encode_accessor_as_xform(Ref<FBXState> p_state,
			const Vector<Transform3D> p_attribs,
			const bool p_for_vertex);
	Error _encode_buffer_view(Ref<FBXState> p_state, const double *p_src,
			const int p_count, const FBXType p_type,
			const int p_component_type, const bool p_normalized,
			const int p_byte_offset, const bool p_for_vertex,
			FBXBufferViewIndex &r_accessor);
	Error _encode_accessors(Ref<FBXState> p_state);
	Error _encode_buffer_views(Ref<FBXState> p_state);
	String interpolation_to_string(const FBXAnimation::Interpolation p_interp);
	FBXAnimation::Track _convert_animation_track(Ref<FBXState> p_state,
			FBXAnimation::Track p_track,
			Ref<Animation> p_animation,
			int32_t p_track_i,
			FBXNodeIndex p_node_i);
public:
	// https://www.itu.int/rec/R-REC-BT.601
	// https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.601-7-201103-I!!PDF-E.pdf
	static constexpr float R_BRIGHTNESS_COEFF = 0.299f;
	static constexpr float G_BRIGHTNESS_COEFF = 0.587f;
	static constexpr float B_BRIGHTNESS_COEFF = 0.114f;

private:
	// https://github.com/microsoft/glTF-SDK/blob/master/GLTFSDK/Source/PBRUtils.cpp#L9
	// https://bghgary.github.io/glTF/convert-between-workflows-bjs/js/babylon.pbrUtilities.js
	static float solve_metallic(float p_dielectric_specular, float p_diffuse,
			float p_specular,
			float p_one_minus_specular_strength);
	static float get_perceived_brightness(const Color p_color);
	static float get_max_component(const Color &p_color);

public:
	Error append_from_file(String p_path, Ref<FBXState> p_state, uint32_t p_flags = 0, String p_base_path = String());
	Error append_from_buffer(PackedByteArray p_bytes, String p_base_path, Ref<FBXState> p_state, uint32_t p_flags = 0);
	Error append_from_scene(Node *p_node, Ref<FBXState> p_state, uint32_t p_flags = 0);

public:
	Node *generate_scene(Ref<FBXState> p_state, float p_bake_fps = 30.0f, bool p_trimming = false, bool p_remove_immutable_tracks = true);

public:
	Error _parse_fbx_state(Ref<FBXState> p_state, const String &p_search_path);
	Error _parse_fbx_extensions(Ref<FBXState> p_state);
	void _process_mesh_instances(Ref<FBXState> p_state, Node *p_scene_root);
	void _generate_scene_node(Ref<FBXState> p_state, const FBXNodeIndex p_node_index, Node *p_scene_parent, Node *p_scene_root);
	void _generate_skeleton_bone_node(Ref<FBXState> p_state, const FBXNodeIndex p_node_index, Node *p_scene_parent, Node *p_scene_root);
	void _import_animation(Ref<FBXState> p_state, AnimationPlayer *p_animation_player,
			const FBXAnimationIndex p_index, const float p_bake_fps, const bool p_trimming, const bool p_remove_immutable_tracks);
	void _convert_mesh_instances(Ref<FBXState> p_state);
	FBXCameraIndex _convert_camera(Ref<FBXState> p_state, Camera3D *p_camera);
	void _convert_spatial(Ref<FBXState> p_state, Node3D *p_spatial, Ref<FBXNode> p_node);
	void _convert_scene_node(Ref<FBXState> p_state, Node *p_current,
			const FBXNodeIndex p_fbx_current,
			const FBXNodeIndex p_fbx_root);

#ifdef MODULE_CSG_ENABLED
	void _convert_csg_shape_to_fbx(CSGShape3D *p_current, FBXNodeIndex p_gltf_parent, Ref<FBXNode> p_gltf_node, Ref<FBXState> p_state);
#endif // MODULE_CSG_ENABLED

	void _create_fbx_node(Ref<FBXState> p_state,
			Node *p_scene_parent,
			FBXNodeIndex p_current_node_i,
			FBXNodeIndex p_parent_node_index,
			FBXNodeIndex p_root_gltf_node,
			Ref<FBXNode> p_gltf_node);
	void _convert_animation_player_to_fbx(
			AnimationPlayer *p_animation_player, Ref<FBXState> p_state,
			FBXNodeIndex p_gltf_current,
			FBXNodeIndex p_gltf_root_index,
			Ref<FBXNode> p_gltf_node, Node *p_scene_parent);
	void _check_visibility(Node *p_node, bool &r_retflag);
	void _convert_camera_to_fbx(Camera3D *p_camera, Ref<FBXState> p_state,
			Ref<FBXNode> p_gltf_node);
#ifdef MODULE_GRIDMAP_ENABLED
	void _convert_grid_map_to_fbx(
			GridMap *p_grid_map,
			FBXNodeIndex p_parent_node_index,
			FBXNodeIndex p_root_node_index,
			Ref<FBXNode> p_gltf_node, Ref<FBXState> p_state);
#endif // MODULE_GRIDMAP_ENABLED
	void _convert_multi_mesh_instance_to_fbx(
			MultiMeshInstance3D *p_multi_mesh_instance,
			FBXNodeIndex p_parent_node_index,
			FBXNodeIndex p_root_node_index,
			Ref<FBXNode> p_gltf_node, Ref<FBXState> p_state);
	void _convert_skeleton_to_fbx(
			Skeleton3D *p_scene_parent, Ref<FBXState> p_state,
			FBXNodeIndex p_parent_node_index,
			FBXNodeIndex p_root_node_index,
			Ref<FBXNode> p_gltf_node);
	void _convert_bone_attachment_to_fbx(BoneAttachment3D *p_bone_attachment,
			Ref<FBXState> p_state,
			FBXNodeIndex p_parent_node_index,
			FBXNodeIndex p_root_node_index,
			Ref<FBXNode> p_gltf_node);
	void _convert_mesh_instance_to_fbx(MeshInstance3D *p_mesh_instance,
			Ref<FBXState> p_state,
			Ref<FBXNode> p_gltf_node);
	FBXMeshIndex _convert_mesh_to_fbx(Ref<FBXState> p_state,
			MeshInstance3D *p_mesh_instance);
	void _convert_animation(Ref<FBXState> p_state, AnimationPlayer *p_animation_player, String p_animation_track_name);
	Error _parse(Ref<FBXState> p_state, String p_path, Ref<FileAccess> p_file);
};

#endif // FBX_DOCUMENT_H
