use std::io::{self, Read};


fn find_farthest_node( n: usize, x: usize, partial: &Vec<i64>, ext: &Vec<i64> ) -> usize {
    let mut idx_farthest = ( x as usize -1 + n as usize - 1 ) % n as usize;
    for idx in x as usize -1 .. x as usize -1 + n as usize{
        let l0 = partial[x as usize -1 + n as usize - 1 ] - partial[x as usize -1 ];
        let idx_mod = idx % n as usize;
        let l2 = ext[idx_mod];
        if l2 > l0 {
            idx_farthest = idx % n as usize;
        }
    }
    idx_farthest
}

fn main() {

    use std::collections::{HashMap,HashSet, BinaryHeap};

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let input_strs = buffer.split_whitespace().map( |x| x.parse::<i64>().unwrap() ).collect::< Vec<i64> >();

    let n = *input_strs.iter().nth(0).unwrap();

    let mut rest = input_strs.iter().skip(1);

    let mut w = rest.take(n as usize).cloned().collect::<Vec<i64> >();

    w.resize( n as usize *2, 0i64 );
    for i in 0..n as usize {
        w[n as usize +i] = w[i];
    }
    
    rest = input_strs.iter().skip(1+n as usize);

    let m = *rest.next().unwrap();


    let mut partial = vec![ 0i64; 2*n as usize ];

    for i in 0..2*n as usize {
        partial[i] = w[i];
    }

    for i in 1..2*n as usize {
        partial[i] += partial[i-1];
    }


    let mut ext = vec![ 0i64; n as usize ];

    let mut ext_segs : Vec< Vec< Vec<i64> > > = vec! [ vec![]; n as usize ];
    
    //println!("w: {:#?}", w );

    //println!("paritlal sum: {:#?}", partial );
    
    for _ in 0..m {
        let q_type = *rest.next().unwrap();
        let x = *rest.next().unwrap();
        match q_type {
            1 => {
                let w = *rest.next().unwrap();
                //println!("query 1: {}, {}", x, w);
                //find farthest node
                let idx_farthest = find_farthest_node( n as usize, x as usize, &partial, &ext );
                //println!("farthest node index: {}", idx_farthest + 1 );

                let mut s_max = 0i64;
                let mut s_index = 0usize;
                if ext_segs[idx_farthest].len() > 0 {
                    for j in 0..ext_segs[idx_farthest].len() {
                        let s = ext_segs[idx_farthest][j].iter().sum();
                        if s > s_max {
                            s_max = s;
                            s_index = j;
                        }
                    }
                    ext_segs[idx_farthest][s_index].push( w );
                    ext[idx_farthest] += w;
                } else {
                    //add a new edge and node
                    ext_segs[idx_farthest].push( vec![ w ] );
                    if w > ext[idx_farthest] {
                        ext[idx_farthest] = w;
                    }
                }
            },
            2 => {
                let w = *rest.next().unwrap();
                //println!("query 2: {}, {}", x, w);
                
                //println!( "ext distance before adding: {}", ext[x as usize -1] );
                //add a new edge and node
                ext_segs[x as usize -1].push( vec![ w ] );
                if w > ext[x as usize -1] {
                    ext[x as usize -1] = w;
                }
                //println!( "ext distance after adding: {}", ext[x as usize -1] );
            },
            3 => {
                //println!("query 3: {}", x);
                //find farthest node
                let idx_farthest = find_farthest_node( n as usize, x as usize, &partial, &ext );
                //delete the farthest node
                let mut s_max = 0i64;
                let mut s_index = 0usize;
                for j in 0..ext_segs[idx_farthest].len() {
                    let s = ext_segs[idx_farthest][j].iter().sum();
                    if s > s_max {
                        s_max = s;
                        s_index = j;
                    }
                }

                //println!( "distance before removal: {}", ext[idx_farthest] );
                
                ext_segs[idx_farthest][s_index].pop();
                if ext_segs[idx_farthest][s_index].len() == 0 {
                    ext_segs[idx_farthest].swap_remove(s_index);
                }

                for j in 0..ext_segs[idx_farthest].len() {
                    let s = ext_segs[idx_farthest][j].iter().sum();
                    if s > s_max {
                        s_max = s;
                        s_index = j;
                    }
                }

                if ext_segs[idx_farthest].len() == 0 {
                    ext[idx_farthest] = 0i64;
                } else {
                    ext[idx_farthest] = s_max;
                }

                //println!( "distance after removal: {}", ext[idx_farthest] );
            },
            _ => {
                //println!("query 4: {}", x);
                //print distance to farthest node
                //find farthest node
                let idx_farthest = find_farthest_node( n as usize, x as usize, &partial, &ext );
                let partial_dif = if idx_farthest < x as usize - 1 {
                    partial[ idx_farthest + n as usize ] - partial[ x as usize - 1 ]
                } else {
                    partial[ idx_farthest ] - partial[ x as usize - 1 ]
                };
                let total = partial_dif + ext[idx_farthest as usize];
                //println!( "distance: {}", total );
                println!( "{}", total );
            }
        }
    }
}

