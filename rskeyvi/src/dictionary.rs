use std::ffi::CString;
use keyvi_string::KeyviString;
use keyvi_match::KeyviMatch;
use keyvi_match_iterator::KeyviMatchIterator;
use bindings::*;

pub struct Dictionary {
    dict: *mut root::keyvi_dictionary,
}


impl Dictionary {
    pub fn new(filename: &str) -> Result<Dictionary, &str> {
        let fn_c = CString::new(filename).unwrap();
        let ptr = unsafe { root::keyvi_create_dictionary(fn_c.as_ptr()) };
        if ptr.is_null() {
            Err("could not load file")
        } else {
            Ok(Dictionary { dict: ptr })
        }
    }

    pub fn statistics(&self) -> String {
        let c_buf: *mut ::std::os::raw::c_char = unsafe { root::keyvi_dictionary_get_statistics(self.dict) };
        KeyviString::new(c_buf).to_owned()
    }

    pub fn size(&self) -> u64 {
        unsafe { root::keyvi_dictionary_get_size(self.dict) }
    }

    pub fn get(&self, key: &str) -> KeyviMatch {
        let key_c = CString::new(key).unwrap();
        let match_ptr = unsafe { root::keyvi_dictionary_get(self.dict, key_c.as_ptr()) };
        KeyviMatch::new(match_ptr)
    }

    pub fn get_prefix_completions(&self, key: &str, cutoff: i32) -> KeyviMatchIterator {
        let key_c = CString::new(key).unwrap();
        let ptr = unsafe {
            root::keyvi_dictionary_get_prefix_completions(self.dict, key_c.as_ptr(), cutoff)
        };
        KeyviMatchIterator::new(ptr)
    }

    pub fn get_multi_word_completions(&self, key: &str, cutoff: i32) -> KeyviMatchIterator {
        let key_c = CString::new(key).unwrap();
        let ptr = unsafe {
            root::keyvi_dictionary_get_multi_word_completions(self.dict, key_c.as_ptr(), cutoff)
        };
        KeyviMatchIterator::new(ptr)
    }
}

impl Drop for Dictionary {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_dictionary_destroy(self.dict);
        }
    }
}
