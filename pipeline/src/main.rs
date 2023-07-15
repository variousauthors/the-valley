use std::{fs::File, io::Write};

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
    // file to read
    #[arg(short, long)]
    in_file: String,
}

fn main() {
    let args = Args::parse();

    println!("Hello {}!", args.in_file);

    let result = {
        let result = match std::fs::read_to_string(&args.in_file) {
            Ok(data) => data,
            Err(error) => panic!("Problem: {:?}", error),
        };

        serde_json::from_str::<Map>(&result)
    };

    /* this is throwing because the layers in the exported json is not homogeneous
     * so it doesn't match the type Map
     */
    let map = match result {
        Ok(data) => data,
        Err(error) => panic!("Problem: {:?}", error),
    };

    // convert each datum into a hex string
    let bytes: Vec<String> = map.layers[0].data.iter().map(|n| {
        format!("{:#04x}", n - 1)
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

    // reduce the rows to strings
    let final_bytes = rows.iter().map(|row| {
        row.iter().fold("db ".to_string(), |acc, &el| {
            acc + el + ", "
        })
    }).reduce(|acc, el| {
        acc + "\n" + &el
    }).unwrap();

    fn write_stuff(out_file: &String, bytes: &String) -> std::io::Result<()> {
        let mut file = File::create(out_file)?;

        let filename = match out_file.split("/").last() {
            Some(filename) => filename,
            None => "",
        };

        let name = filename
            .replace("-", "_")
            .replace(".inc", "");

        let inc_name = name.to_ascii_uppercase();

        let data = format!("
IF !DEF({1}_INC)
{1}_INC = 1

Section \"{0}\", ROM0
{0}:
{2}

{0}AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        ", name, inc_name, bytes);

        file.write_all(data.as_bytes())?;
        Ok(())
    }
    
    let out_file = args.in_file.replace(".json", ".inc");

    let _ = write_stuff(&out_file, &final_bytes);
}