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

    let mut sum = 0;
    for i in 0..5 {
        sum += i;
    }
    println!("sum al numers of 0 to 5 is {}", sum);


    let mut sum = 0.0;
    for i in 0..5 {
        sum += i as f64;
    }
    println!("sum al numers of 0 to 5 is {}", sum);

    let sum_no_cast = sqr(2.0).to_string();
    let sum_cast = (sqr(2.0) as f64).to_string();

    println!("the sqr of {:.1} is {}", 2.0, sum_no_cast);
    println!("the sqr of {:.1} is {}", 2.0, sum_cast);

    let x = 10;
    let res1 = by_ref(&x);
    let res2 = by_ref(&41);

    println!("{} {}", res1, res2);

    let mut res = 0.0;
    modifies(&mut res);
    println!("res is {}", res);

    array();

    array_slice();
}

fn sqr(x: f64) -> f64 {
    return x * x;
}

fn by_ref(x: &i32) -> i32 {
    *x + 1
}

fn modifies(x: &mut f64) {
    *x = 1.0;
}

fn array() {
    let arr = [10, 20, 30, 40];
    let first = arr[0];
    println!("first {}", first);

    for i in 0..4 {
        println!("[{}] = {}", i, arr[i]);
    }
    println!("length {}", arr.len());
}

fn array_slice() {
    let ints = [1, 2, 3];
    let floats = [1.1, 2.1, 3.1];
    let strings = ["hello", "world"];
    let ints_ints = [[1, 2], [10, 20]];
    println!("ints {:?}", ints);
    println!("floats {:?}", floats);
    println!("strings {:?}", strings);
    println!("ints_ints {:?}", ints_ints);

    let ints = [1, 2, 3, 4, 5];
    let slice1 = &ints[0..2];
    let slice2 = &ints[1..];  // open range!

    println!("ints {:?}", ints);
    println!("slice1 {:?}", slice1);
    println!("slice2 {:?}", slice2);
}