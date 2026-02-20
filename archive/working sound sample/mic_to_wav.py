import serial
import wave

ser = serial.Serial('COM12', 921600)   # adjust port

wav = wave.open("recording.wav", "wb")
wav.setnchannels(1)
wav.setsampwidth(2)   # 16-bit
wav.setframerate(16000)

try:
    while True:
        data = ser.read(512)
        wav.writeframes(data)
except KeyboardInterrupt:
    wav.close()
