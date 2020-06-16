fn main() {

    use std::io::{self, Read};
    use std::cmp::Ordering;
    use std::collections::{HashMap,HashSet};
    use std::mem;

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let input_strs = buffer.split_whitespace().map( |x| x.parse::<i64>().unwrap() ).collect::< Vec<i64> >();

    let n = *input_strs.iter().nth(0).unwrap();

    let nums = input_strs.iter().skip(1).cloned().collect::<Vec<i64>>();

    let mut sorted = nums.clone();
    sorted.sort();

    let mut count = 0;
    for i in 0..n as usize {
        if sorted[i] != nums[i] {
            count += 1;
        }
    }

    if count == 0 {
        println!( "0" );
    } else if count == 2 {
        println!( "1" );
    } else {
        println!( "-1" );
    }

}
