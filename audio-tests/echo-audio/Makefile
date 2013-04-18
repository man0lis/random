all: echo-audio

echo-audio: echo-audio.c
	gcc -lSDL -lportaudio -lfftw3 -o echo-audio echo-audio.c

clean:
	rm echo-audio
