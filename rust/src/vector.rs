/* * keyvi - A key value store.
 *
 * Copyright 2017   Narek Gharibyan <narekgharibyan@gmail.com>
 *                  Subu <subu@cliqz.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 *  dictionary.rs
 *
 *  Created on: February 9, 2018
 *  Author: Narek Gharibyan <narekgharibyan@gmail.com>
 *          Subu <subu@cliqz.com>
 */

use std::ffi::CString;
use keyvi_string::KeyviString;
use bindings::*;

#[derive(Clone)]
pub struct StringVector {
    vec: *mut root::keyvi_vector_string,
}

unsafe impl Send for StringVector {}

unsafe impl Sync for StringVector {}

impl StringVector {
    pub fn new(filename: &str) -> Result<StringVector, &str> {
        let fn_c = CString::new(filename).unwrap();
        let ptr = unsafe { root::keyvi_create_vector_string(fn_c.as_ptr()) };
        if ptr.is_null() {
            Err("could not load file")
        } else {
            Ok(StringVector { vec: ptr })
        }
    }

    pub fn size(&self) -> usize {
        unsafe { root::keyvi_vector_string_get_size(self.vec) }
    }

    pub fn get(&self, key: usize) -> String {
        let c_buf: *mut ::std::os::raw::c_char =
            unsafe { root::keyvi_vector_string_get(self.vec, key) };
        KeyviString::new(c_buf).to_owned()
    }
}

impl Drop for StringVector {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_vector_string_destroy(self.vec);
        }
    }
}
