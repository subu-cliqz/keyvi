include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::ffi::{CStr, CString};
use std::ops::Deref;
use keyvi_string::KeyviString;

pub struct Dictionary {
    dict: *mut root::keyvi_dictionary,
}


impl Dictionary {
    pub fn new(filename: &str) -> Self {
        let fn_c = CString::new(filename).unwrap();
        Dictionary {
            dict: unsafe { root::keyvi_create_dictionary(fn_c.as_ptr()) }
        }
    }

    pub fn statistics(&self) -> String {
        let c_buf: *mut ::std::os::raw::c_char = unsafe { root::keyvi_dictionary_get_statistics(self.dict) };
        KeyviString::new(c_buf).to_owned()
    }

    pub fn size(&self) -> u64 {
        return unsafe { root::keyvi_dictionary_get_size(self.dict) };
    }
}

impl Drop for Dictionary {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_dictionary_destroy(self.dict);
        }
    }
}
