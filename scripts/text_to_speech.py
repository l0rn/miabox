import base64
import requests

google_voice_locales = {
    'de': {'languageCode': 'de-DE', 'name': 'de-DE-Wavenet-C'},
    'en': {'languageCode': 'en-US', 'name': 'en-US-Wavenet-D'},
}


def google_voice(snippet, key):
    response = requests.post(
        'https://texttospeech.googleapis.com/v1beta1/text:synthesize?key={}'.format(key),
        json={
            'audioConfig': {
                'audioEncoding': 'MP3',
                'speakingRate': 1.0,
                'pitch': 0,  # Default is 0.0
                'sampleRateHertz': 44100,
                'effectsProfileId': ['small-bluetooth-speaker-class-device']
            },
            'voice': google_voice_locales['de'],
            'input': {'text': snippet}
        }
    )
    return base64.b64decode(response.json()['audioContent'])
