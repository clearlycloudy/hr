use std::io::{self, Read};
use std::collections::HashSet;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = arr[0] as i64;

    for x in arr[1..].chunks(10) {

        let mut ms = HashSet::new();

        let mychunks = x[..].chunks(2);
        
        for j in x[..].chunks(2) {
            ms.insert( (j[0], j[1] ) );
        }

        let mut counts = vec![];
        let mut data = vec![];
        let mut index = 0;
        for j in x[..].chunks(2) {
            let mut neighbour_count = 0;
            let neighbour_1 = ( j[0]-1, j[1] );
            let neighbour_2 = ( j[0]+1, j[1] );
            let neighbour_3 = ( j[0], j[1]-1 );
            let neighbour_4 = ( j[0], j[1]+1 );
            if ms.contains( &neighbour_1 ) {
                neighbour_count += 1;
            }
            if ms.contains( &neighbour_2 ) {
                neighbour_count += 1;
            }
            if ms.contains( &neighbour_3 ) {
                neighbour_count += 1;
            }
            if ms.contains( &neighbour_4 ) {
                neighbour_count += 1;
            }

            data.push( ( j[0], j[1] ) );
            counts.push( ( neighbour_count, index ) );
            index += 1;
        }

        counts.sort();

        let mut valid = true;
        for x in &counts[0..3] {
            if x.0 != 1 {
                valid = false;
            }
        }
        if counts[3].0 != 2 {
            valid = false;
        }
        if counts[4].0 != 3 {
            valid = false;
        }

        // println!("{:?}", counts );
        
        if !valid {
            println!("No");
        } else {

            assert!( counts[4].1 >= 0 );
            let a = data[counts[4].1 as usize];
            
            // println!("a: {:?}",a);
            
            let mut count_x = 1;
            let mut count_y = 1;
            for j in 1..3 {
                let x = a.0 - j;
                let y = a.1;
                if ms.contains( &(x,y) ) {
                    count_x += 1;
                } else {
                    break;
                }
            }
            for j in 1..3 {
                let x = a.0 + j;
                let y = a.1;
                if ms.contains( &(x,y) ) {
                    count_x += 1;
                } else {
                    break;
                }
            }
            for j in 1..3 {
                let x = a.0;
                let y = a.1-j;
                if ms.contains( &(x,y) ) {
                    count_y += 1;
                } else {
                    break;
                }
            }
            for j in 1..3 {
                let x = a.0;
                let y = a.1+j;
                if ms.contains( &(x,y) ) {
                    count_y += 1;
                } else {
                    break;
                }
            }

            let val = ( count_x, count_y );
            // println!("{:?}", val );
            if val == (3,3) {
                println!("Yes");
            } else {
                println!("No");
            }
        }
    }
    
}
