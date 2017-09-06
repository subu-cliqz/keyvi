include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::ffi::{CStr, CString};
use std::ops::Deref;


pub struct KeyviString {
    str_: *mut ::std::os::raw::c_char,
}

impl KeyviString {
    pub fn new(str: *mut ::std::os::raw::c_char) -> KeyviString {
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
