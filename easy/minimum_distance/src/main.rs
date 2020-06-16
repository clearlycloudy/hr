use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let inp : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = *inp.iter().nth(0).unwrap() as usize;
    let arr = inp.iter().cloned().skip(1).collect::<Vec<_>>();

    let mut hm = HashMap::new();
    
    for (idx,val) in arr.iter().enumerate() {
        if !hm.contains_key(val) {
            hm.insert(*val,vec![]);
        }
        let v = hm.get_mut(val).unwrap();
        v.push(idx as isize );
    }

    let mut shortest_dist = None;
    
    for (key,mut vals) in hm.iter_mut() {
        if vals.len() > 1 {
            vals.sort();
            for i in 1..vals.len(){
                let diff = (vals[i]-vals[i-1]).abs();
                if shortest_dist.is_none() {
                    shortest_dist = Some(diff);
                } else if shortest_dist.unwrap() > diff {
                    shortest_dist = Some(diff);
                }
            }
        }
    }

    match shortest_dist {
        Some(x) => {println!("{}",x);},
        _ => {println!("-1")},
    }
}
