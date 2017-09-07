use keyvi_string::KeyviString;
use bindings::*;

pub struct KeyviMatch {
    match_ptr_: *mut root::keyvi_match,
}

impl KeyviMatch {
    pub fn new(match_ptr: *mut root::keyvi_match) -> KeyviMatch {
        KeyviMatch { match_ptr_: match_ptr }
    }

    pub fn get_value(&self) -> String {
        let c_buf = unsafe { root::keyvi_match_get_value_as_string(self.match_ptr_) };
        KeyviString::new(c_buf).to_owned()
    }

    pub fn is_empty(&self) -> bool {
        unsafe { root::keyvi_match_is_empty(self.match_ptr_) }
    }

    pub fn get_score(&self) -> f64 {
        unsafe { root::keyvi_match_get_score(self.match_ptr_) }
    }

    pub fn matched_string(&self) -> String {
        let c_buf = unsafe { root::keyvi_match_get_matched_string(self.match_ptr_) };
        KeyviString::new(c_buf).to_owned()
    }
}

impl Drop for KeyviMatch {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_match_destroy(self.match_ptr_);
        }
    }
}
