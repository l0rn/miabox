#!env python3
import argparse
import os
from shutil import copyfile
from pydub import AudioSegment

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

parser.add_argument(
    '-s',
    '--split',
    default=None,
    metavar='SPLIT',
    type=int,
    help='Number of seconds the tracks should be split into'
)



args = parser.parse_args()


def get_next_free_folder_number(folder):
    for i in range(1, 99):
        if '{:02}'.format(i) not in os.listdir(folder):
            print('{:02} still free, assigning'.format(i))
            return i


if __name__ == '__main__':
    for subdir, dirs, files in os.walk(args.audio_files):
        for audio_folder in dirs:
            audio_folder_path = os.path.join(args.audio_files, audio_folder)
            print('Walking through {}'.format(audio_folder))
            folder_name = '{:02}'.format(get_next_free_folder_number(args.sdcard))
            outdir = os.path.join(args.sdcard, folder_name)
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
                        if args.split is None:
                            copyfile(audio_track_path, os.path.join(outdir, '{:03}.mp3'.format(file_number)))
                            file_number += 1
                        else:
                            song = AudioSegment.from_mp3(audio_track_path)
                            step = args.split * 1000
                            for i in range(0, len(song), args.split * 1000):
                                outfile = os.path.join(outdir, '{:03}.mp3'.format(file_number))
                                with open(outfile, 'wb') as out:
                                    song[i:(i+step)].export(out)
                                    file_number += 1


