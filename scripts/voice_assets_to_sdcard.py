#!env python3
import argparse
import os
from text_to_speech import google_voice


def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)


parser = argparse.ArgumentParser(description='Create header files for audio assets')
parser.add_argument(
    'text_file',
    metavar='VOICE_SNIPPETS',
    type=argparse.FileType('r'),
    help='Path to text-to-speech files'
)

parser.add_argument(
    'sdcard',
    metavar='SDCARD',
    type=dir_path,
    help='Path to sdcard folder'
)

parser.add_argument(
    '-k',
    '--google-key',
    required=True,
    metavar='GOOGLE_KEY',
    type=str,
    help='Google key eligible for Cloud Speech-to-Text API'
)

args = parser.parse_args()

if __name__ == '__main__':
    mp3_dir = os.path.join(args.sdcard, 'mp3')
    os.makedirs(mp3_dir, exist_ok=True)
    for line in args.text_file:
        [voice_code, _, voice_snippet] = line.split('|')
        binary_audio = google_voice(voice_snippet, args.google_key)
        with open(os.path.join(mp3_dir, '{}.mp3'.format(voice_code)), 'wb') as outfile:
            outfile.write(binary_audio)
