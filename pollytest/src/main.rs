// ------------------------------------------------------------------------------
// Copyright 2019 Uwe Arzt, mail@uwe-arzt.de
// SPDX-License-Identifier: Apache-2.0
// ------------------------------------------------------------------------------

use rusoto_core::Region;
use rusoto_polly::{Polly, PollyClient, SynthesizeSpeechInput};

use std::fs::File;
use std::io::Write;

fn main() {
    println!("-- starting tts --");

    let en_text = "Hello, my name is Mneme. How can i help you";
    let de_text = "Hallo, mein Name ist Mneme. Was kann ich für dich tun";
    let en_voice = "Joanna";
    let de_voice = "Vicki";

    let en_filename = "en_tts";
    let de_filename = "de_tts";

    create_files(en_text, en_voice, en_filename);
    create_files(de_text, de_voice, de_filename);
}

fn create_files(text: &str, voiceid: &str, filename: &str) {
    let client = PollyClient::new(Region::EuCentral1);

    let mut voice = SynthesizeSpeechInput::default();
    voice.text = text.to_string();
    voice.output_format = "ogg_vorbis".to_string();
    voice.voice_id = voiceid.to_string();

    let mut viseme = SynthesizeSpeechInput::default();
    viseme.text = text.to_string();
    viseme.output_format = "json".to_string();
    viseme.voice_id = voiceid.to_string();
    viseme.speech_mark_types = Some(vec![String::from("viseme")]);

    create_file(&client, voice, &format!("{}{}", filename, ".ogg"));
    create_file(&client, viseme, &format!("{}{}", filename, ".json"));
}

fn create_file(polly: &PollyClient, input: SynthesizeSpeechInput, filename: &str) {
    match polly.synthesize_speech(input).sync() {
        Ok(out) => match out.audio_stream {
            Some(stream) => {
                let mut buffer = File::create(filename).unwrap();
                match buffer.write(&stream) {
                    Ok(count) => println!("written bytes: {} to {}", count, filename),
                    Err(e) => println!("Err: {}", e),
                }
            }
            None => println!("No audio stream :("),
        },
        Err(e) => println!("Error: {}", e),
    }
}
