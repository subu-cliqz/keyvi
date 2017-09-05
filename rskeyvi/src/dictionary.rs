include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::ffi::CString;


pub struct Dictionary {
    dict: *mut root::keyvi_dictionary,
}

impl Dictionary {
    pub fn new(filename: &str) -> Self {
        unsafe {
            Dictionary {
                dict: root::keyvi_create_dictionary(CString::new(filename).unwrap().as_ptr())
            }
        }
    }

    pub fn statistics(&self) -> String {
        unsafe {
            CString::from_raw(root::keyvi_dictionary_get_statistics(self.dict)).into_string().unwrap()
        }
    }

    pub fn size(&self) -> u64 {
        unsafe {
            return root::keyvi_dictionary_get_size(self.dict);
        }
    }
}

impl Drop for Dictionary {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_dictionary_destroy(self.dict);
        }
    }
}
