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

fn exp(base: u128, exp: u128) -> u128 {
    let mut result = base;
    if exp == 0 { return 1 }
    for _ in 1..exp {
        result *= base;
    }
    return result
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
            Some(i) => {
                if i>base-1 { return None };
                counter += i * exp(base, exponent);
            },
        }
        exponent+= 1;
    }
    return Some(counter)
}

fn print_num(num: String, base: Option<String>) {
    let new_base;
    match base {
        None => new_base = Some(10),
        Some(i) => new_base = parse_num(i),
    }
    match parse_num(num) {
        None => println!("Invalid input number"),
        Some(i) => match new_base { // Probably a better way to do this
            Some(2) => println!("0b{:b}", i),
            Some(8) => println!("0{:o}", i),
            Some(16) => println!("0x{:x}", i),
            Some(10) => println!("{}", i),
            None => println!("{}", i), // can this be done on the same line?
            Some(x) => println!("Invalid base input: {}", x),
        }
    }
}

fn help() {
    println!("Usage: con input base");
    println!("");
    println!("For example con 0b11 16, which results in 0x3");
    println!("Inputs are interpreted by their prefix so: 0b (binary), 0x (hex), 0 (octal) and either 0d or nothing for base 10");
    println!("Available bases for formatting output are 2, 8, 10, 16");
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let name = args.get(1);
    match args.get(1) { // 1 since the previous get consumed it
        Some(num) => if num == "help" || num == "--help" || num == "-h" { help(); }
        else {
            print_num(num.to_string(), args.get(2).cloned());
        },
        None => println!("Incorrect usage, should be {:?} NUM. Run 'con help'", name),
    }
}
