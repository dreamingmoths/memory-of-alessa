use std::ffi::{CString};

#[unsafe(no_mangle)]
pub extern "C" fn pretty_float(f: f32) -> *mut i8 {
    let result = CString::new(format!("{}", f)).unwrap();
    result.into_raw()
}
