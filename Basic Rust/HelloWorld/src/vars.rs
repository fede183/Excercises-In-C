pub fn run() {
    
    let mut name = "Federico"; 
    let place = "Argentina";

    // Basic Formatting
    println!("{} is from {}", name, place);

    name = "Alejandro";
    // Arguments
    println!("{0} likes {1}, {0} dislikes {2}", name, "Magdalenas", "Churros");

    let x = 5;

    let x = x + 1;

    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {}", x);
    }

    println!("The value of x is: {}", x);
}