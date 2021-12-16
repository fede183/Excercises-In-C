pub fn run() {
    
    // Hello world
    print!("Hello, world!");

    // Basic Formatting
    println!("Number: {}", 1);
    println!("{} is from {}", "Federico", "Argentina");

    // Arguments
    println!("{0} likes {1}, {0} dislikes {2}", "Alejandro", "Magdalenas", "Churros");

    // Named Arguments
    println!("{name} likes {firstFood}, {name} dislikes {secondFood}", 
    name = "Alejandro", 
    firstFood = "Magdalenas", 
    secondFood = "Churros");

    // Placeholders traits
    println!("Binary: {:b}, Hex: {:x}, Octal: {:o}", 
    10, 10, 10);


    // Placeholders traits conditional
    println!("{:?}", (12, true, "hello"));

}