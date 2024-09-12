use std::{fs::File, io::Write};
use glob::glob;

// clap docs https://docs.rs/clap/latest/clap/
use clap::Parser;

use serde_derive::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct Map {
    height: u8,
    width: u8,
    layers: Vec<Layer>
}

#[derive(Serialize, Deserialize, Debug)]
struct Layer {
    data: Vec<u8>
}

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    // file to read
    #[arg(short, long)]
    in_file: String,
}

fn process_file (in_file: String) {
    println!("Reading {}", in_file);

    let result = {
        let result = match std::fs::read_to_string(&in_file) {
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

    println!("Map y: {}, x: {}", map.height, map.width);

    // convert each datum into a hex string nibble
    let bytes: Vec<String> = map.layers[0].data.iter().map(|n| {
        format!("{:#02x}", n - 1)
    }).map(|n| {
        // convert the 0x0 nibbles to $0 nibbles :D
        n.replace("0x", "$")
    }).enumerate()
    // fold em nibbles up into bytes
    .fold(Vec::new(), |mut acc, (index, el)| {
        if index % 2 == 0 {
            // if this is the last element append 0
            if index == (map.width as usize) - 1 {
                acc.push(el + "0");
            } else {
                // append the element
                acc.push(el);
            }
        } else {
            // append the element to the last element
            let prev = match acc.pop() {
                Some(data) => data,
                None => panic!("Problem: tried to get last element of an array when there wasn't one"),
            };

            acc.push(prev + &el.replace("$", ""));
        }

        acc
    });

    // now we have to put the bytes into map.height rows, each being map.width / 2 wide
    let mut rows: Vec<Vec<&String>> = Vec::<Vec<&String>>::new();

    for y in 0..map.height {
        let mut row = Vec::<&String>::new();

        for x in 0..(map.width / 2) {
            let index: i32 = <u8 as Into<i32>>::into(y) * <u8 as Into<i32>>::into(map.width / 2) + <u8 as Into<i32>>::into(x);
            let el = &bytes[<i32 as TryInto<usize>>::try_into(index).unwrap()];

            row.push(el);
        }

        rows.push(row);
    }

    // reduce the rows to strings
    let final_bytes = rows.iter().map(|row| {
        row.iter().fold("  db ".to_string(), |acc, &el| {
            acc + el + ", "
        })
    }).reduce(|acc, el| {
        acc + "\n" + &el
    }).unwrap();

    fn write_stuff(out_file: &String, bytes: &String, map: &Map) -> std::io::Result<()> {
        let mut file = File::create(out_file)?;

        let filename = match out_file.split("/").last() {
            Some(filename) => filename,
            None => "",
        };

        let name = kebab_to_camel_case(&filename
            .replace("-", "_")
            .replace(".inc", ""));

        let inc_name = name.to_ascii_uppercase();

        let data = format!("
IF !DEF({1}_INC)
{1}_INC = 1

Section \"{0}\", ROMX, BANK[1]
{0}:
  db {3}, {4}, 
  db HIGH({0}AutoEvents), LOW({0}AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH({0}BumpEvents), LOW({0}BumpEvents)
  db HIGH({0}Entities), LOW({0}Entities)
{2}

{0}AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

{0}BumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

{0}Entities:
  ret

ENDC", name, inc_name, bytes, map.height, map.width);

        file.write_all(data.as_bytes())?;
        Ok(())
    }
    
    let out_file = in_file.replace(".json", ".inc");

    let _ = write_stuff(&out_file, &final_bytes, &map);
}

fn kebab_to_camel_case(s: &str) -> String {
  s.split('-')
      .map(|word| {
          let mut chars = word.chars();
          match chars.next() {
              Some(first) => first.to_ascii_uppercase().to_string() + chars.as_str(),
              None => String::new(),
          }
      })
      .collect()
}

fn main() {
    let args = Args::parse();

    for entry in glob(&args.in_file).expect("Failed to read glob pattern") {
        match entry {
            Ok(path) => match path.to_str() {
                Some(str) => process_file(str.to_string()),
                None => println!("What's this? {:?}", path.display())
            },
            Err(e) => println!("{:?}", e),
        }
    }
}