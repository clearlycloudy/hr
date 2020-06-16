use std::io::{self, Read};
use std::cmp;
use std::collections::HashSet;
use std::collections::HashMap;

fn build_kmp_table( pattern: &[u8], table: & mut Vec<i32> ){
    let mut pos = 1isize; //position in table
    let mut cnd = 0isize; //index in pattern of next character of the current candidate substring
    table.clear();
    table.resize( pattern.len()+1, -1 );

    //build a backtracking path for previously matched characters

    while pos < pattern.len() as isize {
        if pattern[pos as usize] == pattern[cnd as usize] {
            table[pos as usize] = table[cnd as usize];
            pos += 1;
            cnd += 1;
        } else {
            table[pos as usize] = cnd as i32;
            cnd = table[cnd as usize] as isize;
            while cnd >= 0 && pattern[pos as usize] != pattern[cnd as usize] {
                cnd = table[cnd as usize] as isize;
            }
            pos += 1;
            cnd += 1;
        }
    }
    table[pos as usize] = cnd as i32;
}

fn kmp_match( body: &[u8], pattern: &[u8], table: &[i32], loc: & mut Vec<usize> ) {

    let mut j = 0i32; //in body
    let mut k = 0i32; //in pattern

    while j < body.len() as i32{
        if pattern[k as usize] == body[j as usize] {
            j += 1;
            k += 1;
            if k as usize == pattern.len() {
                //found an instance here
                assert!( (j-k) >= 0 );
                loc.push( (j-k) as usize);
                k = table[k as usize];
            }
        } else {
            k = table[k as usize];
            if k < 0 {
                k += 1;
                j += 1;
            }
        }
    }
}

fn bit_add( total_size: u32, mut index: u32, val: i32, v: & mut Vec<i32>, segs: & mut HashMap<u32,HashSet<(u32,u32)> >, segs_exc: & mut HashMap<u32,HashSet<(u32,u32)> >, start: u32, end: u32 ){
    let orig_index = index;
    index += 1;
    while index < total_size {
        // v[index as usize] += val;
        if val > 0 {
            if !segs.contains_key( &index ) {
                segs.insert( index, HashSet::new() );
            }
            segs.get_mut( &index ).unwrap().insert( (start+1,end+1) );
        } else {
            if !segs_exc.contains_key( &index ) {
                segs_exc.insert( index, HashSet::new() );
            }
            segs_exc.get_mut( &index ).unwrap().insert( (start+1,end+1) );
        }
        let temp = (!index).wrapping_add(1) & index;
        index += temp;
    }
}

// fn bit_query( total_size: u32, mut index: u32, v: & mut Vec<i32> ) -> i32 {
//     index += 1;
//     //sum from 1..
//     let mut ret = 0;

//     while index > 0 {
//         ret += v[index as usize];
//         let temp = (!index).wrapping_add(1) & index;
//         index -= temp;
//     }

//     ret
// }

fn bit_remove_segs( total_size: u32, mut index: u32, v: & mut Vec<i32>, segs: & mut HashMap<u32,HashSet<(u32,u32)> >, segs_exc: & mut HashMap<u32,HashSet<(u32,u32)> >, segs_removed: & mut HashSet<(u32,u32)> ) {

    index += 1;

    let mut s = HashSet::new();
    let mut s_exc = HashSet::new();
    {
        while index > 0 {
            match segs.get( &index ) {
                Some(x) => {
                    for i in x.iter() {
                        s.insert(*i);
                    }
                },
                _ => {},
            }
            match segs_exc.get( &index ) {
                Some(x) => {
                    for i in x.iter() {
                        s_exc.insert(*i);
                    }
                },
                _ => {},
            }
            let temp = (!index).wrapping_add(1) & index;
            index -= temp;
        }
    }
    for i in s.difference( &s_exc ) {
        segs_removed.insert(*i);
    }
}

fn main() {

    const M : u32 = 1_000_000_007;
    
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let mut iio = buffer.split_whitespace();
    
    let tc = iio.next().unwrap().parse::<usize>().unwrap();

    for _ in 0..tc {
        // println!("testcase");
        let s : Vec<_> = iio.next().unwrap().chars().map(|x| x as u8).collect();
        let p : Vec<_> = iio.next().unwrap().chars().map(|x| x as u8).collect();
        let q = iio.next().unwrap().parse::<usize>().unwrap();
        // println!("{:?} {:?} {}", s,p,q);

        let mut loc = vec![];
        let mut table = vec![];
        
        build_kmp_table(p.as_slice(), &mut table);
        // println!("table: {:?}", table);
        kmp_match(s.as_slice(),p.as_slice(),&mut table, &mut loc);
        // println!("loc: {:?}", loc);

        const total_bit_size : u32 = 262144;
        let mut v = vec![0;262144]; //2^18 items > 200000 constraint

        let mut segs = HashMap::new();
        let mut segs_remove = HashSet::new();
        let mut segs_exc = HashMap::new();
        
        //populate v
        let mut count = 0i32;
        for i in loc.iter() {
            let a = *i as u32;
            let b = a + p.len() as u32-1;

            bit_add( total_bit_size, a, 1, & mut v, & mut segs, &mut segs_exc, a, b );
            bit_add( total_bit_size, b+1, -1, & mut v, & mut segs, &mut segs_exc, a, b );
            count += 1;
        }

        // println!("segs: {:?}", segs);
        // println!("segs exclude: {:?}", segs_exclude);
        
        if count == 0 {
            for counter in 0..q {
                let x = iio.next().unwrap().parse::<u32>().unwrap();
                let c = iio.next().unwrap();
            }
            println!("0");
        } else {
            let mut ans = None;
            for counter in 0..q {
                let x = iio.next().unwrap().parse::<u32>().unwrap();
                let c = iio.next().unwrap().chars().nth(0).unwrap() as u8;
                // println!("{} {}", x,c);

                // let queried = bit_query( total_bit_size,x,&mut v);
                // println!("queried: {}", queried);
                
                if ans.is_none() {

                    if s[x as usize] != c {
                        bit_remove_segs( total_bit_size, x, & mut v, & mut segs, &mut segs_exc, & mut segs_remove );

                        // println!("segs removed: {}", segs_remove.len() );
                        if segs_remove.len() as i32 >= count {
                            ans = Some( counter+1 );
                        }
                    }
                }
            }
            match ans {
                Some(x) => {
                    println!("{}", x );
                },
                _ => {
                    println!("-1");
                }
            }
        }
    }
}
