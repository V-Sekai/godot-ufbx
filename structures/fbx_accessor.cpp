/**************************************************************************/
/*  fbx_accessor.cpp                                                      */
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

#include "fbx_accessor.h"

void FBXAccessor::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_buffer_view"), &FBXAccessor::get_buffer_view);
	ClassDB::bind_method(D_METHOD("set_buffer_view", "buffer_view"), &FBXAccessor::set_buffer_view);
	ClassDB::bind_method(D_METHOD("get_byte_offset"), &FBXAccessor::get_byte_offset);
	ClassDB::bind_method(D_METHOD("set_byte_offset", "byte_offset"), &FBXAccessor::set_byte_offset);
	ClassDB::bind_method(D_METHOD("get_component_type"), &FBXAccessor::get_component_type);
	ClassDB::bind_method(D_METHOD("set_component_type", "component_type"), &FBXAccessor::set_component_type);
	ClassDB::bind_method(D_METHOD("get_normalized"), &FBXAccessor::get_normalized);
	ClassDB::bind_method(D_METHOD("set_normalized", "normalized"), &FBXAccessor::set_normalized);
	ClassDB::bind_method(D_METHOD("get_count"), &FBXAccessor::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "count"), &FBXAccessor::set_count);
	ClassDB::bind_method(D_METHOD("get_type"), &FBXAccessor::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &FBXAccessor::set_type);
	ClassDB::bind_method(D_METHOD("get_min"), &FBXAccessor::get_min);
	ClassDB::bind_method(D_METHOD("set_min", "min"), &FBXAccessor::set_min);
	ClassDB::bind_method(D_METHOD("get_max"), &FBXAccessor::get_max);
	ClassDB::bind_method(D_METHOD("set_max", "max"), &FBXAccessor::set_max);
	ClassDB::bind_method(D_METHOD("get_sparse_count"), &FBXAccessor::get_sparse_count);
	ClassDB::bind_method(D_METHOD("set_sparse_count", "sparse_count"), &FBXAccessor::set_sparse_count);
	ClassDB::bind_method(D_METHOD("get_sparse_indices_buffer_view"), &FBXAccessor::get_sparse_indices_buffer_view);
	ClassDB::bind_method(D_METHOD("set_sparse_indices_buffer_view", "sparse_indices_buffer_view"), &FBXAccessor::set_sparse_indices_buffer_view);
	ClassDB::bind_method(D_METHOD("get_sparse_indices_byte_offset"), &FBXAccessor::get_sparse_indices_byte_offset);
	ClassDB::bind_method(D_METHOD("set_sparse_indices_byte_offset", "sparse_indices_byte_offset"), &FBXAccessor::set_sparse_indices_byte_offset);
	ClassDB::bind_method(D_METHOD("get_sparse_indices_component_type"), &FBXAccessor::get_sparse_indices_component_type);
	ClassDB::bind_method(D_METHOD("set_sparse_indices_component_type", "sparse_indices_component_type"), &FBXAccessor::set_sparse_indices_component_type);
	ClassDB::bind_method(D_METHOD("get_sparse_values_buffer_view"), &FBXAccessor::get_sparse_values_buffer_view);
	ClassDB::bind_method(D_METHOD("set_sparse_values_buffer_view", "sparse_values_buffer_view"), &FBXAccessor::set_sparse_values_buffer_view);
	ClassDB::bind_method(D_METHOD("get_sparse_values_byte_offset"), &FBXAccessor::get_sparse_values_byte_offset);
	ClassDB::bind_method(D_METHOD("set_sparse_values_byte_offset", "sparse_values_byte_offset"), &FBXAccessor::set_sparse_values_byte_offset);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "buffer_view"), "set_buffer_view", "get_buffer_view"); // FBXBufferViewIndex
	ADD_PROPERTY(PropertyInfo(Variant::INT, "byte_offset"), "set_byte_offset", "get_byte_offset"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "component_type"), "set_component_type", "get_component_type"); // int
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "normalized"), "set_normalized", "get_normalized"); // bool
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type"), "set_type", "get_type"); // FBXType
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT64_ARRAY, "min"), "set_min", "get_min"); // Vector<real_t>
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT64_ARRAY, "max"), "set_max", "get_max"); // Vector<real_t>
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_count"), "set_sparse_count", "get_sparse_count"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_indices_buffer_view"), "set_sparse_indices_buffer_view", "get_sparse_indices_buffer_view"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_indices_byte_offset"), "set_sparse_indices_byte_offset", "get_sparse_indices_byte_offset"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_indices_component_type"), "set_sparse_indices_component_type", "get_sparse_indices_component_type"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_values_buffer_view"), "set_sparse_values_buffer_view", "get_sparse_values_buffer_view"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sparse_values_byte_offset"), "set_sparse_values_byte_offset", "get_sparse_values_byte_offset"); // int
}

