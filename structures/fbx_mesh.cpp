/**************************************************************************/
/*  fbx_mesh.cpp                                                          */
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

#include "fbx_mesh.h"

#include "scene/resources/importer_mesh.h"

void FBXMesh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_mesh"), &FBXMesh::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "mesh"), &FBXMesh::set_mesh);
	ClassDB::bind_method(D_METHOD("get_blend_weights"), &FBXMesh::get_blend_weights);
	ClassDB::bind_method(D_METHOD("set_blend_weights", "blend_weights"), &FBXMesh::set_blend_weights);
	ClassDB::bind_method(D_METHOD("get_blend_channels"), &FBXMesh::get_blend_channels);
	ClassDB::bind_method(D_METHOD("set_blend_channels", "blend_channels"), &FBXMesh::set_blend_channels);
	ClassDB::bind_method(D_METHOD("get_instance_materials"), &FBXMesh::get_instance_materials);
	ClassDB::bind_method(D_METHOD("set_instance_materials", "instance_materials"), &FBXMesh::set_instance_materials);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh"), "set_mesh", "get_mesh");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "blend_weights"), "set_blend_weights", "get_blend_weights"); // Vector<float>
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "blend_channels"), "set_blend_channels", "get_blend_channels"); // Vector<float>
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "instance_materials"), "set_instance_materials", "get_instance_materials");
}

Ref<ImporterMesh> FBXMesh::get_mesh() {
	return mesh;
}

void FBXMesh::set_mesh(Ref<ImporterMesh> p_mesh) {
	mesh = p_mesh;
}

TypedArray<Material> FBXMesh::get_instance_materials() {
	return instance_materials;
}

void FBXMesh::set_instance_materials(TypedArray<Material> p_instance_materials) {
	instance_materials = p_instance_materials;
}

Vector<float> FBXMesh::get_blend_weights() {
	return blend_weights;
}

void FBXMesh::set_blend_weights(Vector<float> p_blend_weights) {
	blend_weights = p_blend_weights;
}

Vector<int> FBXMesh::get_blend_channels() {
	return blend_channels;
}

void FBXMesh::set_blend_channels(Vector<int> p_blend_channels) {
	blend_channels = p_blend_channels;
}
