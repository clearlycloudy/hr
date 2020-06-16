use std::io::{self, Read};
use std::collections::HashMap;

#[derive(Clone, Copy, Debug)]
struct Trie {
    k: [usize;26],
    count: u32,
    prev: isize,
    letter: u8,
}

impl Default for Trie {
    fn default() -> Self {
        Trie { k: [ std::usize::MAX as usize; 26 ], count: 0, prev: -1, letter: 0xff }
    }
}

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    let mut idx_next = 1usize;
    let mut order = 1usize;
    let mut b = vec![ Trie::default(); 1_000_001 ];

    handle.read_to_string(&mut buffer).unwrap();

    let mut arr = buffer.split_whitespace().collect::<Vec<_>>();
    let s = arr.iter().skip(1).collect::<Vec<_>>();

    let mut order : Vec<(usize,u32)> = vec![];
    //---
    
    for i in s.iter() {

        let mut idx = 0;
        let mut added_first_new_node = false;
        
        for (k,j) in i.chars().enumerate() {

            let c = j as usize - 'a' as usize;

            if b[idx].k[c] != std::usize::MAX {
                //go to the next node that already exists
                idx = b[idx].k[c] as usize;
            } else {
                //add new node
                b[idx].k[c] = idx_next;
                b[idx_next as usize].prev = idx as isize; //save parent idx for backtrace later
                if !added_first_new_node {
                    order.push( ( idx_next as usize, 1 ) ); //save order of arrival
                    added_first_new_node = true;
                }
                idx = idx_next as usize;
                b[idx].letter = c as u8;
                idx_next += 1;
            }
        }
        if idx != 0 {
            b[idx].count += 1;
        }
        if !added_first_new_node {
            //means the name overlaps over a previous person and thus no new node was added
            order.push( ( idx, b[idx].count) ); //save order of arrival and count
        }
    }

    // println!("{:?}", &b[0..idx_next as usize]);
    // println!("{:?}", order );

    //recover names from order of arrival and backtrace
    for i in order {

        let mut idx = i.0 as isize;
        let count = i.1;

        let mut v = vec![];

        while idx != -1 && idx != 0 {
            v.push( b[idx as usize].letter as u8 + 'a' as u8 );
            idx = b[idx as usize].prev;
        }
        v.reverse();

        use std::str;
        let ss = str::from_utf8(v.as_slice()).unwrap();
        
        if count > 1 {
            println!("{} {}", ss, count );
        } else {
            println!("{}", ss );
        }
    }
}
