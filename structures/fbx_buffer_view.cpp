/**************************************************************************/
/*  gltf_buffer_view.cpp                                                  */
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

#include "fbx_buffer_view.h"

void FBXBufferView::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_buffer"), &FBXBufferView::get_buffer);
	ClassDB::bind_method(D_METHOD("set_buffer", "buffer"), &FBXBufferView::set_buffer);
	ClassDB::bind_method(D_METHOD("get_byte_offset"), &FBXBufferView::get_byte_offset);
	ClassDB::bind_method(D_METHOD("set_byte_offset", "byte_offset"), &FBXBufferView::set_byte_offset);
	ClassDB::bind_method(D_METHOD("get_byte_length"), &FBXBufferView::get_byte_length);
	ClassDB::bind_method(D_METHOD("set_byte_length", "byte_length"), &FBXBufferView::set_byte_length);
	ClassDB::bind_method(D_METHOD("get_byte_stride"), &FBXBufferView::get_byte_stride);
	ClassDB::bind_method(D_METHOD("set_byte_stride", "byte_stride"), &FBXBufferView::set_byte_stride);
	ClassDB::bind_method(D_METHOD("get_indices"), &FBXBufferView::get_indices);
	ClassDB::bind_method(D_METHOD("set_indices", "indices"), &FBXBufferView::set_indices);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "buffer"), "set_buffer", "get_buffer"); // FBXBufferIndex
	ADD_PROPERTY(PropertyInfo(Variant::INT, "byte_offset"), "set_byte_offset", "get_byte_offset"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "byte_length"), "set_byte_length", "get_byte_length"); // int
	ADD_PROPERTY(PropertyInfo(Variant::INT, "byte_stride"), "set_byte_stride", "get_byte_stride"); // int
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "indices"), "set_indices", "get_indices"); // bool
}

FBXBufferIndex FBXBufferView::get_buffer() {
	return buffer;
}

void FBXBufferView::set_buffer(FBXBufferIndex p_buffer) {
	buffer = p_buffer;
}

int FBXBufferView::get_byte_offset() {
	return byte_offset;
}

void FBXBufferView::set_byte_offset(int p_byte_offset) {
	byte_offset = p_byte_offset;
}

int FBXBufferView::get_byte_length() {
	return byte_length;
}

void FBXBufferView::set_byte_length(int p_byte_length) {
	byte_length = p_byte_length;
}

int FBXBufferView::get_byte_stride() {
	return byte_stride;
}

void FBXBufferView::set_byte_stride(int p_byte_stride) {
	byte_stride = p_byte_stride;
}

bool FBXBufferView::get_indices() {
	return indices;
}

void FBXBufferView::set_indices(bool p_indices) {
	indices = p_indices;
}
