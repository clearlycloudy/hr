 
use std::io::{self, Read};
use std::cmp;
use std::mem;
use std::collections::HashSet;
use std::collections::HashMap;

fn find_gcd( mut a: i32, mut b: i32 ) -> i32 {
    if b < a {
        mem::swap( & mut a, & mut b );
    }
    let mut r = b % a;
    while r != 0 {
        b = r;
        if b < a {
            mem::swap( & mut a, & mut b );
        }
        r = b % a;
    }
    return a
}

#[cfg(test)]
fn test_gcd() {
    assert_eq!( 18, find_gcd(36, 18) );
    assert_eq!( 2, find_gcd(10, 4) );
}

struct dsu {
    id: Vec< i32 >,
    rank: Vec< i32 >,
    size: Vec< i32 >,
}

impl dsu {
    fn new( s: usize ) -> dsu {
        let mut array = vec![ 0i32; s ];
        let mut rank = vec![ 0i32; s ];
        let mut size = vec![ 1i32; s ];
        for i in 0..s {
            array[i] = i as i32;
        }
        dsu {
            id: array,
            rank: rank,
            size: size,
        }
    }
    fn find_with_path_compression( & mut self, id: i32 ) -> i32 {
        let mut current = self.id[id as usize];
        if current != self.id[current as usize] {
            let updated = self.find_with_path_compression( current );
            self.id[id as usize] = updated;
        }
        self.id[id as usize]
    }
    fn attach( & mut self, from: i32, to: i32 ) {
        self.id[from as usize] = to;
        self.size[to as usize] += self.size[from as usize];
    }
    fn union( & mut self, a: i32, b: i32 ) -> bool {
        let id_a = self.find_with_path_compression( a );
        let id_b = self.find_with_path_compression( b );
        if id_a == id_b {
            false
        } else {
            //compare ranks and attach the smaller rank to the bigger rank
            if self.rank[id_a as usize] == self.rank[id_b as usize] {
                self.rank[id_b as usize] += 1;
                self.attach( id_a, id_b );
            } else if self.rank[id_a as usize] < self.rank[id_b as usize] { 
                self.attach( id_a, id_b );               
            } else {
                self.attach( id_b, id_a );
            }
            true
        }
    }
}


fn pow_modulus( base: i32, mut exp: i32, m: i32 ) -> i32 {
    let mut ans = 1;
    let mut base_accum = base as i64;
    while exp > 0 {
        if exp & 0x01 > 0 {
            ans = ( ans * base_accum ) % m as i64;
        }
        exp = exp >> 1;
        base_accum = (base_accum * base_accum) % m as i64;
    }
    ans as i32
}

#[cfg(test)]
fn test_pow(){
    assert_eq!( 8, pow_modulus( 2, 3, 1e9 as i32 ) );
    assert_eq!( 64, pow_modulus( 4, 3, 1e9 as i32 ) );
}

fn main() {
    
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let str_iter = buffer.split_whitespace();
    let data = str_iter.map(|x| x.parse::<i32>().unwrap() ).collect::<Vec<i32>>();

    let mut it = data.iter();
    let num_tests = *it.next().unwrap();

    //precompute factors of numbers up to lim
    let lim = 1e6 as isize;

    let mut factors = vec![ vec![]; lim as usize + 1];
    let mut processed = vec![ false; lim as usize + 1];
    for i in 2..lim+1 {
        if processed[i as usize] == false {
            let mut j = i;
            while j <= lim {
                processed[j as usize] = true;
                factors[j as usize].push(i);
                j += i;
            }
        }
    }

    for _ in 0..num_tests {
        let dim = *it.next().unwrap();
        let mut hs = HashSet::new();
        let mut count_ones = 0;
        let mut nums = vec![];
        for i in 0..dim {
            let next = *it.next().unwrap();
            nums.push(next);
            //get factors for this number
            for j in factors[next as usize].iter() {
                hs.insert(j);
            }
            if next == 1 {
                count_ones += 1;
            }
        }
        //compress factors into contiguous range
        let mut hm = HashMap::new();
        for (k,v) in hs.iter().enumerate() {
            hm.insert( *v, k );
        }
        let mut count_unioned = 0;
        let mut disjoint_set = dsu::new(hm.len());
        for i in nums.iter() {
            for j in 0..factors[*i as usize].len() as i32 -1 {
                let compressed_id_1 = hm.get(&factors[*i as usize][j as usize]).unwrap();
                let compressed_id_2 = hm.get(&factors[*i as usize][j as usize +1]).unwrap();
                let compressed = disjoint_set.union( *compressed_id_1 as i32, *compressed_id_2 as i32 );
                count_unioned += if compressed { 1 } else { 0 };
            }
        }
        let count_connected_components = hm.len() - count_unioned + count_ones;

        //compute number of configuration when placing connected components in 2 sets
        //discount 2 configurations for all 0 and all 1 because either set cannot be empty
        let m = 1e9 as i32 + 7;
        let mut num_configurations = pow_modulus( 2, count_connected_components as i32, m ) - 2;

        if num_configurations < 0 {
            num_configurations += m;
        }

        println!("{}", num_configurations );
    }
}
