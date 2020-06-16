use std::io::{self, Read};
use std::collections::{ HashMap, HashSet };

#[derive(Debug)]
struct Node {
    l: isize, //0
    r: isize, //1
    idx: usize,
}

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u64>().unwrap() ).collect();
    
    let n = arr[0] as usize;
    let k = arr[1];

    let mut accum = 0;
    let mut sum : Vec<u64> = vec![0];
    let mut ns = vec![ Node{ l:-1, r: -1, idx: 0 } ]; //init with root node

    //init tree with 0b0....0
    //30bits are needed for number up to 10^9
    for i in 0..30 {
        if i != 29 {
            ns.push( Node { l: 1 + i + 1, r: -1, idx: 1 + i as usize } );
        } else {
            ns.push( Node { l: -1, r: -1, idx: 1 + i as usize } );
        }
        sum.push( 1u64 );
    }
    ns[0].l = 1;
    
    let mut ans : u64 = 0;

    for i in 0..n {
        let v = arr[2+i];
        accum = accum ^ v;
        //calculate number of previously inserted partial xor sum that is less than k when xored with current accum value
        let mut cur_idx = 0;
        'bp: for j in 0..30 {
            let bit_accum = if (accum >> (29-j)) & 0b01 > 0 { 1 } else { 0 };
            let bit_k = if (k >> (29-j)) & 0b01 > 0 { 1 } else { 0 };
            match (bit_accum,bit_k) {
                (0,0) => { //go L branch
                    if ns[cur_idx].l != -1 {
                        cur_idx = ns[cur_idx].l as usize;
                    } else {
                        break 'bp;
                    }
                }, 
                (0,1) => { //sum L branch since they are all smaller, go R branch
                    if ns[cur_idx].l != -1 {
                        ans += sum[ ns[cur_idx].l as usize ];
                        // println!("{}: sum L branch: {}", i, ans );
                    }
                    if ns[cur_idx].r != -1 {
                        cur_idx = ns[cur_idx].r as usize;
                    } else {
                        break 'bp;
                    }   
                }, 
                (1,0) => {//go R branch
                    if ns[cur_idx].r != -1 {
                        cur_idx = ns[cur_idx].r as usize;
                    } else {
                        break 'bp;
                    }
                },
                (1,1) => { //sum R branch since when xored is smaller than k, go L branch
                    if ns[cur_idx].r != -1 {
                        ans += sum[ ns[cur_idx].r as usize ];
                        // println!("{}: sum R branch: {}", i, ans );
                    }
                    if ns[cur_idx].l != -1 {
                        cur_idx = ns[cur_idx].l as usize;
                    } else {
                        break 'bp;
                    }
                }, 
                _ => {panic!();},
            }
        }
        
        //insert new accumulated value
        cur_idx = 0;
        for j in 0..30 {
            let bit_accum = if (accum >> (29-j)) & 0b01 > 0 { 1 } else { 0 };
            match bit_accum {
                0 => { //L branch
                    if ns[cur_idx].l == -1 { //new node creation
                        let new_idx = ns.len();
                        ns.push( Node { l: -1, r: -1, idx: new_idx } );
                        sum.push( 0 );
                        ns[cur_idx].l = new_idx as isize;
                    }
                    cur_idx = ns[cur_idx].l as usize;
                    sum[cur_idx] += 1;
                },
                1 => {
                    if ns[cur_idx].r == -1 { //new node creation
                        let new_idx = ns.len();
                        ns.push( Node { l: -1, r: -1, idx: new_idx } );
                        sum.push( 0 );
                        ns[cur_idx].r = new_idx as isize;
                    }
                    cur_idx = ns[cur_idx].r as usize;
                    sum[cur_idx] += 1;
                },
                _ => { panic!(); },
            }
        }
    }
    // println!("{:?}", ns );
    println!("{}",ans);
}
