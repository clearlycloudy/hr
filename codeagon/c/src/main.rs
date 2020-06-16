use std::io::{self, Read};
use std::collections::HashSet;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u32>().unwrap() ).collect();

    let n = arr[0] as usize;

    for i in 0..n {
        let x = arr[1+3*i];
        let l = arr[1+3*i+1];
        let r = arr[1+3*i+2];
        let mut v : u32 = !x;

        let mut check_l = true;
        let mut check_r = true;
        for j in 0..32 {
            let bitpos = 31-j;
            let mut bit_v = (v >> bitpos & 0b1) == 0b1;
            let bit_r = (r >> bitpos & 0b1) == 0b1;
            let bit_l = (l >> bitpos & 0b1) == 0b1;
            
            // println!("pos {}, v {:b}", bitpos, v);

            if check_r {
                match (bit_r, bit_v) {
                    (false,true) => {
                        let mask : u32 = !(1u32 << bitpos);
                        v &= mask;
                        bit_v = false;
                        check_l = true;
                        check_r = false;
                    },
                    _ => {},
                }
            }

            if check_l {
                match (bit_l, bit_v) {
                    (true,false) => {
                        v |= ( 1u32 << bitpos ) as u32;
                        bit_v = true;
                        check_r = true;
                        check_l = false;
                    },
                    _ => {},
                }
            }
        }

        println!("v1:{}", v);
        
        // for j in 0..32 {
        //     let bitpos = 31-j;
        //     let bit_v = (v >> bitpos & 0b1) == 0b1;
        //     let bit_l = (l >> bitpos & 0b1) == 0b1;
            
        //     let cont = match (bit_l, bit_v) {
        //         (false,false) => { true },
        //         (false,true) => { false },
        //         (true,false) => {
        //             v |= ( 1u32 << bitpos ) as u32;
        //             true
        //         },
        //         (true,true) => { true },
        //     };

        //     if !cont {
        //         // println!("bit break:{}, v:{}", bitpos, v);
        //         break;
        //     }   
        // }

        // println!("v2:{}", v);
        
        let ans : u32= v ^ x;

        println!("{}", ans );
    }
}
