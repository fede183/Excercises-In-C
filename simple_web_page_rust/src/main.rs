#[macro_use] extern crate rocket;
use std::io;
use rocket::tokio::time::{sleep, Duration};
use rocket::tokio::task::spawn_blocking;
use rocket::response::content::Json;

#[get("/")]
fn index() -> &'static str {
    "Hello"
}

#[get("/world")]
fn world() -> &'static str {
    "Hello, world!"
}

#[get("/hello/<name>")]
fn hello(name: &str) -> String {
    format!("Hello, {}!", name)
}

#[get("/delay/<seconds>")]
async fn delay(seconds: u64) -> String {
    sleep(Duration::from_secs(seconds)).await;
    format!("Waited for {} seconds", seconds)
}

#[get("/blocking_task")]
async fn blocking_task() -> io::Result<Vec<u8>> {
    // In a real app, use rocket::fs::NamedFile or tokio::fs::File.
    let vec = spawn_blocking(|| std::fs::read("data.txt")).await
        .map_err(|e| io::Error::new(io::ErrorKind::Interrupted, e))??;

    Ok(vec)
}

#[get("/user/<id>")]
fn user(id: usize) -> String {
    format!("Hello User, {}!", id)
}

#[get("/user/<id>", rank = 2)]
fn user_int(id: isize) -> String {
    format!("Hello User id, {}!", id)
}

#[get("/user/<id>", rank = 3)]
fn user_str(id: &str) -> String {
    format!("Hello User name, {}!", id)
}

#[get("/foo/<_>/bar")]
fn foo_bar() -> &'static str {
    "Foo _____ bar!"
}

#[get("/<_..>")]
fn everything() -> &'static str {
    "Hey, you're here."
}

#[get("/success")]
fn json_success() -> Json<&'static str> {
  Json("{
    'status': 'success',
    'message': 'Hello API!'
  }")
}

#[rocket::main]
async fn main() {
    rocket::build()
        .mount("/", routes![index, hello, delay, blocking_task, user, user_int, user_str,
        foo_bar, everything, json_success])
        .mount("/hello", routes![world])
        .launch()
        .await;
}