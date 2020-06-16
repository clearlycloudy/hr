use std::io::{self, Read};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let s = arr[0] as i64;

    match s {
        x if x <= 90 => { println!("0 No punishment"); },
        x if x > 90 && x <= 110 => {
            println!("{} Warning", 300 *( x - 90) );
        },
        x => {
            println!("{} License removed", 500*(x-90));
        }
    }
}
