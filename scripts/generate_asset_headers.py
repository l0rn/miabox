#!env python3
import argparse
import os

base_path = os.path.join(os.path.dirname(__file__), '..')
header_file = os.path.join(base_path, 'src', 'assets', 'Assets.h')

parser = argparse.ArgumentParser(description='Create header files for audio assets')
parser.add_argument(
    'text_file',
    metavar='VOICE_SNIPPETS',
    type=argparse.FileType('r'),
    help='Path to text-to-speech files'
)
parser.add_argument(
    'header_file',
    metavar='HEADER_FILE',
    nargs='?',
    type=argparse.FileType('w'),
    help='Path to header file',
    default=header_file
)

args = parser.parse_args()

if __name__ == '__main__':
    for line in args.text_file:
        [voice_code, define_name] = line.split('|')[:2]
        args.header_file.write('#define {} {}\n'.format(define_name, voice_code.lstrip('0')))