FBXBufferViewIndex FBXAccessor::get_buffer_view() {
	return buffer_view;
}

void FBXAccessor::set_buffer_view(FBXBufferViewIndex p_buffer_view) {
	buffer_view = p_buffer_view;
}

int FBXAccessor::get_byte_offset() {
	return byte_offset;
}

void FBXAccessor::set_byte_offset(int p_byte_offset) {
	byte_offset = p_byte_offset;
}

int FBXAccessor::get_component_type() {
	return component_type;
}

void FBXAccessor::set_component_type(int p_component_type) {
	component_type = p_component_type;
}

bool FBXAccessor::get_normalized() {
	return normalized;
}

void FBXAccessor::set_normalized(bool p_normalized) {
	normalized = p_normalized;
}

int FBXAccessor::get_count() {
	return count;
}

void FBXAccessor::set_count(int p_count) {
	count = p_count;
}

int FBXAccessor::get_type() {
	return (int)type;
}

void FBXAccessor::set_type(int p_type) {
	type = (FBXType)p_type; // TODO: Register enum
}

Vector<double> FBXAccessor::get_min() {
	return min;
}

void FBXAccessor::set_min(Vector<double> p_min) {
	min = p_min;
}

Vector<double> FBXAccessor::get_max() {
	return max;
}

void FBXAccessor::set_max(Vector<double> p_max) {
	max = p_max;
}

int FBXAccessor::get_sparse_count() {
	return sparse_count;
}

void FBXAccessor::set_sparse_count(int p_sparse_count) {
	sparse_count = p_sparse_count;
}

int FBXAccessor::get_sparse_indices_buffer_view() {
	return sparse_indices_buffer_view;
}

void FBXAccessor::set_sparse_indices_buffer_view(int p_sparse_indices_buffer_view) {
	sparse_indices_buffer_view = p_sparse_indices_buffer_view;
}

int FBXAccessor::get_sparse_indices_byte_offset() {
	return sparse_indices_byte_offset;
}

void FBXAccessor::set_sparse_indices_byte_offset(int p_sparse_indices_byte_offset) {
	sparse_indices_byte_offset = p_sparse_indices_byte_offset;
}

int FBXAccessor::get_sparse_indices_component_type() {
	return sparse_indices_component_type;
}

void FBXAccessor::set_sparse_indices_component_type(int p_sparse_indices_component_type) {
	sparse_indices_component_type = p_sparse_indices_component_type;
}

int FBXAccessor::get_sparse_values_buffer_view() {
	return sparse_values_buffer_view;
}

void FBXAccessor::set_sparse_values_buffer_view(int p_sparse_values_buffer_view) {
	sparse_values_buffer_view = p_sparse_values_buffer_view;
}

int FBXAccessor::get_sparse_values_byte_offset() {
	return sparse_values_byte_offset;
}

void FBXAccessor::set_sparse_values_byte_offset(int p_sparse_values_byte_offset) {
	sparse_values_byte_offset = p_sparse_values_byte_offset;
}
