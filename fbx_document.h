/**************************************************************************/
/*  fbx_document.h                                                        */
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
	void _build_parent_hierarchy(Ref<FBXState> p_state);
	Error _parse_scenes(Ref<FBXState> p_state);
	Error _parse_nodes(Ref<FBXState> p_state);
	String _gen_unique_name(Ref<FBXState> p_state, const String &p_name);
	String _sanitize_animation_name(const String &p_name);
	String _gen_unique_animation_name(Ref<FBXState> p_state, const String &p_name);
	String _sanitize_bone_name(const String &p_name);
	String _gen_unique_bone_name(Ref<FBXState> p_state,
			const FBXSkeletonIndex p_skel_i,
			const String &p_name);
	Ref<Texture2D> _get_texture(Ref<FBXState> p_state,
			const FBXTextureIndex p_texture, int p_texture_type);
	Error _parse_meshes(Ref<FBXState> p_state);
	Ref<Image> _parse_image_bytes_into_image(Ref<FBXState> p_state, const Vector<uint8_t> &p_bytes, const String &p_filename, int p_index);
	void _parse_image_save_image(Ref<FBXState> p_state, const Vector<uint8_t> &p_bytes, const String &p_file_extension, int p_index, Ref<Image> p_image);
	Error _parse_images(Ref<FBXState> p_state, const String &p_base_path);
	Error _parse_materials(Ref<FBXState> p_state);
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
	FBXAnimation::Track _convert_animation_track(Ref<FBXState> p_state,
			FBXAnimation::Track p_track,
			Ref<Animation> p_animation,
			int32_t p_track_i,
			FBXNodeIndex p_node_i);

public:
	Error append_from_file(String p_path, Ref<FBXState> p_state, uint32_t p_flags = 0, String p_base_path = String());
	Error append_from_buffer(PackedByteArray p_bytes, String p_base_path, Ref<FBXState> p_state, uint32_t p_flags = 0);
	Error append_from_scene(Node *p_node, Ref<FBXState> p_state, uint32_t p_flags = 0);

public:
	Node *generate_scene(Ref<FBXState> p_state, float p_bake_fps = 30.0f, bool p_trimming = false, bool p_remove_immutable_tracks = true);

public:
	Error _parse_fbx_state(Ref<FBXState> p_state, const String &p_search_path);
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
