use std::env;

fn get_base(mut num: String) -> u128 {
    let zero = num.remove(0);
    if  zero != '0' {
        return 10;
    } 
    match num.remove(0) {
        'x' => return 16,
        'b' => return 2,
        'd' => return 10,
        _ => return 8,
    }
}

fn char_to_int(c: char) -> Option<u128> {
    match c {
        '1' => Some(1),
        '2' => Some(2),
        '3' => Some(3),
        '4' => Some(4),
        '5' => Some(5),
        '6' => Some(6),
        '7' => Some(7),
        '8' => Some(8),
        '9' => Some(9),
        '0' => Some(0),
        _ => None,
    }
}

fn exp(mut base: u128, exp: u128) -> u128 {
    for _ in 1..exp {
        base *= base;
    }
    return base
}

fn parse_num(mut num: String) -> Option<u128> {
    let base = get_base(num.clone());
    if base == 16 || base == 2 {
        num.remove(0);
        num.remove(0);
    }
    if base == 8 {
        num.remove(0);
    }

    let mut counter: u128 = 0;
    let mut exponent: u128 = 0;
    for char in num.chars().rev() {
        let bit = char_to_int(char);
        match bit {
            None => return None,
            Some(i) => counter += i * exp(base, exponent),
        }
        exponent+= 1;
    }
    return Some(counter)

}

fn main() {
    let args: Vec<String> = env::args().collect();
    let name = args.get(1);
    match args.get(1) { // 1 since the previous get consumed it
        Some(num) => println!("{:?}", parse_num(num.to_string())),
        None => println!("Incorrect usage, should be {:?} NUM", name),
    }
}
