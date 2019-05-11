#!env python3
import argparse
import os
from shutil import copyfile, rmtree

from text_to_speech import google_voice


def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)


parser = argparse.ArgumentParser(description='Copy audio files in correct format and prepend introduction')

parser.add_argument(
    'audio_files',
    metavar='AUDIO_FOLDER',
    type=dir_path,
    help='Path to audio files folder'
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
    help='Google key eligible for Cloud Speech-to-Text for introduction text'
)

args = parser.parse_args()

if __name__ == '__main__':
    folder_number = 1
    for subdir, dirs, files in os.walk(args.audio_files):
        for audio_folder in dirs:
            audio_folder_path = os.path.join(args.audio_files, audio_folder)
            print('Walking through {}'.format(audio_folder))
            folder_name = '{:02}'.format(folder_number)
            outdir = os.path.join(args.sdcard, folder_name)
            rmtree(outdir)
            print('Will write audio to folder {}'.format(outdir))
            os.makedirs(outdir, exist_ok=True)
            introduction_file = google_voice(audio_folder, args.google_key)
            with open(os.path.join(outdir, '{:03}.mp3'.format(1)), 'wb') as outfile:
                outfile.write(introduction_file)
            file_number = 2
            for _, _, audio_tracks in os.walk(audio_folder_path):
                for audio_track in audio_tracks:
                    if audio_track.endswith('mp3'):
                        audio_track_path = os.path.join(audio_folder_path, audio_track)
                        copyfile(audio_track_path, os.path.join(outdir, '{:03}.mp3'.format(file_number)))
                        file_number += 1
            folder_number += 1

