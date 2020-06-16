use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = *arr.iter().nth(0).unwrap() as usize;
    let clouds = arr.iter().cloned().skip(1).collect::<Vec<_>>();

    let mut q = vec![(0usize,0usize)];

    let mut ret;
    'outer: loop {
        let mut temp = vec![];
        q.sort();
        q.dedup();
        q.reverse();
        for (index,count) in q.iter().take(2) {
            if *index == n -1 {
                ret = *count;
                break 'outer;
            }
            if *index + 1 < n && clouds[*index+1] == 0 {
                temp.push((*index+1,*count+1));
            }
            if *index + 2 < n && clouds[*index+2] == 0 {
                temp.push((*index+2,*count+1));
            }
        }
        std::mem::swap( & mut temp, & mut q );
    }

    println!("{}",ret);
}
