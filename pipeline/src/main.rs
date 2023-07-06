use std::{fs::File, io::Write, fmt::format};

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

    // convert each datum into a hex string
    let mut bytes: Vec<String> = map.layers[0].data.iter().map(|n| {
        format!("{:#04x}", n)
    }).map(|n| {
        // convert the 0x00 bytes to $00 bytes :D
        n.replace("0x", "$")
    }).collect();

    let mut rows: Vec<Vec<&String>> = Vec::<Vec<&String>>::new();

    for y in 0..map.height {
        let mut row = Vec::<&String>::new();

        for x in 0..map.width {
            let index: i32 = <i8 as Into<i32>>::into(y) * <i8 as Into<i32>>::into(map.height) + <i8 as Into<i32>>::into(x);
            let el = &bytes[<i32 as TryInto<usize>>::try_into(index).unwrap()];

            row.push(el);
        }

        rows.push(row);
    }

    fn write_stuff(out_file: &String, bytes: &String) -> std::io::Result<()> {
        let mut file = File::create(out_file)?;
        let bob = format!("
what

{:?}
        ", bytes);

        file.write_all(bob.as_bytes())?;
        Ok(())
    }

    print!("wat {:?}", rows);
}