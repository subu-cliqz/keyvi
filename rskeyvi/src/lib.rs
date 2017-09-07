#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));


mod dictionary;
mod keyvi_string;
mod keyvi_match;
mod bindings;

use dictionary::Dictionary;
use keyvi_match::KeyviMatch;

#[cfg(test)]
mod tests {
    use super::*;


    #[test]
    fn dictionary_size() {
        let dict = Dictionary::new("test.kv");
        assert_eq!(dict.size(), 3);
    }

    #[test]
    fn match_string() {
        let m = Dictionary::new("test.kv").get("a");
        assert_eq!(m.matched_string(), "a");
    }

    #[test]
    fn match_value() {
        let m = Dictionary::new("test.kv").get("a");
        assert_eq!(m.get_value(), "[12,13]");
    }

    #[test]
    fn match_is_empty() {
        let m = Dictionary::new("test.kv").get("a");
        assert_eq!(m.is_empty(), false);
    }
}
