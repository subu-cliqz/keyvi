#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

#![feature(libc)]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
extern crate libc;
use self::libc::*;
use std::ffi::{CStr, CString};

#[cfg(test)]
mod tests {
    use super::*;
    use std::mem;
    use std::str::FromStr;

    #[test]
    fn dictionary_load() {
        unsafe {
            let dname = CString::new("/Users/narek/projects/keyvi/test.kv").unwrap();
            let f = keyvi_create_dictionary(dname.as_ptr());
            println!("{:?}", CStr::from_ptr(keyvi_get_dictionary_stats(f)));
            println!("{:?}", CStr::from_ptr(keyvi_get_dictionary_value(f, CString::new("a").unwrap().as_ptr())));
        }
    }
}
