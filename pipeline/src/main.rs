// clap docs https://docs.rs/clap/latest/clap/
use clap::Parser;

use serde_derive::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct Map {
    height: i8,
    width: i8,
    layers: Vec<Layer>
}

#[derive(Serialize, Deserialize, Debug)]
struct Layer {
    data: Vec<i8>
}



/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Name of the person to greet
    #[arg(short, long)]
    in_file: String,

    /// Name of the person to greet
    #[arg(short, long)]
    out_file: String,
}

fn main() {
    let args = Args::parse();

    println!("Hello {}!", args.in_file);

    let result = {
        let result = match std::fs::read_to_string(&args.in_file) {
            Ok(data) => data,
            Err(error) => panic!("Problem: {:?}", error),
        };

        // Load the MissyFoodSchedule structure from the string.
        serde_json::from_str::<Map>(&result)
    };

    let map = match result {
        Ok(data) => data,
        Err(error) => panic!("Problem: {:?}", error),
    };

    println!("height {}!", map.height);
    println!("width {}!", map.width);
    println!("layer {:?}!", map.layers);
}