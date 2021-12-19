use std::io::{stdin, stdout, Write};


fn read(input: &mut String) {
    stdout().flush().expect("Fallo al leer");
    stdin().read_line(input).expect("Fallo al leer");
}

fn is_a_number(possible_number: &String) -> bool {
    let possible_values = "0123456789.";
    let chars = possible_number.trim().chars();
    for letter in chars {
        if !possible_values.contains(letter) {
            return false;
        }
    }

    return true;
}

fn main() {
    let mut operator = String::new();
    let mut num1 = String::new();
    let mut num2 = String::new();

    println!("Ingrese el primer número:");
    read(&mut num1);

    if !is_a_number(&num1) {
        println!("Error: debe ingresar un número");
        return;
    }

    println!("Ingrese el segundo número:");
    read(&mut num2);

    if !is_a_number(&num2) {
        println!("Error: debe ingresar número");
        return;
    }
    
    println!("Ingrese operación, debe ser una de estas +-*/:");
    read(&mut operator);

    let num1 : f32 = num1.trim().parse().unwrap();
    let num2 : f32 = num2.trim().parse().unwrap();
    let operator : char = operator.trim().chars().next().unwrap();

    let operators = String::from("+-*/");

    if !operators.contains(operator) {
        println!("Error: operador inválido");
        return;
    }

    if operator == '/' && num2 == 0.0 {
        println!("Error: no se puede dividir por cero");
        return;
    }

    let result : f32 = match operator {
        '+' => num1 + num2,
        '-' => num1 - num2,
        '*' => num1 * num2,
        '/' => num1 / num2,
        _ => 0.0
    };

    println!("El resultado es: {}", result);
}
