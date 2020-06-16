use std::io::{self, Read};
// use std::collections::HashMap;

#[derive(Clone, Copy, Debug)]
enum Node {
    Op {
        op_type: u8,
        l: usize,
        r: usize,
        accm: i32,
    },
    Val(i32),
    None,
}

impl Default for Node {
    fn default() -> Self { Node::None }
}

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let mut b = vec![ Node::default(); 10_000_000 ];

    let mut idx_new = 0;
    
    let mut v = vec![idx_new]; //stack of ops and inputs
    idx_new += 1;

    let mut sign = vec![ 0i8; 10_000_000 ]; //records sign of variables

    let mut var_idxs = vec![];
    let mut level = vec![ 0u32; 10_000_000 ]; //level in the tree
    
    for i in buffer.chars() {
        match i {
            '-' | '+' | '?' =>{},
            _ => { break; },
        }
        // println!("stack: {:?}", v );
        let idx = *v.last().unwrap();
        let cur_level = level[idx];
        v.pop();
        match i {
            '-' => {
                let n = Node::Op { op_type: '-' as u8, l: idx_new, r: idx_new+1, accm: 0 };
                b[idx] = n;
                v.push(idx_new+1);
                v.push(idx_new);
                level[idx_new] = cur_level + 1;
                level[idx_new+1] = cur_level + 1;
                idx_new += 2;
            },
            '+' => {
                let n = Node::Op { op_type: '+' as u8, l: idx_new, r: idx_new+1, accm: 0 };
                b[idx] = n;
                v.push(idx_new+1);
                v.push(idx_new);
                level[idx_new] = cur_level + 1;
                level[idx_new+1] = cur_level + 1;
                idx_new += 2;
            },
            '?' => {
                match b[idx] {
                    Node::None => {
                        b[idx] = Node::Val(1);
                        var_idxs.push( (level[idx], idx) );
                    },
                    _ => { panic!("unexpected node type: {:?}", b[idx]); },
                }
            },
            _ => {},
        }
    }
    // println!("");
    // dfs_print( b.as_mut_slice(), 0 );
    // println!("");

    // println!("evaluate..");
    dfs_sum( b.as_mut_slice(), 0 );

    let accumulated = if let Node::Op{ accm, .. } = b[0] {
        // println!("accumulated: {}", accm );
        accm
    } else {
        0
    };

    // dfs_print( b.as_mut_slice(), 0 );
    // println!("");

    dfs_print_accm( b.as_mut_slice(), 0 );
    println!("");

    //distribute signs over all variables
    dfs_sign_propagate( b.as_mut_slice(), 0, 1i8, sign.as_mut_slice() );

    let mut var_neg = var_idxs.iter().filter(|x| sign[(*x).1] < 0i8 ).collect::<Vec<_>>();
    let mut var_pos = var_idxs.iter().filter(|x| sign[(*x).1] > 0i8 ).collect::<Vec<_>>();
    println!("neg: {:?}", var_neg);
    println!("pos: {:?}", var_pos);

    if accumulated == 0 {
        for i in var_idxs.iter().filter_map( 
            |x| if let Node::Val(y) = b[x.1] { Some(y) } else { None }
        ) {
            print!("{} ", i );
        }
        println!("");
    } else {
        let pos = if accumulated < 0 {
            var_pos.sort_by( |a,b| b.cmp(a) );
            &var_pos
        } else {
            var_neg.sort_by( |a,b| b.cmp(a) );
            &var_neg
        };

        println!("{:?}",pos);

        assert!( pos.len() > 0 );
        
        let distribute = accumulated.abs() / pos.len() as i32;
        let mut rem = accumulated.abs() % pos.len() as i32;

        for &i in pos.iter() {
            if let &mut Node::Val(ref mut x) = & mut b[i.1] {
                *x += distribute;
                if rem > 0 {
                    *x += 1;
                    rem -= 1;
                }
            }
        }

        for i in var_idxs.iter().filter_map( 
            |x| if let Node::Val(y) = b[x.1] { Some(y) } else { None }
        ) {
            print!("{} ", i );
        }
        println!("");
    }
}

fn dfs_sign_propagate( n: & mut [Node], idx: usize, sign: i8, sign_array: & mut [i8] ) {
    match n[idx] {
        Node::None => {},
        Node::Op{ op_type, l, r, .. } => {

            let sign_propagate = if op_type as char == '+' {
                sign
            } else {
                -1 * sign
            };
            
            dfs_sign_propagate( n, l, sign_propagate, sign_array );
            dfs_sign_propagate( n, r, sign_propagate, sign_array );
        },
        Node::Val(_) => {
            sign_array[idx] = sign;
        },
    }
}

fn dfs_sum( n: & mut [Node], idx: usize ) {
    match n[idx] {
        Node::None => {},
        Node::Op{ op_type, l, r, .. } => {

            dfs_sum( n, l );
            dfs_sum( n, r );
            
            let ( mut sum_l, mut sum_r )  = ( 0i32, 0i32 );

            if let Node::Val(x) = n[l] {
                sum_l += x as i32;
            } else if let Node::Op{accm, ..} = n[l] {
                sum_l += accm;
            }
            if let Node::Val(x) = n[r] {
                sum_r += x as i32;
            } else if let Node::Op{accm, ..} = n[r] {
                sum_r += accm;
            }

            let mut sum;
            
            if op_type as char == '+' {
                sum = sum_l + sum_r;
            } else {
                sum = sum_l - sum_r;                
            }
            
            // n[idx] = Node::Val(sum);
            n[idx] = Node::Op { op_type: op_type, l: l, r: r, accm: sum };
        },
        Node::Val(_) => {},
    }
}

fn dfs_print( n: & mut [Node], idx: usize ) {
    match n[idx] {
        Node::None => {},
        Node::Op{ op_type, l, r, .. } => {
            print!("(");
            dfs_print( n, l );
            print!("{}", op_type as char );
            dfs_print( n, r );
            print!(")");
        },
        Node::Val(x) => { print!( "{}", x ); },
    }
}

fn dfs_print_accm( n: & mut [Node], idx: usize ) {
    match n[idx] {
        Node::None => {},
        Node::Op{ op_type, l, r, accm } => {
            print!("( {} = ", accm);
            dfs_print_accm( n, l );
            print!("{}", op_type as char );
            dfs_print_accm( n, r );
            print!(")");
        },
        Node::Val(x) => { print!( "{}", x ); },
    }
}


