include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::ffi::{CStr, CString};
use std::ops::Deref;


pub struct Dictionary {
    dict: *mut root::keyvi_dictionary,
}

struct KeyviString {
    str_: *mut ::std::os::raw::c_char,
}

impl KeyviString {
    fn new(str: *mut ::std::os::raw::c_char) -> KeyviString {
        KeyviString { str_: str }
    }
}

impl Drop for KeyviString {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_string_destroy(self.str_);
        }
    }
}

impl Deref for KeyviString {
    type Target = str;

    fn deref<'a>(&'a self) -> &'a str {
        let c_str = unsafe { CStr::from_ptr(self.str_) };
        c_str.to_str().unwrap()
    }
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
