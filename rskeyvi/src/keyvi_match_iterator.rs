use bindings::*;
use keyvi_match::KeyviMatch;

pub struct KeyviMatchIterator {
    ptr_: *mut root::keyvi_match_iterator,
}

impl KeyviMatchIterator {
    pub fn new(ptr: *mut root::keyvi_match_iterator) -> KeyviMatchIterator {
        KeyviMatchIterator { ptr_: ptr }
    }
}

impl Iterator for KeyviMatchIterator {
    type Item = KeyviMatch;

    fn next(&mut self) -> Option<KeyviMatch> {
        let empty = unsafe { root::keyvi_match_iterator_empty(self.ptr_) };
        if empty {
            return None;
        } else {
            let ret = Some(KeyviMatch::new(unsafe { root::keyvi_match_iterator_dereference(self.ptr_) }));
            unsafe { root::keyvi_match_iterator_increment(self.ptr_) };
            return ret;
        }
    }
}

impl Drop for KeyviMatchIterator {
    fn drop(&mut self) {
        unsafe {
            root::keyvi_match_iterator_destroy(self.ptr_);
        }
    }
}
